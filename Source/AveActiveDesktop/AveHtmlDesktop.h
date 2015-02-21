// AveHtmlDesktop.h : Declaration of the CAveHtmlDesktop

#pragma once
#include "resource.h"       // main symbols

#include "AveActiveDesktop.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CAveHtmlDesktop

class ATL_NO_VTABLE CAveHtmlDesktop :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAveHtmlDesktop, &CLSID_AveHtmlDesktop>,
	public IDispatchImpl<IAveHtmlDesktop, &IID_IAveHtmlDesktop, &LIBID_AveActiveDesktopLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAveHtmlDesktop()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AVEHTMLDESKTOP)


BEGIN_COM_MAP(CAveHtmlDesktop)
	COM_INTERFACE_ENTRY(IAveHtmlDesktop)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	static HRESULT _GetHost(IAveActiveDesktopHost** host);

public:

	STDMETHOD(Set)(BSTR urlOrFile);
	STDMETHOD(get_IsActive)(VARIANT_BOOL* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(AveHtmlDesktop), CAveHtmlDesktop)
