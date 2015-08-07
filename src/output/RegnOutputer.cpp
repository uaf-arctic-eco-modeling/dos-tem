/*
 * This class is for output variables in TEM regional run
 * in netcdf format
 * 
*/

#include "RegnOutputer.h"

RegnOutputer::RegnOutputer(){
	 
};

RegnOutputer::~RegnOutputer(){
 	if(rFile!=NULL){
    	rFile->close();
		delete rFile;
 	}

};

void RegnOutputer::missingValues(const int & MAX_DRV_YR, const int & chtcount){
 	regnod->status =-999;
  	for(int iy=0; iy<MAX_DRV_YR; iy++){
   		regnod->ysf=-999;

   		regnod->burnthick=-999;
  		regnod->burnvegc=-999;
  		regnod->burnsoic=-999;
		regnod->burnsoiln=-999;
		regnod->burnvegn=-999;
		regnod->ndepo=-999;
		regnod->ORL=-999;

  		regnod->growstart=-999;
  		regnod->growend=-999;
  		regnod->snowstart=-999;
  		regnod->snowend=-999;		
  		regnod->perm=-999;
  		regnod->mossdz=-999;
  		regnod->shlwdz=-999;
  		regnod->deepdz=-999;

  		for (int im=0; im<12; im++){
  			regnod->lai[im]=-999;
  			regnod->vegc[im]=-999;
  			regnod->vegn[im]=-999;
			regnod->dwd[im]=-999;
			regnod->dwdrh[im]=-999;
			regnod->deadc[im]=-999;
			regnod->deadn[im]=-999;

  			regnod->gpp[im] =-999;
  			regnod->npp[im] =-999;
  			regnod->rh[im] =-999;
  			regnod->ltrfalc[im]=-999;
  			regnod->ltrfaln[im]=-999;

  			regnod->shlwc[im]=-999;
  			regnod->deepc[im]=-999;
  			regnod->minec[im]=-999;
  	  		regnod->orgn[im]=-999;
  	  		regnod->avln[im]=-999;

  	  		regnod->netnmin[im]=-999;
  	  		regnod->nuptake[im]=-999;
  	  		regnod->ninput[im]=-999;
  	  		regnod->nlost[im]=-999;

  			regnod->eet[im]=-999;
  			regnod->pet[im]=-999;
  			regnod->qdrain[im]=-999;
  			regnod->qrunoff[im]=-999;

   			regnod->snowthick[im]=-999;
  			regnod->swe[im]=-999;
   			regnod->wtd[im]=-999;
  			regnod->ald[im]=-999;

  	  		regnod->vwcshlw[im] =-999;
  			regnod->vwcdeep[im] =-999;
  			regnod->vwcminetop[im] =-999;
  			regnod->vwcminebot[im] =-999;

  			regnod->tshlw[im] =-999;
  			regnod->tdeep[im] =-999;
  			regnod->tminetop[im] =-999;
  			regnod->tminebot[im] =-999;

  			regnod->hkshlw[im] =-999;
  			regnod->hkdeep[im] =-999;
  			regnod->hkminetop[im] =-999;
  			regnod->hkminebot[im] =-999;

  			regnod->tcshlw[im] =-999;
  			regnod->tcdeep[im] =-999;
  			regnod->tcminetop[im] =-999;
  			regnod->tcminebot[im] =-999;

  			regnod->trock34[im]=-999;

  			regnod->somcald[im]=-999;
  			regnod->vwcald[im] =-999;
  			regnod->tald[im] =-999;
	 
  		}

  		outputYearCohortVars(iy, chtcount);
  	}
  	
};

