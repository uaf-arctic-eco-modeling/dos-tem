/*! \file
*
*/

#include "Integrator.h"

float Integrator::a1  =   0.115740741;
float Integrator::a3  =   0.548927875;
float Integrator::a31 =   0.09375;
float Integrator::a32 =   0.28125;

float Integrator::a4  =   0.535331384;
float Integrator::a41 =   0.879380974; 
float Integrator::a42 =  -3.277196177;
float Integrator::a43 =   3.320892126;

float  Integrator::a5  =  -0.20;
float  Integrator::a51 =   2.032407407;
float  Integrator::a52 =  -8.0;
float  Integrator::a53 =   7.173489279;
float  Integrator::a54 =  -0.2058966866;

float   Integrator::b1 =   0.118518519;
float   Integrator::b3 =   0.518986355;
float   Integrator::b4 =   0.50613149;
float   Integrator::b5 =  -0.18;
float   Integrator::b6 =   0.036363636;
float  Integrator::b61 =  -0.296296296;
float  Integrator::b62 =   2.0;
float  Integrator::b63 =  -1.381676413;
float  Integrator::b64 =   0.45297271;
float  Integrator::b65 =  -0.275;

int REJECT =0;
int ACCEPT=1;

Integrator::Integrator(){
	inittol = 0.01;
   	maxit = 20;
    maxitmon = 100;
    syint = 1;
    
    strcpy( predstr[I_VEGC],"VEGC" );       // vegetation carbon

    // Ecosystem nitrogen pools *************************************

    strcpy( predstr[I_STRN],"STRN" );  // vegetation structural nitrogen
  	strcpy( predstr[I_STON],"STON" );   // vegetation labile nitrogen
  	strcpy( predstr[I_UNNORMLEAF],"UNNORMLEAF" );  // vegetation unormleaf
  	strcpy( predstr[I_WDEBRIS],"WDEBRIS" ); // wood debris

	// Phenology variables for ecosystems ***************************

	// Carbon fluxes for ecosystems **********************************

  	// GPP not limited by nutrient availability
  	strcpy( predstr[I_INGPP],"INGPP" );
 	strcpy( predstr[I_GPP],"GPP" );      // gross primary production

  	// NPP not limited by nutrient availability
  	strcpy( predstr[I_INNPP],"INNPP" );
  	strcpy( predstr[I_NPP],"NPP" );      // net primary production
  	strcpy( predstr[I_RM],"RM" );      // gross plant respiration
  	strcpy( predstr[I_RG],"RG" );      // gross plant respiration

  	strcpy( predstr[I_LTRC],"LTRC" );   // litterfall carbon
 // strcpy( predstr[I_AGSTUBC],"CRPSTUBC" );   // stubble carbon
  	strcpy( predstr[I_RH_WD],"RHWD" );   // litterfall carbon


// Nitrogen fluxes for ecosystems ********************************

  	strcpy( predstr[I_NINP],"NINPUT" );   	// total nitrogen inputs into ecosystem
  	strcpy( predstr[I_INNUP],"VEGINNUP" );   	// VEGNUP not limited by carbon availability
  	strcpy( predstr[I_VNUP],"VEGNUP" );   	// nitrogen uptake by vegetation
   	strcpy( predstr[I_VSUP],"VEGSUP" ); // vegetation nitrogen uptake for structural components
   	strcpy( predstr[I_VLUP],"VEGLUP" ); // vegetation nitrogen uptake for labile components
  
  	strcpy( predstr[I_VNMBL],"VNMOBIL" ); // nitrogen mobilization by vegetation
  	strcpy( predstr[I_VNRSRB],"VNRESORB" ); // nitrogen resorption by vegetation
  	strcpy( predstr[I_LTRN],"LTRN" );       // litterfall nitrogen
 
	strcpy( predstr[I_SOLN],"SOLN");   // soil organic nitrogen
	strcpy( predstr[I_AVLN],"AVLN" );   // soil available nitrogen
	strcpy( predstr[I_NMIN],"NMIN" );   // soil net n minerization
	strcpy( predstr[I_MNUP],"MNUP" );   // 
	strcpy( predstr[I_NLST],"NLOST");      //  nitrogen losses from ecosystem
	strcpy( predstr[I_SNUP],"SNUP");      //  nitrogen uptake from each layer
	
	for(int il =0; il<MAX_SOI_LAY; il++){
		stringstream out ;
		out <<" " <<il;
		string str = out.str();
		strcpy( predstr[I_L_REAC+il],(string("REAC") +str).c_str() );   // soil reactive carbon
		strcpy( predstr[I_L_NONC+il],(string("NONC") +str).c_str() );   // soil non-reactive carbon
		strcpy( predstr[I_L_RRH+il],(string("RRH") +str).c_str() );   // soil rh
		strcpy( predstr[I_L_NRH+il],(string("NRH") +str).c_str() );   // soil rh
	}

};

 
void Integrator::updateMonthly(){
	//before integration , initialize the state and flux
	// from ssl, veg;
	 // first reset all the fluxes variables to zero
	 nfeed = bd->nfeed;
     NUMSL = ed->m_soid.actual_num_soil;
     for (int iv = 0; iv < NUMEQ; iv++ ){ 
     	y[iv] = 0.0; 
     }
     
     c2ystate(y);
	
	 adapt(y);

    // after integration , save results back to veg and ssl;	
	 y2cstate(y);
     y2cflux(y);
     
     /*ssl->soil.sn2sl = ssl->snow.sn2sl;*/
	
	// after adaptation, store back state and flux to ssl and veg
};

