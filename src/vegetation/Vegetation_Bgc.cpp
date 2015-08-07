#include "Vegetation_Bgc.h"

Vegetation_Bgc::Vegetation_Bgc(){
	dc2n = 0.000519;
	//increase of c:n = 0.176 if the nitrogen of veg is decreased by 15% per doubling of co2
	
	//proportional change in c:n per change co2
	//0.15 increase in C:N with double co2
	
};

Vegetation_Bgc::~Vegetation_Bgc(){
	
};

/*! this method is called only once when a new cohort is created*/
void Vegetation_Bgc::initializeParameter(const int & drgtypep, const int & vegtypep){
	
	int drgtype = drgtypep;
	int vegtype = vegtypep;

  	bgcpar.raq10a0 = chtlu->raq10a0[vegtype];
  	bgcpar.raq10a1 = chtlu->raq10a1[vegtype];
  	bgcpar.raq10a2 = chtlu->raq10a2[vegtype];
  	bgcpar.raq10a3 = chtlu->raq10a3[vegtype];
  
	bgcpar.maturefoliagemin = chtlu->maturefoliagemin[vegtype];
  
  	bgcpar.aleaf = chtlu->aleaf[vegtype];
  	bgcpar.bleaf = chtlu->bleaf[vegtype];
  	bgcpar.cleaf = chtlu->cleaf[vegtype];
  	bgcpar.minleaf = chtlu->minleaf[vegtype];
  	
 	bgcpar.m1 = chtlu->m1[vegtype]; 
  	bgcpar.m2 = chtlu->m2[vegtype];
  	bgcpar.m3 = chtlu->m3[vegtype];
  	bgcpar.m4 = chtlu->m4[vegtype];
  
  	bgcpar.sla = chtlu->sla[vegtype];
  	bgcpar.leafmxc = chtlu->leafmxc[vegtype];
  	bgcpar.kleafc = chtlu->kleafc[vegtype];
  	bgcpar.cov = chtlu->cov[vegtype];
  
  	bgcpar.kc= chtlu->kc[vegtype];
  	bgcpar.ki =chtlu->ki[vegtype];
  	bgcpar.kn1 = chtlu->kn1[vegtype];
  	bgcpar.tmin = chtlu->tmin[vegtype];
  	bgcpar.tmax = chtlu->tmax[vegtype];
  	bgcpar.toptmax = chtlu->toptmax[vegtype];
  	bgcpar.toptmin = chtlu->toptmin[vegtype];
  	bgcpar.labncon = chtlu->labncon[vegtype];
  
  	bgcpar.initleafmx = chtlu->initleafmx[vegtype];
  	bgcpar.c2nmin = chtlu->c2nmin[vegtype];
  	bgcpar.cnmin = chtlu->cnmin[vegtype];
  
  	bgcpar.c2na = chtlu->c2na[vegtype];
  	bgcpar.c2nb = chtlu->c2nb[vegtype];
  	bgcpar.initcneven = chtlu->initcneven[vegtype];
  	bgcpar.abv2totmass = chtlu->abv2totmass[vegtype];
  	cneven = bgcpar.initcneven;
	bd->c2n= bgcpar.initcneven;
 
  	calpar.kra = chtlu->kra[drgtype][vegtype];
  	calpar.krb = chtlu->krb[drgtype][vegtype];
  	calpar.cmax = chtlu->cmax[drgtype][vegtype];
  	calpar.nmax = chtlu->nmax[drgtype][vegtype];
  	calpar.cfall = chtlu->cfall[drgtype][vegtype];
  	calpar.nfall = chtlu->nfall[drgtype][vegtype];
	
};

