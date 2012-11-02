#include "Snow_Env.h"

Snow_Env::Snow_Env(){
	
	
	int indl=1;
	mindz[indl] =0.03;
	maxdz[indl] =0.1;
	
	indl++;
	mindz[indl] =0.045;
	maxdz[indl] =0.15;
	
	indl++;
	mindz[indl] =0.075;
	maxdz[indl] =0.33;

    indl++;
	mindz[indl] =0.165;
	maxdz[indl] =0.69;
	
	indl++;
	mindz[indl] =0.345;
	maxdz[indl] =100;
	
	
};

Snow_Env::~Snow_Env(){
	
};


void Snow_Env::updateDailySurfFlux( Layer* frontl, const double & tdrv){
	
	double albnir = frontl->getAlbedoNir();
	double albvis = frontl->getAlbedoVis();
	
	/*albvis *=1.5;
	albnir *=1.5;
	
	if(albvis>1) albvis=1;
	if(albnir>1) albnir =1; // sensitivity test
	*/
	
	
	double insw =  ed->d_v2g.sw * ed->y_vegd.vegfrac + (1-ed->y_vegd.vegfrac)* ed->d_a2l.nirr;
	//if(chttype==0){ //tundra, the snow should be on top of canopy, so the radiation is from atm to lnd
	//	veg2gsw = ed->d_a2l.nirr;
	//}
	
	//if(chttype!=0){//only for burned forest

	//}
	ed->d_snw2a.solrad = insw *0.5 * albnir + insw *0.5 * albvis;
	 
	double rn = insw- ed->d_snw2a.solrad;
	
	
 //   double sthfl = ed->d_v2g.sthfl;
 //   double sdrip = ed->d_v2g.sdrip;
     
   
  //  snodd.melt =getThflMelt(tdrv,rn, sthfl, sdrip);
    
   
    double sublim = getSublimation(rn, ed->d_snws.swe, tdrv); //mm/day
    //see Zhuang et al., 2004 D4 not sure whether equation D8 is right, when compared with the one from
    //Brubaker et al., 1996
   // double melt = 2.99*rn/0.2388 *86400/10000.+2.0*tdrv; //mm/day
    double melt =0.26*rn +2.0*tdrv;//mm/day
    /*
     if(tdrv>=-1){
    	 ed->d_snw2a.sublim =0;
    	 ed->d_snwd.melt = sublim;
    }else{
    	 ed->d_snw2a.sublim = sublim;
    	 ed->d_snwd.melt = 0;
    } 
    */
    
    if(melt>0 && melt<=sublim){
    	 ed->d_snwd.melt = melt;
    	 ed->d_snw2a.sublim = sublim-melt;
    	 
    }else if(melt<=0){
         ed->d_snwd.melt = 0;
         ed->d_snw2a.sublim = sublim;
    }else if (melt>sublim){
        ed->d_snw2a.sublim = 0;
     	  ed->d_snwd.melt = sublim;
    }
    
    //snosd.swe = snosd. swe - sublim + sthfl +sdrip -snodd.melt ;
};



void Snow_Env::initializeParameter(const int &vegtypep){
	//set the parameters
	
	
	dztot =0.;
	
	envpar.denmax = chtlu->snwdenmax[vegtypep];
	envpar.albmax = chtlu->snwalbmax[vegtypep];
	envpar.albmin = chtlu->snwalbmin[vegtypep];
	envpar.newden = chtlu->snwdennew[vegtypep];

	fcmelt =5. ;  //
	extramass =0.; 

	
//	maxdz =0.15

	
}