int Integrator::adapt(float pstate[]){
  	int i;
  	float ipart;
  	float fpart;
  	float time = 0.0;
  	float dt = 1.0;
  	int mflag = 0;
  	long nintmon = 0;
  	float oldstate[NUMEQ];
  	float  ptol =0.01;
 // temporary
 	int numeq = NUMEQ;

 //

  	blackhol = 0;
  	while ( time != 1.0 ){
    	test = REJECT;
    	if ( syint == 1 ){
      		while ( test != ACCEPT ){
      			// cout << "integration time step " << dt << "\n";
				bool testavln = rkf45( numeq,pstate,dt);
				if(testavln){
					test = boundcon( dum4,error,ptol );
				}else{
	 				test =testavln;	
				}
				
				//if(test>1)cout <<predstr[test-1] << " error is " << error[test-1] <<"------Integrator-------\n";
				if ( dt <= pow(0.5,maxit) ){
	  				test = ACCEPT;
	  				mflag = 1;
          			if ( nintmon == 0 ){
            			for( i = 0; i < numeq;i++ ) { oldstate[i] = pstate[i]; }
          			}
	  				++nintmon;
				}

        		if ( test == ACCEPT ){
          			for( i = 0; i < numeq;i++ ) { pstate[i] = dum4[i]; }
          			time += dt;
          			fpart = modf( (0.01 + (time/(2.0*dt))),&ipart );
          			if ( fpart < 0.1 && dt < 1.0) { dt *= 2.0; }
        		}else {
        			dt *= 0.500; 
        		}

        		if ( nintmon == maxitmon ){
          			time = 1.0;
          			blackhol = 1;
          			for( i = 0; i < numeq;i++ ) { pstate[i] = oldstate[i]; }
        		}
      		}
    	}    /* end rkf integrator (if) */
  	}      /* end time while */

  	return mflag;

};

bool Integrator::checkPools(){
   	bool negativepool =false;
   	if(ydum[I_AVLN]<0 ||ydum[I_VEGC]<0||ydum[I_STRN]<0 || ydum[I_STON]<0){
   	 	negativepool =true;
   	}
   	return negativepool;
}

