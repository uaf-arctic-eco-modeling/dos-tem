#include "Soil_Bgc.h"

Soil_Bgc::Soil_Bgc(){
 	nitroadd =0.;
};

Soil_Bgc::~Soil_Bgc(){
	
};

double Soil_Bgc::getMossThickness(){// in meter
	double ysf =fd->ysf;
	double maxmoss = bgcpar.maxmossthick;
	return maxmoss*( (ysf*1.0)/(ysf+5.));
};

void Soil_Bgc::updateDeepThickness(Layer* fstdeepl, Layer* lstdeepl){

	if(fstdeepl==NULL || lstdeepl==NULL){
 	  return;
 	}

 	SoilLayer* sl;
 	PeatLayer* pl;
	double tempdz =0;
 	double dbmtop =0;
 	double dbmbot;
 	double cumcarbonbot;
 	double cumcarbontop =0;
 	double totdeep=0;

 	Layer* currl=fstdeepl;
 	while(currl!=NULL){
 	  	if(currl->isSoil()){
 	  		sl=dynamic_cast<SoilLayer*>(currl);
 			if(sl->isPeat()){
 				 pl=dynamic_cast<PeatLayer*>(sl);
 				 if(pl->isHumic){ 
 			 		cumcarbonbot = cumcarbontop + sl->reac + sl->nonc;
 			 		dbmbot = pow( (cumcarbonbot/10000.)/bgcpar.deepa, 1./bgcpar.deepb)/100.;
 			 		tempdz = dbmbot - dbmtop;
 			 		dbmtop = dbmbot;
 				    	cumcarbontop = cumcarbonbot;
 			 		sl->dz = tempdz;
 			 		totdeep += tempdz;
 					sl->updateProperty4LayerChange();
 				 }
 			}else{
 			  	 break;	
 			}
 	  		
 	  	}
 		currl =currl->nextl;
 	}

};
 
void Soil_Bgc::updateShallowThickness(Layer* fstshlwl, Layer* lstshlwl){
 	
 	SoilLayer* sl;
 	PeatLayer* pl;

 	if(fstshlwl==NULL || lstshlwl==NULL){
 	  return;	
 	}
 	
 	double tempdz =0;
 	double dbmtop =0;
 	double dbmbot;
 	double cumcarbonbot;
 	double cumcarbontop =0;
 	double totshlw=0;

 	Layer* currl =fstshlwl;
 	while(currl!=NULL){
 	  	if(currl->isSoil()){
 	  		sl=dynamic_cast<SoilLayer*>(currl);
 			if(sl->isPeat()){
 				 pl=dynamic_cast<PeatLayer*>(sl);
 				 if(pl->isFibric){ //only update shallow organic layer
 				 	
  			 		cumcarbonbot = cumcarbontop + sl->reac + sl->nonc;
 			 		dbmbot = pow( (cumcarbonbot/10000.)/bgcpar.shlwa, 1./bgcpar.shlwb)/100.;
 			 		tempdz = dbmbot - dbmtop; 		
 				    	dbmtop = dbmbot;
 				    	cumcarbontop = cumcarbonbot;
 			 		sl->dz = tempdz;
 			 		totshlw += tempdz;
 					sl->updateProperty4LayerChange();
				}
 	  		}
 	  	}
 		currl =currl->nextl;
 	}
    
 //must have a fibric soil layer for above-ground litterfall
 	// if there is only one shallow layer and after calculation, the thickness of this layer is less than 2 cm.
 	// the thickness of this layer will not be updated
   if(totshlw<0.02){
       fstshlwl->dz = 0.02;	
       sl=dynamic_cast<SoilLayer*>(fstshlwl);

       sl->updateProperty4LayerChange();     
    }
 			 		
};
 
void Soil_Bgc::assignCarbon5Struct2Layer(Layer* fstsoill){
 	Layer* currl = fstsoill;
 	SoilLayer* sl ;
 	while(currl!=NULL){
 		if(currl->isSoil()){
 			sl=dynamic_cast<SoilLayer*>(currl);
 			
 			sl->reac=	bd->m_sois.reac[sl->solind-1];
	        sl->nonc=	bd->m_sois.nonc[sl->solind-1];
 		}else{
			break;	
 		}
 			 
 		currl = currl->nextl;		
 	}
 	
};
 
void Soil_Bgc::assignCarbon5Layer2Struct(Layer* fstsoill, const double & wdebris){
 	Layer* currl = fstsoill;
 	SoilLayer* sl ;
    PeatLayer* pl;
 	int lstprocessedlayer = 0;
 	double totinputnonc = wdebris;
 	while(currl!=NULL){
 		if(currl->isSoil()){
 			sl=dynamic_cast<SoilLayer*>(currl);
 			if(sl->isMoss()){
 				bd->m_sois.reac[sl->solind-1]= 0;
 				bd->m_sois.nonc[sl->solind-1]= 0;
 			}else{
 				lstprocessedlayer = sl->solind-1;
 				if(totinputnonc>0){
 			  		if(sl->isPeat()){
 			  			pl =dynamic_cast<PeatLayer*>(currl);
 			  			if(pl->isHumic){
 			      			sl->nonc+= totinputnonc;
 			      			totinputnonc =0.;	
 			  			}
 			  		}
 				}
 				
 				bd->m_sois.reac[sl->solind-1]= sl->reac;
 				bd->m_sois.nonc[sl->solind-1]= sl->nonc;
 			}
 		}else{
 			break;	
 		}
			
 	 	currl = currl->nextl;		
 	}
 	
 	for(int il = lstprocessedlayer+1; il<MAX_SOI_LAY;il++){
 		bd->m_sois.reac[il]=0.;
 		bd->m_sois.nonc[il]=0.;
 	}
 	
 };
 
 void Soil_Bgc::updateShallowCarbonAfterLayerDivide(Layer* fstshlwl, Layer* lstshlwl){
	double cumcarbon =0.;
	double prevcumcarbon=0.;
	double dbm =0.;
	double prevdbm=0.;
	double r2tot=0.;
	
//	if(fstshlwl->indl == lstshlwl->indl  && fstshlwl->dz==0.02){
//	 	return;
//	}
	
	Layer* currl = fstshlwl;
	PeatLayer* pl =NULL;
	SoilLayer* sl = NULL;
	while(currl!=NULL){
		if(currl->isSoil()){
		  	sl=dynamic_cast<SoilLayer*>(currl);
		  	if(sl->isPeat()){
			 	pl=dynamic_cast<PeatLayer*>(currl);
			 	if(pl->isFibric){
			     	dbm = prevdbm+ pl->dz;
			     	cumcarbon = bgcpar.shlwa * pow( dbm*100., bgcpar.shlwb*1.) *10000; 
			     
			     	if(pl->reac+ pl->nonc>0){
			     		r2tot = pl->reac/ (pl->reac+pl->nonc);
			     		pl->reac = (cumcarbon-prevcumcarbon) * r2tot;
			     		pl->nonc = (cumcarbon-prevcumcarbon) * (1-r2tot);
			     	}
			     	
			     	prevcumcarbon = cumcarbon;
			     	prevdbm= dbm;
			 	
			 	} else {
			 		break;	
			 	}
		  
		  	}else{
		  		break;
		  	}
		  
		}else{
		 	break;	
		}
		
		currl = currl->nextl;	
	}
	
};


