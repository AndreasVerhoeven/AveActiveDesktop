

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "AveActiveDesktop.h"

#define TYPE_FORMAT_STRING_SIZE   41                                
#define PROC_FORMAT_STRING_SIZE   113                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _AveActiveDesktop_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AveActiveDesktop_MIDL_TYPE_FORMAT_STRING;

typedef struct _AveActiveDesktop_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AveActiveDesktop_MIDL_PROC_FORMAT_STRING;

typedef struct _AveActiveDesktop_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AveActiveDesktop_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const AveActiveDesktop_MIDL_TYPE_FORMAT_STRING AveActiveDesktop__MIDL_TypeFormatString;
extern const AveActiveDesktop_MIDL_PROC_FORMAT_STRING AveActiveDesktop__MIDL_ProcFormatString;
extern const AveActiveDesktop_MIDL_EXPR_FORMAT_STRING AveActiveDesktop__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAveActiveDesktopHost_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAveActiveDesktopHost_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAxWinHostWindowAggregator_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAxWinHostWindowAggregator_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAveHtmlDesktop_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAveHtmlDesktop_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAveHtmlBackgroundMenuHandler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAveHtmlBackgroundMenuHandler_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const AveActiveDesktop_MIDL_PROC_FORMAT_STRING AveActiveDesktop__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetHTMLBackground */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter urlOrFile */

/* 16 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsRunning */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x22 ),	/* 34 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 44 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Set */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x7 ),	/* 7 */
/* 64 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter urlOrFile */

/* 72 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsActive */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x8 ),	/* 8 */
/* 92 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x22 ),	/* 34 */
/* 98 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 100 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 104 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const AveActiveDesktop_MIDL_TYPE_FORMAT_STRING AveActiveDesktop__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xc ),	/* Offset= 12 (16) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 16 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x8 ),	/* 8 */
/* 20 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (6) */
/* 22 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 24 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 38 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAveActiveDesktopHost, ver. 0.0,
   GUID={0xA03E3472,0x694A,0x4834,{0xBC,0x25,0x86,0x53,0x3D,0x14,0x3E,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IAveActiveDesktopHost_FormatStringOffsetTable[] =
    {
    0,
    28
    };

static const MIDL_STUBLESS_PROXY_INFO IAveActiveDesktopHost_ProxyInfo =
    {
    &Object_StubDesc,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveActiveDesktopHost_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAveActiveDesktopHost_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveActiveDesktopHost_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IAveActiveDesktopHostProxyVtbl = 
{
    &IAveActiveDesktopHost_ProxyInfo,
    &IID_IAveActiveDesktopHost,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IAveActiveDesktopHost::SetHTMLBackground */ ,
    (void *) (INT_PTR) -1 /* IAveActiveDesktopHost::get_IsRunning */
};

const CInterfaceStubVtbl _IAveActiveDesktopHostStubVtbl =
{
    &IID_IAveActiveDesktopHost,
    &IAveActiveDesktopHost_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IAxWinHostWindowAggregator, ver. 0.0,
   GUID={0x1C4AE50B,0x88FF,0x4050,{0xA0,0x5C,0xB1,0x22,0x81,0x70,0xA4,0x81}} */

#pragma code_seg(".orpc")
static const unsigned short IAxWinHostWindowAggregator_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAxWinHostWindowAggregator_ProxyInfo =
    {
    &Object_StubDesc,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAxWinHostWindowAggregator_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAxWinHostWindowAggregator_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAxWinHostWindowAggregator_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IAxWinHostWindowAggregatorProxyVtbl = 
{
    0,
    &IID_IAxWinHostWindowAggregator,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IAxWinHostWindowAggregatorStubVtbl =
{
    &IID_IAxWinHostWindowAggregator,
    &IAxWinHostWindowAggregator_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAveHtmlDesktop, ver. 0.0,
   GUID={0x2BD41F4F,0xD619,0x46FC,{0x92,0xDF,0xA3,0xA3,0x93,0xB6,0x2C,0x51}} */

#pragma code_seg(".orpc")
static const unsigned short IAveHtmlDesktop_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    56,
    84
    };

static const MIDL_STUBLESS_PROXY_INFO IAveHtmlDesktop_ProxyInfo =
    {
    &Object_StubDesc,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveHtmlDesktop_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAveHtmlDesktop_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveHtmlDesktop_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IAveHtmlDesktopProxyVtbl = 
{
    &IAveHtmlDesktop_ProxyInfo,
    &IID_IAveHtmlDesktop,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IAveHtmlDesktop::Set */ ,
    (void *) (INT_PTR) -1 /* IAveHtmlDesktop::get_IsActive */
};


static const PRPC_STUB_FUNCTION IAveHtmlDesktop_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAveHtmlDesktopStubVtbl =
{
    &IID_IAveHtmlDesktop,
    &IAveHtmlDesktop_ServerInfo,
    9,
    &IAveHtmlDesktop_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAveHtmlBackgroundMenuHandler, ver. 0.0,
   GUID={0x4F0B462B,0x6EFD,0x493B,{0x83,0xAD,0x8E,0x8A,0xE0,0xD3,0xD1,0x17}} */

#pragma code_seg(".orpc")
static const unsigned short IAveHtmlBackgroundMenuHandler_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAveHtmlBackgroundMenuHandler_ProxyInfo =
    {
    &Object_StubDesc,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveHtmlBackgroundMenuHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAveHtmlBackgroundMenuHandler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AveActiveDesktop__MIDL_ProcFormatString.Format,
    &IAveHtmlBackgroundMenuHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IAveHtmlBackgroundMenuHandlerProxyVtbl = 
{
    0,
    &IID_IAveHtmlBackgroundMenuHandler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IAveHtmlBackgroundMenuHandlerStubVtbl =
{
    &IID_IAveHtmlBackgroundMenuHandler,
    &IAveHtmlBackgroundMenuHandler_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    AveActiveDesktop__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x8000253, /* MIDL Version 8.0.595 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _AveActiveDesktop_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAxWinHostWindowAggregatorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAveHtmlBackgroundMenuHandlerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAveHtmlDesktopProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAveActiveDesktopHostProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _AveActiveDesktop_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAxWinHostWindowAggregatorStubVtbl,
    ( CInterfaceStubVtbl *) &_IAveHtmlBackgroundMenuHandlerStubVtbl,
    ( CInterfaceStubVtbl *) &_IAveHtmlDesktopStubVtbl,
    ( CInterfaceStubVtbl *) &_IAveActiveDesktopHostStubVtbl,
    0
};

PCInterfaceName const _AveActiveDesktop_InterfaceNamesList[] = 
{
    "IAxWinHostWindowAggregator",
    "IAveHtmlBackgroundMenuHandler",
    "IAveHtmlDesktop",
    "IAveActiveDesktopHost",
    0
};

const IID *  const _AveActiveDesktop_BaseIIDList[] = 
{
    0,
    0,
    &IID_IDispatch,
    0,
    0
};


#define _AveActiveDesktop_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _AveActiveDesktop, pIID, n)

int __stdcall _AveActiveDesktop_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _AveActiveDesktop, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _AveActiveDesktop, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _AveActiveDesktop, 4, *pIndex )
    
}

const ExtendedProxyFileInfo AveActiveDesktop_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _AveActiveDesktop_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _AveActiveDesktop_StubVtblList,
    (const PCInterfaceName * ) & _AveActiveDesktop_InterfaceNamesList,
    (const IID ** ) & _AveActiveDesktop_BaseIIDList,
    & _AveActiveDesktop_IID_Lookup, 
    4,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

