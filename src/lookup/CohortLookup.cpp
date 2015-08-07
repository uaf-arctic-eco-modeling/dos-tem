
#include "CohortLookup.h"

CohortLookup::CohortLookup(){

}

CohortLookup::~CohortLookup(){

}

void CohortLookup::init(){

   assignVegetationParams();
   assignLeafParams();
   assignMicrobeParams();
   assignRootParams();
   assignSOCParams();
   assignSoilTextureParams();
   assignHydroPara();
   assignSnowPara();
   assignFirePara();
   setEnvLAI();
}

void CohortLookup::assignFirePara(){
	//I_TUNDRA, I_DF, I_WSF, I_BSF

	float dum_burnthickmax[] = {0.,0.127, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
	float dum_vegcombust[] = {0.,0.23,0.23,0.23,0.23, 0.23,0.23, 0.23};
	float dum_vegslash[] = {0.,0.76,0.76,0.76,0.76, 0.76,0.76, 0.76};

	float dum_matureage[]={0.,70.,120.,20.,20.,20.,20.,20.};

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		burnthick_max[ic] = dum_burnthickmax[ic];
		vegcombust[ic]    = dum_vegcombust[ic];
		vegslash[ic]      = dum_vegslash[ic];
		matureage[ic]     = dum_matureage[ic];
	}

};

void CohortLookup::assignSnowPara(){
	snwdenmax[0] = 0.;//362; //from Ling and Zhang// Gray and Prowse 1993, and in WATCLASS THDavison12003a
	snwdenmax[1] = 250.;//362; //from Ling and Zhang// Gray and Prowse 1993, and in WATCLASS THDavison12003a
	snwdenmax[2] = 250.;//362; //from Ling and Zhang// Gray and Prowse 1993, and in WATCLASS THDavison12003a
	snwdenmax[3] = 250.;//362; //from Ling and Zhang// Gray and Prowse 1993, and in WATCLASS THDavison12003a
	snwdenmax[4] = 350.;
	snwdenmax[5] = 350.;
	snwdenmax[6] = 350.;// 250 for forest , ATPomeroy71998a
	snwdenmax[7] = 350.;// 250 for forest , ATPomeroy71998a

	snwdennew[0] = 120.;
	snwdennew[1] = 120.;
	snwdennew[2] = 120.;
	snwdennew[3] = 120.;
	snwdennew[4] = 120.;
	snwdennew[5] = 120.;
	snwdennew[6] = 120.;
	snwdennew[7] = 120.;

	// from atroesh42001a
	snwalbmax[0] = 0.8;
	snwalbmax[1] = 0.8;
	snwalbmax[2] = 0.8;
	snwalbmax[3] = 0.8;
	snwalbmax[4] = 0.8;
	snwalbmax[5] = 0.8;
	snwalbmax[6] = 0.8;
	snwalbmax[7] = 0.8;

	snwalbmin[0] = 0.4;
	snwalbmin[1] = 0.4;
	snwalbmin[2] = 0.4;
	snwalbmin[3] = 0.4;
	snwalbmin[4] = 0.4;
	snwalbmin[5] = 0.4;
	snwalbmin[6] = 0.4;
	snwalbmin[7] = 0.4;


};