void Soil_Bgc::updateDeepCarbonAfterLayerDivide(Layer* fstdeepl){
	double cumcarbon =0.;
	double prevcumcarbon=0.;
	double ham =0.;
	double prevham=0.;
	double r2tot=0.;
	
	Layer* currl  = fstdeepl;
	PeatLayer* pl = NULL;
	SoilLayer* sl = NULL;
	
	while(currl!=NULL){
		 if(currl->isSoil()){
		  	sl=dynamic_cast<SoilLayer*>(currl);
		  	if(sl->isPeat()){
			 	pl=dynamic_cast<PeatLayer*>(currl);
			 	if(pl->isHumic){
			     	ham = prevham+ pl->dz;
			      	cumcarbon = bgcpar.deepa * pow( ham*100., bgcpar.deepb*1.) *10000;
			     	if(pl->reac+ pl->nonc>0){
			     		r2tot = pl->reac/ (pl->reac+pl->nonc);
			     		pl->reac = (cumcarbon-prevcumcarbon) * r2tot;
			     		pl->nonc = (cumcarbon-prevcumcarbon) * (1-r2tot);
			     	}
			     	prevcumcarbon = cumcarbon;
			     	prevham= ham;
			 	}else{
			 		break;	
			 	}
		  	}
		  	
		 }else{
		 	break;	
		 }
		 
		 currl = currl->nextl;	
	}

};

void Soil_Bgc::prepareIntegration(){
	 nfeed   = bd->nfeed;
	 avlnflg = bd->avlnflg;
 	 numsl   = ed->m_soid.actual_num_soil;
     blwfrac = bgcpar.blwltrr2t;
     abvfrac = bgcpar.abvltrr2t;
     
     for(int i=0;i<numsl; i++){
       abvlfcfrac[i]=0;
     }

     //put all above-ground literfall into the first soil layer
     for(int i=0;i<numsl; i++){
        if(ed->m_sois.type[i]==1){// moss is zero, fibric organic is 1, humic is 2, mineral is 3
       		abvlfcfrac[i]=1.0;
       		break;
        }
     }

     //for below-ground literfall distribution
     for(int i=0;i<numsl; i++){
           	blwlfcfrac[i] = ed->m_sois.rootfrac[i];	
//		if (i <= 4) cout<<"ed->m_sois.rootfrac[i]: "<<ed->m_sois.rootfrac[i]<<"\n";
     }
     
     //prepare totsolliq in root zone
     totsolliq =0;
     double templiq =0;
     for(int i=0;i<numsl; i++){
     	if(ed->m_sois.rootfrac[i]>0.01){
     		templiq =  ed->m_sois.liq[i];
     		if(templiq<0) templiq=0;
        	totsolliq += templiq;	
     	}
     }
     if(totsolliq<0.001) totsolliq =0;
     
     meanksoil =0.;
  	 for(int il =0; il<numsl; il++){
     	if(ed->m_sois.rootfrac[il]>0){
  	 		bd->m_soid.ksoil[il] = getKSoil( ed->m_soid.allvwc[il]);
  	 		meanksoil += bd->m_soid.ksoil[il] * ed->m_sois.rootfrac[il];
     	}
     } 
  
  	 if(fd->ysf < fd->gd->fri){
  		bd->m_sois.orgn += fd->y_a2soi.orgn/12.;
  	 }
  	 
  	 if(fd->ysf<9){
  		if(bd->m_vegs.deadc>0){
  			bd->m_sois.wdebris += bd->m_vegs.deadc/9./12.;
//  			bd->m_vegs.standingc = bd->m_vegs.deadc-bd->m_sois.wdebris;	
  		}  	
  	 }else{
//  		bd->m_vegs.standingc =0.;
  		bd->m_vegs.deadc =0.;
  		bd->m_vegs.deadn=0.;
  	 }

};

void Soil_Bgc::afterIntegration(){
 //update the diagnostic variables
 	 numsl = ed->m_soid.actual_num_soil;
	 for(int i=0;i<numsl; i++){
	 	bd->m_soid.totc[i] = bd->m_sois.reac[i] +  bd->m_sois.nonc[i];
     }
      
};

void Soil_Bgc::initializeState(Layer* fstshlwl, Layer* fstminl,  const int & drgtypep,const int & vegtypep){
 
  int drgtype = drgtypep;	
  int vegtype = vegtypep;
          
  //set initiate state variable
//   initSoilCarbon(fstshlwl, fstminl);  //Yuan: modified as following
   double soilc = chtlu->initsolc[drgtype][vegtype];
   initSoilCarbon(fstshlwl, fstminl, soilc);

   bd->m_sois.avln=chtlu->initavln[drgtype][vegtype];
   bd->m_sois.orgn=chtlu->initsoln[drgtype][vegtype];
   bd->m_sois.wdebris = 0;
   bd->kdfib = calpar.kdcfib;	
   bd->kdhum = calpar.kdchum;	
   bd->kdmin = calpar.kdcmin;
   bd->kdslow = calpar.kdcslow;

  
   shlw2cmcarbon = bgcpar.shlwa * pow(2., bgcpar.shlwb*1.) *10000;
   deep2cmcarbon = bgcpar.deepa * pow( 2., bgcpar.deepb*1.) *10000;

};

