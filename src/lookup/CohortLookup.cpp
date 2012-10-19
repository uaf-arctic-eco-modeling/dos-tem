
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

	float dum_burnthickmax[] = {0.1, 0.1, 0.1,  0.127};
	float dum_vegcombust[] = {0.23, 0.23,0.23, 0.23};
	float dum_vegslash[] = {0.76, 0.76,0.76, 0.76};

	float dum_matureage[]={20, 15, 120, 70};

	for (int ic =0; ic<MAX_VEG_TYPE; ic++){
		burnthick_max[ic] = dum_burnthickmax[ic];
		vegcombust[ic]    = dum_vegcombust[ic];
		vegslash[ic]      = dum_vegslash[ic];
		matureage[ic]     = dum_matureage[ic];
	}

};

void CohortLookup::assignSnowPara(){
	snwdenmax[0] = 350;//362; //from Ling and Zhang// Gray and Prowse 1993, and in WATCLASS THDavison12003a
	snwdenmax[1] = 250;
	snwdenmax[2] = 250;
	snwdenmax[3] = 250;// 250 for forest , ATPomeroy71998a

	snwdennew[0] = 120;
	snwdennew[1] = 120;
	snwdennew[2] = 120;
	snwdennew[3] = 120;

	// from atroesh42001a
	snwalbmax[0] = 0.8;
	snwalbmax[1] = 0.8;
	snwalbmax[2] = 0.8;
	snwalbmax[3] = 0.8;

	snwalbmin[0] = 0.4;
	snwalbmin[1] = 0.4;
	snwalbmin[2] = 0.4;
	snwalbmin[3] = 0.4;

};


void CohortLookup::setEnvLAI(){
	///tussock tundra
	  envlai[0][0]	=1.5;
	  envlai[0][1]	=1.5;
	  envlai[0][2]	=1.5;
	  envlai[0][3]	=2.;
	  envlai[0][4]	=2.5;
	  envlai[0][5]	=3;
	  envlai[0][6]	=3.5;
	  envlai[0][7]	=4.;
	  envlai[0][8]	=3.5;
	  envlai[0][9]	=3.;
	  envlai[0][10] =2.5;
	  envlai[0][11] =2.;
	///deciduous forest, aspen
	  envlai[1][0]	=0;
	  envlai[1][1]	=0;
	  envlai[1][2]	=0;
	  envlai[1][3]	=0.5;
	  envlai[1][4]	=0.8;
	  envlai[1][5]	=1.8;
	  envlai[1][6]	=2.5;
	  envlai[1][7]	=2.0;
	  envlai[1][8]	=1.5;
	  envlai[1][9]	=1;
	  envlai[1][10] =0;
	  envlai[1][11] =0;
	  //white spruce
	  envlai[2][0]	=1.1;
	  envlai[2][1]	=1.15;
	  envlai[2][2]	=1.2;
	  envlai[2][3]	=1.2;
	  envlai[2][4]	=1.3;
	  envlai[2][5]	=1.9;
	  envlai[2][6]	=2;
	  envlai[2][7]	=2.;
	  envlai[2][8]	=1.5;
	  envlai[2][9]	=1.3;
	  envlai[2][10] =1.15;
	  envlai[2][11] =1.1;
	  //black spruce
	  envlai[3][0]	=1.1;
	  envlai[3][1]	=1.15;
	  envlai[3][2]	=1.2;
	  envlai[3][3]	=1.2;
	  envlai[3][4]	=1.3;
	  envlai[3][5]	=1.9;
	  envlai[3][6]	=2;
	  envlai[3][7]	=2.;
	  envlai[3][8]	=1.5;
	  envlai[3][9]	=1.3;
	  envlai[3][10] =1.15;
	  envlai[3][11] =1.1;

};

