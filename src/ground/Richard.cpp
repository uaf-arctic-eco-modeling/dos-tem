#include "Richard.h"


Richard::Richard(){
     ITMAX = 1;      //Yuan: no iteration, but only timestep shrinking???
     TSTEPMAX = 0.2;
     TSTEPORG = 0.1;
          
     ttole =1;  
};

Richard::~Richard(){
	
};


void Richard::updateSoilStructure(Layer* fstsoill){
	Layer* curr = fstsoill;
	int ind =0;
	while(curr!=NULL){
		
	  	ind++;
	  	poro[ind] = curr->poro;
	  	dzmm[ind] = curr->dz *1.e3;
		zmm[ind]  = curr->z *1.e3 +0.5 *dzmm[ind]; // the node depth
		minliq[ind] = curr->minliq;
		maxliq[ind] = curr->maxliq;
		if(curr->isSoil()){
			SoilLayer* sl =dynamic_cast<SoilLayer*>(curr);
			rootr[ind] = sl->rootfrac;
		}else{
			break;	
		}
		curr= curr->nextl;
	}
	
};

void Richard::update(Layer * frontl, Layer *backl, Layer *fstsoill, Layer* drainl,  double & drain,
 	       const double & trans, const double & evap,const double & infil, const double & zwt){
 	// prepare arrays for variables which will not change during one day
    // root fraction, temperature, ice
    // it is assumed that all layers in Richard will be unfrozen       	
	//get number of unfrozen layers
	Layer* currl= fstsoill;
	int ind = 0;
	numal = 0;
	double roottot =0.;
        while(currl!=NULL){
    	if(currl->isSoil()){
    		if(currl->frozen==-1){
    			ind++;
    			numal++;
    			roottot += rootr[ind];
    			currl->liq +=currl->ice;
    			currl->ice =0.;
    			if(currl->liq>currl->maxliq){
    				currl->liq=currl->maxliq;	
    			}
    			liq[ind] =currl->liq;
    			drainratio[ind] = 0.;
    			lstunfl = currl;
    		}else{
    			break;
    		}
    	}else{
    		break;	
    	}
    	currl = currl->nextl;	
    }
    
    if(lstunfl==NULL){
    	return;	
    }

    double maxrootfr =-1;
    maxrootfr =rootr[0];
    for(int il=0; il<numal;il++){
      if(roottot>0){	
    	  rootfr[il] = rootr[il]/roottot;
      }else{
    	  rootfr[il] =0.;
      }	
    }
    
    //Yuan: calculation
    iterate(fstsoill, trans, evap, infil);   
   
    //Yuan: post-iteration 
    currl = fstsoill;
    ind =0;
    while(currl!=NULL){
    	ind++;
    	if(ind >numal){ 
    		break;
    		liqld[ind] = currl->liq;
    	}
    	
    	currl->liq = liqld[ind];

    	if(currl->liq<0){ //currl->minliq){
    		string msg = "water is negative in richard";
//    		char* msgc = const_cast< char* > ( msg.c_str());
//    		throw Exception(msgc, I_NEG_WATER);
    		cout<<msg<<"\n";  //Yuan: don't break the model
    		currl->liq=currl->minliq;   //Yuan: set to the min. value
    	}
    	
    	if(currl->liq>currl->maxliq){
    		currl->liq=currl->maxliq;
    	}
    	currl->wat =currl->liq;
    	
        // Yuan: for output of hydraulic conductivity
    	SoilLayer* cursl=dynamic_cast<SoilLayer*>(currl);
    	double ss = cursl->getEffVolWater()/cursl->poro;
 		double hcond = cursl->hksat * pow((double)ss, (double)2*cursl->bsw +2); //Yuan:
  		currl->hcond = hcond*86400.; //unit: mm/day (hksat: mm/sec)

     	currl=currl->nextl;
//    	if(currl!=NULL){
//   		if(currl->indl>lstunfl->indl) break;   //Yuan: need to refresh the soil profile water status for all layers
//   	}
    };
   	
};


void Richard::iterate(Layer *fstsoill,const double & trans, const double & evap,
		                             const double & infil){
  	
	tschanged = true;
	tmld  = 0;    // tmld is time that is last determined	
	itsum = 0;
	tleft = 1;  // at beginning of update, tleft is one day
	if(infil>0){
		TSTEPORG =TSTEPMAX/5.;	
	}else{
		TSTEPORG =TSTEPMAX;
	}
	tstep = TSTEPORG;
	
	for(int il =1; il<=numal; il++){
		liqid[il] = liq[il]; // liq at the begin of one day	
		liqld[il] = liq[il]; // the last determined liq
	}

	while(tmld<1){
		//cout <<"TMLD " << tmld << " time step " << tstep << "\n";
		for(int i=1; i<=numal; i++){
	 		liqis[i] = liqld[i];	
		}
		
		//find one solution for one timestep
		int st = updateOneTimeStep(fstsoill, trans, evap, infil);
		if(st==-1) {				
			tstep = tstep/2;   // half the time step
			if(tstep < 1.e-6){
//				string msg = "tstep is too small in richard2 ";
//				char* msgc = const_cast< char* > ( msg.c_str());
//				throw Exception(msgc, I_WAT_TSTEP_SMALL);   //Yuan: this will break the model
//				cout<<msg<<"\n";
				return;
			}
			tschanged = true;
		
		} else if(st==0){   //advance to next timestep
			
			tleft -= tstep;
			tmld += tstep;
		 
			// find the proper timestep for rest period		 
			if(!tschanged){ // if timestep has not been changed during last time step 
				if(tstep<TSTEPMAX){
					tstep = TSTEPORG;  //*=2;   //Yuan:
					tschanged = true;
				}		    
			}else{
				tschanged =false;	
			}
			
			// make sure tleft is greater than zero
			tstep = min(tleft, tstep);	
			if(tstep==0) tmld=1;
		}
	} // end of while
  	
};
    