/*! this method is called only once when a new cohort is created*/
void Vegetation_Bgc::initializeState(const int & drgtypep, const int & vegtypep){
	
	int drgtype = drgtypep;
	int vegtype = vegtypep;

	bd->m_vegs.c = chtlu->initvegc[drgtype][vegtype];
    	bd->m_vegs.strn = chtlu->initstrn[drgtype][vegtype];
    	bd->m_vegs.ston = chtlu->initston[drgtype][vegtype];
	bd->m_vegs.deadc =0;
	bd->m_vegs.deadn =0;
	bd->m_vegd.lai =0.1;
//	bd->m_vegs.standingc =0;
};

//Yuan: better not to read in netcdf file data here
void Vegetation_Bgc::initializeState5restart(RestartData *resin){
 	bd->m_vegs.c    = resin->vegc; //resin->getVEGC(bd->m_vegs.c, fd->cd->reschtid);
 	bd->m_vegs.strn = resin->strn; //resin->getSTRN(bd->m_vegs.strn, fd->cd->reschtid);
 	bd->m_vegs.ston = resin->ston; //resin->getSTON(bd->m_vegs.ston, fd->cd->reschtid);
 	bd->m_vegs.deadc = resin->deadc; //resin->getDEADC(bd->m_vegs.deadc, fd->cd->reschtid);
 	bd->m_vegs.deadn = resin->deadn; //resin->getDEADN(bd->m_vegs.deadn, fd->cd->reschtid);
 	bd->m_vegs.unnormleaf = resin->unnormleaf; //resin->getUNNORMLEAF(bd->m_vegs.unnormleaf, fd->cd->reschtid);

 	bd->prvunleafmx = resin->prvunnormleafmx; //resin->getPRVUNNORMLEAFMX(bd->prvunleafmx, fd->cd->reschtid);
 	bd->prvtopt     = resin->prvtopt; //resin->getPRVTOPT(bd->prvtopt, fd->cd->reschtid);
 	bd->c2n         = resin->c2n; //resin->getC2N(bd->c2n, fd->cd->reschtid);
 	bd->foliagemx   = resin->foliagemx; //resin->getFOLIAGEMX(bd->foliagemx, fd->cd->reschtid);

 	bd->topt        = bd->prvtopt;
	bd->unleafmx    = bd->prvunleafmx; 	
 
 	bd->m_vegd.lai  = resin->lai; //resin->getLAI(bd->m_vegd.lai, fd->cd->reschtid);
 
 	double topta[10];
	double unleafmxa[10];
	
	for(int i=0; i<10; i++){
	 	topta[i] = resin->toptA[i]; //resin->getTOPTA(topta, ed->cd->reschtid);
		if(topta[i]>0){
	 		bd->toptque.push_back(topta[i]);
		}

		unleafmxa[i] = resin->unnormleafmxA[i]; //resin->getUNNORMLEAFMXA(unleafmxa, ed->cd->reschtid);
		if(unleafmxa[i]>0){
	 		bd->unleafmxque.push_back(unleafmxa[i]);
		}
	 	
	}
	
};
 
/*! this method is called once a month, before integration*/

void Vegetation_Bgc::prepareIntegration(const bool & equil ){
	//calculate some variables that are constant through out the integration
	nfeed = bd->nfeed;
	avlnflg = bd->avlnflg;
	equiled = equil;
	
	double pet = ed->m_l2a.pet;
    	double eet = ed->m_l2a.eet;
  	if (pet==0.0) pet = 0.0001;    //Yuan: to avoid gv=NaN
	bd->m_vegd.gv = getGV(eet,  pet);
	
	//assign states to temporary state variable
	tmp_vegs.c = bd->m_vegs.c;
	tmp_vegs.ston = bd->m_vegs.ston;
	tmp_vegs.strn = bd->m_vegs.strn;
	tmp_vegs.unnormleaf = bd->m_vegs.unnormleaf;
	
	bd->m_vegd.ftemp = getTempFactor4GPP(ed->m_atms.ta);
//	cout << "ed->m_atms.ta in vegetation_bgc: "<< ed->m_atms.ta << "\n";
	bd->m_vegd.raq10 = getRaq10(ed->m_atms.ta);
	
};