//Yuan: modification to avoid reading netcdf file here
void Soil_Bgc::initializeState5restart(Layer* fstsoill, RestartData* resin){

    double NONC[MAX_SOI_LAY];
    for(int i=0; i<MAX_SOI_LAY; i++){
    	NONC[i] = resin->NONCsoil[i]; //resin->getNONC(NONC, ed->cd->reschtid);
    }
	
	double REAC[MAX_SOI_LAY];
    for(int i=0; i<MAX_SOI_LAY; i++){
    	REAC[i] = resin->REACsoil[i]; //resin->getREAC(REAC, ed->cd->reschtid);
    }
	
	Layer* currl = fstsoill;
	SoilLayer* sl;
	int slind =-1;
	while(currl!=NULL){
		if(currl->isSoil()){
		  slind ++;
		  sl = dynamic_cast<SoilLayer*>(currl);
		
		  sl->nonc= NONC[slind];
		  sl->reac= REAC[slind];	  
			
		}else{
		  break;
		}
		
		currl = currl->nextl;
	};
	
	bd->m_sois.orgn=resin->soln; //resin->getSOLN(bd->m_sois.orgn, ed->cd->reschtid);
	bd->m_sois.avln=resin->avln; //resin->getAVLN(bd->m_sois.avln, ed->cd->reschtid);
	bd->m_sois.wdebris=resin->wdebris; //resin->getWDEBRIS(bd->m_sois.wdebris, ed->cd->reschtid);


//	bd->kdfib=calpar.kdcfib; //resin->getKDFIB(bd->kdfib, ed->cd->reschtid);
//	bd->kdhum=calpar.kdchum;  //resin->getKDHUM(bd->kdhum, ed->cd->reschtid);
//	bd->kdmin=calpar.kdcmin;  //resin->getkdmin(bd->kdmin, ed->cd->reschtid);
//	bd->kdslow=calpar.kdcslow;  //resin->getkdlitter(bd->kdlitter, ed->cd->reschtid);


	bd->kdfib=resin->kdfib; //resin->getKDFIB(bd->kdfib, ed->cd->reschtid);
	bd->kdhum=resin->kdhum;  //resin->getKDHUM(bd->kdhum, ed->cd->reschtid);
	bd->kdmin=resin->kdmin;  //resin->getkdmin(bd->kdmin, ed->cd->reschtid);
	bd->kdslow=resin->kdslow;  //resin->getkdlitter(bd->kdlitter, ed->cd->reschtid);
 
    assignCarbon5Layer2Struct( fstsoill,  0);
   	
    shlw2cmcarbon =  bgcpar.shlwa * pow(2., bgcpar.shlwb*1.) *10000;
    deep2cmcarbon =bgcpar.deepa * pow( 2., bgcpar.deepb*1.) *10000;
};

void Soil_Bgc::initializeParameter(const int & drgtypep,const int & vegtypep){
 	int drgtype  = drgtypep;	
 	int  vegtype = vegtypep;	
    
    	bgcpar.rootza = chtlu->rootza[vegtype];
	bgcpar.rootzb = chtlu->rootzb[vegtype];
	bgcpar.rootzc = chtlu->rootzc[vegtype];
	bgcpar.minrootz = chtlu->minrootz[vegtype];

	bgcpar.rhq10    = chtlu->rhq10[vegtype];   
  	bgcpar.moistmin = chtlu->moistmin[vegtype];
  	bgcpar.moistmax = chtlu->moistmax[vegtype];
  	bgcpar.moistopt = chtlu->moistopt[vegtype];
  
  	bgcpar.abvltrr2t = chtlu->abvltrr2t[vegtype];
  	bgcpar.blwltrr2t = chtlu->blwltrr2t[vegtype];
  
   	bgcpar.kn2 = chtlu->kn2[vegtype];
  
    	bgcpar.shlwa =chtlu->coefshlwa[drgtype][vegtype];
    	bgcpar.shlwb =chtlu->coefshlwb[drgtype][vegtype];
  	
    	bgcpar.deepa =chtlu->coefdeepa[drgtype][vegtype];
    	bgcpar.deepb =chtlu->coefdeepb[drgtype][vegtype];
  
    	bgcpar.minea =chtlu->coefminea[drgtype][vegtype];
    	bgcpar.mineb =chtlu->coefmineb[drgtype][vegtype];

    	bgcpar.fsoma =chtlu->fsoma[drgtype][vegtype];
    	bgcpar.fsompr=chtlu->fsompr[drgtype][vegtype];
    	bgcpar.fsomcr=chtlu->fsomcr[drgtype][vegtype];
    	bgcpar.som2co2=chtlu->som2co2[drgtype][vegtype];
 
    	bgcpar.maxmossthick = chtlu->maxmossthick[vegtype];
    	bgcpar.propftos     = chtlu->propftos[vegtype];
  	bgcpar.nloss        = chtlu->nloss[vegtype];
  
  	calpar.nup    = chtlu->nup[drgtype][vegtype];
  	calpar.kdcfib = chtlu->kdcfib[drgtype][vegtype];
  	calpar.kdchum = chtlu->kdchum[drgtype][vegtype];
  	calpar.kdcmin = chtlu->kdcmin[drgtype][vegtype];
  	calpar.kdcslow = chtlu->kdcslow[drgtype][vegtype];
  
    	bgcpar.lcclnc   = chtlu->lcclnc[vegtype]; 
  	bgcpar.abvltrr2t= chtlu->abvltrr2t[vegtype];
  	bgcpar.blwltrr2t= chtlu->blwltrr2t[vegtype];
  	bgcpar.cnsoil   = chtlu->cnsoil[vegtype];

    decay = 0.26299 + (1.14757*bgcpar.propftos)
                    - (0.42956*pow( (double) bgcpar.propftos,2.0 ));

};

