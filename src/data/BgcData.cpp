#include "BgcData.h"

BgcData::BgcData(){
	baseline =0;
	nfeed=0;
	avlnflg =0;
};

BgcData::~BgcData(){
	
};

void BgcData::init(){
	m_vegs.unnormleaf =0.0;
	prvunleafmx =0.0;//if this value is not initiated, the model will provide nan to it
	foliagemx =0.0;

	for(int il=0; il<MAX_SOI_LAY; il++){
		m_sois.reac[il]= 0.;
		m_sois.nonc[il]= 0.;
	  	m_soi2a.rrh[il]= 0.;
	  	m_soi2a.nrh[il]= 0.;
	}
	
	m_sois.wdebris =0.;
	m_vegs.deadc =0.;
	m_vegs.deadn=0.;	
};

void BgcData::beginOfMonth(const int & currmind){
	
	veg_beginOfMonth();
	soi_beginOfMonth();
};

void BgcData::beginOfYear(){
	
	y_a2soi.ninput = 0.0;
    	y_soi2l.nlost = 0.0;
      
 	y_vegs.c = 0;
 	y_vegs.ston = 0;
 	y_vegs.strn = 0;
 	y_vegs.unnormleaf = 0;
 	y_vegs.deadn = 0;
 	y_vegs.deadc = 0; 
 	y_vegd.abvgndc =0.;
 	y_v2a.rg = 0;
 	y_v2a.rm = 0;
 
 	y_v2v.nmobil =0;
 	y_v2v.nresorb = 0;
 
 	y_a2v.gpp = 0;
 	y_a2v.ingpp = 0;
 	y_a2v.npp = 0;
 	y_a2v.innpp = 0;
 
 	y_v2soi.ltrfalc = 0;
 	y_v2soi.ltrfaln = 0;
 
 	y_soi2v.innuptake =0;
 	y_soi2v.nuptake =0;
 	y_soi2v.luptake =0;
 	y_soi2v.suptake =0;
 
 	y_vegd.lai =0;
 	y_vegd.foliage =0;
 	y_vegd.fca =0;
 	y_vegd.fna=0;
 	y_vegd.fpc =0;
 	y_vegd.ftemp =0;
 	y_vegd.gv =0;
 	y_vegd.kr =0;
 	y_vegd.leaf =0;
 	y_vegd.raq10 =0;
 
 	y_sois.wdebris =0.;
 	y_soi2a.wdrh =0.;
 
 	y_soid.reacsum =0.;
 	y_soid.rrhsum =0.;
 	y_soid.noncsum =0.;
 	y_soid.nrhsum =0.;
 
 	for (int il =0; il<MAX_SOI_LAY; il++){
 		y_sois.reac[il]=0.;
 		y_sois.nonc[il]=0.;

 		y_soid.kdl[il] = 0;
 		y_soid.kdr[il] = 0;
   		y_soid.kdn[il] = 0;

   		y_soid.ksoil[il] = 0;
   		y_soid.rhmoist[il] = 0;
   		y_soid.rhq10[il] = 0;
   		y_soi2a.rrh[il] = 0;
   		y_soi2a.nrh[il] = 0;
   	
 	}
 
 	y_soid.rrhsum =0;
 	y_soid.reacsum = 0;
 	y_soid.nrhsum =0;
 	y_soid.noncsum = 0;
 
 	y_soid.shlwc= 0;
 	y_soid.deepc = 0;
 	y_soid.minec = 0;
 
 	y_sois.avln = 0;
 	y_sois.orgn = 0;
 
 	y_soi2soi.netnmin = 0;
 	y_soi2soi.nimmob = 0;
};


