// AveHtmlBackgroundMenuHandler.h : Declaration of the CAveHtmlBackgroundMenuHandler

#pragma once
#include "resource.h"       // main symbols

#include "AveActiveDesktop.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CAveHtmlBackgroundMenuHandler

class ATL_NO_VTABLE CAveHtmlBackgroundMenuHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAveHtmlBackgroundMenuHandler, &CLSID_AveHtmlBackgroundMenuHandler>,
	public IAveHtmlBackgroundMenuHandler,
	public IShellExtInit,
	public IContextMenu
{
public:
	CAveHtmlBackgroundMenuHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AVEHTMLBACKGROUNDMENUHANDLER)


BEGIN_COM_MAP(CAveHtmlBackgroundMenuHandler)
	COM_INTERFACE_ENTRY(IAveHtmlBackgroundMenuHandler)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComPtr<IAveHtmlDesktop> htmlDesktop;

public:
	// IShellExtInit
	STDMETHODIMP Initialize(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

	// IContextMenu
	STDMETHODIMP GetCommandString(UINT_PTR, UINT, UINT*, LPSTR, UINT);
	STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
	STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);

	// custom
	STDMETHODIMP SelectHtmlFile(HWND, BOOL unsetIfCancel);
};

OBJECT_ENTRY_AUTO(__uuidof(AveHtmlBackgroundMenuHandler), CAveHtmlBackgroundMenuHandler)
