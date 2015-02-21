

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Tue Apr 29 01:07:17 2014
 */
/* Compiler settings for AveActiveDesktop.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __AveActiveDesktop_h__
#define __AveActiveDesktop_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAveActiveDesktopHost_FWD_DEFINED__
#define __IAveActiveDesktopHost_FWD_DEFINED__
typedef interface IAveActiveDesktopHost IAveActiveDesktopHost;

#endif 	/* __IAveActiveDesktopHost_FWD_DEFINED__ */


#ifndef __IAxWinHostWindowAggregator_FWD_DEFINED__
#define __IAxWinHostWindowAggregator_FWD_DEFINED__
typedef interface IAxWinHostWindowAggregator IAxWinHostWindowAggregator;

#endif 	/* __IAxWinHostWindowAggregator_FWD_DEFINED__ */


#ifndef __IAveHtmlDesktop_FWD_DEFINED__
#define __IAveHtmlDesktop_FWD_DEFINED__
typedef interface IAveHtmlDesktop IAveHtmlDesktop;

#endif 	/* __IAveHtmlDesktop_FWD_DEFINED__ */


#ifndef __IAveHtmlBackgroundMenuHandler_FWD_DEFINED__
#define __IAveHtmlBackgroundMenuHandler_FWD_DEFINED__
typedef interface IAveHtmlBackgroundMenuHandler IAveHtmlBackgroundMenuHandler;

#endif 	/* __IAveHtmlBackgroundMenuHandler_FWD_DEFINED__ */


#ifndef __AveActiveDesktopHost_FWD_DEFINED__
#define __AveActiveDesktopHost_FWD_DEFINED__

#ifdef __cplusplus
typedef class AveActiveDesktopHost AveActiveDesktopHost;
#else
typedef struct AveActiveDesktopHost AveActiveDesktopHost;
#endif /* __cplusplus */

#endif 	/* __AveActiveDesktopHost_FWD_DEFINED__ */


#ifndef __AxWinHostWindowAggregator_FWD_DEFINED__
#define __AxWinHostWindowAggregator_FWD_DEFINED__

#ifdef __cplusplus
typedef class AxWinHostWindowAggregator AxWinHostWindowAggregator;
#else
typedef struct AxWinHostWindowAggregator AxWinHostWindowAggregator;
#endif /* __cplusplus */

#endif 	/* __AxWinHostWindowAggregator_FWD_DEFINED__ */


#ifndef __AveHtmlDesktop_FWD_DEFINED__
#define __AveHtmlDesktop_FWD_DEFINED__

#ifdef __cplusplus
typedef class AveHtmlDesktop AveHtmlDesktop;
#else
typedef struct AveHtmlDesktop AveHtmlDesktop;
#endif /* __cplusplus */

#endif 	/* __AveHtmlDesktop_FWD_DEFINED__ */


#ifndef __AveHtmlBackgroundMenuHandler_FWD_DEFINED__
#define __AveHtmlBackgroundMenuHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class AveHtmlBackgroundMenuHandler AveHtmlBackgroundMenuHandler;
#else
typedef struct AveHtmlBackgroundMenuHandler AveHtmlBackgroundMenuHandler;
#endif /* __cplusplus */

#endif 	/* __AveHtmlBackgroundMenuHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAveActiveDesktopHost_INTERFACE_DEFINED__
#define __IAveActiveDesktopHost_INTERFACE_DEFINED__

