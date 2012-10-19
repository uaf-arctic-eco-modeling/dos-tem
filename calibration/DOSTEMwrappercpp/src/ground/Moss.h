/*! \file
 */
 
#ifndef MOSS_H_
#define MOSS_H_

class Moss{
	public:
	Moss();
	
	int num; //num of moss layers
	double dza[2]; // there are maximum 2 layers
	double thick;

	void updateThicknesses(int type[], double dz[],const int & maxnum);
	void updateThicknesses(const double & thickness);
	bool sameThickRange(const double & thickness);
};
#endif /*MOSS_H_*/
