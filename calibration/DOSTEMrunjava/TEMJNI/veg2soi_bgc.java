/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package TEMJNI;

public class veg2soi_bgc {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected veg2soi_bgc(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(veg2soi_bgc obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        temcoreJNI.delete_veg2soi_bgc(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setLtrfalc(double value) {
    temcoreJNI.veg2soi_bgc_ltrfalc_set(swigCPtr, this, value);
  }

  public double getLtrfalc() {
    return temcoreJNI.veg2soi_bgc_ltrfalc_get(swigCPtr, this);
  }

  public void setLtrfaln(double value) {
    temcoreJNI.veg2soi_bgc_ltrfaln_set(swigCPtr, this, value);
  }

  public double getLtrfaln() {
    return temcoreJNI.veg2soi_bgc_ltrfaln_get(swigCPtr, this);
  }

  public veg2soi_bgc() {
    this(temcoreJNI.new_veg2soi_bgc(), true);
  }

}