bool Integrator::rkf45( const int& numeq, float pstate[], 
                   float& pdt ) {
  	bool negativepool =false;
  	int i;
  	float ptdt = 0;

  	for ( i = 0; i < numeq;i++ ) {
    	dum4[i] = dum5[i] = pstate[i];
    	yprime[i] = rk45[i] = error[i] = 0.0;
    	f11[i]=f3[i]=f4[i]=f5[i]=f6[i] = 0.0;
  	}

  	ptdt = pdt * 0.25;
  	delta(dum4,f11 );
  	
  	step( numeq,yprime,f11,yprime,a1 );
  	step( numeq,rk45,f11,rk45,b1 );
  	step( numeq,dum4,f11,ydum,ptdt );
  	negativepool = checkPools();
  	if(negativepool){
  	  	return false;	
  	}
  	
  	delta(ydum,f2 );
  	for ( i = 0; i < numeq; i++ ) {
    	f13[i] = a31*f11[i] + a32*f2[i];
  	}
  
  	step( numeq,dum4,f13,ydum,pdt );
 	negativepool = checkPools();
  	if(negativepool){
  	  return false;	
  	}
  	
  	delta(ydum,f3 );
  	step( numeq,yprime,f3,yprime,a3 );
  	step( numeq,rk45,f3,rk45,b3 );
  	for ( i = 0; i < numeq; i++ ){
    	f14[i] = a41*f11[i] + a42*f2[i] + a43*f3[i];
  	}
  	
  	step( numeq,dum4,f14,ydum,pdt );
  	negativepool = checkPools();
  	if(negativepool){
  	  return false;	
  	}
  	
  	delta(ydum,f4 );
  	step( numeq,yprime,f4,yprime,a4 );
  	step( numeq,rk45,f4,rk45,b4 );
  	for ( i = 0; i < numeq; i++ ) {
    	f15[i] = a51*f11[i] + a52*f2[i] + a53*f3[i] + a54*f4[i];
  	}
  	
  	step( numeq,dum4,f15,ydum,pdt );
  	negativepool = checkPools();
  	if(negativepool){
  	  return false;	
  	}
  	
  	delta(ydum,f5 );
  	step( numeq,yprime,f5,yprime,a5 );
  	step( numeq,rk45,f5,rk45,b5 );
  	for ( i = 0; i < numeq; i++ ){
    	f16[i] = b61*f11[i] + b62*f2[i] + b63*f3[i] + b64*f4[i] + b65*f5[i];
  	}
  	
  	step( numeq,dum4,f16,ydum,pdt );
  	negativepool = checkPools();
  	if(negativepool){
  	  return false;	
  	}
  	
  	delta(ydum,f6 );
  	step( numeq,rk45,f6,rk45,b6 );
  	step( numeq,dum4,yprime,dum4,pdt );
  	step( numeq,dum5,rk45,dum5,pdt );
  	for ( i = 0; i < numeq; i++ ) {
    	error[i] = fabs( dum4[i] - dum5[i] );
  	}
  
    return true;
};

/***************************************************************
 ***************************************************************/

void Integrator::step( const int& numeq, float pstate[], 
                    float pdstate[], float ptstate[],
			        float& pdt ) {
 
  	for ( int i = 0; i < numeq; i++ ) {
    	ptstate[i] = pstate[i] + (pdt * pdstate[i]);
  	}
	
}

