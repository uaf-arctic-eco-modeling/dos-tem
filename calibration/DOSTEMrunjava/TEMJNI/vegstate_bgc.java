/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package TEMJNI;

public class vegstate_bgc {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected vegstate_bgc(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vegstate_bgc obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        temcoreJNI.delete_vegstate_bgc(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setC(double value) {
    temcoreJNI.vegstate_bgc_c_set(swigCPtr, this, value);
  }

  public double getC() {
    return temcoreJNI.vegstate_bgc_c_get(swigCPtr, this);
  }

  public void setDeadc(double value) {
    temcoreJNI.vegstate_bgc_deadc_set(swigCPtr, this, value);
  }

  public double getDeadc() {
    return temcoreJNI.vegstate_bgc_deadc_get(swigCPtr, this);
  }

  public void setDeadn(double value) {
    temcoreJNI.vegstate_bgc_deadn_set(swigCPtr, this, value);
  }

  public double getDeadn() {
    return temcoreJNI.vegstate_bgc_deadn_get(swigCPtr, this);
  }

  public void setSton(double value) {
    temcoreJNI.vegstate_bgc_ston_set(swigCPtr, this, value);
  }

  public double getSton() {
    return temcoreJNI.vegstate_bgc_ston_get(swigCPtr, this);
  }

  public void setStrn(double value) {
    temcoreJNI.vegstate_bgc_strn_set(swigCPtr, this, value);
  }

  public double getStrn() {
    return temcoreJNI.vegstate_bgc_strn_get(swigCPtr, this);
  }

  public void setUnnormleaf(double value) {
    temcoreJNI.vegstate_bgc_unnormleaf_set(swigCPtr, this, value);
  }

  public double getUnnormleaf() {
    return temcoreJNI.vegstate_bgc_unnormleaf_get(swigCPtr, this);
  }

  public vegstate_bgc() {
    this(temcoreJNI.new_vegstate_bgc(), true);
  }

}
