/*! \file provides freezing or thawing fronts */
#ifndef FRONT_H_
#define FRONT_H_

class Front{
  public:
    Front();
    
    /*! relative position to a layer */
    double dz;	
    /*! relative position to soil surface */		
//	double z;
	
    void setFrzing(const double & tsur, const double & tf);
	void reset();
	/*! whether is a freezing/thawing front */
	int frzing;
	
	void assign(const Front & of);
	void set(const double &dz, const int& frz);
};
#endif /*FRONT_H_*/
