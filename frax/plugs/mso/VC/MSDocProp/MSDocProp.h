
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Feb 05 21:43:06 2002
 */
/* Compiler settings for C:\Programming Projects\Columbia\VC\MSDocProp\MSDocProp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MSDocProp_h__
#define __MSDocProp_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAMTSSimpleProp_FWD_DEFINED__
#define __IAMTSSimpleProp_FWD_DEFINED__
typedef interface IAMTSSimpleProp IAMTSSimpleProp;
#endif 	/* __IAMTSSimpleProp_FWD_DEFINED__ */


#ifndef __AMTSSimpleProp_FWD_DEFINED__
#define __AMTSSimpleProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class AMTSSimpleProp AMTSSimpleProp;
#else
typedef struct AMTSSimpleProp AMTSSimpleProp;
#endif /* __cplusplus */

#endif 	/* __AMTSSimpleProp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAMTSSimpleProp_INTERFACE_DEFINED__
#define __IAMTSSimpleProp_INTERFACE_DEFINED__

/* interface IAMTSSimpleProp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAMTSSimpleProp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4CA377E-7A32-49C5-B0CB-003ABEF42439")
    IAMTSSimpleProp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewSummaryInfo( 
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewDocSummaryInfo( 
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewMFSummaryInfo( 
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewUserDefinedProperties( 
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewHyperlinks( 
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTSSimplePropVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTSSimpleProp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTSSimpleProp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTSSimpleProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAMTSSimpleProp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAMTSSimpleProp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAMTSSimpleProp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAMTSSimpleProp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewSummaryInfo )( 
            IAMTSSimpleProp * This,
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewDocSummaryInfo )( 
            IAMTSSimpleProp * This,
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewMFSummaryInfo )( 
            IAMTSSimpleProp * This,
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewUserDefinedProperties )( 
            IAMTSSimpleProp * This,
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewHyperlinks )( 
            IAMTSSimpleProp * This,
            /* [in] */ BSTR bstrFullQDocPath,
            /* [retval][out] */ BSTR *pbstrXMLPropString);
        
        END_INTERFACE
    } IAMTSSimplePropVtbl;

    interface IAMTSSimpleProp
    {
        CONST_VTBL struct IAMTSSimplePropVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTSSimpleProp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTSSimpleProp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTSSimpleProp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTSSimpleProp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAMTSSimpleProp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAMTSSimpleProp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAMTSSimpleProp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAMTSSimpleProp_ViewSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)	\
    (This)->lpVtbl -> ViewSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)

#define IAMTSSimpleProp_ViewDocSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)	\
    (This)->lpVtbl -> ViewDocSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)

#define IAMTSSimpleProp_ViewMFSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)	\
    (This)->lpVtbl -> ViewMFSummaryInfo(This,bstrFullQDocPath,pbstrXMLPropString)

#define IAMTSSimpleProp_ViewUserDefinedProperties(This,bstrFullQDocPath,pbstrXMLPropString)	\
    (This)->lpVtbl -> ViewUserDefinedProperties(This,bstrFullQDocPath,pbstrXMLPropString)

#define IAMTSSimpleProp_ViewHyperlinks(This,bstrFullQDocPath,pbstrXMLPropString)	\
    (This)->lpVtbl -> ViewHyperlinks(This,bstrFullQDocPath,pbstrXMLPropString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAMTSSimpleProp_ViewSummaryInfo_Proxy( 
    IAMTSSimpleProp * This,
    /* [in] */ BSTR bstrFullQDocPath,
    /* [retval][out] */ BSTR *pbstrXMLPropString);


void __RPC_STUB IAMTSSimpleProp_ViewSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAMTSSimpleProp_ViewDocSummaryInfo_Proxy( 
    IAMTSSimpleProp * This,
    /* [in] */ BSTR bstrFullQDocPath,
    /* [retval][out] */ BSTR *pbstrXMLPropString);


void __RPC_STUB IAMTSSimpleProp_ViewDocSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAMTSSimpleProp_ViewMFSummaryInfo_Proxy( 
    IAMTSSimpleProp * This,
    /* [in] */ BSTR bstrFullQDocPath,
    /* [retval][out] */ BSTR *pbstrXMLPropString);


void __RPC_STUB IAMTSSimpleProp_ViewMFSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAMTSSimpleProp_ViewUserDefinedProperties_Proxy( 
    IAMTSSimpleProp * This,
    /* [in] */ BSTR bstrFullQDocPath,
    /* [retval][out] */ BSTR *pbstrXMLPropString);


void __RPC_STUB IAMTSSimpleProp_ViewUserDefinedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAMTSSimpleProp_ViewHyperlinks_Proxy( 
    IAMTSSimpleProp * This,
    /* [in] */ BSTR bstrFullQDocPath,
    /* [retval][out] */ BSTR *pbstrXMLPropString);


void __RPC_STUB IAMTSSimpleProp_ViewHyperlinks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTSSimpleProp_INTERFACE_DEFINED__ */



#ifndef __MSDOCPROPLib_LIBRARY_DEFINED__
#define __MSDOCPROPLib_LIBRARY_DEFINED__

/* library MSDOCPROPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSDOCPROPLib;

EXTERN_C const CLSID CLSID_AMTSSimpleProp;

#ifdef __cplusplus

class DECLSPEC_UUID("E4920D42-218D-4AE5-BCE5-8A6B3B276D80")
AMTSSimpleProp;
#endif
#endif /* __MSDOCPROPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


