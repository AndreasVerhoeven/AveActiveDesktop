// AveActiveDesktopHost.h : Declaration of the CAveActiveDesktopHost

#pragma once
#include "resource.h"       // main symbols

#include "AveActiveDesktop.h"

#include "AveListViewMarquee.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include "IconRegionCache.h"
#include "AveHostWindow.h"
#include <vector>


class ATL_NO_VTABLE CAveActiveDesktopHost :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAveActiveDesktopHost, &CLSID_AveActiveDesktopHost>,
	public IAveActiveDesktopHost,
	public IShellExtInit
{

	BOOL hasInitialized;
	BOOL isRunning;
	BOOL isInDebugHost;

	HWND listView;
	HWND defView;

	HHOOK mouseHook;
	HHOOK msgHook;

	CIconRegionCache iconRegionCache;

	CAveListViewMarquee marquee;
	static CAveActiveDesktopHost* theHost;

	ULONG rotHandle;

	std::vector<CAveHostWindow*> windows;

	static LRESULT CALLBACK MouseHookProc(int nCode,WPARAM wParam,LPARAM lParam);
	static LRESULT CALLBACK GetMsgHookProc(int nCode,WPARAM wParam,LPARAM lParam);
	static BOOL DoesElementNeedMouse(IHTMLElement* element);
	static void StealMouse(BOOL doSteal, UINT origMsg);
	BOOL ShouldStealMouse(HWND hwnd, const POINT& pt);

	int HitTestListView(const POINT& pt);
	BOOL IsIeWindow(HWND hwnd);

	HWND GetIeHost();

	// methods
	HRESULT InternalInitialize();
	HRESULT Start();
	HRESULT Stop();

	HRESULT _CheckSettingsAndKickStart();

	HRESULT SubclassDesktop();
	HRESULT UnsubclassDesktop();
	HRESULT InstallHooks();
	HRESULT UninstallHooks();

	void _DrawListViewManually(HWND hwnd, HDC dc);
	HRGN _CalcListViewRegion(HWND hwnd, HDC dc);

	static HRGN RegionFromImageListIcon(RECT& rcIcon, HIMAGELIST imgList, int index, UINT state, UINT flags);

	void _ClearItems();
	void _RemoveItem(CAveHostWindow* item);
	CAveHostWindow* _AddItem(const WCHAR* url, RECT* rc, DWORD flags);

public:
	CAveActiveDesktopHost()
	{
		hasInitialized	= FALSE;
		isRunning		= FALSE;
		isInDebugHost	= FALSE;

		listView		= NULL;
		defView			= NULL;

		mouseHook		= NULL;
		msgHook			= NULL;
		
		rotHandle		= NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AVEACTIVEDESKTOPHOST)


BEGIN_COM_MAP(CAveActiveDesktopHost)
	COM_INTERFACE_ENTRY(IAveActiveDesktopHost)
	COM_INTERFACE_ENTRY(IShellExtInit)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	static BOOL hasHost() { return theHost != NULL;}

	LRESULT HandleListViewMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleDefViewMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// IShellExtInit
	STDMETHODIMP Initialize(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

	// IContextMenu
//	STDMETHODIMP GetCommandString(UINT_PTR, UINT, UINT*, LPSTR, UINT);
	//STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
	//STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);

	DECLARE_CLASSFACTORY_SINGLETON(CAveActiveDesktopHost)


	STDMETHOD(SetHTMLBackground)(BSTR urlOrFile);
	STDMETHOD(get_IsRunning)(VARIANT_BOOL* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(AveActiveDesktopHost), CAveActiveDesktopHost)