void CohortLookup::setEnvLAI(){
	///NO VEG
	  envlai[0][0]	=0.;
	  envlai[0][1]	=0.;
	  envlai[0][2]	=0.;
	  envlai[0][3]	=0.;
	  envlai[0][4]	=0.;
	  envlai[0][5]	=0.;
	  envlai[0][6]	=0.;
	  envlai[0][7]	=0.;
	  envlai[0][8]	=0.;
	  envlai[0][9]	=0.;
	  envlai[0][10] =0.;
	  envlai[0][11] =0.;
	  //black spruce
	  envlai[1][0]	=1.1;
	  envlai[1][1]	=1.15;
	  envlai[1][2]	=1.2;
	  envlai[1][3]	=1.2;
	  envlai[1][4]	=1.3;
	  envlai[1][5]	=1.9;
	  envlai[1][6]	=2.;
	  envlai[1][7]	=2.;
	  envlai[1][8]	=1.5;
	  envlai[1][9]	=1.3;
	  envlai[1][10] =1.15;
	  envlai[1][11] =1.1;
	  //white spruce
	  envlai[2][0]	=1.1;
	  envlai[2][1]	=1.15;
	  envlai[2][2]	=1.2;
	  envlai[2][3]	=1.2;
	  envlai[2][4]	=1.3;
	  envlai[2][5]	=1.9;
	  envlai[2][6]	=2.;
	  envlai[2][7]	=2.;
	  envlai[2][8]	=1.5;
	  envlai[2][9]	=1.3;
	  envlai[2][10] =1.15;
	  envlai[2][11] =1.1;
	///deciduous forest, aspen
	  envlai[3][0]	=0.;
	  envlai[3][1]	=0.;
	  envlai[3][2]	=0.;
	  envlai[3][3]	=0.5;
	  envlai[3][4]	=0.8;
	  envlai[3][5]	=1.8;
	  envlai[3][6]	=2.5;
	  envlai[3][7]	=2.0;
	  envlai[3][8]	=1.5;
	  envlai[3][9]	=1.;
	  envlai[3][10] =0.;
	  envlai[3][11] =0.;

///HG: Dynamics in tundra types from Williams et al. 2006 amd Stow et al. 2004

	///Shrub tundra
	  envlai[4][0]	=0.;
	  envlai[4][1]	=0.;
	  envlai[4][2]	=0.;
	  envlai[4][3]	=0.05;
	  envlai[4][4]	=0.143;
	  envlai[4][5]	=0.641;
	  envlai[4][6]	=0.921;
	  envlai[4][7]	=0.927;
	  envlai[4][8]	=0.534;
	  envlai[4][9]	=0.116;
	  envlai[4][10] =0.;
	  envlai[4][11] =0.;

	///Tussock tundra
	  envlai[5][0]	=0.;
	  envlai[5][1]	=0.;
	  envlai[5][2]	=0.;
	  envlai[5][3]	=0.007;
	  envlai[5][4]	=0.043;
	  envlai[5][5]	=0.398;
	  envlai[5][6]	=0.617;
	  envlai[5][7]	=0.626;
	  envlai[5][8]	=0.383;
	  envlai[5][9]	=0.087;
	  envlai[5][10] =0.;
	  envlai[5][11] =0.;

	///Wetsedge tundra
	  envlai[6][0]	=0.;
	  envlai[6][1]	=0.;
	  envlai[6][2]	=0.;
	  envlai[6][3]	=0.0;
	  envlai[6][4]	=0.011;
	  envlai[6][5]	=0.308;
	  envlai[6][6]	=0.658;
	  envlai[6][7]	=0.683;
	  envlai[6][8]	=0.345;
	  envlai[6][9]	=0.085;
	  envlai[6][10] =0.0;
	  envlai[6][11] =0.0;

	///Heath tundra
	  envlai[7][0]	=0.0;
	  envlai[7][1]	=0.0;
	  envlai[7][2]	=0.0;
	  envlai[7][3]	=0.023;
	  envlai[7][4]	=0.090;
	  envlai[7][5]	=0.405;
	  envlai[7][6]	=0.581;
	  envlai[7][7]	=0.585;
	  envlai[7][8]	=0.338;
	  envlai[7][9]	=0.073;
	  envlai[7][10] =0.0;
	  envlai[7][11] =0.0;
};