void Vegetation_Bgc::afterIntegration(){
 	bd->m_vegd.abvgndc = bgcpar.abv2totmass * bd->m_vegs.c;
	
};

void Vegetation_Bgc::delta(){

	/// some environment variables
	double co2 = ed->m_atms.co2;
	double par = ed->m_a2l.par;
	//double pet = ed->m_l2a.pet;
	double eet = ed->m_l2a.eet;
//cout << "ed->m_l2a.eet: "<<ed->m_l2a.eet<<"\n";  	
//cout << "par: "<<par<<"\n";  	
//cout << "bd->m_vegd.leaf: "<<bd->m_vegd.leaf<<"\n"; 
//cout << "bd->m_vegd.foliage: "<< bd->m_vegd.foliage<<"\n"; 


	double tempunnormleaf; 
    	tempunnormleaf = getUnnormleaf(ed->prveetmx, eet, tmp_vegs.unnormleaf);
   	del_vegs.unnormleaf = tempunnormleaf - tmp_vegs.unnormleaf;
  	bd->m_vegd.leaf = getLeaf(tempunnormleaf);
  
  	if(bd->cd->vegtype>3){
  		double alleaf =bgcpar.leafmxc/(1.0 +bgcpar.kleafc * exp( bgcpar.cov* tmp_vegs.c ));
     		bd->m_vegd.foliage = alleaf /bgcpar.leafmxc;
 	} else {
  	 	bd->m_vegd.foliage = getFoliage();
  	}

  	bd->m_vegd.lai = bgcpar.sla *bgcpar.leafmxc*bd->m_vegd.foliage* bd->m_vegd.leaf ;

  	bd->m_vegd.fpc = 1.0 - exp( -0.5 * bd->m_vegd.lai);

  	del_a2v.ingpp = getGPP(co2, par, bd->m_vegd.leaf, bd->m_vegd.foliage, bd->m_vegd.ftemp, bd->m_vegd.gv);             
//cout << "co2: "<<co2<<"\n";  	
//cout << "par: "<<par<<"\n";  	
//cout << "bd->m_vegd.leaf: "<<bd->m_vegd.leaf<<"\n"; 
//cout << "bd->m_vegd.foliage: "<< bd->m_vegd.foliage<<"\n"; 
//cout << "bd->m_vegd.ftemp: "<<bd->m_vegd.ftemp<<"\n"; 
//cout << "bd->m_vegd.gv: "<<bd->m_vegd.gv<<"\n"; 



  	del_soi2v.innuptake =sb->getNuptake(bd->m_vegd.foliage, bd->m_vegd.raq10, bgcpar.kn1, calpar.nmax);

   	if ( del_soi2v.innuptake< 0.0 ) { del_soi2v.innuptake = 0.0; }
  
  	del_v2soi.ltrfalc = calpar.cfall * tmp_vegs.c;
  	if(del_v2soi.ltrfalc<0.) del_v2soi.ltrfalc=0.;
  	del_v2soi.ltrfaln = calpar.nfall * tmp_vegs.strn;
  	if(del_v2soi.ltrfaln<0.) del_v2soi.ltrfaln=0.;
  
  	bd->m_vegd.kr = getKr(tmp_vegs.c);
  	del_v2a.rm = getRm(tmp_vegs.c, bd->m_vegd.raq10, bd->m_vegd.kr);
  	del_a2v.innpp = del_a2v.ingpp - del_v2a.rm;
  
  	del_v2a.rg = 0.;
  	if ( del_a2v.innpp > 0.0 ){
    	del_v2a.rg = 0.25 * del_a2v.innpp;
    	del_a2v.innpp *= 0.75;
  	}
 
  	/// need to put the following lines here
  	/// since in the deltanfeed del_a2v.npp is used
  	del_soi2v.nuptake = del_soi2v.innuptake;
  	del_soi2v.suptake = del_soi2v.nuptake;
  	del_soi2v.luptake = 0.0;
  	del_a2v.gpp = del_a2v.ingpp;
  	del_a2v.npp = del_a2v.innpp;
  	del_v2v.nmobil = 0.0;
  	del_v2v.nresorb = 0.0;
 
};


