//when there is only one layer is unfrozen, use bucket method
#ifndef BUCKET_H_
#define BUCKET_H_
#include "layer/Layer.h"
class Bucket{
	public:
	Bucket();
	
	void update(const double & trans, const double & evap, const double & rnth,
	          const double &  melt,double & runoff,double & infil,  Layer* fstsoill);
	
};
#endif /*BUCKET_H_*/