void RegnOutputer::init(string& outputdir, const int & myid, string & stage, int MAX_DRV_YR){

	string moncfn =outputdir+"output"+stage+".nc";

	rFile = new NcFile(moncfn.c_str(), NcFile::Replace);
	
		chtD  = rFile->add_dim("CHTID");
		yearD = rFile->add_dim("YEAR", MAX_DRV_YR);
		monthD = rFile->add_dim("MONTH", 12);
	 
		chtidCYV  =rFile->add_var("CHTID", ncInt,chtD);
		statusCYV =rFile->add_var("STATUS", ncInt,chtD);
		ysfCYV  = rFile->add_var("YSF", ncFloat, chtD, yearD);

		//yearly only
		if (regnod->outvarlist[0]>=1){
			burnthickCYV = rFile->add_var("BURNTHICK", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[1]>=1){
			burnsoicCYV = rFile->add_var("BURNSOIC", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[2]>=1){
			burnvegcCYV = rFile->add_var("BURNVEGC", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[3]>=1){
			growstartCYV = rFile->add_var("GROWSTART", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[4]>=1){
			growendCYV   = rFile->add_var("GROWEND", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[5]>=1){
			permCYV = rFile->add_var("PERMAFROST", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[6]>=1){
			mossdzCYV = rFile->add_var("MOSSDZ", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[7]>=1){
			shlwdzCYV = rFile->add_var("SHLWDZ", ncFloat, chtD, yearD);
		}
		if (regnod->outvarlist[8]>=1){
			deepdzCYV = rFile->add_var("DEEPDZ", ncFloat, chtD, yearD);
		}

		//yearly or monthly
		if (regnod->outvarlist[9]==1){
			laiCYV  = rFile->add_var("LAI", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[9]==2) {
			laiCYV  = rFile->add_var("LAI", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[10]==1){
			vegcCYV = rFile->add_var("VEGC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[10]==2) {
			vegcCYV = rFile->add_var("VEGC", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[11]==1){
			vegnCYV = rFile->add_var("VEGN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[11]==2) {
			vegnCYV = rFile->add_var("VEGN", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[12]==1){
			gppCYV = rFile->add_var("GPP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[12]==2) {
			gppCYV = rFile->add_var("GPP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[13]==1){
			nppCYV = rFile->add_var("NPP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[13]==2) {
			nppCYV = rFile->add_var("NPP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[14]==1){
			rhCYV  = rFile->add_var("RH", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[14]==2) {
			rhCYV  = rFile->add_var("RH", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[15]==1){
			ltrfalcCYV = rFile->add_var("LTRFALC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[15]==2) {
			ltrfalcCYV = rFile->add_var("LTRFALC", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[16]==1){
			ltrfalnCYV = rFile->add_var("LTRFALN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[16]==2) {
			ltrfalnCYV = rFile->add_var("LTRFALN", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[17]==1){
			shlwcCYV = rFile->add_var("SHLWC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[17]==2) {
			shlwcCYV = rFile->add_var("SHLWC", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[18]==1){
			deepcCYV = rFile->add_var("DEEPC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[18]==2) {
			deepcCYV = rFile->add_var("DEEPC", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[19]==1){
			minecCYV  = rFile->add_var("MINEC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[19]==2) {
			minecCYV  = rFile->add_var("MINEC", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[20]==1){
			orgnCYV = rFile->add_var("ORGN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[20]==2) {
			orgnCYV = rFile->add_var("ORGN", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[21]==1){
			avlnCYV = rFile->add_var("AVLN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[21]==2) {
			avlnCYV = rFile->add_var("AVLN", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[22]==1){
			netnminCYV = rFile->add_var("NETNMIN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[22]==2) {
			netnminCYV = rFile->add_var("NETNMIN", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[23]==1){
			nuptakeCYV = rFile->add_var("NUPTAKE", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[23]==2) {
			nuptakeCYV = rFile->add_var("NUPTAKE", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[24]==1){
			ninputCYV = rFile->add_var("NINPUT", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[24]==2) {
			ninputCYV = rFile->add_var("NINPUT", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[25]==1){
			nlostCYV = rFile->add_var("NLOST", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[25]==2) {
			nlostCYV = rFile->add_var("NLOST", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[26]==1){
			eetCYV  = rFile->add_var("EET", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[26]==2) {
			eetCYV  = rFile->add_var("EET", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[27]==1){
			petCYV  = rFile->add_var("PET", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[27]==2) {
			petCYV  = rFile->add_var("PET", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[28]==1){
			qdrainCYV  = rFile->add_var("DRAINAGE", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[28]==2) {
			qdrainCYV  = rFile->add_var("DRAINAGE", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[29]==1){
			qrunoffCYV = rFile->add_var("RUNOFF", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[29]==2) {
			qrunoffCYV = rFile->add_var("RUNOFF", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[30]==1){
			sthickCYV = rFile->add_var("SNOWTHICK", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[30]==2) {
			sthickCYV = rFile->add_var("SNOWTHICK", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[31]==1){
			sweCYV    = rFile->add_var("SWE", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[31]==2) {
			sweCYV    = rFile->add_var("SWE", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[32]==1){
			wtdCYV  = rFile->add_var("WATERTAB", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[32]==2) {
			wtdCYV  = rFile->add_var("WATERTAB", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[33]==1){
			aldCYV  = rFile->add_var("ALD", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[33]==2) {
			aldCYV  = rFile->add_var("ALD", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[34]==1){
			vwcshlwCYV  = rFile->add_var("VWCSHLW", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[34]==2) {
			vwcshlwCYV  = rFile->add_var("VWCSHLW", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[35]==1){
			vwcdeepCYV  = rFile->add_var("VWCDEEP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[35]==2) {
			vwcdeepCYV  = rFile->add_var("VWCDEEP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[36]==1){
			vwcminetopCYV = rFile->add_var("VWCMINETOP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[36]==2) {
			vwcminetopCYV = rFile->add_var("VWCMINETOP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[37]==1){
			vwcminebotCYV = rFile->add_var("VWCMINEBOT", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[37]==2) {
			vwcminebotCYV = rFile->add_var("VWCMINEBOT", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[38]==1){
			tshlwCYV  = rFile->add_var("TSHLW", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[38]==2) {
			tshlwCYV  = rFile->add_var("TSHLW", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[39]==1){
			tdeepCYV  = rFile->add_var("TDEEP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[39]==2) {
			tdeepCYV  = rFile->add_var("TDEEP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[40]==1){
			tminetopCYV = rFile->add_var("TMINETOP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[40]==2) {
			tminetopCYV = rFile->add_var("TMINETOP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[41]==1){
			tminebotCYV = rFile->add_var("TMINEBOT", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[41]==2) {
			tminebotCYV = rFile->add_var("TMINEBOT", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[42]==1){
			hkshlwCYV  = rFile->add_var("HKSHLW", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[42]==2) {
			hkshlwCYV  = rFile->add_var("HKSHLW", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[43]==1){
			hkdeepCYV  = rFile->add_var("HKDEEP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[43]==2) {
			hkdeepCYV  = rFile->add_var("HKDEEP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[44]==1){
			hkminetopCYV = rFile->add_var("HKMINETOP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[44]==2) {
			hkminetopCYV = rFile->add_var("HKMINETOP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[45]==1){
			hkminebotCYV = rFile->add_var("HKMINEBOT", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[45]==2) {
			hkminebotCYV = rFile->add_var("HKMINEBOT", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[46]==1){
			tcshlwCYV  = rFile->add_var("TCSHLW", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[46]==2) {
			tcshlwCYV  = rFile->add_var("TCSHLW", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[47]==1){
			tcdeepCYV  = rFile->add_var("TCDEEP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[47]==2) {
			tcdeepCYV  = rFile->add_var("TCDEEP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[48]==1){
			tcminetopCYV = rFile->add_var("TCMINETOP", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[48]==2) {
			tcminetopCYV = rFile->add_var("TCMINETOP", ncFloat, chtD, yearD, monthD);
		}
		if (regnod->outvarlist[49]==1){
			tcminebotCYV = rFile->add_var("TCMINEBOT", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[49]==2) {
			tcminebotCYV = rFile->add_var("TCMINEBOT", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[50]==1){
			trock34CYV = rFile->add_var("TROCK34M", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[50]==2) {
			trock34CYV = rFile->add_var("TROCK34M", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[51]==1){
			somcaldCYV = rFile->add_var("SOMCALD", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[51]==2) {
			somcaldCYV = rFile->add_var("SOMCALD", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[52]==1){
			vwcaldCYV = rFile->add_var("VWCALD", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[52]==2) {
			vwcaldCYV = rFile->add_var("VWCALD", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[53]==1){
			taldCYV = rFile->add_var("TALD", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[53]==2) {
			taldCYV = rFile->add_var("TALD", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[54]>=1){
			snowstartCYV = rFile->add_var("SNOWSTART", ncFloat, chtD, yearD);
		}

		if (regnod->outvarlist[55]>=1){
			snowendCYV   = rFile->add_var("SNOWEND", ncFloat, chtD, yearD);
		}

		if (regnod->outvarlist[56]>=1){
			burnsoilnCYV   = rFile->add_var("BURNSOILN", ncFloat, chtD, yearD);
		}

		if (regnod->outvarlist[57]>=1){
			burnvegnCYV   = rFile->add_var("BURNVEGN", ncFloat, chtD, yearD);
		}

		if (regnod->outvarlist[58]>=1){
			ndepoCYV   = rFile->add_var("NDEPO", ncFloat, chtD, yearD);
		}

		if (regnod->outvarlist[59]==1){
			deadcCYV = rFile->add_var("DEADC", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[59]==2) {
			deadcCYV = rFile->add_var("DEADC", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[60]==1){
			deadnCYV = rFile->add_var("DEADN", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[60]==2) {
			deadnCYV = rFile->add_var("DEADN", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[61]==1){
			dwdCYV = rFile->add_var("DWD", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[61]==2) {
			dwdCYV = rFile->add_var("DWD", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[62]==1){
			dwdrhCYV = rFile->add_var("DWDRH", ncFloat, chtD, yearD);
		} else if (regnod->outvarlist[62]==2) {
			dwdrhCYV = rFile->add_var("DWDRH", ncFloat, chtD, yearD, monthD);
		}

		if (regnod->outvarlist[63]>=1){
			ORLCYV   = rFile->add_var("ORL", ncFloat, chtD, yearD);
		}

};

void RegnOutputer::outputYearCohortVars(const int & yrind, const int & chtcount){

   	chtidCYV->set_cur(chtcount);
   	chtidCYV->put(&regnod->chtid,1);

   	statusCYV->set_cur(chtcount);
   	statusCYV->put(&regnod->status,1);

   	ysfCYV->set_cur(chtcount, yrind);
   	ysfCYV->put(&regnod->ysf, 1, 1);

	//yearly only
	if (regnod->outvarlist[0]>=1){
		burnthickCYV->set_cur(chtcount, yrind);
		burnthickCYV->put(&regnod->burnthick, 1, 1);
	}
	if (regnod->outvarlist[1]>=1){
		burnsoicCYV->set_cur(chtcount, yrind);
		burnsoicCYV->put(&regnod->burnsoic, 1, 1);
	}
	if (regnod->outvarlist[2]>=1){
		burnvegcCYV->set_cur(chtcount, yrind);
		burnvegcCYV->put(&regnod->burnvegc, 1, 1);
	}
	if (regnod->outvarlist[3]>=1){
		growstartCYV->set_cur(chtcount, yrind);
		growstartCYV->put(&regnod->growstart, 1, 1);
	}
	if (regnod->outvarlist[4]>=1){
		growendCYV->set_cur(chtcount, yrind);
		growendCYV->put(&regnod->growend, 1, 1);
	}
	if (regnod->outvarlist[5]>=1){
		permCYV->set_cur(chtcount, yrind);
		permCYV->put(&regnod->perm, 1, 1);
	}
	if (regnod->outvarlist[6]>=1){
		mossdzCYV->set_cur(chtcount, yrind);
		mossdzCYV->put(&regnod->mossdz, 1, 1);
	}
	if (regnod->outvarlist[7]>=1){
		shlwdzCYV->set_cur(chtcount, yrind);
		shlwdzCYV->put(&regnod->shlwdz, 1, 1);
	}
	if (regnod->outvarlist[8]>=1){
		deepdzCYV->set_cur(chtcount, yrind);
		deepdzCYV->put(&regnod->deepdz, 1, 1);
	}

	//yearly or monthly
	if (regnod->outvarlist[9]==1){
	  	laiCYV->set_cur(chtcount, yrind);
	   	laiCYV->put(&regnod->lai[0], 1, 1);
	} else if (regnod->outvarlist[9]==2) {
	  	laiCYV->set_cur(chtcount, yrind, 0);
	   	laiCYV->put(&regnod->lai[0], 1, 1, 12);
	}
	if (regnod->outvarlist[10]==1){
		vegcCYV->set_cur(chtcount, yrind);
	   	vegcCYV->put(&regnod->vegc[0], 1, 1);
	} else if (regnod->outvarlist[10]==2) {
		vegcCYV->set_cur(chtcount, yrind, 0);
	   	vegcCYV->put(&regnod->vegc[0], 1, 1, 12);
	}
	if (regnod->outvarlist[11]==1){
		vegnCYV->set_cur(chtcount, yrind);
	   	vegnCYV->put(&regnod->vegn[0], 1, 1);
	} else if (regnod->outvarlist[11]==2) {
		vegnCYV->set_cur(chtcount, yrind, 0);
	   	vegnCYV->put(&regnod->vegn[0], 1, 1, 12);
	}

	if (regnod->outvarlist[12]==1){
		gppCYV->set_cur(chtcount, yrind);
	   	gppCYV->put(&regnod->gpp[0], 1, 1);
	} else if (regnod->outvarlist[12]==2) {
		gppCYV->set_cur(chtcount, yrind, 0);
	   	gppCYV->put(&regnod->gpp[0], 1, 1, 12);
	}
	if (regnod->outvarlist[13]==1){
		nppCYV->set_cur(chtcount, yrind);
	   	nppCYV->put(&regnod->npp[0], 1, 1);
	} else if (regnod->outvarlist[13]==2) {
		nppCYV->set_cur(chtcount, yrind, 0);
	   	nppCYV->put(&regnod->npp[0], 1, 1, 12);
	}
	if (regnod->outvarlist[14]==1){
		rhCYV->set_cur(chtcount, yrind);
	   	rhCYV->put(&regnod->rh[0], 1, 1);
	} else if (regnod->outvarlist[14]==2) {
		rhCYV->set_cur(chtcount, yrind, 0);
	   	rhCYV->put(&regnod->rh[0], 1, 1, 12);
	}
	if (regnod->outvarlist[15]==1){
		ltrfalcCYV->set_cur(chtcount, yrind);
	   	ltrfalcCYV->put(&regnod->ltrfalc[0], 1, 1);
	} else if (regnod->outvarlist[15]==2) {
		ltrfalcCYV->set_cur(chtcount, yrind, 0);
	   	ltrfalcCYV->put(&regnod->ltrfalc[0], 1, 1, 12);
	}
	if (regnod->outvarlist[16]==1){
		ltrfalnCYV->set_cur(chtcount, yrind);
	   	ltrfalnCYV->put(&regnod->ltrfaln[0], 1, 1);
	} else if (regnod->outvarlist[16]==2) {
		ltrfalnCYV->set_cur(chtcount, yrind, 0);
	   	ltrfalnCYV->put(&regnod->ltrfaln[0], 1, 1, 12);
	}

	if (regnod->outvarlist[17]==1){
		shlwcCYV->set_cur(chtcount, yrind);
	   	shlwcCYV->put(&regnod->shlwc[0], 1, 1);
	} else if (regnod->outvarlist[17]==2) {
		shlwcCYV->set_cur(chtcount, yrind, 0);
	   	shlwcCYV->put(&regnod->shlwc[0], 1, 1, 12);
	}
	if (regnod->outvarlist[18]==1){
		deepcCYV->set_cur(chtcount, yrind);
	   	deepcCYV->put(&regnod->deepc[0], 1, 1);
	} else if (regnod->outvarlist[18]==2) {
		deepcCYV->set_cur(chtcount, yrind, 0);
	   	deepcCYV->put(&regnod->deepc[0], 1, 1, 12);
	}
	if (regnod->outvarlist[19]==1){
		minecCYV->set_cur(chtcount, yrind);
	   	minecCYV->put(&regnod->minec[0], 1, 1);
	} else if (regnod->outvarlist[19]==2) {
		minecCYV->set_cur(chtcount, yrind, 0);
	   	minecCYV->put(&regnod->minec[0], 1, 1, 12);
	}
	if (regnod->outvarlist[20]==1){
		orgnCYV->set_cur(chtcount, yrind);
	   	orgnCYV->put(&regnod->orgn[0], 1, 1);
	} else if (regnod->outvarlist[20]==2) {
		orgnCYV->set_cur(chtcount, yrind, 0);
	   	orgnCYV->put(&regnod->orgn[0], 1, 1, 12);
	}
	if (regnod->outvarlist[21]==1){
		avlnCYV->set_cur(chtcount, yrind);
	   	avlnCYV->put(&regnod->avln[0], 1, 1);
	} else if (regnod->outvarlist[21]==2) {
		avlnCYV->set_cur(chtcount, yrind, 0);
	   	avlnCYV->put(&regnod->avln[0], 1, 1, 12);
	}

	if (regnod->outvarlist[22]==1){
		netnminCYV->set_cur(chtcount, yrind);
	   	netnminCYV->put(&regnod->netnmin[0], 1, 1);
	} else if (regnod->outvarlist[22]==2) {
		netnminCYV->set_cur(chtcount, yrind, 0);
	   	netnminCYV->put(&regnod->netnmin[0], 1, 1, 12);
	}
	if (regnod->outvarlist[23]==1){
		nuptakeCYV->set_cur(chtcount, yrind);
	   	nuptakeCYV->put(&regnod->nuptake[0], 1, 1);
	} else if (regnod->outvarlist[23]==2) {
		nuptakeCYV->set_cur(chtcount, yrind, 0);
	   	nuptakeCYV->put(&regnod->nuptake[0], 1, 1, 12);
	}
	if (regnod->outvarlist[24]==1){
		ninputCYV->set_cur(chtcount, yrind);
	   	ninputCYV->put(&regnod->ninput[0], 1, 1);
	} else if (regnod->outvarlist[24]==2) {
		ninputCYV->set_cur(chtcount, yrind, 0);
	   	ninputCYV->put(&regnod->ninput[0], 1, 1, 12);
	}
	if (regnod->outvarlist[25]==1){
		nlostCYV->set_cur(chtcount, yrind);
	   	nlostCYV->put(&regnod->nlost[0], 1, 1);
	} else if (regnod->outvarlist[25]==2) {
		nlostCYV->set_cur(chtcount, yrind, 0);
	   	nlostCYV->put(&regnod->nlost[0], 1, 1, 12);
	}

	if (regnod->outvarlist[26]==1){
		eetCYV->set_cur(chtcount, yrind);
	   	eetCYV->put(&regnod->eet[0], 1, 1);
	} else if (regnod->outvarlist[26]==2) {
		eetCYV->set_cur(chtcount, yrind, 0);
	   	eetCYV->put(&regnod->eet[0], 1, 1, 12);
	}
	if (regnod->outvarlist[27]==1){
		petCYV->set_cur(chtcount, yrind);
	   	petCYV->put(&regnod->pet[0], 1, 1);
	} else if (regnod->outvarlist[27]==2) {
		petCYV->set_cur(chtcount, yrind, 0);
	   	petCYV->put(&regnod->pet[0], 1, 1, 12);
	}
	if (regnod->outvarlist[28]==1){
		qdrainCYV->set_cur(chtcount, yrind);
	   	qdrainCYV->put(&regnod->qdrain[0], 1, 1);
	} else if (regnod->outvarlist[28]==2) {
		qdrainCYV->set_cur(chtcount, yrind, 0);
	   	qdrainCYV->put(&regnod->qdrain[0], 1, 1, 12);
	}
	if (regnod->outvarlist[29]==1){
		qrunoffCYV->set_cur(chtcount, yrind);
	   	qrunoffCYV->put(&regnod->qrunoff[0], 1, 1);
	} else if (regnod->outvarlist[29]==2) {
		qrunoffCYV->set_cur(chtcount, yrind, 0);
	   	qrunoffCYV->put(&regnod->qrunoff[0], 1, 1, 12);
	}

	if (regnod->outvarlist[30]==1){
		sthickCYV->set_cur(chtcount, yrind);
	   	sthickCYV->put(&regnod->snowthick[0], 1, 1);
	} else if (regnod->outvarlist[30]==2) {
		sthickCYV->set_cur(chtcount, yrind, 0);
	   	sthickCYV->put(&regnod->snowthick[0], 1, 1, 12);
	}
	if (regnod->outvarlist[31]==1){
		sweCYV->set_cur(chtcount, yrind);
	   	sweCYV->put(&regnod->swe[0], 1, 1);
	} else if (regnod->outvarlist[31]==2) {
		sweCYV->set_cur(chtcount, yrind, 0);
	   	sweCYV->put(&regnod->swe[0], 1, 1, 12);
	}

	if (regnod->outvarlist[32]==1){
		wtdCYV->set_cur(chtcount, yrind);
	   	wtdCYV->put(&regnod->wtd[0], 1, 1);
	} else if (regnod->outvarlist[32]==2) {
		wtdCYV->set_cur(chtcount, yrind, 0);
	   	wtdCYV->put(&regnod->wtd[0], 1, 1, 12);
	}
	if (regnod->outvarlist[33]==1){
		aldCYV->set_cur(chtcount, yrind);
	   	aldCYV->put(&regnod->ald[0], 1, 1);
	} else if (regnod->outvarlist[33]==2) {
		aldCYV->set_cur(chtcount, yrind, 0);
	   	aldCYV->put(&regnod->ald[0], 1, 1, 12);
	}

	if (regnod->outvarlist[34]==1){
		vwcshlwCYV->set_cur(chtcount, yrind);
	   	vwcshlwCYV->put(&regnod->vwcshlw[0], 1, 1);
	} else if (regnod->outvarlist[34]==2) {
		vwcshlwCYV->set_cur(chtcount, yrind, 0);
	   	vwcshlwCYV->put(&regnod->vwcshlw[0], 1, 1, 12);
	}
	if (regnod->outvarlist[35]==1){
		vwcdeepCYV->set_cur(chtcount, yrind);
	   	vwcdeepCYV->put(&regnod->vwcdeep[0], 1, 1);
	} else if (regnod->outvarlist[35]==2) {
		vwcdeepCYV->set_cur(chtcount, yrind, 0);
	   	vwcdeepCYV->put(&regnod->vwcdeep[0], 1, 1, 12);
	}
	if (regnod->outvarlist[36]==1){
		vwcminetopCYV->set_cur(chtcount, yrind);
	   	vwcminetopCYV->put(&regnod->vwcminetop[0], 1, 1);
	} else if (regnod->outvarlist[36]==2) {
		vwcminetopCYV->set_cur(chtcount, yrind, 0);
	   	vwcminetopCYV->put(&regnod->vwcminetop[0], 1, 1, 12);
	}
	if (regnod->outvarlist[37]==1){
		vwcminebotCYV->set_cur(chtcount, yrind);
	   	vwcminebotCYV->put(&regnod->vwcminebot[0], 1, 1);
	} else if (regnod->outvarlist[37]==2) {
		vwcminebotCYV->set_cur(chtcount, yrind, 0);
	   	vwcminebotCYV->put(&regnod->vwcminebot[0], 1, 1, 12);
	}

	if (regnod->outvarlist[38]==1){
		tshlwCYV->set_cur(chtcount, yrind);
	   	tshlwCYV->put(&regnod->tshlw[0], 1, 1);
	} else if (regnod->outvarlist[38]==2) {
		tshlwCYV->set_cur(chtcount, yrind, 0);
	   	tshlwCYV->put(&regnod->tshlw[0], 1, 1, 12);
	}
	if (regnod->outvarlist[39]==1){
		tdeepCYV->set_cur(chtcount, yrind);
	   	tdeepCYV->put(&regnod->tdeep[0], 1, 1);
	} else if (regnod->outvarlist[39]==2) {
		tdeepCYV->set_cur(chtcount, yrind, 0);
	   	tdeepCYV->put(&regnod->tdeep[0], 1, 1, 12);
	}
	if (regnod->outvarlist[40]==1){
		tminetopCYV->set_cur(chtcount, yrind);
	   	tminetopCYV->put(&regnod->tminetop[0], 1, 1);
	} else if (regnod->outvarlist[40]==2) {
		tminetopCYV->set_cur(chtcount, yrind, 0);
	   	tminetopCYV->put(&regnod->tminetop[0], 1, 1, 12);
	}
	if (regnod->outvarlist[41]==1){
		tminebotCYV->set_cur(chtcount, yrind);
	   	tminebotCYV->put(&regnod->tminebot[0], 1, 1);
	} else if (regnod->outvarlist[41]==2) {
		tminebotCYV->set_cur(chtcount, yrind, 0);
	   	tminebotCYV->put(&regnod->tminebot[0], 1, 1, 12);
	}

	if (regnod->outvarlist[42]==1){
		hkshlwCYV->set_cur(chtcount, yrind);
	   	hkshlwCYV->put(&regnod->hkshlw[0], 1, 1);
	} else if (regnod->outvarlist[42]==2) {
		hkshlwCYV->set_cur(chtcount, yrind, 0);
	   	hkshlwCYV->put(&regnod->hkshlw[0], 1, 1, 12);
	}
	if (regnod->outvarlist[43]==1){
		hkdeepCYV->set_cur(chtcount, yrind);
	   	hkdeepCYV->put(&regnod->hkdeep[0], 1, 1);
	} else if (regnod->outvarlist[43]==2) {
		hkdeepCYV->set_cur(chtcount, yrind, 0);
	   	hkdeepCYV->put(&regnod->hkdeep[0], 1, 1, 12);
	}
	if (regnod->outvarlist[44]==1){
		hkminetopCYV->set_cur(chtcount, yrind);
	   	hkminetopCYV->put(&regnod->hkminetop[0], 1, 1);
	} else if (regnod->outvarlist[44]==2) {
		hkminetopCYV->set_cur(chtcount, yrind, 0);
	   	hkminetopCYV->put(&regnod->hkminetop[0], 1, 1, 12);
	}
	if (regnod->outvarlist[45]==1){
		hkminebotCYV->set_cur(chtcount, yrind);
	   	hkminebotCYV->put(&regnod->hkminebot[0], 1, 1);
	} else if (regnod->outvarlist[45]==2) {
		hkminebotCYV->set_cur(chtcount, yrind, 0);
	   	hkminebotCYV->put(&regnod->hkminebot[0], 1, 1, 12);
	}

	if (regnod->outvarlist[46]==1){
		tcshlwCYV->set_cur(chtcount, yrind);
	   	tcshlwCYV->put(&regnod->tcshlw[0], 1, 1);
	} else if (regnod->outvarlist[46]==2) {
		tcshlwCYV->set_cur(chtcount, yrind, 0);
	   	tcshlwCYV->put(&regnod->tcshlw[0], 1, 1, 12);
	}
	if (regnod->outvarlist[47]==1){
		tcdeepCYV->set_cur(chtcount, yrind);
	   	tcdeepCYV->put(&regnod->tcdeep[0], 1, 1);
	} else if (regnod->outvarlist[47]==2) {
		tcdeepCYV->set_cur(chtcount, yrind, 0);
	   	tcdeepCYV->put(&regnod->tcdeep[0], 1, 1, 12);
	}
	if (regnod->outvarlist[48]==1){
		tcminetopCYV->set_cur(chtcount, yrind);
	   	tcminetopCYV->put(&regnod->tcminetop[0], 1, 1);
	} else if (regnod->outvarlist[48]==2) {
		tcminetopCYV->set_cur(chtcount, yrind, 0);
	   	tcminetopCYV->put(&regnod->tcminetop[0], 1, 1, 12);
	}
	if (regnod->outvarlist[49]==1){
		tcminebotCYV->set_cur(chtcount, yrind);
	   	tcminebotCYV->put(&regnod->tcminebot[0], 1, 1);
	} else if (regnod->outvarlist[49]==2) {
		tcminebotCYV->set_cur(chtcount, yrind, 0);
	   	tcminebotCYV->put(&regnod->tcminebot[0], 1, 1, 12);
	}

	if (regnod->outvarlist[50]==1){
		trock34CYV->set_cur(chtcount, yrind);
	   	trock34CYV->put(&regnod->trock34[0], 1, 1);
	} else if (regnod->outvarlist[50]==2) {
		trock34CYV->set_cur(chtcount, yrind, 0);
	   	trock34CYV->put(&regnod->trock34[0], 1, 1, 12);
	}

	if (regnod->outvarlist[51]==1){
		somcaldCYV->set_cur(chtcount, yrind);
	   	somcaldCYV->put(&regnod->somcald[0], 1, 1);
	} else if (regnod->outvarlist[51]==2) {
		somcaldCYV->set_cur(chtcount, yrind, 0);
	   	somcaldCYV->put(&regnod->somcald[0], 1, 1, 12);
	}

	if (regnod->outvarlist[52]==1){
		vwcaldCYV->set_cur(chtcount, yrind);
	   	vwcaldCYV->put(&regnod->vwcald[0], 1, 1);
	} else if (regnod->outvarlist[52]==2) {
		vwcaldCYV->set_cur(chtcount, yrind, 0);
	   	vwcaldCYV->put(&regnod->vwcald[0], 1, 1, 12);
	}

	if (regnod->outvarlist[53]==1){
		taldCYV->set_cur(chtcount, yrind);
	   	taldCYV->put(&regnod->tald[0], 1, 1);
	} else if (regnod->outvarlist[53]==2) {
		taldCYV->set_cur(chtcount, yrind, 0);
	   	taldCYV->put(&regnod->tald[0], 1, 1, 12);
	}

	if (regnod->outvarlist[54]>=1){
		snowstartCYV->set_cur(chtcount, yrind);
		snowstartCYV->put(&regnod->snowstart, 1, 1);
	}
	if (regnod->outvarlist[55]>=1){
		snowendCYV->set_cur(chtcount, yrind);
		snowendCYV->put(&regnod->snowend, 1, 1);
	}

	if (regnod->outvarlist[56]>=1){
		burnsoilnCYV->set_cur(chtcount, yrind);
		burnsoilnCYV->put(&regnod->burnsoiln, 1, 1);
	}

	if (regnod->outvarlist[57]>=1){
		burnvegnCYV->set_cur(chtcount, yrind);
		burnvegnCYV->put(&regnod->burnvegn, 1, 1);
	}

	if (regnod->outvarlist[58]>=1){
		ndepoCYV->set_cur(chtcount, yrind);
		ndepoCYV->put(&regnod->ndepo, 1, 1);
	}

	if (regnod->outvarlist[59]==1){
		deadcCYV->set_cur(chtcount, yrind);
	   	deadcCYV->put(&regnod->deadc[0], 1, 1);
	} else if (regnod->outvarlist[59]==2) {
		deadcCYV->set_cur(chtcount, yrind, 0);
	   	deadcCYV->put(&regnod->deadc[0], 1, 1, 12);
	}

	if (regnod->outvarlist[60]==1){
		deadnCYV->set_cur(chtcount, yrind);
	   	deadnCYV->put(&regnod->deadn[0], 1, 1);
	} else if (regnod->outvarlist[60]==2) {
		deadnCYV->set_cur(chtcount, yrind, 0);
	   	deadnCYV->put(&regnod->deadn[0], 1, 1, 12);
	}

	if (regnod->outvarlist[61]==1){
		dwdCYV->set_cur(chtcount, yrind);
	   	dwdCYV->put(&regnod->dwd[0], 1, 1);
	} else if (regnod->outvarlist[61]==2) {
		dwdCYV->set_cur(chtcount, yrind, 0);
	   	dwdCYV->put(&regnod->dwd[0], 1, 1, 12);
	}

	if (regnod->outvarlist[62]==1){
		dwdrhCYV->set_cur(chtcount, yrind);
	   	dwdrhCYV->put(&regnod->dwdrh[0], 1, 1);
	} else if (regnod->outvarlist[62]==2) {
		dwdrhCYV->set_cur(chtcount, yrind, 0);
	   	dwdrhCYV->put(&regnod->dwdrh[0], 1, 1, 12);
	}

	if (regnod->outvarlist[63]>=1){
		ORLCYV->set_cur(chtcount, yrind);
		ORLCYV->put(&regnod->ORL, 1, 1);
	}


};

void RegnOutputer::setOutData(RegnOutData *regnodp) {
	regnod = regnodp;
};