void CohortLookup::assignVegetationParams(){
	// first column for ice, the value will make no difference
	// data are from tveg43d.ecd
	float dumkc[] = {0.,400.,400.,400.,400., 400., 400.,400.};
	float dumki[] = {0.,75.0,75.0,75.0,75.0, 75.00,75.00,75.0 };
	float dumgva[] = {0.,55.3933,55.3933,55.3933,55.3933,55.3933, 55.3933,55.3933 };
	float dumtmin[] = {0.,-1.0,-1.0 ,-1.0,-8.0,-5.0,-5.0,-5.0};
	float dumtoptmin[] = {0.,15.0,5.5,5.5,5.5,5.5, 5.5, 5.5 };
	float dumtoptmax[] = {0.,22.4,20.,20.,23.,20.,20.0,20.0};
	float dumtmax[] = {0.,29.0,35.,35.,25.,35., 35.0,35.0};
	float dumraq10a0[] = {0., 2.35665000,2.35665000,2.35665000,2.35665,2.35665000, 2.35665000, 2.35665000};
	float dumraq10a1[] = {0.,-0.05307700,-0.05307700,-0.05307700,-0.053077,-0.05307700, -0.05307700, -0.05307700};
	float dumraq10a2[] = {0.,0.00238420, 0.00238420, 0.00238420,0.0023842,0.00238420,0.00238420,0.00238420};
	float dumraq10a3[] = {0.,-0.00004110, -0.00004110, -0.00004110, -0.0000411, -0.00004110, -0.00004110, -0.00004110};
	float dumkn1[] = {0.,0.0042,0.0042,0.0042,0.0042,0.0042 ,0.0042, 0.0042};
	float dumlabncon[] = {0.,0.2,0.2,0.2,0.2,0.2, 0.2,  0.2};
	float dumleafmxc[] = {0., 268.2, 630.3, 347.2,107.32,96.98,59.73,28.49 };    
	float dumkleafc[] = {0.,1.6662,1.6662,1.6662,1.6662, 1.6662, 1.6662,1.6662};
	float dumsla[] = {0.,0.0072,0.0072,0.0072,0.0135, 0.00674, 0.01208, 0.02369 };
	float dumcov[] = {0.,-0.001571, -0.0005673,-0.000292,-0.023,-2.753,-0.01954,-0.01954 }; 

	float dummaturefoliagemin[] = {0.,0.5,0.5,0.5,0.5,0.5,0.5,0.5 };
	//there is a positive feedback between foliage and vegc
	//so set a minimal value
	//shuhua Oct. 7, 2008
	float dumfpcmax[] = {1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00};  //yuan
    	float duminitleafmx[] = {1.,1.,1.,1.,1.,1.,1.,1.};
	float dumc2nmin[] = {0.,200.42, 334.88, 207.43,38.9,40.4,46.5,40.8};
	float dumcnmin[] = {0.,0.,0.,0.,0.,0.,0.,0.};
	float dumc2na[] = {0.,0.,0.,0.,0.,0.,0.,0.};  
	float dumc2nb[] = {0., 200.42, 334.88, 207.43,38.9,40.4,46.5,40.8};  
	float dumabv2totmass[] = {0., 0.64,0.87,0.80,0.60, 0.60, 0.60,  0.60};     
   	float duminitcneven[] = {0.,106.35,112.61,43.49,33.33,34.7,29.4,32.0}; 

   	float dumcmax[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,1125.0,940.3,1175.,1920.,582.7,582.7,175.0},
   	                                             {0.,743.8,940.3,1384.,1920.,582.7,582.7,175.0}};  

   	float dumnmax[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,3.06, 3.85,2.85,2.536,2.536,2.536,3.5},
   	 		                             {0.,3.06, 3.85,2.85,2.536,2.536,2.536,3.5}};    

    	float dumcfall[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,0.0030318, 0.0039595, 0.0035541,0.0062836,0.0166255,0.0098541,0.0077507},
    	                                              {0.,0.0040880, 0.0051757, 0.0037434,0.0062836,0.0166255,0.0098541,0.0077507}};
    	float dumnfall[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,0.0039994, 0.0082423, 0.0118662,0.0051331,0.0135597,0.0108968,0.0069213},
    	                                              {0.,0.0053927, 0.0107740, 0.0124981,0.0051331,0.0135597,0.0108968,0.0069213}}; 

    	float dumvegc[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,2839.,4618.,7028.,1808.,561.,459.,249.},
    	    					     {0.,2105.,4180.,6673.,1808.,561.,459.,249.}};

    	float dumstrn[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,13.6, 13.2, 32.5,44.635,13.327,9.48,5.859},
    	                                             {0.,10.1, 12.0, 30.9,44.635,13.327,9.48,5.859}};  

    	float dumston[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,0.57, 0.55, 1.36,1.86,0.555,0.395,0.244},
    	                                             {0.,0.42, 0.50, 1.29,1.86,0.555,0.395,0.244}};

	float dumkra[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0., -8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05},
		                                    {0., -8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05,-8.06e-05}};

  	float dumkrb[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0., -5.06, -6.25, -5.65,-5.009,-4.962,-4.962,-4.9},
  	 		                            {0., -5.06, -6.25, -5.627,-5.009,-4.962,-4.962,-4.9}};	 

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		kc[ic] = dumkc[ic];
		ki[ic] = dumki[ic];
		gva[ic] = dumgva[ic];
		tmin[ic] = dumtmin[ic];
		toptmin[ic] = dumtoptmin[ic];
	    	toptmax[ic] = dumtoptmax[ic];
		tmax[ic] = dumtmax[ic];
		raq10a0[ic] = dumraq10a0[ic];
		raq10a1[ic] = dumraq10a1[ic];
		raq10a2[ic] = dumraq10a2[ic];
		raq10a3[ic] = dumraq10a3[ic];
		kn1[ic] = dumkn1[ic];

		maturefoliagemin[ic] = dummaturefoliagemin[ic];
		labncon[ic] = dumlabncon[ic];
		leafmxc[ic] = dumleafmxc[ic];
		kleafc[ic] = dumkleafc[ic] ;
		sla[ic] = dumsla[ic];
		cov[ic] = dumcov[ic];
		fpcmax[ic] = dumfpcmax[ic];

		initleafmx[ic] = duminitleafmx[ic];
		c2nmin[ic] = dumc2nmin[ic];
		cnmin[ic] = dumcnmin[ic];
		c2na[ic] = dumc2na[ic];
		c2nb[ic] = dumc2nb[ic];
		initcneven[ic] = duminitcneven[ic];

		for(int id =0; id<MAX_DRG_TYPE; id++){
			initvegc[id][ic] = dumvegc[id][ic];

			initstrn[id][ic] = dumstrn[id][ic];

			initston[id][ic] = dumston[id][ic];

			kra[id][ic] = dumkra[id][ic];
			krb[id][ic] = dumkrb[id][ic];

			cmax[id][ic] = dumcmax[id][ic];
			nmax[id][ic] = dumnmax[id][ic];

			cfall[id][ic] = dumcfall[id][ic];
			nfall[id][ic] = dumnfall[id][ic];

		}

		abv2totmass[ic]= dumabv2totmass[ic];
	}

};


