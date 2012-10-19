#ifndef RESTARTINPUTER_H_
#define RESTARTINPUTER_H_

#include "netcdfcpp.h"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include <string>
using std::string;

#include "../inc/layerconst.h"
#include "../inc/timeconst.h"
#include "../inc/ErrorCode.h"
#include "../util/Exception.h"

class RestartInputer {
	public :
		RestartInputer();
		void init(string & dir);
		~RestartInputer();

		int getRecordId(const int &chtid);
		void getChtId(int & chtid, const int &cid);
		void getERRCODE(int & errcode, const int &cid);
		void getPERMAFROST(int & perma, const int &cid);
		void getYSF(int & ysf, const int &cid);
		void getBURNEDN(double & burnedn, const int &cid);
	
		void getVEGC(double & vegc, const int &cid);
		void getSTRN(double & strn, const int &cid);
		void getSTON(double & ston, const int &cid);
		void getDEADN(double & deadc, const int &cid);
		void getUNNORMLEAF(double & unnormleaf, const int &cid);
		void getPRVUNNORMLEAFMX(double & prevunormleafmx, const int &cid);
		void getPRVTOPT(double & prvtopt, const int &cid);
		void getC2N(double & c2n, const int &cid);
		void getKDFIB(double & kdfib, const int &cid);
		void getKDHUM(double & kdhum, const int &cid);
		void getKDMIN(double & kdmin, const int &cid);
		void getKDSLOW(double & kdslow, const int &cid);

		void getPRVEETMX(double & prveetmx, const int &cid);
		void getPRVPETMX(double & prveetmx, const int &cid);
		void getFOLIAGEMX(double & foliagemx, const int &cid);

		//void getEET(double & prveetmx, const int &cid);
		//void getPET(double & prveetmx, const int &cid);

		void getLAI(double & lai, const int &cid);

		void getDEADC(double & deadc, const int &cid);

		void getAVLN(double & avln, const int &cid);

		void getSOLN(double & soln, const int &cid);

		void getWDEBRIS(double & wdebris, const int &cid);

		void getDZsnow(double  DZsnow[], const int &cid);
		void getTSsnow(double  TSsnow[], const int &cid);
		void getICEsnow(double  ICEsnow[], const int &cid);
		void getAGEsnow(double  AGEsnow[], const int &cid);
		void getRHOsnow(double  RHOsnow[], const int &cid);

		void getDZsoil(double  DZsoil[], const int &cid);
		void getLIQsoil(double  DZsoil[], const int &cid);
		void getTSsoil(double  DZsoil[], const int &cid);
		void getICEsoil(double  DZsoil[], const int &cid);
		void getFROZENsoil(int DZsoil[], const int &cid);
		void getNONC(double  DZsoil[], const int &cid);
		void getREAC(double  DZsoil[], const int &cid);

		void getFrontFT(int frotnft[], const int &cid);
		void getFrontZ(double frotnZ[], const int &cid);

		void getDZrock(double  DZrock[], const int &cid);
		void getTSrock(double  DZrock[], const int &cid);

		void getTYPEsoil(int TYPEsoil[], const int &cid);
		void getTYPEmin(int TYPEmin[], const int &cid);

		void getTOPTA(double TYPEmin[], const int &cid);
		
		void getEETMXA(double TYPEmin[], const int &cid);
		void getPETMXA(double TYPEmin[], const int &cid);
		void getUNNORMLEAFMXA(double TYPEmin[], const int &cid);

    private:
		NcFile* restartFile;
		NcDim * chtD;
		NcDim * snowlayerD;
		NcDim * soillayerD;
		NcDim * rocklayerD;
		NcDim * frontD;
		NcDim * meanyearD ;
	
		NcVar* chtidV;
		NcVar* errcodeV;
	
		NcVar* permaV;
		NcVar* TSsnowV;
		NcVar* DZsnowV;
		NcVar* LIQsnowV;
		NcVar* ICEsnowV;

		NcVar* AGEsnowV;
		NcVar* RHOsnowV;
	
		NcVar* TSsoilV;
		NcVar* DZsoilV;
		NcVar* LIQsoilV;
		NcVar* ICEsoilV;
		NcVar* FROZENsoilV;
		NcVar* NONCsoilV;
		NcVar* REACsoilV;
		NcVar* TYPEsoilV;
		NcVar* TYPEminV;
	
		NcVar* TSrockV;
		NcVar* DZrockV;
	
		NcVar* frontZV;
		NcVar* frontFTV;
	
		NcVar* solnV;
		NcVar* avlnV;
		NcVar* wdebrisV;
	
		NcVar* strnV;
		NcVar* stonV;
		NcVar* vegcV;
		NcVar* deadcV;
		NcVar* deadnV;
	
		NcVar* prveetmxV;
		NcVar* prvpetmxV;
		NcVar* foliagemxV;
	
	//	NcVar* eetV;
	//	NcVar* petV;
		NcVar* laiV;
	
		NcVar* unnormleafV;
		NcVar* prvunnormleafmxV;
		NcVar* prvtoptV;
		NcVar* c2nV;
		NcVar* kdfibV;
		NcVar* kdhumV;
		NcVar* kdminV;
		NcVar* kdslowV;
	//	NcVar* EnvLaiV;
	
		NcVar* ysfV;
		NcVar* burnednV;
	
     	NcVar* toptAV;
		NcVar* eetmxAV;
		NcVar* petmxAV;
		NcVar* unnormleafmxAV;
   	
};

#endif /*RESTARTINPUTER_H_*/
