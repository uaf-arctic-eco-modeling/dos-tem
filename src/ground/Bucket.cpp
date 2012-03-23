#include "Bucket.h"

Bucket::Bucket(){
	
};


void Bucket::update(const double & trans, const double & evap, const double & rnth,
				const double &  melt,double & runoff, double & infil,  Layer* fstsoill){
		double bala = rnth +melt -evap -trans;
		double ice , liq, poro , dz ;
		double ice2 , liq2, poro2 , dz2 ;
		double infil2;
		ice =fstsoill->ice;
		liq =fstsoill->liq;
		poro =fstsoill->poro;
		dz =fstsoill->dz;
		Layer *nextl = fstsoill->nextl;
		ice2 =nextl->ice;
		liq2 =nextl->liq;
		poro2 =nextl->poro;
		dz2 =fstsoill->dz;
				
		if(bala>0){
			//if(fstsoill->frozen==-1 &&
			if(fstsoill->frozen <=0) {
				
				if(ice +liq +bala >poro *dz *917){
				  infil = poro*dz *917 -ice -liq;
				  runoff = bala-infil;
				  fstsoill->liq = infil +liq;	
				}else{
				  infil =bala;
				  runoff =0.;
				  fstsoill->liq = infil +liq;	
				}
			}else if(fstsoill->frozen ==-1){
			   if(ice +liq +bala >poro *dz *1000){
				  double extra = bala-poro*dz *1000 +ice +liq;
				  fstsoill->liq =poro*dz *1000-ice;
				  if(extra +ice2 +liq2 >poro2 *dz2 *1000){
				  	infil2 = poro2*dz2*1000-ice2 -liq2;
				  	runoff = extra-infil2;
				  	infil = bala-runoff;
				  	nextl->liq +=infil2; 
				  }else{
				  	infil = bala;
				  	runoff =0.;
				  	nextl->liq +=extra;
				  }
				  	
				}else{
				  infil =bala;
				  runoff =0.;
				  fstsoill->liq = infil +liq;	
				}
			}
		}else { //bala<0

				if(fstsoill->liq - fstsoill->minliq <-bala){
				  fstsoill->liq = fstsoill->minliq; //minimum
				}else{
				  fstsoill->liq -=bala;	
				  
				}

			infil =melt+rnth;
			runoff =0.;
		}		
	
}