void CohortLookup::assignLeafParams(){


	float dumminleaf[] = {0,0.5,0.5,0.5,0.0,0.0,0.0,0.0};
	float dumaleaf[] = {0,0.42893,0.42893,0.42893,0.79640,0.79640,0.79640,0.79640};
	float dumbleaf[] = {0,0.33295,0.33295,0.33295,0.46635,0.46635,0.46635,0.46635 };
	float dumcleaf[] = {0,0.32228,0.32228,0.32228,-0.02873,-0.02873,-0.02873,-0.02873};
	float dumalbvisnir[] = {0,0.10,0.10,0.19,0.16,0.16,0.16,0.16};           //from Beringer et al., 2005  (ATBeringer42005a)

    //m1, m2, m3 and m4 used for calculating f(FOLIAGE) in Zhuang et al. (2003)
	float dumm1[] = {0.,19.62,28.55,38.57,15.206,15.206,15.206,15.206};                 //redone by Yuan (2009):tudra (not used!!!, rather using the old function), aspen, ws, dry-bs, wet-bs
	float dumm2[] = {0.,-0.3999,-0.3641,-0.4509,-0.3197,-0.3197,-0.3197,-0.3197};
	float dumm3[] = {0.,0.1487,0.0781,0.0743,0.0401,0.0401,0.0401,0.0401};
	float dumm4[] = {0.,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001};

	//boundary layer conductance (projected area basis) m/s
     	float dumgl_bl[] ={0,0.08,0.08,0.01,0.04,0.04,0.04,0.04};

    	// cuticular conductance m/s
    	float dumgl_c[] ={0,0.00001,0.00001,0.00001,0.00001, 0.00001, 0.00001,  0.00001};

    //tundra and white spruce using black spruce
    // from ~/code/biomebgc-4.2/epc
    //float dumer[] ={0.5, 0.7, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
     float dumer[] ={0,0.5,0.5,0.5,0.5, 0.5, 0.5, 0.5};

    float dumircoef[] ={0,0.041,0.041,0.041,0.041, 0.041, 0.041,  0.041};
    float dumiscoef[] ={0,0.041,0.041,0.041,0.041, 0.041, 0.041,  0.041};
    float dumvpd_open[] ={0,930,930,930,930, 930, 930, 930};//pa
    float dumvpd_close[] ={0,4100,4100,4100,4100, 4100,4100, 4100};//pa
    float dumglmax[] ={0,0.003,0.003,0.005,0.005, 0.005, 0.005,  0.005};//m/s

    float dumall2prj[] ={0,2.6,2.6,2.2,2.2, 2.0,2.2,2.2};//m/s

    float dumppfd50[] ={0,75,75,75,75, 75, 75,75};//

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		minleaf[ic] = dumminleaf[ic];
		aleaf[ic] = dumaleaf[ic];
		bleaf[ic] = dumbleaf[ic];
		cleaf[ic] = dumcleaf[ic];
		albvisnir[ic] = dumalbvisnir[ic];

		m1[ic] = dumm1[ic]; 
		m2[ic] = dumm2[ic];
		m3[ic] = dumm3[ic];
		m4[ic] = dumm4[ic];

		gl_bl[ic] = dumgl_bl[ic];
		gl_c[ic] = dumgl_c[ic];
		er[ic] = dumer[ic];
		ircoef[ic] = dumircoef[ic];
		iscoef[ic] = dumiscoef[ic];
		vpd_open[ic] = dumvpd_open[ic];
		vpd_close[ic] = dumvpd_close[ic];
		glmax[ic] = dumglmax[ic];
		all2prj[ic]=dumall2prj[ic];
		ppfd50[ic]=dumppfd50[ic];
	}

};

