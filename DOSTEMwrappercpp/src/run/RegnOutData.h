#ifndef REGNOUTDATA_H_
#define REGNOUTDATA_H_
/* 
 * define output variables for regional TEM run
 * memory consumption too much, so modified as output year by year
 *  rather than cohort by cohort - Yuan
 */

class RegnOutData{
	
	public:
   
		RegnOutData();
		~RegnOutData();

		int chtid;
	  	int status;
	  	float ysf;

	  	int outvarlist[54];  // switches for a list of following variables. read in from a .txt file
	  	                     // 0 - not output; 1 - yearly; 2 - monthly;

	  	// Yuan: yearly output variables (if set monthly, it's always same value)
		float burnthick;
	 	float burnsoic;
	 	float burnvegc;

	 	float growstart;
		float growend;
		float perm;

		float mossdz;
		float shlwdz;
		float deepdz;
	 
	 	//Yuan: variables are in monthly, so when yearly output needed, it's in [0]
    	float lai[12];    //Yuan: monthly
	  	float vegc[12];   //Yuan: monthly
    	float vegn[12];   //Yuan: monthly
	 	float gpp[12];    //Yuan: monthly
     	float npp[12];    //Yuan: monthly
	 	float rh[12];     //Yuan: monthly
	 
    	float ltrfalc[12];   //Yuan: monthly
       	float ltrfaln[12];   //Yuan: monthly

	  	float shlwc[12];       //Yuan: monthly;;
	  	float deepc[12];       //Yuan: monthly;;
	  	float minec[12];       //Yuan: monthly;;
	  	float orgn[12];       //Yuan: monthly;;
    	float avln[12];       //Yuan: monthly;

    	float netnmin[12];   //Yuan: monthly;
    	float nuptake[12];   //Yuan: monthly;
		float ninput[12];   //Yuan: monthly;
		float nlost[12];   //Yuan: monthly;

    	float eet[12];   //Yuan: monthly
    	float pet[12];   //Yuan: monthly

		float qdrain[12];   //Yuan: monthly;
		float qrunoff[12];   //Yuan: monthly;

		float snowthick[12];   // Yuan: monthly snow pack thickness
		float swe[12];        // Yuan: monthly snow water equivalent (mm)

		float wtd[12];   //Yuan: monthly
    	float ald[12];   //Yuan: monthly
	 
		float vwcshlw[12];   //Yuan: monthly
		float vwcdeep[12];   //Yuan: monthly
		float vwcminetop[12];   //Yuan: monthly (top minearl 20 cm)
		float vwcminebot[12];   //Yuan: monthly (below top mineral 20 cm)

		float tshlw[12];   //Yuan: monthly
		float tdeep[12];   //Yuan: monthly
    	float tminetop[12];   //Yuan: monthly (top minearl 20 cm)
		float tminebot[12];   //Yuan: monthly (below top mineral 20 cm)

		float hkshlw[12];   //Yuan: monthly hydraulic conductivity
		float hkdeep[12];   //Yuan: monthly hydraulic conductivity
		float hkminetop[12];   //Yuan: monthly (top minearl 20 cm)
		float hkminebot[12];   //Yuan: monthly (below top mineral 20 cm)

		float tcshlw[12];   //Yuan: monthly thermal conductivity
		float tcdeep[12];   //Yuan: monthly thermal conductivity
    	float tcminetop[12];   //Yuan: monthly (top minearl 20 cm)
		float tcminebot[12];   //Yuan: monthly (below top mineral 20 cm)

		float trock34[12];   //Yuan: monthly;;

	  	float somcald[12];       //Yuan: monthly;;
		float vwcald[12];   //Yuan: monthly (above ALD)
		float tald[12];   //Yuan: monthly (above ALD)

};

#endif /*REGNOUTDATA_H_*/