void Vegetation_Bgc::deltanfeed(){
	 //////// nitrogen feedback
  	if(nfeed ==1){
	  	if(del_soi2v.innuptake ==0.0) del_soi2v.innuptake =0.000001;
	  	
	  	double inprodcn = del_a2v.innpp / (del_soi2v.innuptake + tmp_vegs.ston);
	  	
	  	if(del_v2soi.ltrfaln <= del_v2soi.ltrfalc/cneven){
	  		del_v2v.nresorb = del_v2soi.ltrfalc/cneven - del_v2soi.ltrfaln;
	  	}else{
	  		del_v2soi.ltrfaln = del_v2soi.ltrfalc/cneven;
	  		del_v2v.nresorb =0.;
	  	}
	  
	  	if(tmp_vegs.c>0.){
	  		del_v2v.nresorb  *= tmp_vegs.strn/tmp_vegs.c  *bd->c2n;
	  	}
	  
	  	if(inprodcn > cneven){//cneven is corresponding to Pcn in ATMcGuire71992a P106
	  	  	del_a2v.npp = cneven * (del_soi2v.nuptake +tmp_vegs.ston);
	      		if (del_a2v.npp > 0.0) { 
	      			del_v2a.rg = 0.25 * del_a2v.npp;
	      		} else {
	      			del_v2a.rg = 0.0;
	      		}
	   
	      		del_a2v.gpp = del_a2v.npp + del_v2a.rg + del_v2a.rm;
	      		if (del_a2v.gpp < 0.0) { del_a2v.gpp = 0.0; }
	      		del_v2v.nmobil = tmp_vegs.ston;
	  	} else {
	  	   	del_soi2v.nuptake = del_soi2v.innuptake*(inprodcn-bgcpar.cnmin)*(inprodcn-2*cneven+bgcpar.cnmin);
	       		del_soi2v.nuptake /= ((inprodcn - bgcpar.cnmin)* (inprodcn - 2*cneven+ bgcpar.cnmin)) - pow( inprodcn- cneven,2.0 );

	      		if ( del_soi2v.nuptake< 0.0 ) {del_soi2v.nuptake = 0.0; }
	      		if ( tmp_vegs.ston>= del_a2v.npp/cneven ){
				del_v2v.nmobil = del_a2v.npp/cneven;
				if ( del_v2v.nmobil < 0.0 && tmp_vegs.c > 0.0 ){
		  				del_v2v.nmobil *= (tmp_vegs.strn/tmp_vegs.c) * bd->c2n;
				}
				del_soi2v.suptake = 0.0;
	      		} else {
				del_v2v.nmobil = tmp_vegs.ston;
				del_soi2v.suptake = (del_a2v.npp/cneven) - del_v2v.nmobil;
				if ( del_soi2v.suptake < 0.0 ) { del_soi2v.suptake = 0.0; }
				if (del_soi2v.suptake > del_soi2v.nuptake) {
		  			del_soi2v.suptake = del_soi2v.nuptake;
				}
	      		}

	      		if ( (tmp_vegs.ston+del_soi2v.nuptake-del_soi2v.suptake+del_v2v.nresorb-del_v2v.nmobil) < (bgcpar.labncon*(tmp_vegs.strn+del_soi2v.suptake-del_v2soi.ltrfaln-del_v2v.nresorb+del_v2v.nmobil)) ) {
				del_soi2v.luptake = del_soi2v.nuptake - del_soi2v.suptake;
	      		} else {
				del_soi2v.luptake = (bgcpar.labncon * (tmp_vegs.strn+del_soi2v.suptake-del_v2soi.ltrfaln-del_v2v.nresorb + del_v2v.nmobil))-(tmp_vegs.ston+del_v2v.nresorb-del_v2v.nmobil);
		   		if ( del_soi2v.luptake < 0.0 ) { del_soi2v.luptake = 0.0; }
		     		del_soi2v.nuptake = del_soi2v.suptake + del_soi2v.luptake;
	       		}
	    	}
  	}
};