void CohortLookup::assignMicrobeParams(){
	// first column for ice, the value will make no difference
	// data are from tmcrv43d.ecd
	float dumrhq10[] = {0.,2.0,2.0,2.0,2.0,2.0,2.0,2.0};
	float dumkn2[] = {0.,0.0042,0.0042,0.0042,0.0042,0.0042,0.0042,0.0042};
	float dummoistmin[] = {0.,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	float dummoistopt[] = {0.,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
	float dummoistmax[] = {0.,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
	float dumcnsoil[] = {0.,18.26,17.12,16.30,24.5,24.6,20.8,24.8};  

	float dumlcclnc[] = {0.,151.9,160.9,62.13,47.61,49.54,42.01,45.69};  

	float dumpropftos[] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};
	float dumnloss[] = {0.,0.,0.,0.,0.,0.,0.,0.};

	float dumsolc[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,25452.,16415.0,15597.0,45215.4,54185.7,56012.1,34776.}, 
			                             {0.,33011.,21191.0,17771.0,45215.4,54185.7,56012.1,34776.}};

	float dumsoln[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,1483.,1009.,974.,1843.,2206.,2698.,1404.},   
			                             {0.,1704.,1179.,1071.,1843.,2206.,2698.,1404.}};	

	float dumavln[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,0.75,1.50,3.50,0.68,0.68,0.48,0.17},
			                             {0.,0.50,1.00,1.50,0.68,0.68,0.48,0.17}};

 	float dumnup[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,1.48, 0.728, 0.2,0.2,1.7,0.3,0.7},
			 		            {0.,1.48, 0.728, 1.267,0.2,1.7,0.3,0.7}};

    	float dumkdcfib[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0., 0.006237, 0.01211, 0.0144,0.008605,0.008605,0.008605,0.00136},
           	                                       {0., 0.007223, 0.01211, 0.003163,0.008605,0.008605,0.008605,0.00136}};

    	float dumkdchum[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0., 0.000955, 0.003525, 0.001152,0.0010575,0.0010575,0.0010575,0.0005},
           	                                       {0., 0.002085, 0.003525, 0.000916,0.0010575,0.0010575,0.0010575,0.0005}};

    	float dumkdcmin[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0., 0.000114, 0.001438, 0.000392,0.00002188,0.00002188,0.00002188,0.000017},
           	                                       {0., 0.000854, 0.001438, 0.008032,0.00002188,0.00002188,0.00002188,0.000017}};

    	float dumkdcslow[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.,0.000001,0.000001,0.000001,0.000001, 0.000001, 0.000001, 0.000001},
           	                                        {0.,0.000001,0.000001,0.000001,0.000001, 0.000001, 0.000001, 0.000001}};


	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		rhq10[ic] = dumrhq10[ic];
		kn2[ic] = dumkn2[ic];

		moistmin[ic] = dummoistmin[ic];
		moistopt[ic] = dummoistopt[ic];
		moistmax[ic] = dummoistmax[ic];

		cnsoil[ic] = dumcnsoil[ic];
		propftos[ic] = dumpropftos[ic];
		nloss[ic] = dumnloss[ic];
		lcclnc[ic] = dumlcclnc[ic];

		for(int id =0; id<MAX_DRG_TYPE; id++){
			initsolc[id][ic] = dumsolc[id][ic];
			initsoln[id][ic] = dumsoln[id][ic];
	    	initavln[id][ic] = dumavln[id][ic];

			nup[id][ic] = dumnup[id][ic];
			kdcfib[id][ic] = dumkdcfib[id][ic];
			kdchum[id][ic] = dumkdchum[id][ic];
			kdcmin[id][ic] = dumkdcmin[id][ic];
			kdcslow[id][ic] = dumkdcslow[id][ic];
		}

	}
};