int Integrator::boundcon( float ptstate[], float err[], float& ptol ) {

  	int test = ACCEPT;

	// Check carbon and nitrogen state variables
 	//extra check
  	if ( nfeed == 1 && ptstate[I_AVLN] <0 )
  {
    return test = temkey( I_AVLN )+1;
  }
  if ( err[I_VEGC] > fabs( ptol * ptstate[I_VEGC] ) )
  {
    return test = temkey( I_VEGC )+1;
  }
  if ( nfeed == 1 && err[I_STRN] > fabs( ptol * ptstate[I_STRN] ) )
  {
    return test = temkey( I_STRN )+1;
  }
  
    if ( nfeed == 1 && err[I_MNUP] > fabs( ptol * ptstate[I_MNUP] ) )
  {
    return test = temkey( I_MNUP  )+1;
  }
  
  if ( nfeed == 1 && err[I_SOLN] > fabs( ptol * ptstate[I_SOLN] ) )
  {
    return test = temkey( I_SOLN )+1;
  }
  if ( nfeed == 1 && err[I_AVLN] > fabs( ptol * ptstate[I_AVLN] ) )
  {
    return test = temkey( I_AVLN )+1;
  }
 
  
  
  
  if ( nfeed == 1 && err[I_NMIN] > fabs( ptol * ptstate[I_NMIN] ) )
  {
    return test = temkey( I_NMIN  )+1;
  }
  
  if ( nfeed == 1 && err[I_SNUP] > fabs( ptol * ptstate[I_SNUP] ) )
  {
    return test = temkey( I_SNUP  )+1;
  }
  
  
  // begin of layered variables
  for(int il =0; il<NUMSL; il++){
  if ( err[I_L_REAC+il] > fabs( ptol * ptstate[I_L_REAC+il] ) )
  {
    return test = temkey( I_L_REAC+il )+1;
  }
  
  if ( err[I_L_NONC+il] > fabs( ptol * ptstate[I_L_NONC+il] ) )
  {
    return test = temkey( I_L_NONC+il )+1;
  }
  if ( nfeed == 1 && err[I_L_RRH+il] > fabs( ptol * ptstate[I_L_RRH+il] ) )
  {
    return test = temkey( I_L_RRH  +il )+1;
  }
   if ( nfeed == 1 && err[I_L_NRH+il] > fabs( ptol * ptstate[I_L_NRH+il] ) )
  {
    return test = temkey( I_L_NRH  +il )+1;
  }

  }
  //end of layered variables
  if ( err[I_GPP] > fabs( ptol * ptstate[I_GPP] ) )
  {
    return test = temkey( I_GPP )+1;
  }
  if ( err[I_NPP] > fabs( ptol * ptstate[I_NPP] ) )
  {
    return test = temkey( I_NPP )+1;
  }
  if ( nfeed == 1 && err[I_VNUP] > fabs( ptol * ptstate[I_VNUP] ) )
  {
    return test = temkey( I_VNUP )+1;
  }
  if ( nfeed == 1 && err[I_VSUP] > fabs( ptol * ptstate[I_VSUP] ) )
  {
    return test = temkey( I_VSUP )+1;
  }
  if ( nfeed == 1 && err[I_STON] > fabs( ptol * ptstate[I_STON] ) )
  {
    return test = temkey( I_STON )+1;
  }
  if ( nfeed == 1 && err[I_VNMBL] > fabs( ptol * ptstate[I_VNMBL] ) )
  {
    return test = temkey( I_VNMBL )+1;
  }

  
  return test;

};
                            
void Integrator::dc2ystate(float pdstate[]){
	
	   // assign fluxes and state back to pdstate
    pdstate[I_VEGC] = veg->del_vegs.c;
    pdstate[I_STRN] = veg->del_vegs.strn;
    pdstate[I_STON] = veg->del_vegs.ston;
	pdstate[I_UNNORMLEAF] = veg->del_vegs.unnormleaf;
   
    for (int il =0; il<NUMSL; il++){
    	pdstate[I_L_REAC+il] = ssl->del_sois.reac[il];
        pdstate[I_L_NONC+il] = ssl->del_sois.nonc[il];
       
    }
    
		pdstate[I_SOLN] = ssl->del_sois.orgn;
    	pdstate[I_AVLN] = ssl->del_sois.avln;
    	pdstate[I_WDEBRIS] = ssl->del_sois.wdebris;
}   