/* interface IAveActiveDesktopHost */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAveActiveDesktopHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A03E3472-694A-4834-BC25-86533D143E7C")
    IAveActiveDesktopHost : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetHTMLBackground( 
            /* [in] */ BSTR urlOrFile) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsRunning( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAveActiveDesktopHostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAveActiveDesktopHost * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAveActiveDesktopHost * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAveActiveDesktopHost * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHTMLBackground )( 
            IAveActiveDesktopHost * This,
            /* [in] */ BSTR urlOrFile);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRunning )( 
            IAveActiveDesktopHost * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IAveActiveDesktopHostVtbl;

    interface IAveActiveDesktopHost
    {
        CONST_VTBL struct IAveActiveDesktopHostVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAveActiveDesktopHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAveActiveDesktopHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAveActiveDesktopHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAveActiveDesktopHost_SetHTMLBackground(This,urlOrFile)	\
    ( (This)->lpVtbl -> SetHTMLBackground(This,urlOrFile) ) 

#define IAveActiveDesktopHost_get_IsRunning(This,pVal)	\
    ( (This)->lpVtbl -> get_IsRunning(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAveActiveDesktopHost_INTERFACE_DEFINED__ */


#ifndef __IAxWinHostWindowAggregator_INTERFACE_DEFINED__
#define __IAxWinHostWindowAggregator_INTERFACE_DEFINED__

/* interface IAxWinHostWindowAggregator */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAxWinHostWindowAggregator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1C4AE50B-88FF-4050-A05C-B1228170A481")
    IAxWinHostWindowAggregator : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IAxWinHostWindowAggregatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxWinHostWindowAggregator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxWinHostWindowAggregator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxWinHostWindowAggregator * This);
        
        END_INTERFACE
    } IAxWinHostWindowAggregatorVtbl;

    interface IAxWinHostWindowAggregator
    {
        CONST_VTBL struct IAxWinHostWindowAggregatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxWinHostWindowAggregator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxWinHostWindowAggregator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxWinHostWindowAggregator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxWinHostWindowAggregator_INTERFACE_DEFINED__ */


#ifndef __IAveHtmlDesktop_INTERFACE_DEFINED__
#define __IAveHtmlDesktop_INTERFACE_DEFINED__

/* interface IAveHtmlDesktop */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAveHtmlDesktop;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BD41F4F-D619-46FC-92DF-A3A393B62C51")
    IAveHtmlDesktop : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ BSTR urlOrFile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsActive( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAveHtmlDesktopVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAveHtmlDesktop * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAveHtmlDesktop * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAveHtmlDesktop * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAveHtmlDesktop * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAveHtmlDesktop * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAveHtmlDesktop * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAveHtmlDesktop * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Set )( 
            IAveHtmlDesktop * This,
            /* [in] */ BSTR urlOrFile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsActive )( 
            IAveHtmlDesktop * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IAveHtmlDesktopVtbl;

    interface IAveHtmlDesktop
    {
        CONST_VTBL struct IAveHtmlDesktopVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAveHtmlDesktop_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAveHtmlDesktop_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAveHtmlDesktop_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAveHtmlDesktop_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAveHtmlDesktop_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAveHtmlDesktop_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAveHtmlDesktop_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAveHtmlDesktop_Set(This,urlOrFile)	\
    ( (This)->lpVtbl -> Set(This,urlOrFile) ) 

#define IAveHtmlDesktop_get_IsActive(This,pVal)	\
    ( (This)->lpVtbl -> get_IsActive(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAveHtmlDesktop_INTERFACE_DEFINED__ */


#ifndef __IAveHtmlBackgroundMenuHandler_INTERFACE_DEFINED__
#define __IAveHtmlBackgroundMenuHandler_INTERFACE_DEFINED__

/* interface IAveHtmlBackgroundMenuHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAveHtmlBackgroundMenuHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F0B462B-6EFD-493B-83AD-8E8AE0D3D117")
    IAveHtmlBackgroundMenuHandler : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IAveHtmlBackgroundMenuHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAveHtmlBackgroundMenuHandler * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAveHtmlBackgroundMenuHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAveHtmlBackgroundMenuHandler * This);
        
        END_INTERFACE
    } IAveHtmlBackgroundMenuHandlerVtbl;

    interface IAveHtmlBackgroundMenuHandler
    {
        CONST_VTBL struct IAveHtmlBackgroundMenuHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAveHtmlBackgroundMenuHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAveHtmlBackgroundMenuHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAveHtmlBackgroundMenuHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAveHtmlBackgroundMenuHandler_INTERFACE_DEFINED__ */



#ifndef __AveActiveDesktopLib_LIBRARY_DEFINED__
#define __AveActiveDesktopLib_LIBRARY_DEFINED__

/* library AveActiveDesktopLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AveActiveDesktopLib;

EXTERN_C const CLSID CLSID_AveActiveDesktopHost;

#ifdef __cplusplus

class DECLSPEC_UUID("C3E638A6-4610-4029-99CC-04353C212FC1")
AveActiveDesktopHost;
#endif

EXTERN_C const CLSID CLSID_AxWinHostWindowAggregator;

#ifdef __cplusplus

class DECLSPEC_UUID("B4BEE677-4019-4979-A0D9-A23A249FEAC8")
AxWinHostWindowAggregator;
#endif

EXTERN_C const CLSID CLSID_AveHtmlDesktop;

#ifdef __cplusplus

class DECLSPEC_UUID("990825CC-3C93-4E11-8E44-EBA73238FCD1")
AveHtmlDesktop;
#endif

EXTERN_C const CLSID CLSID_AveHtmlBackgroundMenuHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("96A2B6AE-9E00-4708-8B2A-5694F4C2E45E")
AveHtmlBackgroundMenuHandler;
#endif
#endif /* __AveActiveDesktopLib_LIBRARY_DEFINED__ */

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


