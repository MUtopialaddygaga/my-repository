/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace cAudio {

using System;
using System.Runtime.InteropServices;

public class IAudioDecoderFactory : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IAudioDecoderFactory(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IAudioDecoderFactory obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IAudioDecoderFactory() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          cAudioCSharpWrapperPINVOKE.delete_IAudioDecoderFactory(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public IAudioDecoderFactory() : this(cAudioCSharpWrapperPINVOKE.new_IAudioDecoderFactory(), true) {
    SwigDirectorConnect();
  }

  public virtual IAudioDecoder CreateAudioDecoder(IDataSource stream) {
    IntPtr cPtr = cAudioCSharpWrapperPINVOKE.IAudioDecoderFactory_CreateAudioDecoder(swigCPtr, IDataSource.getCPtr(stream));
    IAudioDecoder ret = (cPtr == IntPtr.Zero) ? null : new IAudioDecoder(cPtr, false);
    return ret;
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("CreateAudioDecoder", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateIAudioDecoderFactory_0(SwigDirectorCreateAudioDecoder);
    cAudioCSharpWrapperPINVOKE.IAudioDecoderFactory_director_connect(swigCPtr, swigDelegate0);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(IAudioDecoderFactory));
    return hasDerivedMethod;
  }

  private IntPtr SwigDirectorCreateAudioDecoder(IntPtr stream) {
    return IAudioDecoder.getCPtr(CreateAudioDecoder((stream == IntPtr.Zero) ? null : new IDataSource(stream, false))).Handle;
  }

  public delegate IntPtr SwigDelegateIAudioDecoderFactory_0(IntPtr stream);

  private SwigDelegateIAudioDecoderFactory_0 swigDelegate0;

  private static Type[] swigMethodTypes0 = new Type[] { typeof(IDataSource) };
}

}