void CohortLookup::assignRootParams(){
	// first column for ice, the value will make no difference
	// data are from tmcrv43d.ecd
	// and  see ATJackson61996a for rootmass
	float dumrootza[] = {0,0.0,-4.7210,-4.7210,-4.7210,-4.7210,-4.7210, -4.7210};
	float dumrootzb[] = {0,-2.3874,4.1060,4.1060,4.1060,4.1060, 4.1060, 4.1060};
	float dumrootzc[] = {0,2.8977, 0.3003,0.3003,0.3003,0.3003, 0.3003,0.3003};
	float dumminrootz[] = {0,0.8,0.3000,0.3000,0.3000, 0.3000, 0.3000,  0.300 };

	float dumrootmass[] = {0,2.9,1.2,2.9,2.9,2.9,2.9,2.9};
	float dumrootbeta[] = {0,0.943,0.914,0.943,0.943, 0.943,0.943,0.943 };
	//I_TUNDRA, I_DF, I_WSF, I_BSF_UF, I_BSF_LF
	//second column is for balsam poplar
	//first column: data from Shaver and Billings (1975) 
    	float dum_frprod_010[] =  {0,26.34,51.95,2.2,15.2,15.2,15.2,15.2};
    	float dum_frprod_1020[] = {0,54.57,22.42,46.41,30.3,30.3,30.3,30.3};
    	float dum_frprod_2030[] = {0,13.48,11.05,33.11,45.5,45.5,45.5,45.5};
    	float dum_frprod_3040[] = {0,2.64,5.3,11.59,9.0,9.0,9.0,9.0 };
    	float dum_frprod_4050[] = {0,2.97,5.34,2.37,0,0,0,0};
    	float dum_frprod_5060[] = {0,0,2.97,1.7,0,0,0,0};
    	float dum_frprod_6070[] = {0,0,0.8,0.87,0,0,0,0};
    	float dum_frprod_7080[] = {0,0,0.18,0.87,0,0,0,0};
	float dum_frprod_8090[] = {0,0,0,0.56,0,0,0,0};
    	float dum_frprod_90100[]= {0,0,0,0.33,0,0,0,0};
	
    	float dum_rootdp4infil[]= {0,0.20,0.20,0.45,0.10,0.10,0.10,0.10}; //july 7
    	float dum_richardl[]= {0,0.05,0.10,0.05,0.05,0.05,0.05,0.05};

   //the depth of unfrozen soil which has root.
    // for example, for black spruce,
    //if a layer (except moss, since it is assumed that there is no root in moss layer)
    //is unfrozen, or is partial unfrozen, the unfrozen part is greater than the specified value
    //then start photosynthesis
   float dum_rootdp4gpp[]= {0,0.05,0.01,0.05,0.01,0.01,0.01,0.01};

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		rootza[ic] = dumrootza[ic];
		rootzb[ic] = dumrootzb[ic];
		rootzc[ic] = dumrootzc[ic];
		minrootz[ic] = dumminrootz[ic];
		rootmass[ic] = dumrootmass[ic];
		rootbeta[ic] = dumrootbeta[ic];
		rootdp4infil[ic] = dum_rootdp4infil[ic];
		richardl[ic] = dum_richardl[ic];
		rootdp4gpp[ic] = dum_rootdp4gpp[ic];

	}
	/*! fine root production fraction is from
	 *  Alaska's Changing Boreal Forest, Chapin et al. 2006, pg 196*/
	//aspen's root use balsm's
	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
	  frprod_frac[ic][0]= dum_frprod_010[ic];
	  frprod_frac[ic][1]= dum_frprod_1020[ic];
	  frprod_frac[ic][2]= dum_frprod_2030[ic];
	  frprod_frac[ic][3]= dum_frprod_3040[ic];
	  frprod_frac[ic][4]= dum_frprod_4050[ic];
	  frprod_frac[ic][5]= dum_frprod_5060[ic];
	  frprod_frac[ic][6]= dum_frprod_6070[ic];
	  frprod_frac[ic][7]= dum_frprod_7080[ic];
	  frprod_frac[ic][8]= dum_frprod_8090[ic];
	  frprod_frac[ic][9]= dum_frprod_90100[ic];

	}

};

