// AxWinHostWindowAggregator.h : Declaration of the CAxWinHostWindowAggregator

#pragma once
#include "resource.h"       // main symbols

#include "AveActiveDesktop.h"

#define CAXWINHOSTWINDOWAGGREGATOR_ID 1

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include <atlhost.h>

#include <exdisp.h>
#include <exdispid.h>

// CAxWinHostWindowAggregator
// 
// This class acts as a subclass of the default ATL IAxWinHostWindow implementation by using aggregation.
// We do this since we do not want to implement the OLE hosting (IOleClientSite, etc) interfaces ourself.
// However, Trident QI()s the IOleClientSite implementation for custom interfaces (IDocHostUIHandler, 
// IOleCommandTarget, etc), so we'll implement those and pass all other requests blindly to the inner object.

static _ATL_FUNC_INFO OnDocumentCompleteInfo = {CC_STDCALL, VT_ERROR, 2, {VT_DISPATCH, VT_BYREF | VT_VARIANT}};

class ATL_NO_VTABLE CAxWinHostWindowAggregator :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAxWinHostWindowAggregator, &CLSID_AxWinHostWindowAggregator>,
	public IAxWinHostWindowAggregator,
	public IDocHostUIHandler,
	public IOleCommandTarget,
	public IInternetSecurityManager,
	public IServiceProvider,
	public IDispEventSimpleImpl<CAXWINHOSTWINDOWAGGREGATOR_ID, CAxWinHostWindowAggregator, &DIID_DWebBrowserEvents2>
{
public:
	HWND listView;

	CAxWinHostWindowAggregator() : innerUnknown(NULL), listView(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AXWINHOSTWINDOWAGGREGATOR)

	IUnknown* innerUnknown;

BEGIN_COM_MAP(CAxWinHostWindowAggregator)
	COM_INTERFACE_ENTRY(IAxWinHostWindowAggregator)
	COM_INTERFACE_ENTRY(IDocHostUIHandler)
	COM_INTERFACE_ENTRY(IOleCommandTarget)
	COM_INTERFACE_ENTRY(IServiceProvider)
	COM_INTERFACE_ENTRY(IInternetSecurityManager)
	COM_INTERFACE_ENTRY_AGGREGATE_BLIND(innerUnknown)
END_COM_MAP()

	BEGIN_SINK_MAP(CAxWinHostWindowAggregator)
		SINK_ENTRY_INFO(CAXWINHOSTWINDOWAGGREGATOR_ID, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete, &OnDocumentCompleteInfo)
	END_SINK_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		CAxHostWindow::CreateInstance(GetControllingUnknown(), &innerUnknown);
		CAxHostWindow::_CreatorClass::CreateInstance(GetControllingUnknown(), IID_IUnknown, (void**)&innerUnknown); 

		return S_OK;
	}

	void FinalRelease()
	{
		innerUnknown->Release();
	}

	DECLARE_GET_CONTROLLING_UNKNOWN();

	// DWebBrowserEvents2 functions
	HRESULT __stdcall OnDocumentComplete(IDispatch *pDisp,VARIANT *URL)
	{
		// repaint the listview so we get nice blending
		::InvalidateRect(listView, NULL, FALSE);

		return S_OK;
	}

	// IServiceProvider
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE QueryService( 
                /* [in] */ REFGUID guidService,
                /* [in] */ REFIID riid,
                /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if(::IsEqualGUID(riid, IID_IInternetSecurityManager))
		{
			this->QueryInterface(riid, ppvObject);
			return S_OK;
		}
		return E_NOTIMPL;
	}

	// IOleCommandTarget
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE QueryStatus( 
            /* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
            /* [in] */ ULONG cCmds,
            /* [out][in][size_is] */ __RPC__inout_ecount_full(cCmds) OLECMD prgCmds[  ],
            /* [unique][out][in] */ __RPC__inout_opt OLECMDTEXT *pCmdText)
	{
		return E_NOTIMPL;
	}
        
	virtual HRESULT STDMETHODCALLTYPE Exec( 
            /* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
            /* [in] */ DWORD nCmdID,
            /* [in] */ DWORD nCmdexecopt,
            /* [unique][in] */ __RPC__in_opt VARIANT *pvaIn,
            /* [unique][out][in] */ __RPC__inout_opt VARIANT *pvaOut);


	// IInternetSecurityManager
	virtual HRESULT STDMETHODCALLTYPE SetSecuritySite(IInternetSecurityMgrSite *pSite) 
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE GetSecuritySite(IInternetSecurityMgrSite **ppSite)
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE MapUrlToZone(LPCWSTR pwszUrl, DWORD *pdwZone, DWORD dwFlags)
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE GetSecurityId(LPCWSTR pwszUrl, BYTE *pbSecurityId, DWORD *pcbSecurityId, DWORD_PTR dwReserved)
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE ProcessUrlAction( 
            /* [in] */ __RPC__in LPCWSTR pwszUrl,
            /* [in] */ DWORD dwAction,
            /* [size_is][out] */ __RPC__out_ecount_full(cbPolicy) BYTE *pPolicy,
            /* [in] */ DWORD cbPolicy,
            /* [in] */ __RPC__in BYTE *pContext,
            /* [in] */ DWORD cbContext,
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD dwReserved)
	{
		*pPolicy = URLPOLICY_ALLOW;
		return S_OK;
	}
        
	virtual HRESULT STDMETHODCALLTYPE QueryCustomPolicy( 
            /* [in] */ __RPC__in LPCWSTR pwszUrl,
            /* [in] */ __RPC__in REFGUID guidKey,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*pcbPolicy) BYTE **ppPolicy,
            /* [out] */ __RPC__out DWORD *pcbPolicy,
            /* [in] */ __RPC__in BYTE *pContext,
            /* [in] */ DWORD cbContext,
            /* [in] */ DWORD dwReserved)
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE SetZoneMapping( 
            /* [in] */ DWORD dwZone,
            /* [in] */ __RPC__in LPCWSTR lpszPattern,
            /* [in] */ DWORD dwFlags)
	{
		return INET_E_DEFAULT_ACTION;
	}
        
	virtual HRESULT STDMETHODCALLTYPE GetZoneMappings( 
            /* [in] */ DWORD dwZone,
            /* [out] */ __RPC__deref_out_opt IEnumString **ppenumString,
            /* [in] */ DWORD dwFlags)
	{
		return INET_E_DEFAULT_ACTION;
	}


	// IDocHostUIHandler
	     virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT *ppt,
            /* [in] */ IUnknown *pcmdtReserved,
			/* [in] */ IDispatch *pdispReserved) 
		 {
			 ::PostMessage(listView, WM_CONTEXTMENU, (WPARAM)listView, MAKELPARAM(ppt->x, ppt->y));
			 return S_OK;
		 }
        
        virtual HRESULT STDMETHODCALLTYPE GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO *pInfo)
		{
			pInfo->dwFlags = DOCHOSTUIFLAG_DISABLE_HELP_MENU | DOCHOSTUIFLAG_NO3DBORDER |  DOCHOSTUIFLAG_SCROLL_NO;
			pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE ShowUI( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject *pActiveObject,
            /* [in] */ IOleCommandTarget *pCommandTarget,
            /* [in] */ IOleInPlaceFrame *pFrame,
            /* [in] */ IOleInPlaceUIWindow *pDoc)  { return S_OK;}
        
		virtual HRESULT STDMETHODCALLTYPE HideUI( void) { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE UpdateUI( void)  { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable)  { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
            /* [in] */ BOOL fActivate)  { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate)  { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fRameWindow) { return S_OK;}
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID *pguidCmdGroup,
            /* [in] */ DWORD nCmdID) { return S_FALSE;}
        
        virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
            /* [out] */ 
            __out  LPOLESTR *pchKey,
			/* [in] */ DWORD dw) { return S_FALSE;}
        
        virtual HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [in] */ IDropTarget *pDropTarget,
            /* [out] */ IDropTarget **ppDropTarget)
		{
			return GetShellDropTarget(ppDropTarget);
		}
        
        virtual HRESULT STDMETHODCALLTYPE GetExternal( 
			/* [out] */ IDispatch **ppDispatch) { return E_NOTIMPL;}
        
        virtual HRESULT STDMETHODCALLTYPE TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ 
            __in __nullterminated  OLECHAR *pchURLIn,
            /* [out] */ 
			__out  OLECHAR **ppchURLOut) { return E_NOTIMPL;}
        
        virtual HRESULT STDMETHODCALLTYPE FilterDataObject( 
            /* [in] */ IDataObject *pDO,
			/* [out] */ IDataObject **ppDORet) { return E_NOTIMPL;}

		// Custom methods

		HRESULT GetShellDropTarget(IDropTarget** ppDropTarget)
		{
			CComPtr<IShellWindows> psw; 
			HRESULT hr = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&psw)); 
			if (SUCCEEDED(hr)) 
			{ 
				CComPtr<IDispatch> disp;
				HWND hwnd; 
				VARIANT vEmpty = {}; // VT_EMPTY 
				if (S_OK == psw->FindWindowSW(&vEmpty, &vEmpty, SWC_DESKTOP, (long*)&hwnd, SWFO_NEEDDISPATCH, &disp)) 
				{
					CComPtr<IShellBrowser> psb; 

					hr = IUnknown_QueryService(disp, SID_STopLevelBrowser, IID_PPV_ARGS(&psb)); 
					if (SUCCEEDED(hr)) 
					{ 
						CComPtr<IShellView> psv; 
						hr = psb->QueryActiveShellView(&psv);
						CComQIPtr<IDropTarget> drop = psv;
						if(drop != NULL)
							drop->QueryInterface(ppDropTarget);
					}


				}
			}

			return S_OK;
		}


};

OBJECT_ENTRY_AUTO(__uuidof(AxWinHostWindowAggregator), CAxWinHostWindowAggregator)