void Vegetation_Bgc::deltastate(){
  	del_vegs.c = del_a2v.gpp- del_v2a.rg - del_v2a.rm - del_v2soi.ltrfalc;

//cout << "del_a2v.gpp: "<< del_a2v.gpp <<"\n";
//cout << "del_v2a.rg: "<< del_v2a.rg <<"\n";
//cout << "del_v2a.rm: "<< del_v2a.rm <<"\n";
//cout << "del_v2soi.ltrfalc: "<< del_v2soi.ltrfalc <<"\n";

  	if(tmp_vegs.c + del_vegs.c <0) {
  	 // del_vegs.c = - tmp_vegs.c +0.1;
  	}
  
  	if(nfeed==1){
  		del_vegs.strn = del_soi2v.suptake- del_v2soi.ltrfaln - del_v2v.nresorb
                    + del_v2v.nmobil;

  		del_vegs.ston= del_soi2v.luptake + del_v2v.nresorb - del_v2v.nmobil;
  
  		if(tmp_vegs.strn + del_vegs.strn <0) {
  	  		//del_vegs.strn = - tmp_vegs.strn +0.1;
  		}
  
  		if(tmp_vegs.ston + del_vegs.ston <0) {
  	  		//del_vegs.ston = - tmp_vegs.ston +0.01;
  		}
  
  	}
  
};

/////////////////////////////////////////
/// private functions
/////////////////////////////////////////
double Vegetation_Bgc::getFoliage( ){
  	double foliage =0;
	 //from Zhuang et al., 2003
  	double m1 = bgcpar.m1; //15.206 ;
  	double m2 = bgcpar.m2; //-0.3197;
  	double m3 = bgcpar.m3; //0.0401;
  	double m4 = bgcpar.m4; //0.0001;
  	double vegc = tmp_vegs.c;
  
  	if(vegc<0) vegc =0;
  	double fcv = m3*vegc /(1+m4*vegc);
  	foliage =  1./(1+m1*exp(m2*sqrt(fcv)));
  
  	if(!equiled){
  	//for equilibrium run, //same as calibration
   		if(fd->ysf>=70){
  	  		if(foliage<bgcpar.maturefoliagemin){
  	  	  		foliage = bgcpar.maturefoliagemin;
  	  		}
   		}
  	}
  	
    //it is assumed that foliage will not go down during growth
  	if(foliage>bd->foliagemx){
 		bd->foliagemx = foliage;
  	}else{
 		foliage = bd->foliagemx;  
  	} 
//cout << "vegc: "<< vegc <<"\n"; 	
//cout << "fcv: "<< fcv <<"\n"; 	
//cout << "bgcpar.maturefoliagemin: "<< bgcpar.maturefoliagemin <<"\n"; 	
//cout << "bd->foliagemx: "<< bd->foliagemx <<"\n"; 	

  	return foliage;
};

double Vegetation_Bgc::getUnnormleaf(double &prveetmx, const double & eet, const double & prvunleaf){
  	double normeet;	//prvunleaf is the unleaf from last delta
                    //prveetmx is eetmx of previous simulation period ?
  	double unnormleaf;
  	if (prveetmx <= 0.0) { prveetmx = 1.0; }
  	normeet = eet / prveetmx;
  	if(normeet>1) normeet =1;
  	unnormleaf = (bgcpar.aleaf* normeet) + (bgcpar.bleaf * prvunleaf) + bgcpar.cleaf;
  	if (unnormleaf < (0.5 * bgcpar.minleaf)) {
    		unnormleaf = 0.5 * bgcpar.minleaf;
  	}

//cout << "eet: "<< eet <<"\n";
//cout << "prveetmx: "<< prveetmx <<"\n";
//cout << "bgcpar.aleaf: "<< bgcpar.aleaf <<"\n";
//cout << "bgcpar.bleaf: "<< bgcpar.bleaf <<"\n";
//cout << "bgcpar.cleaf: "<< bgcpar.cleaf <<"\n";
//cout << "bgcpar.minleaf: "<< bgcpar.minleaf <<"\n";

  	return unnormleaf;
};