void Soil_Bgc::initSoilCarbon(Layer* fstshlwl, Layer* fstminl, double & initsoilc){
	//based on soil carbon and ham

	double allreac = 0.;
	double allnonc = 0.;
 
	for(int il =0; il <MAX_SOI_LAY ; il++){
 	   bd->m_sois.reac[il] =0;
 	   bd->m_sois.nonc[il] =0;
 	}
	
	//Init from total soil carbon vs thickness  (depth below moss
	//use the ltdfmh relationship
//	cout<<"allreac = "<<allreac<<"\n";
//	cout<<"allnonc = "<<allnonc<<"\n";

	initShlwCarbon(fstshlwl, allreac, allnonc);
	initDeepCarbon(fstshlwl, allreac, allnonc);

//	cout<<"allreac = "<<allreac<<"\n";
//	cout<<"allnonc = "<<allnonc<<"\n";

//	initMineralCarbon(fstminl, allreac, allnonc);
	double minec = initsoilc - (allreac + allnonc); //Yuan: the mineral-layer somc is the total minus those in peat layers
//	cout<<"minec = "<<minec<<"\n";
	if (minec<0.10) minec = 0.10;
	initMineralCarbon(fstminl, minec, allreac, allnonc);   //Yuan: minec as an input, otherwise, all sites are same

//	cout<<"initsoilc = "<<initsoilc<<"\n";
//	cout<<"allreac = "<<allreac<<"\n";
//	cout<<"allnonc = "<<allnonc<<"\n";
//	cout<<"minec = "<<minec<<"\n";

};

void Soil_Bgc::initShlwCarbon(Layer* fstshlwl, double & allreac, double & allnonc){
	double dbmtop =0;
	double dbmbot =0;
	double cumcarbontop =0;
	double cumcarbonbot;
	SoilLayer* sl;
	PeatLayer* pl;
	Layer* currl = fstshlwl;
	int currind;
	
	while(currl!=NULL){
 	  	if(currl->isSoil()){
 	  		sl=dynamic_cast<SoilLayer*>(currl);
 			if(sl->isPeat()){
 				pl=dynamic_cast<PeatLayer*>(currl);
 				currind = sl->solind-1;
 				dbmbot = dbmtop+  ed->m_sois.dz[currind];
 				if(pl->isFibric){
 				 	cumcarbonbot = bgcpar.shlwa * pow( dbmbot*100. , bgcpar.shlwb*1.) * 10000; //from gC/cm2 to gC/m2	
// 	cout<<"cumcarbonbot = "<<cumcarbonbot<<"\n";
// 	cout<<"bgcpar.shlwa = "<<bgcpar.shlwa<<"\n";
// 	cout<<"dbmbot = "<<dbmbot<<"\n";
// 	cout<<"bgcpar.shlwb = "<<bgcpar.shlwb<<"\n";
//	cout<<"cumcarbontop = "<<cumcarbontop<<"\n";
				 	
 				 	//Yuan: note the changes of initial .reac and .nonc fractions
 				 	if(cumcarbonbot-cumcarbontop>1){
 				 		bd->m_sois.reac[currind] = 10./11. * (cumcarbonbot-cumcarbontop);
 				 		bd->m_sois.nonc[currind] = 1./11. * (cumcarbonbot-cumcarbontop);
//	cout<<"shlw bd->m_sois.reac = "<<bd->m_sois.reac[currind]<<"\n";
//	cout<<"shlw bd->m_sois.nonc = "<<bd->m_sois.nonc[currind]<<"\n";
  				 		sl->reac = bd->m_sois.reac[currind];
 				 		sl->nonc = bd->m_sois.nonc[currind];
 				 		allreac +=sl->reac;
 				 		allnonc +=sl->nonc;
//	cout<<"allreac = "<<allreac<<"\n";
// 	cout<<"allnonc = "<<allnonc<<"\n";
 					}else{
 				 	  	break;	
 				 	}
 				 	
 				}else{ 
 					break;	
 				}
 				cumcarbontop = cumcarbonbot;
 				dbmtop = dbmbot;
 			}else{
 				break;
 			}
 	  		
 	  	}else{
 	  	  	break;	
 	  	}
 		currl =currl->nextl;
 	}
};

void Soil_Bgc::initDeepCarbon(Layer* fstshlwl, double & allreac, double & allnonc){
	double dbmtop =0;
	double dbmbot =0;
	double cumcarbontop =0;
	double cumcarbonbot;
	SoilLayer* sl;
	PeatLayer* pl;
	Layer* currl = fstshlwl;
	int currind;
	
	while(currl!=NULL){
 	  	if(currl->isSoil()){
 	  		sl=dynamic_cast<SoilLayer*>(currl);
 			if(sl->isPeat()){
 				pl=dynamic_cast<PeatLayer*>(currl);
 				if(pl->isHumic){
 				 	currind = sl->solind-1;
 				 	dbmbot  = dbmtop + ed->m_sois.dz[currind];
 				 	cumcarbonbot = bgcpar.deepa * pow( dbmbot*100. , bgcpar.deepb*1.) * 10000; //from gC/cm2 to gC/m2

//	cout<<"deep cumcarbonbot = "<<cumcarbonbot<<"\n";
// 	cout<<"bgcpar.deepa = "<<bgcpar.deepa<<"\n";
// 	cout<<"dbmbot = "<<dbmbot<<"\n";
// 	cout<<"bgcpar.deepb = "<<bgcpar.deepb<<"\n";
// 	cout<<"deep cumcarbontop = "<<cumcarbontop<<"\n";

 				 	//Yuan: note the changes of initial .reac and .nonc fractions
 				 	if(cumcarbonbot-cumcarbontop>1){
 				 		bd->m_sois.reac[currind] = 1./11. * (cumcarbonbot-cumcarbontop);
 				 		bd->m_sois.nonc[currind] = 10./11. * (cumcarbonbot-cumcarbontop);
//	cout<<"deep bd->m_sois.reac = "<<bd->m_sois.reac[currind]<<"\n";
// 	cout<<"deep bd->m_sois.nonc = "<<bd->m_sois.nonc[currind]<<"\n";
 				 		sl->reac = bd->m_sois.reac[currind];
 				 		sl->nonc = bd->m_sois.nonc[currind];
 				 		allreac +=sl->reac;
 				 		allnonc +=sl->nonc;
//	cout<<"allreac = "<<allreac<<"\n";
//	cout<<"allnonc = "<<allnonc<<"\n";
 					}
 				 	
 				 	cumcarbontop = cumcarbonbot;
 				 	dbmtop = dbmbot;
 				}
 				 	
 			}else{
 				break;
 			}
 	  		
 	  	}else{
 	  	  break;	
 	  	}
 		currl =currl->nextl;
 	}

};
		
