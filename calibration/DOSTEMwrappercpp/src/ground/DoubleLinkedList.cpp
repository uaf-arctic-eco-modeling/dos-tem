/*! \file
 * Bug fixed 
 * 1) in insertBefore, need to put the curl->prevl->nextl = l, if curl->prevl is not null
*/

#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList(){
 	frontl = NULL;
 	backl = NULL;	
};


 /*! insert a layer at the end of list */ 
void DoubleLinkedList::insertBack (Layer * l){          
	if(this->backl==NULL){
		//std::cout<<"insert at back";
		insertFront(l);
	} else	{
		//std::cout<<"insert at back";
		insertAfter(l,this->backl  );
	}
};
 
 /*! insert a layer before the front layer */
void DoubleLinkedList::insertFront (Layer * l)
		{
	
			if(this->frontl==NULL)
			{
				this->frontl=l;
				this->backl =l;
				 l->prevl=NULL;
				 l->nextl=NULL;
			}
			else
			{
				 insertBefore(l, this->frontl );
			}
		}

  /*! insert a layer before the specified layer */
 void DoubleLinkedList::insertBefore(Layer *l, Layer *curl)    
	{

		l->prevl=curl->prevl;
		l->nextl =curl;
		if(curl->prevl==NULL)
		{
		this->frontl=l;	
		}else{
		 curl->prevl->nextl = l;	
		}
	    curl->prevl=l;
	//sy removeLayer(l);
	
	}
	
	/*! insert a layer after the specified layer */
void DoubleLinkedList::insertAfter(Layer* l,Layer *curl)
	{
        Layer* tempnext= curl->nextl;
        
		l->nextl= curl->nextl ;
		l->prevl  =curl;
		
		if(curl->nextl==NULL)
		{
			this->backl =l;	
		}else{
			tempnext->prevl= l;
		}
			curl->nextl=l;
			
			
	
	}

/*! remove a layer from the front */
void DoubleLinkedList::removeFront (){
	removeLayer(this->frontl);
}

/*! remove a layer from the back */
void DoubleLinkedList::removeBack (){
	removeLayer(this->backl);
}

/*! remove a layer before a specified layer */
void DoubleLinkedList::removeBefore(Layer *curl) {

	if(curl->prevl==this->frontl)
	{
		this->frontl=curl;
		this->frontl->prevl=NULL;
		delete curl;
	}else{
        removeLayer(curl->prevl);
	}
}

/*! remove a layer after a specified layer */ 
void DoubleLinkedList::removeAfter(Layer * curl ){
	if(curl->nextl==this->backl)
	{
		this->backl=curl;
		this->backl->nextl=NULL;
		delete curl;
	}else{
		removeLayer(curl->nextl);
	}
}

/*! remove a layer */
void DoubleLinkedList::removeLayer(Layer * curl) {
	if(curl==this->frontl){
		if(this->frontl->nextl!=NULL){
			this->frontl=this->frontl->nextl;
			this->frontl->prevl =NULL;
			if(curl->isSoil()){
				SoilLayer*  sl = dynamic_cast<SoilLayer*>(curl);
				sl->clean();	
			}
			delete curl;
			curl =NULL;
		}
		
	}else if (curl==this->backl){   
		if(this->backl->prevl !=NULL){
			this->backl=this->backl->prevl;
			this->backl->nextl =NULL;
			if(curl->isSoil()){
	  	      	SoilLayer*  sl = dynamic_cast<SoilLayer*>(curl);
	  	      	sl->clean();	
			}
			delete curl;
			curl=NULL	; 
		}
	} else	{
		curl->prevl->nextl=curl->nextl;
		curl->nextl->prevl=curl->prevl;
		curl->prevl =NULL;
		curl->nextl =NULL;
		if(curl->isSoil()){
			SoilLayer*  sl = dynamic_cast<SoilLayer*>(curl);
			sl->clean();	
	    }
	    delete curl;
	    curl =NULL;
	}
	//might need to free front in layer
	
	curl=NULL;
	
}