double Vegetation_Bgc::getLeaf(const double & unnormleaf ){
	//leaf is normalized leaf  0~1
	//f(phenology) in gpp calculation
  	double leaf;
  	if ( bd->prvunleafmx <= 0.0 ) { 
  	 	leaf = 0.0; 
  	} else {
  	 	leaf= unnormleaf/bd->prvunleafmx ;
   	}
  
  	if ( leaf < bgcpar.minleaf ){
    		leaf = bgcpar.minleaf;
  	} else  if (leaf > 1.0 ) {
   		leaf = 1.0; 
   	}

//cout << "bd->prvunleafmx: "<< bd->prvunleafmx <<"\n";
//cout << "unnormleaf: "<< unnormleaf <<"\n";
 	
  	return leaf;

};


double Vegetation_Bgc::getGV(const double & eet,const double & pet ){
  	double gv;
  
    if ( eet/pet <= 0.1 ){
      	gv = (-10.0 * pow( (eet/pet),2.0 ))
           	+ (2.9 * (eet/pet));
      	if ( gv < 0.0 ) { gv = 0.0; }
    } else {
      	gv = 0.1 + (0.9 * eet / pet);
    }
  	if(gv>1) gv =1;

  	return gv;	
};

/*! par : photosynthetically active radiation in J/(m2s)
 */
double  Vegetation_Bgc::getGPP(const double &co2, const double & par,const double &leaf, const double & foliage,const double &ftemp, const double & gv) {
	// origianlly the 
  	double ci  = co2 * gv;
  	double thawpcnt = ed->m_soid.growpct;
  	double fpar = par/(bgcpar.ki +par);
  	double gpp = calpar.cmax * foliage * ci / (bgcpar.kc + ci);

  	gpp *= leaf * fpar;
  	gpp *= ftemp;
  	gpp *= thawpcnt;
  	if(gpp<0)gpp=0.;

  	return gpp;
}; 

double  Vegetation_Bgc::getRm(const double & vegc, const double & raq10, 
   const double &kr) {
  	
  	double respq10 = raq10;
  	double rm ;
  	
  	rm = kr * vegc;
  	rm *= respq10;
	if (rm< 0.0 ) { rm= 0.0; }
 	return rm;

};


// for each vegetation in a cohort, there should be
// only one set of parameters
// these parameters can be changed during calibration
// and the parameters derived from these input parameters
// need to be updated

double Vegetation_Bgc::getKr(const double & vegc){
	// kr is for calculating maintainance respiration
  	double kr;
  	double kra = calpar.kra;
  	double krb = calpar.krb;
//  cout << "kra: "<< kra <<"\n";
//  cout << "krb: "<< krb <<"\n";
  	kr = exp((kra*vegc)+krb);	
  	return kr;
}


double Vegetation_Bgc::getRaq10(const double & tair){
  	double raq10;
  	double raq10a0 = bgcpar.raq10a0;
  	double raq10a1 = bgcpar.raq10a1;
  	double raq10a2 = bgcpar.raq10a2;
  	double raq10a3 = bgcpar.raq10a3;
  
  	double q10 = raq10a0+ (raq10a1*tair)
          + (raq10a2*pow( tair,2.0 ))
          + (raq10a3*pow( tair,3.0 ));
  	raq10 = pow( q10,tair/10.0 );
 	// if(isnan(raq10)){
  	//	cout <<"raq10 is nan\n";
 	// 	exit(-1);
 	// }
  	return raq10;
};