int Richard::updateOneTimeStep(Layer *fstsoill,const double & trans, const double & evap,
		                                       const double & infil){
	int status =-1;
	int is;
	
	for(int i=1; i<=numal; i++){
	 	liqii[i] = liqis[i];	
	}
		 
    for (int i=0; i<ITMAX; i++){
    	
    	is = updateOneIteration(fstsoill, trans, evap, infil);
    	
    	if(is==0){// success
    		status = is;
    		for(int i=1; i<=numal; i++){
    			liqld[i] = liqit[i];	
    			if(liqld[i]>maxliq[i]){
    				liqld[i]=maxliq[i];	
    			}
                        if(liqld[i]<minliq[i]){
                                liqld[i]=minliq[i];
                        }
    		}
    		
    	} else {	  	
    		for(int i=1; i<=numal; i++){
    		//	if(liqld[i]<0){  		   
    		//		string msg = "liqit is less than zero ";
    		//		char* msgc = const_cast< char* > ( msg.c_str());
    		//		throw Exception(msgc, I_NEG_WATER);
    		//	}
    			liqii[i] = liqld[i];
    		}
    		status = is;
    	}
	  		  	
    }
	
    return status;
	  
}; 
  
int Richard::updateOneIteration(Layer *fstsoill, const double & trans, const double & evap,
		                                         const double & infil){
	Layer *curr =fstsoill;
	
	double poro1, effporo1, volliq1,s1;
	double poro2, effporo2, volliq2,s2;
	double hksat, bsw,s_node,psisat;
    double wimp = 0.001;// mimumum pore for water to exchange between two layers
    double smpmin = -1.e8;
    double dt =tstep*86400;
	
    SoilLayer* nexts, *thsl;
	int ind=0;
	itsum++;
	for(int il =0; il<MAX_SOI_LAY; il++){
		dwat[il]=0.;	
	}
    
	//Yuan: k-dk/dw-h relationships for all soil layers
	while(curr!=NULL) {
		ind++;
		thsl  = dynamic_cast<SoilLayer*>(curr);
		nexts = dynamic_cast<SoilLayer*>(curr->nextl);
			
		poro1 = poro[ind];
		effporo1 = poro1;
		volliq1 = liqii[ind]/dzmm[ind];
		hksat = thsl->hksat;
		bsw   = thsl->bsw;
			
		if(curr==lstunfl){  //the last unfrozen layer
			hk[ind] = 0.;
			dhkdw[ind] =0.;
		} else {			
			poro2 = poro[ind+1];			
			effporo2 = poro2;			
			volliq2 = liqii[ind+1]/dzmm[ind+1]; //nexts->getVolLiq();	
			
			if(effporo1<wimp || effporo2<wimp ||volliq2<0.001){
				hk[ind] = 0.;
				dhkdw[ind] =0.;	
			} else {
				s1 =(volliq2+volliq1)/(poro2+poro1);
				s2 = nexts->hksat * exp (-2*(nexts->z + nexts->dz/2))* pow((double)s1, (double)2*nexts->bsw +2);//nexts->getHydraulicCond(); 

				hk[ind] = s1*s2;
				dhkdw[ind] = (2.*bsw+3)*s2*0.5/poro2;

			}			
		}
			
		psisat = thsl->psisat;
		s_node = volliq1/poro1;
		s_node = max(0.01, (double)s_node);
		s_node = min(1., (double)s_node);
		smp[ind] = psisat *pow(s_node, -bsw); //psi = psisat * pow(ws, -bsw*1.0);				
		smp[ind] = max(smpmin, smp[ind]);
		
		/*	if(curr->indl==lstunfl->indl){//the last layer
					if(liqii[ind]/dzmm[ind]>poro[ind]-0.001 ){//almost saturated
						double den1 = zmm[ind]-zmm[ind-1];
		                double num1 = smp[ind]-smp[ind-1] -den1;
						if(num1<0){
						 smp[ind]=smp[ind-1]+den1;	
						} 
					}
		}*/
		
		dsmpdw[ind]= -bsw * smp[ind] /(s_node*poro1);
			
		curr= dynamic_cast<SoilLayer*>(curr->nextl);
		if(curr!=NULL){
			if(curr->indl>lstunfl->indl) break;
		}
		
    }
	
	//Yuan: 
	double den1, num1;
	for(int il=numal ; il>=2; il--){
		if(liqii[il]/dzmm[il]>poro[il]-0.01){
			den1 = zmm[il] - zmm[il-1];
		    num1 = smp[il] - smp[il-1] - den1;    //hydraulic potential difference
		   		       
		   if(num1<0) {
		   	    smp[il] = smp[il-1]+den1;    
		   		hk[il-1]= 0.;              //Yuan: so will be no upward water moving
		   }	  
		}      
	}	

	// for first layer
	ind =1;   
	double qtrans = trans;
	double den, num;
	double dqodw1, dqodw2, dqidw0, dqidw1;	
	double sdamp =0.;
	
	qin[ind] = infil -evap;
	den = zmm[ind+1]-zmm[ind];
	num = smp[ind+1]-smp[ind] -den;
	qout[ind] = -hk[ind] * num/den;
	dqodw1 = -(-hk[ind]*dsmpdw[ind] + num* dhkdw[ind])/den;
	dqodw2 = -(hk[ind]*dsmpdw[ind+1] + num* dhkdw[ind])/den;
		
	rmx[ind] = qin[ind] - qout[ind] - qtrans*rootfr[ind];	
	amx[ind] = 0.;
	bmx[ind] = dzmm[ind] *(sdamp +1/dt) + dqodw1;
	cmx[ind] = dqodw2;
		
	// layer 2 ~ last bottom layer
	for(ind =2; ind<=numal-1;ind++){
		den = zmm[ind]-zmm[ind-1];
		num = smp[ind]-smp[ind-1] -den;
		qin[ind] = -hk[ind-1]*num/den;
		dqidw0 = -(-hk[ind-1]*dsmpdw[ind-1] + num* dhkdw[ind-1])/den;
		dqidw1 = -(hk[ind-1]*dsmpdw[ind] + num* dhkdw[ind-1])/den;
		
		den = zmm[ind+1]-zmm[ind];
		num = smp[ind+1]-smp[ind] -den;
		qout[ind] = -hk[ind] * num/den;
		dqodw1 = -(-hk[ind]*dsmpdw[ind] + num* dhkdw[ind])/den;
		dqodw2 = -(hk[ind]*dsmpdw[ind+1] + num* dhkdw[ind])/den;
			
		rmx[ind] = qin[ind] -qout[ind] -qtrans*rootfr[ind];	
		amx[ind] =-dqidw0;
		bmx[ind] = dzmm[ind] /dt - dqidw1 + dqodw1;
		cmx[ind] = dqodw2;
			
	};

	//bottom layer
	if(numal>=2){
		ind = numal;
		den = zmm[ind]-zmm[ind-1];
		num = smp[ind]-smp[ind-1] -den;
		qin[ind] = -hk[ind-1]*num/den;
	
		dqidw0 = -(-hk[ind-1]*dsmpdw[ind-1] + num* dhkdw[ind-1])/den;
		dqidw1 = -(hk[ind-1]*dsmpdw[ind] + num* dhkdw[ind-1])/den;
		qout[ind] = hk[ind];
		
		
		dqodw1 = dhkdw[ind];
		rmx[ind] = qin[ind] -qout[ind] -qtrans * rootfr[ind];
		amx[ind] = -dqidw0;
		bmx[ind] = dzmm[ind]/dt - dqidw1 + dqodw1;
		cmx[ind] = 0.;
	}
		
	ind =1;
	cn.tridiagonal(ind, numal, amx, bmx,cmx,rmx, dwat);  //solution
	
	// soil water for each layer after one iteration
    for(int il =1; il<=numal; il++){
    	liqit[il] = liqii[il] + dzmm[il] * dwat[il];
    	if(isnan(liqit[il])){
    		string msg = "water is nan in richard";
 //   		char* msgc = const_cast< char* > ( msg.c_str());
    		//throw Exception(msgc, I_NAN_WATER);

    		break;   //Yuan:
    	}
    }	
        
    //check the change of liquid water
    
    if (liqit[0] <0) liqit[0]=0.01;
    if (liqit[1] <0) liqit[1]=0.01;
    for(int il =2; il<=numal; il++){
    	if(ed->m_sois.type[il]>=1){//moss 0; shlw 1; deep 2; mine 3
    		if(liqit[il]<0 ){
    			liqit[il]=0.01;  //Yuan:  bug here??
    			return -1;           //yuan:  should adjust Evaportation here, BUT ...
    		}else if(liqit[il]>maxliq[il]*1.1){  //if more than 10% of maxliq
    			return -1;  	 	
    		}else if(fabs((liqit[il]-liqii[il])/maxliq[il])>0.50){ //if change more than 50% of maxliq
    			return -1;	
    		}
    	}
   }
     
   return 0;
	
};

void Richard::setEnvData(EnvData* edp){
	ed = edp;
	
};



