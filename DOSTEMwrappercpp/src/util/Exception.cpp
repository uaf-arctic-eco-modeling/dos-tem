#include "Exception.h"

Exception::Exception(char* msg, ERRORKEY code){
  message = msg;	
  errorid =code;
}

void Exception::mesg(){
 //cout << what() <<"\n";	
 cout << chtid <<"  " <<message << "\n";	
}

int Exception::getErrorCode(){
 	return errorid;
}

