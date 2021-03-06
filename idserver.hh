// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __idserver_hh__
#define __idserver_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_idserver
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_idserver
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_idserver
#endif






#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE MiLissa

_CORBA_MODULE_BEG

#ifndef __MiLissa_mIdServer__
#define __MiLissa_mIdServer__

  class IdServer;
  class _objref_IdServer;
  class _impl_IdServer;
  
  typedef _objref_IdServer* IdServer_ptr;
  typedef IdServer_ptr IdServerRef;

  class IdServer_Helper {
  public:
    typedef IdServer_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_IdServer, IdServer_Helper> IdServer_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_IdServer,IdServer_Helper > IdServer_out;

#endif

  // interface IdServer
  class IdServer {
  public:
    // Declarations for this interface type.
    typedef IdServer_ptr _ptr_type;
    typedef IdServer_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_IdServer :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    char* generateId(const char* fileName);
    ::CORBA::Boolean verifyId(const char* id);

    inline _objref_IdServer()  { _PR_setobj(0); }  // nil
    _objref_IdServer(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_IdServer();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_IdServer(const _objref_IdServer&);
    _objref_IdServer& operator = (const _objref_IdServer&);
    // not implemented

    friend class IdServer;
  };

  class _pof_IdServer : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_IdServer() : _OMNI_NS(proxyObjectFactory)(IdServer::_PD_repoId) {}
    virtual ~_pof_IdServer();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_IdServer :
    public virtual omniServant
  {
  public:
    virtual ~_impl_IdServer();

    virtual char* generateId(const char* fileName) = 0;
    virtual ::CORBA::Boolean verifyId(const char* id) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_MiLissa
_CORBA_MODULE_BEG

  class IdServer :
    public virtual MiLissa::_impl_IdServer,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~IdServer();

    inline ::MiLissa::IdServer_ptr _this() {
      return (::MiLissa::IdServer_ptr) _do_this(::MiLissa::IdServer::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_MiLissa
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr



inline void
MiLissa::IdServer::_marshalObjRef(::MiLissa::IdServer_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_idserver
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_idserver
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_idserver
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_idserver
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_idserver
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_idserver
#endif

#endif  // __idserver_hh__