void Soil_Bgc::initMineralCarbon(Layer* fstminl, double & minec, double & allreac, double & allnonc){
 	double dbm=0.;
 	double prevcumcarbon =0.;
 	double  cumcarbon =0.;
 	Layer* currl = fstminl;
 	int currind;
 	SoilLayer* sl;
 	double ca=  bgcpar.minea;
 	double cb=  bgcpar.mineb;
	
	while(currl!=NULL){
 	  	if(currl->isSoil()){
 			currind =currl->solind-1;
// 		 	if(dbm>1) break;

 			//Yuan: note the changes of initial .reac and .nonc fractions
 			dbm += ed->m_sois.dz[currind];	
//			cumcarbon = ca/cb*(exp(cb*dbm*100) -1) *10000 + 0.0025 *dbm*100*10000;
			cumcarbon = ca*pow((dbm*100),cb)*10000;
// 	cout<<"mine cumcarbon = "<<cumcarbon<<"\n";
// 	cout<<"mine prevcumcarbon = "<<prevcumcarbon<<"\n";
			if(cumcarbon-prevcumcarbon>1.0 && dbm <= 1.01){   // Yuan: soc will not exist more than 1 m
			 	sl = dynamic_cast<SoilLayer*> (currl);
 				bd->m_sois.reac[currind] = 1./11. * (cumcarbon -prevcumcarbon);
 				bd->m_sois.nonc[currind] = 10./11. * (cumcarbon -prevcumcarbon);
// 				sl->reac = bd->m_sois.reac[currind];   //Yuan: moving down below
// 				sl->nonc = bd->m_sois.nonc[currind];   //Yuan: moving down below
// 				allreac +=sl->reac;   //Yuan: moving down below
// 				allnonc +=sl->nonc;   //Yuan: moving down below
//	cout<<"mine1 dbm = "<<dbm<<"\n";
//	cout<<"mine1 cumcarbon = "<<cumcarbon<<"\n";
//	cout<<"mine1 bd->m_sois.reac = "<<bd->m_sois.reac[currind]<<"\n";
//	cout<<"mine1 bd->m_sois.nonc = "<<bd->m_sois.nonc[currind]<<"\n";
			}else{
// 				break;
 				bd->m_sois.reac[currind] = 0.0;    //
 				bd->m_sois.nonc[currind] = 0.0;
//HG: line added to fix bug computing mineral carbon
				cumcarbon = ca*pow((1.0*100),cb)*10000;;
			}
//	cout<<"mine1 bd->m_sois.reac = "<<bd->m_sois.reac[currind]<<"\n";
//	cout<<"mine1 bd->m_sois.nonc = "<<bd->m_sois.nonc[currind]<<"\n";
//	cout<<"mine1 cumcarbon = "<<cumcarbon<<"\n";
			prevcumcarbon = cumcarbon;
 	  		
 	  	}else{
 	  	  	break;	
 	  	}
 		currl =currl->nextl;
 	}

	//Yuan: above calculation will give all soil mineral layer C content UPON two parameters,
	//      the following will adjust that by actual initial MINEC amount as an input

	double adjfactor = minec/cumcarbon;
// 	cout<<"adjfactor = "<<adjfactor<<"\n";
//	cout<<"cumcarbon = "<<cumcarbon<<"\n";
//	cout<<"minec = "<<minec<<"\n";
	currl = fstminl;
	while(currl!=NULL){
 	  	if(currl->isSoil()){
 			currind =currl->solind-1;
		 	sl = dynamic_cast<SoilLayer*> (currl);
			bd->m_sois.reac[currind] *= adjfactor;
 			bd->m_sois.nonc[currind] *= adjfactor;
 			sl->reac = bd->m_sois.reac[currind];
 			sl->nonc = bd->m_sois.nonc[currind];
// 	cout<<"mine2 bd->m_sois.reac = "<<bd->m_sois.reac[currind]<<"\n";
//	cout<<"mine2 bd->m_sois.nonc = "<<bd->m_sois.nonc[currind]<<"\n";
			allreac +=sl->reac;
 			allnonc +=sl->nonc;
//	cout<<"mine allreac = "<<allreac<<"\n";
//	cout<<"mine allnonc = "<<allnonc<<"\n";
 	  	}
 		currl =currl->nextl;
 	}

};