void Integrator::dc2yflux(float pdstate[]){

	 pdstate[I_INGPP] = veg->del_a2v.ingpp  ;
	 pdstate[I_GPP] = veg->del_a2v.gpp   ;
	 pdstate[I_INNPP] = veg->del_a2v.innpp   ;
	 pdstate[I_NPP] = veg->del_a2v.npp ;
	 
	 pdstate[I_RG] = veg->del_v2a.rg ;
	 pdstate[I_RM] = veg->del_v2a.rm ;
	 
	 pdstate[I_LTRC] = veg->del_v2soi.ltrfalc   ;
     pdstate[I_NINP] = ssl->del_a2soi.ninput  ;
     pdstate[I_INNUP] =  veg->del_soi2v.innuptake   ;
     pdstate[I_VNUP] =  veg->del_soi2v.nuptake  ;
  	 pdstate[I_VSUP] = veg->del_soi2v.suptake ;
     pdstate[I_VLUP] = veg->del_soi2v.luptake  ;
  	 pdstate[I_VNMBL] = veg->del_v2v.nmobil  ;
  	 pdstate[I_VNRSRB] =veg->del_v2v.nresorb  ;
  	 pdstate[I_LTRN] = veg->del_v2soi.ltrfaln  ;
    
 	pdstate[I_RH_WD] = ssl->del_soi2a.wdrh  ;
	for (int il =0; il<NUMSL; il++){
		pdstate[I_L_RRH +il] = ssl->del_soi2a.rrh[il];
	    pdstate[I_L_NRH +il] = ssl->del_soi2a.nrh[il];
	}
	pdstate[I_MNUP] =ssl->del_soi2soi.nimmob  ;
 	    pdstate[I_NMIN  ] =ssl->del_soi2soi.netnmin  ;
 	    pdstate[I_NLST] =ssl->del_soi2l.nlost   ;//30
 	    pdstate[I_SNUP] =ssl->del_soi2v.nuptake   ;//30
   
}                         
void Integrator::y2tcstate(float pstate[]){
 	 veg->tmp_vegs.c=   pstate[I_VEGC]  ;
     veg->tmp_vegs.strn =pstate[I_STRN] ;
     veg->tmp_vegs.ston = pstate[I_STON] ;
     veg->tmp_vegs.unnormleaf = pstate[I_UNNORMLEAF] ;
     for(int il =0; il<NUMSL; il++){
     	ssl->tmp_sois.reac[il] =pstate[I_L_REAC+il];
        ssl->tmp_sois.nonc[il] =pstate[I_L_NONC+il];
     
     } 
     
    ssl->tmp_sois.orgn =pstate[I_SOLN];
    ssl->tmp_sois.avln= pstate[I_AVLN];
    ssl->tmp_sois.wdebris= pstate[I_WDEBRIS];
   
}                         
void Integrator::y2cstate(float y[]){
	 bd->m_vegs.c=  y[I_VEGC]  ;
     
     if(y[I_STON]<0){//add by shuhua Dec 8 2007
	  y[I_STRN]+=y[I_STON] -0.001;	
	  y[I_STON]=0.001;	
	 }
	 bd->m_vegs.strn =y[I_STRN] ;
     bd->m_vegs.ston = y[I_STON] ;
     bd->m_vegs.unnormleaf = y[I_UNNORMLEAF] ;
     
     for(int il=0; il<NUMSL; il++){
     	
     	bd->m_sois.reac[il] =y[I_L_REAC +il];
        bd->m_sois.nonc[il] =y[I_L_NONC +il];
     }
	
	if(y[I_AVLN]<0){//add by shuhua Dec 8 2007
	  y[I_SOLN]+=y[I_AVLN] -0.001;	
	  y[I_AVLN]=0.001;	
	}
	bd->m_sois.orgn =  y[I_SOLN];
    bd->m_sois.avln= y[I_AVLN];
    
    bd->m_sois.wdebris= y[I_WDEBRIS];
}