//Yuan: not reading netcdf file here
void Snow_Env::initializeState5restart(Layer* frontl, RestartData* resin){
	//set the parameters
  	double DZsnow[MAX_SNW_LAY];
	double TSsnow[MAX_SNW_LAY];
	double AGEsnow[MAX_SNW_LAY];
	double RHOsnow[MAX_SNW_LAY];
	double ICEsnow[MAX_SNW_LAY];

	for (int i=0; i<MAX_SNW_LAY; i++){
		DZsnow[i] =resin->DZsnow[i];
		TSsnow[i] =resin->TSsnow[i];
		AGEsnow[i]=resin->AGEsnow[i];
		RHOsnow[i]=resin->RHOsnow[i];
		ICEsnow[i]=resin->ICEsnow[i];
	}
	
	Layer* currl = frontl;
	
	int snind =-1;
	ed->d_snws.swe=0;
	SnowLayer* sl;
	while(currl!=NULL){
		if(currl->isSnow()){
		  snind ++;
		  currl->age = AGEsnow[snind];
		  currl->tem = TSsnow[snind];
		
		  currl->ice = ICEsnow[snind];
		  currl->liq = 0;
		  currl->wat = currl->ice + currl->liq;
		  currl->poro = 0;
		  currl->frozen =1;
		  currl->maxliq =0;
		  currl->minliq =0;
		  currl->maxice =0;
	 		  
		  currl->rho = RHOsnow[snind];
		  sl = dynamic_cast<SnowLayer*>(currl);
		  sl->denmax =envpar.denmax;
		  sl->albmax =envpar.albmax;
	      sl->albmin =envpar.albmin;
		  sl->newden =envpar.newden;
			    
		  ed->d_snws.swe += currl->ice;
			
		}else{
		  break;
		}
		
		currl = currl->nextl; 
	};
	
	
}


double Snow_Env::getSublimation(double const & rn, double const & swe, double const & ta){ 
	// rn unit  W/m2,  radiation
	// swe  snow water equivlent mm
	// output sublimation mm/day
	
	double sub;
	//double sab = 0.6 ; //  radiation asorbtivity of snow, Zhuang 0.6 ?
	
	double sabsorb =0.6;
	double lamdaw = 2.501e6; // latent heat of vaporization J/kg
    double lf = 3.337e5 ;// latent heat of fusion J/kg	
    
	
  double rabs = rn * sabsorb; //W/m2
	if( swe>0. && ta<=-1){
	  double psub= rabs*86400/(lamdaw +lf);
	  if(psub>swe){
	  	sub = swe;
	  }else{
	  	sub =psub;
	  }
	}else if(swe>0. && ta>=-1){
	double pmelt= rabs*86400/( lf);
		if(pmelt>swe){
	  	sub = swe;
	  }else{
	  	sub =pmelt;
	  }
	}else{
	  sub =0.;	
	}
 
/*double rabs = rn ; //W/m2
	
	if( swe>0. && ta<=0){
	  double psub= rabs*86400/(lamdaw +lf);
	  if(psub>swe){
	  	sub = swe;
	  }else{
	  	sub =psub;
	  }
	}else if(swe>0. && ta>=0){
	double pmelt= rabs*86400/( lf);
		if(pmelt>swe){
	  	sub = swe;
	  }else{
	  	sub =pmelt;
	  }
	}else{
	  sub =0.;	
	}*/
	return sub;
};

 /*! reset diagnostic variables to initial values */
 void Snow_Env::resetDiagnostic(){
 	dztot=0.;
 	num=0; 	
 };
 
 void Snow_Env::retrieveDailyOutputs(Layer* frontl){
	
	Layer * curr2;
	double swe=0;
	
	curr2 =frontl;
    double thick =0;
    
	while(curr2!=NULL){
	  if(curr2->isSnow()){
	  	thick += curr2->dz;
	  	swe +=curr2->liq +curr2->ice;
	  }else{
	  	
	  	break;
	  }	
	 curr2 = curr2->nextl;
	}	
	
	ed->d_snws.thick =thick;
	ed->d_snws.swe =swe;
	
			
}

 
void Snow_Env::setEnvData(EnvData* edp){
	ed = edp;
};

void Snow_Env::setFirData(FirData* fdp){
	fd = fdp;
};



void Snow_Env::setCohortLookup(CohortLookup * chtlup){
  chtlu =chtlup;	
}
