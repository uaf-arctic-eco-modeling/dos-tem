/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package TEMJNI;

public class atm2lnd_env {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected atm2lnd_env(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(atm2lnd_env obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        temcoreJNI.delete_atm2lnd_env(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setPrec(double value) {
    temcoreJNI.atm2lnd_env_prec_set(swigCPtr, this, value);
  }

  public double getPrec() {
    return temcoreJNI.atm2lnd_env_prec_get(swigCPtr, this);
  }

  public void setSnfl(double value) {
    temcoreJNI.atm2lnd_env_snfl_set(swigCPtr, this, value);
  }

  public double getSnfl() {
    return temcoreJNI.atm2lnd_env_snfl_get(swigCPtr, this);
  }

  public void setRnfl(double value) {
    temcoreJNI.atm2lnd_env_rnfl_set(swigCPtr, this, value);
  }

  public double getRnfl() {
    return temcoreJNI.atm2lnd_env_rnfl_get(swigCPtr, this);
  }

  public void setGirr(double value) {
    temcoreJNI.atm2lnd_env_girr_set(swigCPtr, this, value);
  }

  public double getGirr() {
    return temcoreJNI.atm2lnd_env_girr_get(swigCPtr, this);
  }

  public void setNirr(double value) {
    temcoreJNI.atm2lnd_env_nirr_set(swigCPtr, this, value);
  }

  public double getNirr() {
    return temcoreJNI.atm2lnd_env_nirr_get(swigCPtr, this);
  }

  public void setPar(double value) {
    temcoreJNI.atm2lnd_env_par_set(swigCPtr, this, value);
  }

  public double getPar() {
    return temcoreJNI.atm2lnd_env_par_get(swigCPtr, this);
  }

  public atm2lnd_env() {
    this(temcoreJNI.new_atm2lnd_env(), true);
  }

}