void BgcData::endOfMonth(const int & currmind){
 
	double vegn=0;

	if (currmind==11) {
	 	y_vegs.c = m_vegs.c;
	 	y_vegs.ston = m_vegs.ston;
	 	y_vegs.strn = m_vegs.strn;
	 	y_vegs.unnormleaf = m_vegs.unnormleaf;
	 	vegn = y_vegs.strn+y_vegs.ston;
	 	y_vegs.deadn = m_vegs.deadn;
		y_vegs.deadc = m_vegs.deadc;
	 	y_vegd.abvgndc = m_vegd.abvgndc;
	}
	
//	y_vegs.c += m_vegs.c/12.;
//	y_vegs.ston += m_vegs.ston/12.;
//	y_vegs.strn += m_vegs.strn/12.;
//	y_vegs.unnormleaf += m_vegs.unnormleaf/12.;
//	vegn = y_vegs.strn+y_vegs.ston;
//	y_vegs.deadn += m_vegs.deadn/12.;
//	y_vegs.deadc += m_vegs.deadc/12.;
//	y_vegd.abvgndc += m_vegd.abvgndc/12.;
 
 	y_v2a.rg += m_v2a.rg;
 	y_v2a.rm += m_v2a.rm;
 
 	y_v2v.nmobil += m_v2v.nmobil;
 	y_v2v.nresorb += m_v2v.nresorb;
 
 	y_a2v.gpp += m_a2v.gpp;
 	y_a2v.ingpp += m_a2v.ingpp;
 	y_a2v.npp += m_a2v.npp;
 	y_a2v.innpp += m_a2v.innpp;
	
	if (currmind==11) {
		cout <<"-- Aboveground C --"<<"\n";
		cout <<"GPP "<<y_a2v.gpp<<"\n";
		cout <<"NPP "<<y_a2v.npp<<"\n";
		cout <<"VEGC "<<y_vegs.c<<"\n";
		cout <<"INNPP "<<y_a2v.innpp<<"\n";
		cout <<"DEADC "<<y_vegs.deadc<<"\n";
	}

 	y_v2soi.ltrfalc += m_v2soi.ltrfalc;
 	y_v2soi.ltrfaln += m_v2soi.ltrfaln;
 
 	y_soi2v.innuptake +=m_soi2v.innuptake;
 	y_soi2v.nuptake +=m_soi2v.nuptake;
 	y_soi2v.luptake +=m_soi2v.luptake;
 	y_soi2v.suptake +=m_soi2v.suptake;

 	m_soid.reacsum=0.;
 	m_soid.rrhsum=0.;
 	m_soid.noncsum=0.;
 	m_soid.nrhsum=0.;
 	m_soid.shlwc=0.; m_soid.deepc=0.; m_soid.minec=0.; 
 
// 	for (int il =0; il<MAX_SOI_LAY; il++){
 	for (int il =0; il<ed->m_soid.actual_num_soil; il++){
  		m_soid.reacsum += m_sois.reac[il];	
  		m_soid.rrhsum += m_soi2a.rrh[il];	
   		m_soid.noncsum += m_sois.nonc[il];	
  		m_soid.nrhsum += m_soi2a.nrh[il];	
  
   		if(ed->m_sois.type[il]==1){
   	 		m_soid.shlwc += m_sois.reac[il]+m_sois.nonc[il];
   		} else if(ed->m_sois.type[il]==2){
   	 		m_soid.deepc += m_sois.reac[il]+m_sois.nonc[il];
   		} else if(ed->m_sois.type[il]==3){
   	 		m_soid.minec += m_sois.reac[il]+m_sois.nonc[il];
   		}
   
 	}
 	
	if (currmind==11) {
   		y_soid.shlwc = m_soid.shlwc;
   		y_soid.deepc = m_soid.deepc;
   		y_soid.minec = m_soid.minec;
	}
   	
//	y_soid.shlwc += m_soid.shlwc/12;
//   	y_soid.deepc += m_soid.deepc/12;
//   	y_soid.minec += m_soid.minec/12;

 	if (currmind==11) {
		cout <<"-- Belowground C --"<<"\n";
		cout <<"SHLWC "<<y_soid.shlwc<<"\n";
		cout <<"DEEPC "<<y_soid.deepc<<"\n";
		cout <<"MINEC "<<y_soid.minec<<"\n";
	}
  
 	for (int il =0; il<MAX_SOI_LAY; il++){
		if (currmind==11) {
			y_sois.reac[il] = m_sois.reac[il];
   			y_sois.nonc[il] = m_sois.nonc[il];
		}

//		y_sois.reac[il] += m_sois.reac[il]/12;
//  		y_sois.nonc[il] += m_sois.nonc[il]/12;
   		y_soid.kdl[il] += m_soid.kdl[il]/12;
   		y_soid.kdr[il] += m_soid.kdr[il]/12;
    		y_soid.kdn[il] += m_soid.kdn[il]/12;
   		y_soid.ksoil[il] += m_soid.ksoil[il]/12;
   		y_soid.rhmoist[il] += m_soid.rhmoist[il]/12;
   		y_soid.rhq10[il] += m_soid.rhq10[il]/12;
   		y_soi2a.rrh[il] += m_soi2a.rrh[il];
   		y_soi2a.nrh[il] += m_soi2a.nrh[il]; 	
	} 
 
	if (currmind==11) {
	   	y_sois.wdebris = m_sois.wdebris;
	 	y_soid.reacsum = m_soid.reacsum;
	 	y_soid.noncsum = m_soid.noncsum;
	 	y_sois.avln = m_sois.avln;
	 	y_sois.orgn = m_sois.orgn;
	}

//   	y_sois.wdebris += m_sois.wdebris/12.;
// 	y_soid.reacsum += m_soid.reacsum/12.;
// 	y_soid.noncsum += m_soid.noncsum/12.;
// 	y_sois.avln += m_sois.avln/12.;
// 	y_sois.orgn += m_sois.orgn/12.;

 	y_soi2a.wdrh += m_soi2a.wdrh;	
 	y_soid.rrhsum += m_soid.rrhsum;
 	y_soid.nrhsum += m_soid.nrhsum;


 	if (currmind==11) {
		cout <<"-- N cycle --"<<"\n";
		cout <<"VEGN "<<vegn<<"\n";
		cout <<"NUPTAKE "<<y_soi2v.nuptake<<"\n";
		cout <<"AVLN "<<y_sois.avln<<"\n";
		cout <<"ORGN "<<y_sois.orgn<<"\n";
		cout <<"WDEBRIS "<<y_sois.wdebris<<"\n";
		cout <<"WDRH "<<y_soi2a.wdrh<<"\n";
	}

 
 	if (baseline!=1){
 		y_a2soi.ninput += m_a2soi.ninput;  //Yuan
 		y_soi2l.nlost += m_soi2l.nlost;    //Yuan
 	}
 	
 	y_soi2soi.netnmin += m_soi2soi.netnmin;
 	y_soi2soi.nimmob += m_soi2soi.nimmob;
 
  	y_vegd.lai += m_vegd.lai/12;
 	y_vegd.foliage += m_vegd.foliage/12;
 	y_vegd.fca += m_vegd.fca/12;
 	y_vegd.fna+= m_vegd.fna/12;
 	y_vegd.fpc += m_vegd.fpc/12;
 	y_vegd.ftemp+= m_vegd.ftemp/12;
 	y_vegd.gv += m_vegd.gv/12;
 	y_vegd.kr+= m_vegd.kr/12;
 	y_vegd.leaf+= m_vegd.leaf/12;
 	y_vegd.raq10+= m_vegd.raq10/12;

  	if (currmind==11) {
		cout <<"LAI "<<y_vegd.lai<<"\n";
	}
};


