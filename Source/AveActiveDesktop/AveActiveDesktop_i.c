

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAveActiveDesktopHost,0xA03E3472,0x694A,0x4834,0xBC,0x25,0x86,0x53,0x3D,0x14,0x3E,0x7C);


MIDL_DEFINE_GUID(IID, IID_IAxWinHostWindowAggregator,0x1C4AE50B,0x88FF,0x4050,0xA0,0x5C,0xB1,0x22,0x81,0x70,0xA4,0x81);


MIDL_DEFINE_GUID(IID, IID_IAveHtmlDesktop,0x2BD41F4F,0xD619,0x46FC,0x92,0xDF,0xA3,0xA3,0x93,0xB6,0x2C,0x51);


MIDL_DEFINE_GUID(IID, IID_IAveHtmlBackgroundMenuHandler,0x4F0B462B,0x6EFD,0x493B,0x83,0xAD,0x8E,0x8A,0xE0,0xD3,0xD1,0x17);


MIDL_DEFINE_GUID(IID, LIBID_AveActiveDesktopLib,0x7BFC94E6,0xF3EE,0x4C9E,0x8B,0x8C,0xE8,0x28,0xB9,0x83,0x94,0x15);


MIDL_DEFINE_GUID(CLSID, CLSID_AveActiveDesktopHost,0xC3E638A6,0x4610,0x4029,0x99,0xCC,0x04,0x35,0x3C,0x21,0x2F,0xC1);


MIDL_DEFINE_GUID(CLSID, CLSID_AxWinHostWindowAggregator,0xB4BEE677,0x4019,0x4979,0xA0,0xD9,0xA2,0x3A,0x24,0x9F,0xEA,0xC8);


MIDL_DEFINE_GUID(CLSID, CLSID_AveHtmlDesktop,0x990825CC,0x3C93,0x4E11,0x8E,0x44,0xEB,0xA7,0x32,0x38,0xFC,0xD1);


MIDL_DEFINE_GUID(CLSID, CLSID_AveHtmlBackgroundMenuHandler,0x96A2B6AE,0x9E00,0x4708,0x8B,0x2A,0x56,0x94,0xF4,0xC2,0xE4,0x5E);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



