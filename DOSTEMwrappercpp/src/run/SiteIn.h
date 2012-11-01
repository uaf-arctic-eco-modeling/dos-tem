#ifndef SITEIN_H_
#define SITEIN_H_

#include "../inc/layerconst.h"

class SiteIn {
	public:
	
		SiteIn();
		~SiteIn();
		
		int siteid;
		int ysf;
		float lai[12];	             
		float vegc;
		float vegn;
	
		float mossthick;
		float fibthick;
		float humthick;
	
		float soilc;
		float fibc;
		float humc;
		float minc;
		float orgn;
		float avln;
	
		int mintype[MAX_MIN_LAY];
	
		float initz[MAX_SOI_LAY];
		float initst[MAX_SOI_LAY];
		float initsm[MAX_SOI_LAY];
};

#endif /*SITEIN_H_*/