// before delta and afterdelta are considered in Integrator
void Soil_Bgc::delta(){
	
   	double allreac, allnonc, allrrh, allnrh, allorgc , allrh;
   	double kfastc, kslowc;  //Yuan: kfastc is for relatively-fast-decomposed SOM,
   	                        //      kslowc is for the very-slowly-decomposed SOM
    	double klitrc;    //Yuan: for littering materials (in model, i.e., reactive-C)

 	for (int il =0; il<numsl; il++){
//		bd->m_soid.rhmoist[il] = getRhmoist(ed->m_soid.allaws[il],  //Yuan: vwc normalized by (total pore - ice volume), which makes almost no respiration for poorly-drained BS
		bd->m_soid.rhmoist[il] = getRhmoist(ed->m_soid.allsws[il],  //Yuan: vwc normalized by total pore
	 		   bgcpar.moistmin, bgcpar.moistmax, bgcpar.moistopt);	   
		bd->m_soid.rhq10[il] = getRhq10( ed->m_sois.ts[il]); 
	 
		klitrc = bd->m_soid.kdl[il];
		kfastc = bd->m_soid.kdr[il];
	   	kslowc = bd->m_soid.kdn[il];

		if(tmp_sois.reac[il]>0){    //Yuan: Note the sois.reac is the fibric-like materials
			del_soi2a.rrh[il] = klitrc * tmp_sois.reac[il] * bd->m_soid.rhmoist[il] * bd->m_soid.rhq10[il];
		} else {
			del_soi2a.rrh[il] =0.;	
		}
		
		if(tmp_sois.nonc[il]>0){    //Yuan: Note the sois.nonc is the residue of decomposed fibric-like materials
			//Yuan: the sois.nonc contains (0.076+0.125)/0.2045 fast-decomposable C,
			//                           and 0.0035/0.2045 slow-decomposable C.
			double rslowc= 0.0035/0.2045;
			del_soi2a.nrh[il] =  (kfastc*(1.0-rslowc) + kslowc*rslowc)*tmp_sois.nonc[il]
			                    * bd->m_soid.rhmoist[il] * bd->m_soid.rhq10[il];

		} else {
			del_soi2a.nrh[il] =0.;	
		}
  
   	} // loop for each soil layer   
   
   // for wood debris
   	if(tmp_sois.wdebris>0){
   		double rhmoist_wd =0.;
		double rhq10_wd =0.;
		double wdkd =0.;
	  	for (int il =0; il<numsl; il++){
	  		if(ed->m_sois.type[il]>0){//0 moss 1 shlw, and 2 deep   //Yuan: changed from 2 to >0
	  	  		rhmoist_wd =bd->m_soid.rhmoist[il] ;
	  	  		rhq10_wd = bd->m_soid.rhq10[il] ;
	  	  		//wdkd = bd->m_soid.kdr[il];
	  	  		wdkd = bd->m_soid.kdl[il];   //Yuan:
	  	  		break;	
	  		}
	  	}
	  	del_soi2a.wdrh =   wdkd* tmp_sois.wdebris * rhmoist_wd * rhq10_wd;	
    
    } else { 
      	del_soi2a.wdrh = 0.;
    }

	// nfeed
   	if(nfeed==1){
   		// get the sum of soil rh and then calculate overall netnmin
		allreac=0.;
		allrrh=0.;
		allnonc=0.;
		allnrh=0.;

	 	for (int il =0; il<numsl; il++){
	 	 	if(ed->m_sois.rootfrac[il]>0.01){
//				cout<<"rootfrac: "<<ed->m_sois.rootfrac[il]<<" for layer: "<<il<<"\n";
	   			allreac += tmp_sois.reac[il];	
	   			allrrh  += del_soi2a.rrh[il];
	   			allnonc += tmp_sois.nonc[il];	
	   			allnrh  += del_soi2a.nrh[il]; 
	 	 	}
	 	}
    		allorgc = allreac + allnonc;
    		allrh = allrrh + allnrh;
    
		del_soi2soi.nimmob =  getNimmob(totsolliq, allorgc,tmp_sois.orgn,
					          tmp_sois.avln, meanksoil, bgcpar.kn2);
		del_soi2soi.netnmin= getNetmin(del_soi2soi.nimmob, allorgc,tmp_sois.orgn,
					          tmp_sois.avln,allrh ,bgcpar.cnsoil, decay,  calpar.nup); 
//cout<<"numsl: "<<numsl <<"\n";
//cout<<"nimmob: "<<del_soi2soi.nimmob <<"\n";
//cout<<"allorgc: "<<allorgc <<"\n";
//cout<<"orgn: "<<tmp_sois.orgn <<"\n";
//cout<<"avln: "<<tmp_sois.avln <<"\n";
//cout<<"rh: "<<allrh <<"\n";
//cout<<"cnsoil: "<<bgcpar.cnsoil <<"\n";
//cout<<"decay: "<<decay <<"\n";
//cout<<"nup: "<<calpar.nup <<"\n";
//cout<<"del_soi2soi.netnmin: "<<del_soi2soi.netnmin <<"\n";

	} // nfeed
	  
};

void Soil_Bgc::deltaavln(){
					
 	if (avlnflg == 1){
  		if(totsolliq>0){
    		del_soi2l.nlost = tmp_sois.avln/totsolliq* bgcpar.nloss;// how to deal with this ?
  		}else{
  			del_soi2l.nlost =0.;	
  		}
    
    	if( del_soi2l.nlost > tmp_sois.avln - del_soi2v.nuptake  
       		                 + del_soi2soi.netnmin+ del_a2soi.ninput) {
     		del_soi2l.nlost= tmp_sois.avln  - del_soi2v.nuptake+ 
                            + del_soi2soi.netnmin+ del_a2soi.ninput;
        }
    
    	if (del_soi2l.nlost<0) {      
        	del_soi2l.nlost = 0.0;
        	del_soi2soi.netnmin= del_soi2l.nlost + del_soi2v.nuptake -del_a2soi.ninput
                            -tmp_sois.avln ;
    	} 	
  	
  	} else {
  	//sy
  		del_soi2v.nuptake = 0.;
    	del_soi2l.nlost   = del_a2soi.ninput - del_soi2v.nuptake
                           +del_soi2soi.netnmin;
   
  	}	
  
};