void CohortLookup::assignVegetationParams(){
	// first column for ice, the value will make no difference
	// data are from tveg43d.ecd
	float dumkc[] = {400., 400., 400.,400.};
	float dumki[] = {75.0, 75.00,75.00,75.0 };
	float dumgva[] = {55.3933,55.3933, 55.3933,55.3933 };
	float dumtmin[] = {-5.0, -1.0, -1.0, -8.0 };
	float dumtoptmin[] = {5.5, 5.5, 5.5,14.2 };
	float dumtoptmax[] = {20., 20.0,20.0, 22.4};
	float dumtmax[] = {35., 35.0,35.0,  29.0};
	float dumraq10a0[] = {2.35665000, 2.35665000, 2.35665000, 2.35665000};
	float dumraq10a1[] = {-0.05307700, -0.05307700, -0.05307700,-0.05307700};
	float dumraq10a2[] = {0.00238420, 0.00238420, 0.00238420,0.00238420};
	float dumraq10a3[] = {-0.00004110, -0.00004110, -0.00004110, -0.00004110};
	float dumkn1[] = {0.0042,0.0042 ,0.0042, 0.0042};
	float dumlabncon[] = {0.2,0.2, 0.2,  0.2};
	float dumleafmxc[] = {200.5, 347.2, 630.3, 268.2 };    //Yuan: modified
	float dumkleafc[] = {1.6662, 1.6662, 1.6662,  1.6662};
	float dumsla[] = {0.0072, 0.0072, 0.0072, 0.0072 };
	float dumcov[] = {-0.01954, -0.000292, -0.0005673,-0.001571 }; //Yuan: modified, mainly for Tundra. The rest not used for other vegs.

	float dummaturefoliagemin[] = {0.5, 0.5, 0.5, 0.5 };
	//there is a positive feedback between foliage and vegc
	//so set a minimal value
	//shuhua Oct. 7, 2008
	float dumfpcmax[] = {1.00, 1.00, 1.00, 1.00};  //yuan
    float duminitleafmx[] = {1, 1, 1,  1};
	float dumc2nmin[] = {55.91, 229.13, 295.08, 216.67 };//be carefull about these two
	float dumcnmin[] = {0, 0, 0,  0};

	float dumc2na[] = {0, 0, 0,  0 };  // c2nmin = c2nb
	float dumc2nb[] = {55.91, 229.13, 295.08, 216.67};  //Yuan: modified
	float dumabv2totmass[] = { 0.60, 0.70, 0.81,  0.8};     //yuan: modified

   	float duminitcneven[] = {123.06, 27.66, 164.3,  68.08}; //yuan: modified

   	float dumcmax[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{582.7, 1384.1, 940.3, 713.6},
   	       {582.7, 1384.1, 940.3, 743.8}};  //D

   	float dumnmax[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{2.536, 6.83, 3.85, 3.06},
   	 		{2.536, 6.83, 3.85, 3.06}};    //D

    float dumcfall[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.04219, 0.00166, 0.00422,  0.003897},
    	    {0.04219, 0.00166, 0.00422, 0.003979}};//D
    float dumnfall[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.01120, 0.00757, 0.00800, 0.01017},
    	    {0.01120, 0.00757, 0.00800, 0.01038}}; //D

    float dumvegc[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{260.0, 17483, 9000, 3250},
    	    { 260.0, 17483, 9000,  4000}};//D

    float dumstrn[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{4.464, 73.25, 29.28, 14.40},
    	    {4.464, 73.25, 29.28,  17.76}};  //D

    float dumston[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.186, 3.05, 1.22, 0.600},
    	    { 0.186, 3.05, 1.22, 0.74}};

	float dumkra[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{ -8.06e-05, -8.06e-05, -8.06e-05,  -8.06e-05},
		    { -8.06e-05, -8.06e-05, -8.06e-05,  -8.06e-05}};

  	float dumkrb[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{-4.962, -4.669, -6.25,-5.06},
  	 		{-4.962, -4.669, -6.25, -5.06}};	 //D

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

	float dumminleaf[] = {0.0, 0.0, 0.5 ,0.5};
	float dumaleaf[] = {0.79640, 0.79640,0.79640, 0.42893 };
	float dumbleaf[] = {0.46635,0.46635, 0.46635 , 0.33295};
	float dumcleaf[] = {-0.02873, -0.02873,-0.02873, 0.32228};
	float dumalbvisnir[] = {0.16,0.19, 0.10, 0.10};           //from Beringer et al., 2005  (ATBeringer42005a)

    //m1, m2, m3 and m4 used for calculating f(FOLIAGE) in Zhuang et al. (2003)
	float dumm1[] = {15.206 , 38.57, 28.55, 19.62};                 //redone by Yuan (2009):tudra (not used!!!, rather using the old function), aspen, ws, dry-bs, wet-bs
	float dumm2[] = {-0.3197, -0.4509, -0.3641, -0.3999};
	float dumm3[] = {0.0401, 0.0743,0.0781, 0.1487};   
	float dumm4[] = {0.0001, 0.0001,0.0001, 0.0001};

	//boundary layer conductance (projected area basis) m/s
     float dumgl_bl[] ={0.04, 0.01, 0.08, 0.08};

    // cuticular conductance m/s
    float dumgl_c[] ={0.00001, 0.00001, 0.00001,  0.00001};

    //tundra and white spruce using black spruce
    // from ~/code/biomebgc-4.2/epc
    //float dumer[] ={0.5, 0.7, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
    float dumer[] ={0.5, 0.5, 0.5, 0.5};

    float dumircoef[] ={0.041, 0.041, 0.041,  0.041};
    float dumiscoef[] ={0.041, 0.041, 0.041,  0.041};
    float dumvpd_open[] ={930, 930, 930, 930};//pa
    float dumvpd_close[] ={4100, 4100,4100, 4100};//pa
    float dumglmax[] ={0.005, 0.005, 0.003,  0.003};//m/s

    float dumall2prj[] ={2.2, 2.0,2.6,2.6};//m/s

    float dumppfd50[] ={75, 75, 75,75};//

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
	float dumrhq10[] = {2.0, 2.0, 2.0,2.0};
	float dumkn2[] = {0.0042, 0.0042, 0.0042,  0.0042};
	float dummoistmin[] = {0.0, 0.0, 0.0, 0.0};
	float dummoistopt[] = {0.5, 0.5, 0.5,  0.5};
	float dummoistmax[] = {1.0, 1.0,1.0, 1.0};
	float dumcnsoil[] = {25.72, 17.20, 21.61,  27.34 };  //yuan: modified

	float dumlcclnc[] = {215.36, 48.38, 246.0, 83.06};   //yuan: modified

	float dumpropftos[] = {0.2, 0.2, 0.2,  0.2};
	float dumnloss[] = { 0, 0, 0, 0};

	float dumsolc[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{39462.0, 5907.0, 9940.0, 14439}, //dry
			                                     {39462, 5907.0, 9940.0,  19033}};//wet

	float dumsoln[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{1534, 326, 460.0,  548},   //dry
			                                     {1534, 326, 460.0,  671}};	//wet

	float dumavln[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.450, 1.65, 1.50,  1.00},
			                                     {0.450, 1.65, 1.50,  0.50}};
 	float dumnup[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{1.26, 1.267, 0.728, 1.48},
			 		                            {1.26, 1.267, 0.728, 1.48}};//

    float dumkdcfib[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.003216, 0.003163, 0.01211, 0.003620},
           	                                       {0.003216, 0.003163, 0.01211, 0.007223}};
    float dumkdchum[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.001895, 0.000916, 0.003525, 0.000524},
           	                                       {0.001895, 0.000916, 0.003525, 0.002085}};
    float dumkdcmin[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.0000625, 0.008032, 0.001438, 0.002716},
           	                                           {0.0000625, 0.008032, 0.001438, 0.000854}};
    float dumkdcslow[MAX_DRG_TYPE][MAX_VEG_TYPE] = {{0.00000625, 0.0008032, 0.0001438, 0.0002716},
           	                                           {0.00000625, 0.0008032, 0.0001438, 0.0000854}};

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
	float dumrootza[] = {-4.7210,-4.7210,-4.7210, 0.0};
	float dumrootzb[] = {4.1060, 4.1060, 4.1060,  -2.0875};
	float dumrootzc[] = {0.3003, 0.3003,0.3003, 2.8977};
	float dumminrootz[] = {0.3000, 0.3000, 0.3000,  0.8 };

	float dumrootmass[] = {2.9, 2.9,1.2 ,2.9};
	float dumrootbeta[] = {0.943, 0.943,0.914,0.943 };
	//I_TUNDRA, I_DF, I_WSF, I_BSF_UF, I_BSF_LF
	//second column is for balsam poplar
	//first column: data from Shaver and Billings (1975) (Yuan)
    float dum_frprod_010[] =  {15.2, 2.2, 51.95, 26.34 };
    float dum_frprod_1020[] = {30.3, 46.41, 22.42,54.57};
    float dum_frprod_2030[] = {45.5, 33.11, 11.05,13.48 };
    float dum_frprod_3040[] = {9.0, 11.59,  5.3, 2.64 };
    float dum_frprod_4050[] = {0, 2.37, 5.34, 0.6};
    float dum_frprod_5060[] = {0, 1.7,  2.97, 0.58};
    float dum_frprod_6070[] = {0, 0.87, 0.8, 1.79};
    float dum_frprod_7080[] = {0, 0.87, 0.18, 0.0};
	float dum_frprod_8090[] = {0, 0.56, 0.0,  0.0 };
    float dum_frprod_90100[]= {0, 0.33, 0.0, 0.0 };

    //float dum_rootdp4infil[]= {0.10, 0.45, 0.20, 0.25};
    float dum_rootdp4infil[]= {0.10, 0.45, 0.20, 0.20}; //july 7

    float dum_richardl[]= {0.05, 0.05, 0.10,  0.05};

    //the depth of unfrozen soil which has root.
    // for example, for black spruce,
    //if a layer (except moss, since it is assumed that there is no root in moss layer)
    //is unfrozen, or is partial unfrozen, the unfrozen part is greater than the specified value
    //then start photosynthesis
    float dum_rootdp4gpp[]= {0.01, 0.05, 0.01,  0.05};

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

