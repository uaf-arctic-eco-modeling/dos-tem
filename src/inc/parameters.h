/*! contains parameters for veg, and soil
 */
#ifndef PARAMETERS_H_
#define PARAMETERS_H_
struct vegpar_env{
  	float gl_bl;  //leaf boundary layer conductance m/s
  	float glmax; //maximum leaf conductance m/s
  	float gl_c; // canopy conductance 
  	float albvisnir;
	float er; // canopy light extinction coefficient
	float ircoef;//canopy interception coeff for rain
	float iscoef;//canopy interception coeff for snow
	float vpd_open; //vpd: start of conductance reduction
    float vpd_close; //vpd: complete conductance reduction
    float all2prj; //from all-sided leaf to projected lai
    float ppfd50; //ppfd for half stomata closure
    float matureage; // the age which the stand become mature (80yrs)
};

struct vegpar_cal{//depend both on gridlevel soil texture and cohort type
	float kra;
	float krb;
	float cmax;	
	float nmax;
	float cfall;
	float nfall;
	
};

struct fire_par{
	float burnthick_max;
	float vegcombust;
	float vegslash;
};

struct vegpar_bgc{  // Parameters only depend on cohort type
	float raq10a0;
	float raq10a1;
	float raq10a2;
	float raq10a3;

	float maturefoliagemin;
    float c2na;
    float c2nb;
	float c2nmin;
	float cnmin;
	
	float initcneven;
	float initleafmx;
	
	float aleaf;
	float bleaf;
	float cleaf;
	float minleaf;
	float sla;
	float leafmxc;
	float kleafc;
	float cov;

    float m1;
    float m2;
    float m3;
    float m4;

	float kn1;
	float tmin;
	float tmax;
	float toptmin;
	float toptmax;	

	float kc;
	float ki;
	float labncon;
	float abv2totmass;
};

struct soipar_env{
	
    float psimax;
    float rootmass;
	float rootbeta;
	float rootdp4infil;
	float richardl;
	float rootdp4gpp;
	
	float frprod_frac[10];
	float Ds;
	float Ws;
	float Dsmax;
	float b_infilt;
	
	float drainmax;
	float wfact;
	float evapmin;
};

struct soipar_bgc{

    float kn2;
    float moistmin;
    float moistmax;
    float moistopt;
    float rhq10;
    
    float rootza;
	float rootzb;
	float rootzc;
	float minrootz;
	float propftos;
   	float lcclnc;
    float nloss; 
    float cnsoil;
 
    float abvltrr2t;
    float blwltrr2t;
    
    float shlwa;
    float shlwb;
    
    float deepa;
    float deepb;
    
    float minea;
    float mineb;

    float maxmossthick;

    //Yuan: fraction of soil organic components produced when respiration
    float fsoma;    // active SOM
    float fsompr;   // physically-resistant SOM
    float fsomcr;   // chemically-resistant SOM
    float som2co2;  // ratio of all SOM to released CO2-C during respiration (decomposition)
};

struct soipar_cal{
	
	float nup;
    float kdcfib;
    float kdchum;
    float kdcmin;
    float kdcslow;
    
   
};

struct snwpar_env{
    float denmax;
    float albmax;
    float albmin;
    float newden;	
};

#endif /*PARAMETERS_H_*/