void CohortLookup::assignSOCParams(){

  	float dum_maxmossthick[] = {0,0.035,0.035,0.0,0.015,0.015,0.015,0.015};
  	float dum_abvltrr2t[] = {0,0.431,0.705,0.650,0.5,0.5,0.5,0.5};
  	float dum_blwltrr2t[] = {0,0.569,0.295,0.350,0.5,0.5,0.5,0.5};// from floodplain black spruce and white spruce

	for (int ic=0; ic<MAX_VEG_TYPE; ic++){
	   maxmossthick[ic]=dum_maxmossthick[ic];
	   abvltrr2t[ic]=dum_abvltrr2t[ic];
	   blwltrr2t[ic]=dum_blwltrr2t[ic];

    }
};

void CohortLookup::assignSoilTextureParams(){

  	float dum_mossthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.,0.035,0.035,0.0,0.0,0.0,0.0,0.0 },
							    {0.,0.035,0.025,0.0,0.0, 0.0, 0.0,0.0 }};
 	float dum_fibthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.,0.0514,0.0498,0.0436,0.0608,0.0896,0.1013,0.02},
							   {0.,0.1379,0.1086,0.0744,0.0608,0.0896,0.1013,0.02 }};
 	float dum_humthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.,0.0862,0.0835,0.0731,0.1141,0.1513,0.1654,0.02},
							   {0.,0.2313,0.1821,0.1248,0.1141,0.1513,0.1654,0.02 }};

	//The litter fall into fib, humic and mineral when the original org thicknesses are used
	//as kdratih2f, it will be input from file in site run mode
 	float dum_ltrfalratiom2f[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};
 	float dum_ltrfalratioh2f[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};

	float dum_coefshlwa[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.019,0.019,0.019,0.0652,0.0652,0.0652,0.0652,},
                                                            {0,0.014,0.014,0.014,0.0652,0.0652,0.0652,0.0652}};
	float dum_coefshlwb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,1.125,1.125,1.125,0.708,0.708,0.708,0.708},
		                                            {0,1.088,1.088,1.088,0.708,0.708,0.708,0.708}};
	float dum_coefdeepa[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.02920,0.02920,0.02920,0.0545,0.0545,0.0545,0.0545},
		                                            {0,0.03616,0.03616,0.03616,0.0545,0.0545,0.0545,0.0545}};
	float dum_coefdeepb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,1.2622,1.2622,1.2622,0.975,0.975,0.975,0.975 },
		                                            {0,1.0802,1.0802,1.0802,0.975,0.975,0.975,0.975 }};
	float dum_coefminea[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.1505,0.1317,0.1317,0.0966,0.0966,0.0966,0.0966},
		                                            {0,0.1505,0.1317,0.1317,0.0966,0.0966,0.0966,0.0966}};
	float dum_coefmineb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.5598,0.461,0.461,0.7851,0.8197,0.8239,0.7577},
		                                            {0,0.5598,0.461,0.461,0.7851,0.8197,0.8239,0.7577}};
    //Yuan: the following parameters are changeable, the default are from
		// Jenkinson et al, 1977, soil science 123: 298 - 305
		//    when C is respired, 1 C will produce:
		// 0.076 microbial biomass C, 0.125 physically-resistant C, 0.0035 chemically-resistant C
		// and the rest are released as CO2
	float dum_fsoma[MAX_DRG_TYPE][MAX_VEG_TYPE]  =  {{0,0.3717,0.3717,0.3717,0.3717,0.3717,0.3717,0.3717},
		                                         {0,0.3717,0.3717,0.3717,0.3717,0.3717,0.3717,0.3717}};
	float dum_fsompr[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.6112,0.6112,0.6112,0.6112,0.6112,0.6112,0.6112},
		                                         {0,0.6112,0.6112,0.6112,0.6112,0.6112,0.6112,0.6112}};
	float dum_fsomcr[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0,0.0171,0.0171,0.0171,0.0171,0.0171,0.0171,0.0171},
		                                         {0,0.0171,0.0171,0.0171,0.0171,0.0171,0.0171,0.0171}};
	float dum_som2co2[MAX_DRG_TYPE][MAX_VEG_TYPE]=  {{0,0.3,0.2571,0.2571,0.2571,0.2571,0.2571,0.2571},
		                                         {0,0.3,0.2571,0.2571,0.2571,0.2571,0.2571,0.2571}};

 	float dum_minthick[] = {0.1 ,0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 1.0, 2.0};
 	int dum_minclay[] = {13, 13, 13, 13, 13 , 13, 13, 13, 13, 13, 13, 13, 13};	//correspond to the mean percent clay of the most common texture class in AK:silty loam
 	int dum_minsand[] = {17, 17, 17, 17, 17 , 17, 17, 17, 17, 17, 17, 17, 17};	//correspond to the mean percent clay of the most common texture class in AK:silty loam
 	int dum_minsilt[] = {70, 70, 70, 70, 70 , 70, 70, 70, 70, 70, 70, 70, 70};	//correspond to the mean percent clay of the most common texture class in AK:silty loam

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
	 	for(int id =0; id<MAX_DRG_TYPE; id++){
			mossthick[id][ic] = dum_mossthick[id][ic];
			fibthick[id][ic] = dum_fibthick[id][ic];
			humthick[id][ic] = dum_humthick[id][ic];

			ltrfalratiom2f[id][ic] = dum_ltrfalratiom2f[id][ic];
			ltrfalratioh2f[id][ic] = dum_ltrfalratioh2f[id][ic];

			coefshlwa[id][ic] = dum_coefshlwa[id][ic];
			coefshlwb[id][ic] = dum_coefshlwb[id][ic];
			coefdeepa[id][ic] = dum_coefdeepa[id][ic];
			coefdeepb[id][ic] = dum_coefdeepb[id][ic];

			coefminea[id][ic] = dum_coefminea[id][ic];
			coefmineb[id][ic] = dum_coefmineb[id][ic];

			//Yuan
			fsoma[id][ic]  = dum_fsoma[id][ic];
			fsompr[id][ic] = dum_fsompr[id][ic];
			fsomcr[id][ic] = dum_fsomcr[id][ic];
			som2co2[id][ic]= dum_som2co2[id][ic];
	 	}
	}

	for(int ic =0; ic<MAX_MIN_LAY; ic++){
        	minthick[ic] = dum_minthick[ic];
		minclay[ic] = dum_minclay[ic];
		minsand[ic] = dum_minsand[ic];
		minsilt[ic] = dum_minsilt[ic];
	}

};