/*
	//use black spruce's root as tundra's
	int fromind =2;
	int toind =0;
	  frprod_frac[toind][0]= dum_frprod_010[fromind];
	  frprod_frac[toind][1]= dum_frprod_1020[fromind];
	  frprod_frac[toind][2]= dum_frprod_2030[fromind];
	  frprod_frac[toind][3]= dum_frprod_3040[fromind];
	  frprod_frac[toind][4]= dum_frprod_4050[fromind];
	  frprod_frac[toind][5]= dum_frprod_5060[fromind];
	  frprod_frac[toind][6]= dum_frprod_6070[fromind];
	  frprod_frac[toind][7]= dum_frprod_7080[fromind];
	  frprod_frac[toind][8]= dum_frprod_8090[fromind];
	  frprod_frac[toind][9]= dum_frprod_90100[fromind];

	  fromind =1;
	  toind =1;
	  frprod_frac[toind][0]= dum_frprod_010[fromind];
	  frprod_frac[toind][1]= dum_frprod_1020[fromind];
	  frprod_frac[toind][2]= dum_frprod_2030[fromind];
	  frprod_frac[toind][3]= dum_frprod_3040[fromind];
	  frprod_frac[toind][4]= dum_frprod_4050[fromind];
	  frprod_frac[toind][5]= dum_frprod_5060[fromind];
	  frprod_frac[toind][6]= dum_frprod_6070[fromind];
	  frprod_frac[toind][7]= dum_frprod_7080[fromind];
	  frprod_frac[toind][8]= dum_frprod_8090[fromind];
	  frprod_frac[toind][9]= dum_frprod_90100[fromind];
*/

};