void Integrator::c2ystate(float dy[]){
	dy[I_VEGC] = bd->m_vegs.c;
    dy[I_STRN] = bd->m_vegs.strn;
    dy[I_STON] = bd->m_vegs.ston;
 	dy[I_UNNORMLEAF] = bd->m_vegs.unnormleaf;
    
    for(int il =0; il<NUMSL; il++){
      	dy[I_L_REAC+il] = bd->m_sois.reac[il];
      	dy[I_L_NONC+il] = bd->m_sois.nonc[il];
    }
    
    dy[I_SOLN] = bd->m_sois.orgn;
    dy[I_AVLN] = bd->m_sois.avln;
    dy[I_WDEBRIS] = bd->m_sois.wdebris;
};

void Integrator::y2cflux(float dy[]){
	 bd->m_v2soi.ltrfalc = dy[I_LTRC];
     bd->m_a2soi.ninput = dy[I_NINP];
     bd->m_soi2v.innuptake =  dy[I_INNUP];
     bd->m_soi2v.nuptake = dy[I_VNUP];
  	 bd->m_soi2v.suptake = dy[I_VSUP];
  	 bd->m_soi2v.luptake = dy[I_VLUP];
  	 bd->m_v2v.nmobil = dy[I_VNMBL];
  	 bd->m_v2v.nresorb = dy[I_VNRSRB];
  	 bd->m_v2soi.ltrfaln = dy[I_LTRN];

  	
  	
  	bd->m_a2v.ingpp = dy[I_INGPP];
  	bd->m_a2v.gpp = dy[I_GPP];
  	bd->m_a2v.innpp = dy[I_INNPP];
  	bd->m_a2v.npp = dy[I_NPP];
  	bd->m_v2a.rm = dy[I_RM];
  	bd->m_v2a.rg = dy[I_RG];
  	
  	bd->m_soi2a.wdrh = dy[I_RH_WD];
  	for(int il =0; il<NUMSL; il++){
  		
  		bd->m_soi2a.rrh[il] = dy[I_L_RRH +il];
  		bd->m_soi2a.nrh[il] = dy[I_L_NRH +il];
  	}
   
  	bd->m_soi2soi.nimmob = dy[I_MNUP];
  	bd->m_soi2soi.netnmin = dy[I_NMIN];
  	bd->m_soi2l.nlost = dy[I_NLST];
  	bd->m_soi2v.nuptake = dy[I_SNUP];
};

void Integrator::c2yflux(float dy[]){
	
};
                            
void Integrator::delta(  float pstate[], 
                          float pdstate[] ){
   
   // first assign value from pstate to temporate variables in veg, atm,and ssl
   // only state variabls are needed, since fluxes and diagnostic variables will 
   // be recalculated again based on state variabels	
  
   y2tcstate(pstate);
   
   ssl->delta();
    
   veg->delta();
   veg->deltanfeed(); //the updated ds2v.nuptake will be used by microbe.delta
   
   ssl->del_soi2v = veg->del_soi2v;
   ssl->del_v2soi = veg->del_v2soi;
   
   ssl->deltaavln();
   // after the delta of fluxes have been updated
   // update the delta of state
   ssl->deltastate();
   veg->deltastate();
    
   // assign fluxes and state back to pdstate
   dc2ystate(pdstate);
   dc2yflux(pdstate);
                     	
 };
  
 void Integrator::setSoil_Bgc( Soil_Bgc * soip){
       	 ssl = soip;
 };
       
 void Integrator::setVegetation_Bgc( Vegetation_Bgc * vegp){
       	 veg = vegp;
 };
 
 void Integrator::setBgcData(BgcData* bdp){
       	 bd = bdp;
 }
       
 void Integrator::setEnvData(EnvData* edp){
    	 ed = edp;
 }
       
