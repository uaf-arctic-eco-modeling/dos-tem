/*! \file provides freezing or thawing fronts */
#ifndef OUTPUTDEPTH_H_
#define OUTPUTDEPTH_H_

class OutputDepth{
  public:
    OutputDepth();
    
    /*! relative position to a layer */
    double dz;	
    /*! relative position to soil surface */		
	double z;
	
    int outind; // output index
    
	int type; //0 for soil temperature, 1 for soil moisture, may be carbon (cumulative)
	

	void set(const double &dz, const int & outputind, const int& type);
};
#endif /*OUTPUTDEPTH_H_*/