double Vegetation_Bgc::getTempFactor4GPP(const double & tair){
  	double ftemp;
  	double tmin = bgcpar.tmin;
  	double toptmax = bgcpar.toptmax;
  	double tmax = bgcpar.tmax;  	
  	double tgppopt = bd->prvtopt; //previous using bd->topt
  	if ( tair <=tmin|| tair >=tmax ){
    	ftemp = 0.0;
  	} else {
    	if ( tair >= tgppopt && tair <= toptmax ){
      		ftemp = 1.0;
    	} else {
      		if (tair >tmin && tair< tgppopt ) {
				ftemp = (tair-tmin)*(tair-tmax)
               			/((tair-tmin)*(tair-tmax)
               				- pow( (tair-tgppopt),2.0 ));
      		} else {
				ftemp = (tair-tmin)*(tair-tmax)
               			/((tair-tmin)*(tair-tmax)
              				- pow( (tair-toptmax),2.0 ));
      		}
    	}
  	}
  
  	return ftemp;
};


//at end of each month
void Vegetation_Bgc::updateToptUnleafmx(const int & currmind){

    if(currmind==0){
      bd->topt = ed->m_atms.ta;
      bd->unleafmx = bd->m_vegs.unnormleaf;	
    }else{

       if(bgcpar.aleaf==0 && bgcpar.bleaf==0&& bgcpar.cleaf==1){
       	//in this case unnormleaf will not change over time
       	  if(ed->m_atms.ta> bd->topt){
       	  	 bd->topt = ed->m_atms.ta;
       	  }
       }else{
          if ( bd->m_vegs.unnormleaf > bd->unleafmx ) {
				bd->unleafmx = bd->m_vegs.unnormleaf;
	            bd->topt = ed->m_atms.ta; 
      	  }
       }
       	
   } 
   
   if ( bd->topt > bgcpar.toptmax ) { 
      	 bd->topt = bgcpar.toptmax; 
   }
      
   if ( bd->topt < bgcpar.toptmin ) { 
      	 bd->topt = bgcpar.toptmin; 
   }
	
}

void Vegetation_Bgc::adapt(){ //at end of bgc year

      // Determine vegetation C/N parameter as a function 
      // of vegetation type, annual PET, annual EET, 
      // CO2 concentration

      updateC2N( ed->y_l2a.eet, ed->y_l2a.pet  , ed->initco2, ed->y_atms.co2 );
}
///////////////////////////
// set outside pointer
//////////////////////////

void Vegetation_Bgc::updateC2N(const double & yreet,const double & yrpet, 
  const double & initco2,const double & currentco2 ) {
  
  	double c2na = bgcpar.c2na; 
  	double c2nb = bgcpar.c2nb;
  	double c2nmin = bgcpar.c2nmin;
  	double initcneven = bgcpar.initcneven ;
  
  	if (yrpet != 0.0){
    	bd->c2n = c2nb + c2na*(yreet/yrpet); //only for the grassland
  	} else { 
  		bd->c2n = c2nb; 
  	}

  	if (bd->c2n < c2nmin) { bd->c2n = c2nmin; }
  
  	double adjc2n = 1.0 + (dc2n * (currentco2 - initco2));
  	bd->c2n *= adjc2n;
  	cneven = initcneven* adjc2n;

};

void Vegetation_Bgc::setCohortLookup(CohortLookup* chtlup){
  	 chtlu = chtlup;
};

void Vegetation_Bgc::setEnvData(EnvData* edp){
  	 ed = edp;
};
  
void Vegetation_Bgc::setBgcData(BgcData* bdp){
  	 bd =bdp;
}

void Vegetation_Bgc::setSoilBgc(Soil_Bgc * sbp){
  	 sb = sbp;
};

void Vegetation_Bgc::setFirData(FirData* fdp){
  	 fd =fdp;
};
