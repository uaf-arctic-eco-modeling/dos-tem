/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package TEMJNI;

public class snwpar_env {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected snwpar_env(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(snwpar_env obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        temcoreJNI.delete_snwpar_env(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setDenmax(float value) {
    temcoreJNI.snwpar_env_denmax_set(swigCPtr, this, value);
  }

  public float getDenmax() {
    return temcoreJNI.snwpar_env_denmax_get(swigCPtr, this);
  }

  public void setAlbmax(float value) {
    temcoreJNI.snwpar_env_albmax_set(swigCPtr, this, value);
  }

  public float getAlbmax() {
    return temcoreJNI.snwpar_env_albmax_get(swigCPtr, this);
  }

  public void setAlbmin(float value) {
    temcoreJNI.snwpar_env_albmin_set(swigCPtr, this, value);
  }

  public float getAlbmin() {
    return temcoreJNI.snwpar_env_albmin_get(swigCPtr, this);
  }

  public void setNewden(float value) {
    temcoreJNI.snwpar_env_newden_set(swigCPtr, this, value);
  }

  public float getNewden() {
    return temcoreJNI.snwpar_env_newden_get(swigCPtr, this);
  }

  public snwpar_env() {
    this(temcoreJNI.new_snwpar_env(), true);
  }

}
