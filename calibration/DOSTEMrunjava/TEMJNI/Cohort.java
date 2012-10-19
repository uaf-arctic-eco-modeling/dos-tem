/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package TEMJNI;

public class Cohort {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected Cohort(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Cohort obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        temcoreJNI.delete_Cohort(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Cohort() {
    this(temcoreJNI.new_Cohort(), true);
  }

  public void setEquiled(boolean value) {
    temcoreJNI.Cohort_equiled_set(swigCPtr, this, value);
  }

  public boolean getEquiled() {
    return temcoreJNI.Cohort_equiled_get(swigCPtr, this);
  }

  public void setSpined(boolean value) {
    temcoreJNI.Cohort_spined_set(swigCPtr, this, value);
  }

  public boolean getSpined() {
    return temcoreJNI.Cohort_spined_get(swigCPtr, this);
  }

  public void setTransed(boolean value) {
    temcoreJNI.Cohort_transed_set(swigCPtr, this, value);
  }

  public boolean getTransed() {
    return temcoreJNI.Cohort_transed_get(swigCPtr, this);
  }

  public void setWatbaled(boolean value) {
    temcoreJNI.Cohort_watbaled_set(swigCPtr, this, value);
  }

  public boolean getWatbaled() {
    return temcoreJNI.Cohort_watbaled_get(swigCPtr, this);
  }

  public void setFailed(boolean value) {
    temcoreJNI.Cohort_failed_set(swigCPtr, this, value);
  }

  public boolean getFailed() {
    return temcoreJNI.Cohort_failed_get(swigCPtr, this);
  }

  public void setErrorid(int value) {
    temcoreJNI.Cohort_errorid_set(swigCPtr, this, value);
  }

  public int getErrorid() {
    return temcoreJNI.Cohort_errorid_get(swigCPtr, this);
  }

  public void setOutputSpinup(boolean value) {
    temcoreJNI.Cohort_outputSpinup_set(swigCPtr, this, value);
  }

  public boolean getOutputSpinup() {
    return temcoreJNI.Cohort_outputSpinup_get(swigCPtr, this);
  }

  public void setFriderived(boolean value) {
    temcoreJNI.Cohort_friderived_set(swigCPtr, this, value);
  }

  public boolean getFriderived() {
    return temcoreJNI.Cohort_friderived_get(swigCPtr, this);
  }

  public void setFirstfireyr(int value) {
    temcoreJNI.Cohort_firstfireyr_set(swigCPtr, this, value);
  }

  public int getFirstfireyr() {
    return temcoreJNI.Cohort_firstfireyr_get(swigCPtr, this);
  }

  public void setEnvmodule(boolean value) {
    temcoreJNI.Cohort_envmodule_set(swigCPtr, this, value);
  }

  public boolean getEnvmodule() {
    return temcoreJNI.Cohort_envmodule_get(swigCPtr, this);
  }

  public void setEcomodule(boolean value) {
    temcoreJNI.Cohort_ecomodule_set(swigCPtr, this, value);
  }

  public boolean getEcomodule() {
    return temcoreJNI.Cohort_ecomodule_get(swigCPtr, this);
  }

  public void setDsbmodule(boolean value) {
    temcoreJNI.Cohort_dsbmodule_set(swigCPtr, this, value);
  }

  public boolean getDsbmodule() {
    return temcoreJNI.Cohort_dsbmodule_get(swigCPtr, this);
  }

  public void setDslmodule(boolean value) {
    temcoreJNI.Cohort_dslmodule_set(swigCPtr, this, value);
  }

  public boolean getDslmodule() {
    return temcoreJNI.Cohort_dslmodule_get(swigCPtr, this);
  }

  public void setOutRegn(boolean value) {
    temcoreJNI.Cohort_outRegn_set(swigCPtr, this, value);
  }

  public boolean getOutRegn() {
    return temcoreJNI.Cohort_outRegn_get(swigCPtr, this);
  }

  public void setOutSiteDay(boolean value) {
    temcoreJNI.Cohort_outSiteDay_set(swigCPtr, this, value);
  }

  public boolean getOutSiteDay() {
    return temcoreJNI.Cohort_outSiteDay_get(swigCPtr, this);
  }

  public void setOutSiteMonth(boolean value) {
    temcoreJNI.Cohort_outSiteMonth_set(swigCPtr, this, value);
  }

  public boolean getOutSiteMonth() {
    return temcoreJNI.Cohort_outSiteMonth_get(swigCPtr, this);
  }

  public void setOutSiteYear(boolean value) {
    temcoreJNI.Cohort_outSiteYear_set(swigCPtr, this, value);
  }

  public boolean getOutSiteYear() {
    return temcoreJNI.Cohort_outSiteYear_get(swigCPtr, this);
  }

  public void setOutSoilClm(boolean value) {
    temcoreJNI.Cohort_outSoilClm_set(swigCPtr, this, value);
  }

  public boolean getOutSoilClm() {
    return temcoreJNI.Cohort_outSoilClm_get(swigCPtr, this);
  }

  public void setChtlu(CohortLookup value) {
    temcoreJNI.Cohort_chtlu_set(swigCPtr, this, CohortLookup.getCPtr(value), value);
  }

  public CohortLookup getChtlu() {
    long cPtr = temcoreJNI.Cohort_chtlu_get(swigCPtr, this);
    return (cPtr == 0) ? null : new CohortLookup(cPtr, false);
  }

  public void setGround(SWIGTYPE_p_Ground value) {
    temcoreJNI.Cohort_ground_set(swigCPtr, this, SWIGTYPE_p_Ground.getCPtr(value));
  }

  public SWIGTYPE_p_Ground getGround() {
    return new SWIGTYPE_p_Ground(temcoreJNI.Cohort_ground_get(swigCPtr, this), true);
  }

  public void setVe(SWIGTYPE_p_Vegetation_Env value) {
    temcoreJNI.Cohort_ve_set(swigCPtr, this, SWIGTYPE_p_Vegetation_Env.getCPtr(value));
  }

  public SWIGTYPE_p_Vegetation_Env getVe() {
    return new SWIGTYPE_p_Vegetation_Env(temcoreJNI.Cohort_ve_get(swigCPtr, this), true);
  }

  public void setVb(SWIGTYPE_p_Vegetation_Bgc value) {
    temcoreJNI.Cohort_vb_set(swigCPtr, this, SWIGTYPE_p_Vegetation_Bgc.getCPtr(value));
  }

  public SWIGTYPE_p_Vegetation_Bgc getVb() {
    return new SWIGTYPE_p_Vegetation_Bgc(temcoreJNI.Cohort_vb_get(swigCPtr, this), true);
  }

  public void setSb(SWIGTYPE_p_Soil_Bgc value) {
    temcoreJNI.Cohort_sb_set(swigCPtr, this, SWIGTYPE_p_Soil_Bgc.getCPtr(value));
  }

  public SWIGTYPE_p_Soil_Bgc getSb() {
    return new SWIGTYPE_p_Soil_Bgc(temcoreJNI.Cohort_sb_get(swigCPtr, this), true);
  }

  public void setIntegrator(SWIGTYPE_p_Integrator value) {
    temcoreJNI.Cohort_integrator_set(swigCPtr, this, SWIGTYPE_p_Integrator.getCPtr(value));
  }

  public SWIGTYPE_p_Integrator getIntegrator() {
    return new SWIGTYPE_p_Integrator(temcoreJNI.Cohort_integrator_get(swigCPtr, this), true);
  }

  public void setFire(SWIGTYPE_p_WildFire value) {
    temcoreJNI.Cohort_fire_set(swigCPtr, this, SWIGTYPE_p_WildFire.getCPtr(value));
  }

  public SWIGTYPE_p_WildFire getFire() {
    return new SWIGTYPE_p_WildFire(temcoreJNI.Cohort_fire_get(swigCPtr, this), true);
  }

  public void setTimer(Timer value) {
    temcoreJNI.Cohort_timer_set(swigCPtr, this, Timer.getCPtr(value), value);
  }

  public Timer getTimer() {
    long cPtr = temcoreJNI.Cohort_timer_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Timer(cPtr, false);
  }

  public void setAtm(SWIGTYPE_p_Atmosphere value) {
    temcoreJNI.Cohort_atm_set(swigCPtr, this, SWIGTYPE_p_Atmosphere.getCPtr(value));
  }

  public SWIGTYPE_p_Atmosphere getAtm() {
    long cPtr = temcoreJNI.Cohort_atm_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Atmosphere(cPtr, false);
  }

  public void init() {
    temcoreJNI.Cohort_init(swigCPtr, this);
  }

  public void reset() {
    temcoreJNI.Cohort_reset(swigCPtr, this);
  }

  public void setTime(Timer timerp) {
    temcoreJNI.Cohort_setTime(swigCPtr, this, Timer.getCPtr(timerp), timerp);
  }

  public void setModelData(ModelData md) {
    temcoreJNI.Cohort_setModelData(swigCPtr, this, ModelData.getCPtr(md), md);
  }

  public void setInputData(RegionData rd, GridData gd, CohortData cd) {
    temcoreJNI.Cohort_setInputData(swigCPtr, this, RegionData.getCPtr(rd), rd, GridData.getCPtr(gd), gd, CohortData.getCPtr(cd), cd);
  }

  public void setProcessData(EnvData ed, BgcData bd, FirData fd) {
    temcoreJNI.Cohort_setProcessData(swigCPtr, this, EnvData.getCPtr(ed), ed, BgcData.getCPtr(bd), bd, FirData.getCPtr(fd), fd);
  }

  public void setAtmData(Grid grid) {
    temcoreJNI.Cohort_setAtmData(swigCPtr, this, Grid.getCPtr(grid), grid);
  }

  public void setSiteOutData(AtmOutData atmodp, VegOutData vegodp, SnowSoilOutData sslodp) {
    temcoreJNI.Cohort_setSiteOutData(swigCPtr, this, AtmOutData.getCPtr(atmodp), atmodp, VegOutData.getCPtr(vegodp), vegodp, SnowSoilOutData.getCPtr(sslodp), sslodp);
  }

  public void setRegnOutData(RegnOutData regnodp) {
    temcoreJNI.Cohort_setRegnOutData(swigCPtr, this, RegnOutData.getCPtr(regnodp), regnodp);
  }

  public void setRestartOutData(RestartData resodp) {
    temcoreJNI.Cohort_setRestartOutData(swigCPtr, this, RestartData.getCPtr(resodp), resodp);
  }

  public boolean testEquilibrium() {
    return temcoreJNI.Cohort_testEquilibrium(swigCPtr, this);
  }

  public void fireDrivingData(boolean runsp, boolean runtr, boolean runsc) {
    temcoreJNI.Cohort_fireDrivingData(swigCPtr, this, runsp, runtr, runsc);
  }

  public int timerOutputYearIndex(boolean equiled, boolean spined, boolean outputSpinup) {
    return temcoreJNI.Cohort_timerOutputYearIndex(swigCPtr, this, equiled, spined, outputSpinup);
  }

  public void updateMonthly(int yrcnt, int curryr, int currmind, int dinmcurr, boolean assigneq, boolean useeq) {
    temcoreJNI.Cohort_updateMonthly(swigCPtr, this, yrcnt, curryr, currmind, dinmcurr, assigneq, useeq);
  }

  public void updateMonthly_Env(int yrcnt, int curryr, int currmind, int dinmcurr, boolean assigneq) {
    temcoreJNI.Cohort_updateMonthly_Env(swigCPtr, this, yrcnt, curryr, currmind, dinmcurr, assigneq);
  }

  public void updateMonthly_Bgc(int yrcnt, int curryr, int currmind, int dinmcurr, boolean useeq) {
    temcoreJNI.Cohort_updateMonthly_Bgc(swigCPtr, this, yrcnt, curryr, currmind, dinmcurr, useeq);
  }

  public void updateMonthly_Fir(int yrcnt, int currmind) {
    temcoreJNI.Cohort_updateMonthly_Fir(swigCPtr, this, yrcnt, currmind);
  }

  public void updateMonthly_Dsl(int currmind) {
    temcoreJNI.Cohort_updateMonthly_Dsl(swigCPtr, this, currmind);
  }

  public void getLitterFallRatio(SWIGTYPE_p_double deepvsshlw, SWIGTYPE_p_double minevsshlw) {
    temcoreJNI.Cohort_getLitterFallRatio(swigCPtr, this, SWIGTYPE_p_double.getCPtr(deepvsshlw), SWIGTYPE_p_double.getCPtr(minevsshlw));
  }

  public void updateSiteDlyOutputBuffer_Env(int doy) {
    temcoreJNI.Cohort_updateSiteDlyOutputBuffer_Env(swigCPtr, this, doy);
  }

  public void updateSiteMlyOutputBuffer_Env(int im) {
    temcoreJNI.Cohort_updateSiteMlyOutputBuffer_Env(swigCPtr, this, im);
  }

  public void updateSiteMlyOutputBuffer_Bgc(int im) {
    temcoreJNI.Cohort_updateSiteMlyOutputBuffer_Bgc(swigCPtr, this, im);
  }

  public void updateSiteYlyOutputBuffer_Env() {
    temcoreJNI.Cohort_updateSiteYlyOutputBuffer_Env(swigCPtr, this);
  }

  public void updateSiteYlyOutputBuffer_Bgc() {
    temcoreJNI.Cohort_updateSiteYlyOutputBuffer_Bgc(swigCPtr, this);
  }

  public void updateSiteYlyOutputBuffer_Fir() {
    temcoreJNI.Cohort_updateSiteYlyOutputBuffer_Fir(swigCPtr, this);
  }

  public void updateRestartOutputBuffer(int stage) {
    temcoreJNI.Cohort_updateRestartOutputBuffer(swigCPtr, this, stage);
  }

  public void updateRegionalOutputBuffer(int im) {
    temcoreJNI.Cohort_updateRegionalOutputBuffer(swigCPtr, this, im);
  }

  public void updateSclmOutputBuffer(int im) {
    temcoreJNI.Cohort_updateSclmOutputBuffer(swigCPtr, this, im);
  }

  public void setEd(EnvData value) {
    temcoreJNI.Cohort_ed_set(swigCPtr, this, EnvData.getCPtr(value), value);
  }

  public EnvData getEd() {
    long cPtr = temcoreJNI.Cohort_ed_get(swigCPtr, this);
    return (cPtr == 0) ? null : new EnvData(cPtr, false);
  }

  public void setBd(BgcData value) {
    temcoreJNI.Cohort_bd_set(swigCPtr, this, BgcData.getCPtr(value), value);
  }

  public BgcData getBd() {
    long cPtr = temcoreJNI.Cohort_bd_get(swigCPtr, this);
    return (cPtr == 0) ? null : new BgcData(cPtr, false);
  }

  public void setFd(FirData value) {
    temcoreJNI.Cohort_fd_set(swigCPtr, this, FirData.getCPtr(value), value);
  }

  public FirData getFd() {
    long cPtr = temcoreJNI.Cohort_fd_get(swigCPtr, this);
    return (cPtr == 0) ? null : new FirData(cPtr, false);
  }

  public void setMd(ModelData value) {
    temcoreJNI.Cohort_md_set(swigCPtr, this, ModelData.getCPtr(value), value);
  }

  public ModelData getMd() {
    long cPtr = temcoreJNI.Cohort_md_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ModelData(cPtr, false);
  }

  public void setRd(RegionData value) {
    temcoreJNI.Cohort_rd_set(swigCPtr, this, RegionData.getCPtr(value), value);
  }

  public RegionData getRd() {
    long cPtr = temcoreJNI.Cohort_rd_get(swigCPtr, this);
    return (cPtr == 0) ? null : new RegionData(cPtr, false);
  }

  public void setGd(GridData value) {
    temcoreJNI.Cohort_gd_set(swigCPtr, this, GridData.getCPtr(value), value);
  }

  public GridData getGd() {
    long cPtr = temcoreJNI.Cohort_gd_get(swigCPtr, this);
    return (cPtr == 0) ? null : new GridData(cPtr, false);
  }

  public void setCd(CohortData value) {
    temcoreJNI.Cohort_cd_set(swigCPtr, this, CohortData.getCPtr(value), value);
  }

  public CohortData getCd() {
    long cPtr = temcoreJNI.Cohort_cd_get(swigCPtr, this);
    return (cPtr == 0) ? null : new CohortData(cPtr, false);
  }

  public void setResid(RestartData value) {
    temcoreJNI.Cohort_resid_set(swigCPtr, this, RestartData.getCPtr(value), value);
  }

  public RestartData getResid() {
    long cPtr = temcoreJNI.Cohort_resid_get(swigCPtr, this);
    return (cPtr == 0) ? null : new RestartData(cPtr, false);
  }

  public void setSitein(SiteIn value) {
    temcoreJNI.Cohort_sitein_set(swigCPtr, this, SiteIn.getCPtr(value), value);
  }

  public SiteIn getSitein() {
    long cPtr = temcoreJNI.Cohort_sitein_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SiteIn(cPtr, false);
  }

  public void setAtmod(AtmOutData value) {
    temcoreJNI.Cohort_atmod_set(swigCPtr, this, AtmOutData.getCPtr(value), value);
  }

  public AtmOutData getAtmod() {
    long cPtr = temcoreJNI.Cohort_atmod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new AtmOutData(cPtr, false);
  }

  public void setVegod(VegOutData value) {
    temcoreJNI.Cohort_vegod_set(swigCPtr, this, VegOutData.getCPtr(value), value);
  }

  public VegOutData getVegod() {
    long cPtr = temcoreJNI.Cohort_vegod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VegOutData(cPtr, false);
  }

  public void setSslod(SnowSoilOutData value) {
    temcoreJNI.Cohort_sslod_set(swigCPtr, this, SnowSoilOutData.getCPtr(value), value);
  }

  public SnowSoilOutData getSslod() {
    long cPtr = temcoreJNI.Cohort_sslod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SnowSoilOutData(cPtr, false);
  }

  public void setRegnod(RegnOutData value) {
    temcoreJNI.Cohort_regnod_set(swigCPtr, this, RegnOutData.getCPtr(value), value);
  }

  public RegnOutData getRegnod() {
    long cPtr = temcoreJNI.Cohort_regnod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new RegnOutData(cPtr, false);
  }

  public void setResod(RestartData value) {
    temcoreJNI.Cohort_resod_set(swigCPtr, this, RestartData.getCPtr(value), value);
  }

  public RestartData getResod() {
    long cPtr = temcoreJNI.Cohort_resod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new RestartData(cPtr, false);
  }

  public void setSclmod(SWIGTYPE_p_SoilClm value) {
    temcoreJNI.Cohort_sclmod_set(swigCPtr, this, SWIGTYPE_p_SoilClm.getCPtr(value));
  }

  public SWIGTYPE_p_SoilClm getSclmod() {
    long cPtr = temcoreJNI.Cohort_sclmod_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_SoilClm(cPtr, false);
  }

  public void setVeupdateLAI5Vegc(boolean value) {
    temcoreJNI.Cohort_veupdateLAI5Vegc_set(swigCPtr, this, value);
  }

  public boolean getVeupdateLAI5Vegc() {
    return temcoreJNI.Cohort_veupdateLAI5Vegc_get(swigCPtr, this);
  }

  public void setVeenvlai(double[] value) {
    temcoreJNI.Cohort_veenvlai_set(swigCPtr, this, value);
  }

  public double[] getVeenvlai() {
    return temcoreJNI.Cohort_veenvlai_get(swigCPtr, this);
  }

  public void resetBgcPar(vegpar_bgc vbbgcpar, soipar_bgc sbbgcpar) {
    temcoreJNI.Cohort_resetBgcPar(swigCPtr, this, vegpar_bgc.getCPtr(vbbgcpar), vbbgcpar, soipar_bgc.getCPtr(sbbgcpar), sbbgcpar);
  }

  public void getBgcPar(vegpar_bgc vbbgcpar, soipar_bgc sbbgcpar) {
    temcoreJNI.Cohort_getBgcPar(swigCPtr, this, vegpar_bgc.getCPtr(vbbgcpar), vbbgcpar, soipar_bgc.getCPtr(sbbgcpar), sbbgcpar);
  }

  public void resetCalPar(vegpar_cal vegcalpar, soipar_cal soicalpar) {
    temcoreJNI.Cohort_resetCalPar(swigCPtr, this, vegpar_cal.getCPtr(vegcalpar), vegcalpar, soipar_cal.getCPtr(soicalpar), soicalpar);
  }

  public void getCalPar(vegpar_cal vegcalpar, soipar_cal soicalpar) {
    temcoreJNI.Cohort_getCalPar(swigCPtr, this, vegpar_cal.getCPtr(vegcalpar), vegcalpar, soipar_cal.getCPtr(soicalpar), soicalpar);
  }

  public void setSiteStates(SiteIn initstate) {
    temcoreJNI.Cohort_setSiteStates(swigCPtr, this, SiteIn.getCPtr(initstate), initstate);
  }

  public void getSiteStates(SiteIn currstate) {
    temcoreJNI.Cohort_getSiteStates(swigCPtr, this, SiteIn.getCPtr(currstate), currstate);
  }

  public void updateSoilLayerType(int[] TYPEsoil, int[] TYPEmin) {
    temcoreJNI.Cohort_updateSoilLayerType(swigCPtr, this, TYPEsoil, TYPEmin);
  }

}