void Soil_Bgc::deltastate(){

	for(int il =0; il<numsl; il++){
/*
		if(ed->m_sois.type[il] ==3){ //for mineral
  			del_sois.reac[il] =blwfrac * del_v2soi.ltrfalc * blwlfcfrac[il] * 1./11
            +abvfrac* del_v2soi.ltrfalc * abvlfcfrac[il] * 1./11  - del_soi2a.rrh[il];
            
  			del_sois.nonc[il] =blwfrac * del_v2soi.ltrfalc * blwlfcfrac[il] *10./11
            +abvfrac* del_v2soi.ltrfalc * abvlfcfrac[il] * 10./11  - del_soi2a.nrh[il] ;
   
 		}else{   //fmy: I didn't see any difference here?
 	 		del_sois.reac[il] =blwfrac * del_v2soi.ltrfalc * blwlfcfrac[il] * 1./11
            +abvfrac* del_v2soi.ltrfalc * abvlfcfrac[il] * 1./11  - del_soi2a.rrh[il];
            
  			del_sois.nonc[il] =blwfrac * del_v2soi.ltrfalc * blwlfcfrac[il] *10./11
            +abvfrac* del_v2soi.ltrfalc * abvlfcfrac[il] * 10./11  - del_soi2a.nrh[il];
 	
  		}
*/

 		//Yuan: the following is modified, assuming that -
 		// 1) reactive-C is not-yet decomposed C, while non-reactive-C is C residue after decomposition

 		// 2) Jenkinson et al, 1977, soil science 123: 298 - 305
 		//    when C is respired, 1 C will produce:
 		// 0.076 microbial biomass C, 0.125 physically-resistant C, 0.0035 chemically-resistant C
 		// and the rest are released as CO2
 		double residuetoco2 = (double)bgcpar.som2co2;

 		del_sois.reac[il] = blwfrac * del_v2soi.ltrfalc * blwlfcfrac[il]
 		                   + abvfrac* del_v2soi.ltrfalc * abvlfcfrac[il]
 		                   - del_soi2a.rrh[il]*(1.0+residuetoco2);    //

 		del_sois.nonc[il] = del_soi2a.rrh[il]*residuetoco2 - del_soi2a.nrh[il];
 	}

 	//Yuan: moving/mixing portion of C among layers
 	//fibric-C (i.e., .reac) will NOT to move between layers
   	double s2dfraction = 1.0;
   	double mobiletoco2 = (double)bgcpar.fsoma*(double)bgcpar.som2co2;
   	double xtopdlthick  = min(0.10, ed->m_soid.deepthick);  //Yuan: the max. thickness of deep-C layers, which shallow-C can move into
   	double xtopmlthick  = 0.20;  //Yuan: the max. thickness of mineral-C layers, which deep-C can move into

   	double s2dcarbon = 0.0;
   	double d2mcarbon = 0.0;
   	double dlleft    = xtopdlthick;
   	double mlleft    = xtopmlthick;
  	double dcaddfrac = 0.0;
  	double thickadded= 0.0;
   	for(int il =0; il<numsl; il++){
    	// 1) most of 'nonc' increment into the fibric-layer (generated above) will move down
	   	if (ed->m_sois.type[il]==1) {
 	   		s2dcarbon += del_sois.nonc[il]*s2dfraction;
 	   		del_sois.nonc[il]*= (1.0-s2dfraction);
   		} else if (ed->m_sois.type[il]==2 && dlleft>0) {
   		// 2) s2dcarbon from above will move into the 'xtopdlthick';
	   		thickadded = min(ed->m_sois.dz[il], dlleft);
 	   		dcaddfrac = thickadded/xtopdlthick;
 	   		del_sois.nonc[il]+=dcaddfrac*s2dcarbon;
 	   		dlleft -=thickadded;

 	   	// 3) meanwhile, the most mobilable portion of 'sois.nonc' increment in deep-C layers will move down
 	   		d2mcarbon += (del_soi2a.nrh[il]+del_soi2a.rrh[il])*mobiletoco2;
	   		del_sois.nonc[il] -= (del_soi2a.nrh[il]+del_soi2a.rrh[il])*mobiletoco2;

	   	// 4) s2dcarbon from above will move into the 'xtopdlthick';
   		} else if (ed->m_sois.type[il]==3) {
 	   		thickadded = min(ed->m_sois.dz[il], mlleft);
 	   		dcaddfrac = thickadded/xtopmlthick;
 	   		del_sois.nonc[il]+=dcaddfrac*d2mcarbon;
 	   		mlleft -=thickadded;

 	   		if (mlleft<=0.0) break;
   		}

 	}

 	//
  	del_sois.wdebris = - del_soi2a.wdrh;

  	// Nitrogen pools in ecosystems
  	if(nfeed==1){
  		del_sois.orgn= del_v2soi.ltrfaln - del_soi2soi.netnmin; 
  	}
  	
  	if(avlnflg==1){  	 	
  		del_sois.avln = del_a2soi.ninput  - del_soi2l.nlost
  		               + del_soi2soi.netnmin - del_soi2v.nuptake;
  	} 

};


double Soil_Bgc::getNuptake(const double & foliage, const double & raq10, 
                            const double & kn1, const double &nmax){

	double nuptake =0.;
  	// need to use root fraction and ksoil average to calculate nuptake
 
    if(nfeed==1){
 	 	if(totsolliq>0 ){
  			nuptake  = (tmp_sois.avln * meanksoil)/ totsolliq;  // availn/soilh2o is the concentration of mineral nitrogen
  			nuptake /= (kn1 +nuptake);
  			if(nuptake>1) {  		 
  		 		string msg = "nuptake is too big";
 				char* msgc = const_cast< char* > ( msg.c_str());
 				throw Exception(msgc, I_NUPTAKE_RANGE);
  			} 
  		
  			nuptake *=(nmax * foliage);
  			nuptake *= raq10; 
   	 	}else{
  			nuptake=0.;
  	 	}
    }
  
  	return nuptake;
};

double Soil_Bgc::getRhmoist(const double &vsm, const double &moistmin, 
	                        const double &moistmax, const double &moistopt){

  	double rhmoist;
 	//set moistlim always 1
    rhmoist = (vsm - moistmin) * (vsm - moistmax);
    rhmoist /= rhmoist - (vsm-moistopt)*(vsm-moistopt);
  	if ( rhmoist < 0.0 ) { rhmoist = 0.0; }

	return rhmoist;
};
	
double Soil_Bgc::getRhq10(const  double & tsoil){
	double rhq10;
    rhq10 =  pow( (double)bgcpar.rhq10, tsoil/10.0);  
 	return rhq10;
};

double Soil_Bgc::getNimmob(const double & soilh2o, const double & soilorgc, 
                           const double & soilorgn, const double & availn, 
                           const double & ksoil, const double kn2){

	 double nimmob     = 0.0;
     double tempnimmob = 0.0;
     double tempkn2    = kn2;
	 //what if put && availn>0 here
	 if(soilorgc>0.0 && soilorgn>0.0 && soilh2o>0 ){
	 	nimmob = (availn * ksoil) / soilh2o;
	 	tempnimmob = nimmob;
        nimmob /= (tempkn2 + nimmob); 
	 }
	 
	 if(nimmob>1 || nimmob<0) {
	 	 
	    string msg = "nimmob is too big";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NIMMOB_RANGE);
	 
	 }
    
	 return nimmob;
};

