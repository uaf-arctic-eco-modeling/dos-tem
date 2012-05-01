/*! \file
 * this class updates the position of freezing and thawing fronts using Stefan Algorithm (ATWoo42004a)
 */
#ifndef STEFAN_H_
#define STEFAN_H_
#include "layer/Layer.h"
#include "layer/SoilLayer.h"
#include "layer/SnowLayer.h"

#include "../inc/PhysicalConstants.h"

#include "../util/CrankNicholson.h"
#include "../util/Exception.h"
#include "../inc/ErrorCode.h"
#include "../inc/layerconst.h"
#include "../util/Exception.h"

class Stefan{
  public:
  Stefan();
  ~Stefan();

  void updateFronts(const double & tdrv, Layer *frontl, Layer *backl,Layer *fstsoill, Layer* lstminl, const int &mind);
  
  void updateTemps(const double & tdrv, Layer *frontl, Layer *backl,Layer *fstsoill, Layer* fstfntl, Layer*lstfntl);
  
  void checkFrontsValidity(Layer *fstsoill);
   int itsumall;
  /*! the maximum allowable time step (double)*/
  private:
  	
  	bool temupdated[MAX_GRN_LAY];
  	double temold[MAX_GRN_LAY];
  	
   void processSoilLayer5Bot(const int &frozenstate, double const & tkres, double const & tkfront ,
                        double & dse, double & sumresabv, const double & tdrv,
 						SoilLayer* sl,  Layer *frontl, Layer *backl);
 						
   void  processSoilLayer5Top(const int &frozenstate, double const & tkres, double const & tkfront ,
                        double & dse, double & sumresabv, const double & tdrv,
 						SoilLayer* sl,  Layer *frontl, Layer *backl); 						
   void processSnowLayer(double const & tkres, double const & tkfront ,
                        double & dse, double & sumresabv, const double & tdrv,
 						Layer* currl);				
  	 /*get the degree seconds needed to fully freeze/thaw  one or part of one layer*/
  	 
  	 double getDegSecNeeded( const double & dz, 
 				const double & volwat, const double & tk , const double & sumresabv);
	 
	 //calculate partial depth based on extra degree seconds
     double getPartialDepth(const double & volwat,const double & tk,
 								const double & sumresabv, const double & dse);
 		
 	void interpSnowTemp(Layer* frontl, Layer* fstsoill,const double & tdrv);
 	 								
 	void updateUpperTemps5Front(Layer* fstfntl, const double & beforedse , const double & afterdse, const double & tdrv,
 					 const int & frzing, const double & dz, const double & abvres);		
 	///////////////////////////////////////////////////////////////////////////////////////////////
 	// for updating temperatures
 	double s[MAX_GRN_LAY+2];
 	double e[MAX_GRN_LAY+2];
 	double cn[MAX_GRN_LAY+2];
 	double cap[MAX_GRN_LAY+2];
 	double t[MAX_GRN_LAY+2];
 	double dx[MAX_GRN_LAY+2];
 	double dxold[MAX_GRN_LAY+2];
 	
 	double tld[MAX_GRN_LAY+2];
 	double tid[MAX_GRN_LAY+2];
 	double tis[MAX_GRN_LAY+2];
 	double tii[MAX_GRN_LAY+2];
 	double tit[MAX_GRN_LAY+2];
 		
 		
 	CrankNicholson cns;	
 	    /*! tolerance of difference*/
    double ttole;
    /*! the maximum number of iteration for one time step*/
    int ITMAX; 
   
    /*! the amount of time left for update (day)*/ 
    double tleft;
    
    /*!the last determined time, short for time-last-determined*/
    double tmld;
    
    /*! whether the time step has been changed for last factional time step
     * 
     */
     
     /* the upper temps should be updated only one time, when the freezing/thawing front first moved,
      * otherwise, if the temps of upper layers updated everytime the FTFs moved,
      * the soil temperature would be lower than actual, so put a flag to indicate
      * that the upper temperature has been updated.
      * while for the rest soil layers above FTFs, use the lefted degree second*/
     bool upperTemps5FrontUpdated;
     
     
     
     
     int itsum;
     int itsumabv;
     int itsumblw;
     double tstep;
     
     bool tschanged;
     

     double  TSTEPMAX;
    /*! the original time step*/
     double TSTEPORG;
    
    void processWholeColumn(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv);
   
    void processAboveLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv);
    void processBelowLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv);
    void processBetweenLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv);
    
    void iterate(const int &startind, const int &endind, const bool & lstlaybot, const bool & fstlaytop, Layer *frontl);
    int updateOneTimeStep(const int startind, const int & endind, const bool & lstlaybot, const bool & fstlaytop, Layer *frontl);
    int updateOneIteration( const int startind, const int & endind, const bool & lstlaybot, const bool & fstlaytop, Layer *frontl);
    void interpolateUpperTemps5Front(const double & tdrv,Layer* frontl);
    							
};

#endif /*STEFAN_H_*/