void BgcData::endOfYear(const double & cnsoil){

	//see EnvData::endOfYear
	toptque.push_back(topt);
	unleafmxque.push_back(unleafmx);
	if(toptque.size()>10){
	  toptque.pop_front();	
	}
	if(unleafmxque.size()>10){
	  unleafmxque.pop_front();	
	}
	
	int numrec = toptque.size();
	int validopt =0;
	int validunleafmx =0;
	
	double sumopt=0;
	double sumunleafmx=0;
	for(int i=	0; i<numrec; i++){
	  	if(toptque[i]>0){
	  		validopt++;
	  		sumopt+=toptque[i];
	  	}
	  	if(unleafmxque[i]>0){
	  		validunleafmx++;
	  		sumunleafmx+=unleafmxque[i];
	  	}
	}
	if(validopt>0){
	  	prvtopt = sumopt/validopt;	
	}
	if(validunleafmx>0){
	  	prvunleafmx = sumunleafmx/validunleafmx;	
	}

   	//need to balance soil org. N, if switched on
   	if (baseline == 1 ) {
		int numsl = ed->m_soid.actual_num_soil;
		double allreac, allnonc, allorgc;

		//Because soil N is estimated for the rooting zone only, 
		//the orgn adkjustment should be computed with soil C summed 
		//over the rooting zone only and not the entire 1m profile...

		 for (int il =0; il<numsl; il++){
	 	 	if(ed->m_sois.rootfrac[il]>0.01){
	   			allreac += m_sois.reac[il];	
	   			allnonc += m_sois.nonc[il];	
	 	 	}
	 	}
    		allorgc = allreac + allnonc;
      		if ( allorgc/cnsoil >= m_sois.orgn ) {
      			y_a2soi.ninput = (allorgc/cnsoil) -m_sois.orgn ;
      		} else {
      			y_soi2l.nlost = m_sois.orgn - (allorgc/cnsoil);
      		}
      		m_sois.orgn =allorgc/cnsoil;   	
//	cout << "cnsoil: " << cnsoil <<"\n";
    	}
};

/////////////////private functions ////////////////
void BgcData::veg_beginOfMonth(){
	
};

void BgcData::soi_beginOfMonth(){

};

void BgcData::setEnvData(EnvData* edp){
  	ed = edp;	
};





