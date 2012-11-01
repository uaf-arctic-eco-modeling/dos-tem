#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
 

#include <exception>

using namespace std;

#include "../inc/ErrorCode.h"

class Exception: public exception{
   public:
   Exception( char * msg, ERRORKEY code);
   void mesg();	
   int getErrorCode();
 
   int chtid;
   private:
   char* message;
   int errorid;
   
	
};

#endif /*EXCEPTION_H_*/