void CohortLookup::assignSOCParams(){

  	float dum_maxmossthick[] = {0.015, 0.0, 0.035, 0.035};
  	float dum_abvltrr2t[] = {0.5, 0.650,0.705, 0.431};
  	float dum_blwltrr2t[] = {0.5, 0.350,0.295, 0.569};// from floodplain black spruce and white spruce

	for (int ic=0; ic<MAX_VEG_TYPE; ic++){
	   maxmossthick[ic]=dum_maxmossthick[ic];
	   abvltrr2t[ic]=dum_abvltrr2t[ic];
	   blwltrr2t[ic]=dum_blwltrr2t[ic];

    }
};

void CohortLookup::assignSoilTextureParams(){

 	float dum_mossthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.0, 0.0, 0.035,  0.035 },{0.0, 0.0, 0.025,  0.035 }};
 	float dum_fibthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.04, 0.050, 0.050,  0.050},{0.04, 0.05, 0.09,  0.20 }};
 	float dum_humthick[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.1, 0.05, 0.050,  0.095},{0.10, 0.10, 0.10,  0.16 }};

	//The litter fall into fib, humic and mineral when the original org thicknesses are used
	//as kdratih2f, it will be input from file in site run mode
 	float dum_ltrfalratiom2f[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1,1,1,1},{1,1,1,1 }};
 	float dum_ltrfalratioh2f[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1,1,1,1},{1,1,1,1 }};

	float dum_coefshlwa[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.01927, 0.01927, 0.01927, 0.01927},
                                                        {0.01386, 0.01386, 0.01386, 0.01386}};
	float dum_coefshlwb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1.1247, 1.1247, 1.1247, 1.1247 },
		                                                {1.0836, 1.0836, 1.0876, 1.0876}};
	float dum_coefdeepa[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.02929, 0.02929, 0.02920, 0.02920},
		                                                {0.03616, 0.03616, 0.03616, 0.03616}};
	float dum_coefdeepb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{1.2622, 1.2622, 1.2622, 1.2622 },
		                                                {1.0802, 1.0802, 1.0802, 1.0802 }};
	float dum_coefminea[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.039693, 0.039693, 0.039693, 0.039693},
		                                                {0.04856, 0.04856, 0.04856, 0.04856}};
	float dum_coefmineb[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.0667389, 0.0667389, 0.0667389, 0.0667389},
		                                                {0.06164, 0.06164, 0.06164, 0.06164}};
    //Yuan: the following parameters are changeable, the default are from
		// Jenkinson et al, 1977, soil science 123: 298 - 305
		//    when C is respired, 1 C will produce:
		// 0.076 microbial biomass C, 0.125 physically-resistant C, 0.0035 chemically-resistant C
		// and the rest are released as CO2
	float dum_fsoma[MAX_DRG_TYPE][MAX_VEG_TYPE]  =  {{0.3717, 0.3717, 0.3717, 0.3717},
		                                             {0.3717, 0.3717, 0.3717, 0.3717}};
	float dum_fsompr[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.6112, 0.6112, 0.6112, 0.6112},
		                                             {0.6112, 0.6112, 0.6112, 0.6112}};
	float dum_fsomcr[MAX_DRG_TYPE][MAX_VEG_TYPE] =  {{0.0171, 0.0171, 0.0171, 0.0171},
		                                             {0.0171, 0.0171, 0.0171, 0.0171}};
	float dum_som2co2[MAX_DRG_TYPE][MAX_VEG_TYPE]=  {{0.2571, 0.2571, 0.2571, 0.2571},
		                                             {0.2571, 0.2571, 0.2571, 0.2571}};

 	float dum_minthick[] = {0.1 ,0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 1.0, 2.0};
 	int dum_mintype[] = {4, 4, 4, 4, 4 , 4, 4, 4, 4, 4, 4, 4, 4};

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
		mintype[ic] = dum_mintype[ic];
	}

};

void CohortLookup::assignHydroPara(){
	//it is not the aim of this study to simulate realistic hydrological processes
	//the parameters are set so that the lowland forest will have higher moisture content
	// than upland, when the precipitation are the same.

	//	float dum_psimax[]=  {-1.5e5,-1.5e4 ,-1.5e5 ,-1.5e4  };//from biomebgc
	float dum_psimax[]=  {-1.5e5,-1.5e6 ,-1.5e5 ,-1.5e7  };//
	float dum_evapmin[]=  {0.08, 0.08, 0.08, 0.08 };//
	// for baseflow

	float dum_Ds[]=  {0.5, 0.5 };//from vic
	float dum_Ws[]=  {0.5, 0.5 };//from vic//july 16

 	float dum_Dsmax[]=    { 1,0 };//from vic mm/day

    float dum_drainmax[]=    { 0.04,0 };//from vic mm/sec
    float dum_wfact[]=    { 0.3,0.3 };//from vic mm/day
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




