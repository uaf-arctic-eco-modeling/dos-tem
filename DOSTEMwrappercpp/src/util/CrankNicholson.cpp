/*! \file
 */
 
#include "CrankNicholson.h"

CrankNicholson::CrankNicholson(){
	
};
  
CrankNicholson::~CrankNicholson(){
	
};

void CrankNicholson::geBackward(const int  &startind, const int & endind, double  t[], 
		        double dx[], double  cn[], double cap[], 
		        double  s[], double e[], double & dt, const bool & lstlaybot) {
	//from bottom numl to ind th layer : ind >=1, numl is total number of snow/soil layer
	double condth;
	double conuth;
	double denm;
	double con;
	double r;
	double rc;
	double rhs;

	//loop from last layer to first layer
	int im1;
	int ip1;

	if(lstlaybot){ // the last layer is soil bottom
		double gflux = -0.5;// very small effect

		con = cn[endind-1];
		rc = cap[endind-1]*0.5/dt;
		denm = rc+con;

		s[endind] = con/denm;
		e[endind]= (rc*t[endind] -gflux)/denm;
	}
	
	//int fstl = startind+1;
	//if(fstf ==1) fstl = ind +1;	

	for (int il =endind-1 ;il>=startind+1;il--){
		im1 =il -1;
		ip1 =il +1;
		conuth = cn[im1];
		condth = cn[il] ;
		rc = (cap[il] + cap[im1]) / dt;
		r = conuth + rc + condth;
		denm = r - condth * s[ip1];
		rhs = (rc - conuth - condth) * t[il] + conuth 
          * t[im1] + condth * t[ip1];

		//   deal with the following later          
		//    rhs = rhs + theta * ht[dnode] + theta1 * htold[dnode];

		s[il] = conuth / denm;
		e[il] = (rhs + condth * e[ip1]) / denm; 
	 
	}

};

void CrankNicholson::geForward(const int  &startind, const int & endind, double  t[], double dx[], double  cn[], 
	 			double cap[], double  s[], double e[], double & dt, const bool & fstlaytop) {

	double condth;
	double conuth;
	double denm;

	double r;
	double rc;
	double rhs;

	int im1;
	int ip1;

	if(fstlaytop){
		rc = cap[1] *0.5/ dt;
		conuth = cn[0];
		condth = cn[1];
		rhs = rc * t[1] ; // +sflux + ht[dnode];
		r = conuth + rc + condth;
		denm = r -conuth *s[0];

		s[1] = condth/denm;
		e[1] = (rhs + conuth * e[0])/ denm;	
	}

	for (int il =startind+1 ;il<=endind-1;il++){
		im1 =il -1;
		ip1 =il +1;
		conuth = cn[im1];	
		condth = cn[il] ;
		rc = (cap[il] + cap[im1]) / dt;
		r = conuth + rc + condth;
		denm = r - conuth * s[im1];
		rhs = (rc - conuth - condth) * t[il] + conuth 
          * t[im1] + condth * t[ip1];

		s[il] = condth / denm;
		e[il] = (rhs + conuth * e[im1]) / denm; 

	}

};

void CrankNicholson::cnForward(const int & startind, const int & endind ,
		double tii[], double tit[], double s[], double e[]) {

	tit[0]= tii[0];
	for ( int il =startind+1; il <= endind-1; il++ ) {
  	
		tit[il] = s[il] * tit[il-1] + e[il];
  
	};  

};



void CrankNicholson::cnBackward(const int & startind, const int & endind ,
		double tii[], double tit[], double s[], double e[]) {
	
	tit[endind]= tii[endind];
	for ( int il =endind-1; il >= startind+1; il-- ) {
		tit[il] = s[il] * tit[il+1] + e[il];
	}

};

/*! copy and modified from TridiagonalMod::Tridiagonal in CLM3*/
void CrankNicholson::tridiagonal(const int ind, const int numsl, 
		double a[], double b[], double c[], double r[], double u[]){
	/* input: a, b, c
	 * input: ind, numsl
	 * output: u
	 */
	
	double gam[numsl-ind+1 +2]; // second +1, for use this function in c++ (c++ starts index from 0, fortran from 1) 
	double tempg, tg;
	double bet = b[ind];
	for(int il =ind; il<=numsl; il++){
		if(il == ind){
			u[il] = r[il]/bet;
		}else{
			tempg = c[il-1] /bet;
			gam[il]= tempg;
			bet = b[il] - a[il] *gam[il];
			u[il] = (r[il] - a[il]*u[il-1])/bet;	
		}	
	}
	
	for(int il=numsl-1; il>=ind;il--){
	   tg = gam[il+1];
	   u[il] = u[il] - gam[il+1] *u[il+1];	
	}
	
};