void CohortLookup::assignHydroPara(){
	//it is not the aim of this study to simulate realistic hydrological processes
	//the parameters are set so that the lowland forest will have higher moisture content
	// than upland, when the precipitation are the same.

	float dum_psimax[]=  {0,-1.5e7,-1.5e5,-1.5e6,-1.5e5,-1.5e5,-1.5e5,-1.5e5};//
	float dum_evapmin[]=  {0,0.08,0.08,0.08,0.08, 0.08, 0.08, 0.08 };//
	// for baseflow

	float dum_Ds[]=  {0.5, 0.5 };//from vic
	float dum_Ws[]=  {0.5, 0.5 };//from vic//july 16

 	float dum_Dsmax[]= { 1,0 };//from vic mm/day
	float dum_drainmax[]= { 0.04,0 };//from vic mm/sec

	float dum_wfact[]= { 0.3,0.3 };//from vic mm/day
	//for infiltration
	//double dum_b_infilt[] = {0.1,  0.001};

	double dum_b_infilt[] = {0.5,  0.1};//july 16


	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
        	psimax[ic] = dum_psimax[ic];
        	evapmin[ic] = dum_evapmin[ic];
	}

	for (int ic =0; ic<MAX_DRG_TYPE; ic++){
		Ds[ic] = dum_Ds[ic];
		Ws[ic] = dum_Ws[ic];
		Dsmax[ic] = dum_Dsmax[ic];
		b_infilt[ic] = dum_b_infilt[ic];
		drainmax[ic] = dum_drainmax[ic];
		wfact[ic] = dum_wfact[ic];
	}
};