double Soil_Bgc::getNetmin(const double & nimmob, const double & soilorgc, 
                           const double & soilorgn, const double & availn, 
                           const double & rh, const double & tcnsoil,
					       const double & decay, const double & nup ) {

  	double nmin = 0.0;

  	if ( soilorgc > 0.0 && soilorgn > 0.0 ) {
    	nmin   = ((soilorgn / soilorgc) - (nup * nimmob * decay)) * rh;
     
    	if ( nmin >= 0.0 ){
    	 	nmin *= (soilorgn/soilorgc) * tcnsoil;
     	} else {
    	 	nmin *= (soilorgc/soilorgn) / tcnsoil; 
     	}
  	} 
  
  	return nmin;

}; 

double Soil_Bgc::getKSoil( const double & vsm){
	double ksoil;
	
	ksoil = pow( vsm,3.0 );
	
	return ksoil;
};

void Soil_Bgc::updateKdyrly4all(const int &yrcnt ){
 	double tmpkdfib = bd->kdfib;//
	double tmpkdhum = bd->kdhum;//
	double tmpkdmin = bd->kdmin;//
	double tmpkdslow = bd->kdslow;//

	if(yrcnt>0  ){
		 tmpkdfib = getKdyrly(bd->y_v2soi.ltrfalc,bd->y_v2soi.ltrfaln, bgcpar.lcclnc, bd->nfeed, calpar.kdcfib);
		 tmpkdhum = getKdyrly(bd->y_v2soi.ltrfalc,bd->y_v2soi.ltrfaln, bgcpar.lcclnc, bd->nfeed, calpar.kdchum);
		 tmpkdmin = getKdyrly(bd->y_v2soi.ltrfalc,bd->y_v2soi.ltrfaln, bgcpar.lcclnc, bd->nfeed,calpar.kdcmin);
		 tmpkdslow = getKdyrly(bd->y_v2soi.ltrfalc,bd->y_v2soi.ltrfaln, bgcpar.lcclnc, bd->nfeed, calpar.kdcslow);
	}
	
	bd->kdfib = tmpkdfib;
	bd->kdhum = tmpkdhum;
	bd->kdmin = tmpkdmin;
	bd->kdslow = min(tmpkdhum, tmpkdhum)/100.0;//tmpkdslow;




/*
	for(int i=0; i<MAX_SOI_LAY; i++){
		 if(ed->m_sois.type[i]==0){ //moss
		 	bd->m_soid.kdr[i] =0.0;
		 	bd->m_soid.kdn[i] =0.0;
		 }else if(ed->m_sois.type[i]==1){ //fib
		 	bd->m_soid.kdr[i] =tmpkdfib;
		 	bd->m_soid.kdn[i] =tmpkdslow;  //Yuan: non-reactive C
		 }else if(ed->m_sois.type[i]==2){ //humic
		 	bd->m_soid.kdr[i] =tmpkdhum;
		 	bd->m_soid.kdn[i] =tmpkdhum;
		 }else if(ed->m_sois.type[i]==3){ //mineral
		 	bd->m_soid.kdr[i] =tmpkdmin;
		 	bd->m_soid.kdn[i] =tmpkdslow;
		 }
	}// end of loop
*/
	//Yuan: the following is modified, assuming that -
	// reactive-C is not-yet decomposed C, while non-reactive-C is C residue after decomposition
	// (will be modified the definition later on)
	// so, kdfib is for reactive-C only;
	//     kdhum/kdmin (i.e.,soid.kdr) are for the fast-decomposable portion (0.2010/0.2045)of non-reactive C in organic/mineral layers, respectively;
	//     kdslow (i.e., soid.kdn) are for the slow-decomposable portion (0.0035/0.2045) of non-reactive C in all types of soil layers
	for(int i=0; i<MAX_SOI_LAY; i++){
		 if(ed->m_sois.type[i]==0){ //moss
		 	bd->m_soid.kdl[i] =0.0;
		 	bd->m_soid.kdr[i] =0.0;
		 	bd->m_soid.kdn[i] =0.0;
		 }else if(ed->m_sois.type[i]==1){ //fib
		 	bd->m_soid.kdl[i] =bd->kdfib;
		 	bd->m_soid.kdr[i] =bd->kdhum;
		 	bd->m_soid.kdn[i] =bd->kdslow;
		 }else if(ed->m_sois.type[i]==2){ //humic
		 	bd->m_soid.kdl[i] =bd->kdfib;
		 	bd->m_soid.kdr[i] =bd->kdhum;
		 	bd->m_soid.kdn[i] =bd->kdslow;
		 }else if(ed->m_sois.type[i]==3){ //mineral
		 	bd->m_soid.kdl[i] =bd->kdfib;
		 	bd->m_soid.kdr[i] =bd->kdmin;
		 	bd->m_soid.kdn[i] =bd->kdslow;
		 }

	}

};

double Soil_Bgc::getKdyrly(double& yrltrc, double& yrltrn, 
                           const double lcclnc, const int & nfeed, 
                           const double & kdc) {
  	double kd;

  	if ( yrltrn <= 1.e-12 ) {
  	 	kd = 0.0; 
  	 	return kd;
  	}
     
  	if ( nfeed == 0 ){
    	kd = kdc; 
   	} else {
    	kd = kdc * pow( (yrltrc/yrltrn),-0.784 ) / pow( lcclnc,-0.784 );
   	}
 	
 	return kd;
};
 
double Soil_Bgc::getLitterFall(const int & type){ //1 fibric; 2 humic; 3 mineral
	double oneroot=0;
	double totroot=0;
	 
	for(int il = 0; il<MAX_SOI_LAY;il++){
		if(ed->m_sois.rootfrac[il]>0.001){
			if(ed->m_sois.type[il]==type){ 		 	  
 		 	 	totroot += ed->m_sois.rootfrac[il];	  
			} 
		}
 	}
 	
 	if(type ==1){
 	 	oneroot = 0.431 +0.569*totroot;
 	}else{
 	 	oneroot = 0.569* totroot;
 	}
 	
 	return oneroot;
};
  
///////////////////////////
// set outside pointer
//////////////////////////
void Soil_Bgc::setCohortLookup(CohortLookup* chtlup){
  	 chtlu = chtlup;
};

void Soil_Bgc::setEnvData(EnvData* edp){
  	 ed = edp;
};
  
void Soil_Bgc::setBgcData(BgcData* bdp){
  	 bd =bdp;
};

void Soil_Bgc::setFirData(FirData* fdp){
  	 fd =fdp;
};
