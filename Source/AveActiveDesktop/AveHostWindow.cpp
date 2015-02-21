#include "StdAfx.h"
#include "AveHostWindow.h"


#include "urlmon.h"
#pragma comment(lib, "urlmon.lib")

CAveHostWindow::CAveHostWindow(void)
{
	flags = 0;
}

CAveHostWindow::~CAveHostWindow(void)
{
	if(axHost != NULL)
	{
		if(web != NULL)
		{
			CComPtr<IUnknown> unknownWeb;
			web->QueryInterface(&unknownWeb);
			if(unknownWeb != NULL)
			{
				axHost->DispEventUnadvise(unknownWeb);
			}
		}

		axHost->Release();
	}
}


CAveHostWindow* CAveHostWindow::Construct(HWND listView, HWND parent, const CString& url, const RECT& rc, DWORD flags)
{
	DWORD style		= WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE;
	DWORD exStyle	= 0;


	if(!(flags & ITEM_FLAG_FULLSCREEN))
	{
		style |= WS_BORDER | WS_CAPTION | WS_THICKFRAME;
	}

	if((flags & ITEM_FLAG_CLICKTHRU))
	{
		exStyle = WS_EX_TRANSPARENT;
	}

	RECT windowRC = rc;


	CAveHostWindow* window = new CAveHostWindow;
	window->url = url;
	window->flags = flags;
	window->listView = listView;
	window->Create(parent, windowRC, url, style, exStyle);
	window->SetWindowPos(HWND_BOTTOM, &windowRC, 0);

	return window;
}


LRESULT CAveHostWindow::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc = {0};
	GetClientRect(&rc);
	wndIE.Create ( *this, rc, _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
	

	INTERNETFEATURELIST featureToEnable = FEATURE_WINDOW_RESTRICTIONS;
	CoInternetSetFeatureEnabled(featureToEnable, SET_FEATURE_ON_PROCESS, TRUE);

	CComObject<CAxWinHostWindowAggregator>::CreateInstance(&axHost);
	if(NULL == axHost)
		return 0;
	
	// DO WE NEED THIS?
	axHost->AddRef();

	axHost->listView = listView;
	
	CComPtr<IAxWinHostWindow> axWin;
	axHost->QueryInterface(&axWin);
	if(NULL == axWin)
		return 0;

	CComPtr<IUnknown> punkCtrl;
	axWin->CreateControlEx(L"{8856F961-340A-11D0-A96B-00C04FD705A2}", wndIE, NULL, &punkCtrl, IID_NULL, NULL );

	axHost->DispEventAdvise(punkCtrl);

	CComQIPtr<IWebBrowser2> pWB2(punkCtrl);
	web = pWB2;
	if(web != NULL)
	{
		web->put_RegisterAsDropTarget(VARIANT_FALSE);
		web->put_Silent(VARIANT_TRUE);
	}


	GoToUrl(url);


	return 0;
}

LRESULT CAveHostWindow::OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	WINDOWPOS* wp = (WINDOWPOS*)(lParam);
	if(NULL == wp)
		return 0;

	wp->hwndInsertAfter = HWND_BOTTOM;
	wp->flags &= ~SWP_NOZORDER;

	if(flags & ITEM_FLAG_FULLSCREEN)
	{
		MONITORINFO info = {0};
		info.cbSize = sizeof(info);
		GetMonitorInfo(MonitorFromPoint(CPoint(1, 1), MONITOR_DEFAULTTOPRIMARY), &info);
		::MapWindowPoints(NULL, GetParent(), (LPPOINT)&info.rcWork, 2);
		wp->x  = info.rcWork.left;
		wp->y  = info.rcWork.top;
		wp->cx = info.rcWork.right - info.rcWork.left;
		wp->cy = info.rcWork.bottom - info.rcWork.top;

		
	}

	if(!(wp->flags & (SWP_NOSIZE | SWP_NOMOVE)))
	{
		RECT rc = {0};
		GetWindowRect(&rc);
		::MapWindowPoints(NULL, listView, (LPPOINT)&rc, 2);
		::InvalidateRect(listView, &rc, FALSE);
	}

	if(!(wp->flags & SWP_NOSIZE))
	{
		if(wndIE.IsWindow())
		{
			wndIE.SetWindowPos(NULL, 0, 0, wp->cx, wp->cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}

	return 0;
}

BOOL CAveHostWindow::hitTest(int x, int y, IHTMLElement** element)
{
	if(NULL == element)
		return FALSE;

	*element = NULL;

	if(NULL == web || !wndIE.IsWindow())
		return FALSE;

	POINT pt = {x, y};
	wndIE.ScreenToClient(&pt);

	CComPtr<IDispatch> unk;
	web->get_Document(&unk);
	CComQIPtr<IHTMLDocument2> doc(unk);
	if(NULL == doc)
		return FALSE;

	CComPtr<IHTMLElement> tempElement;

	BOOL isFrame = FALSE;
	do
	{
		isFrame = FALSE;
		CComPtr<IHTMLElement> hitTestElement;
		doc->elementFromPoint(pt.x, pt.y, &hitTestElement);
		if(hitTestElement != NULL)
		{
			CComBSTR tag;
			hitTestElement->get_tagName(&tag);
			if(_wcsicmp(tag, L"frame") == 0 || _wcsicmp(tag, L"iframe") == 0)
			{
				CComQIPtr<IWebBrowser2> frameDoc(hitTestElement);
				if(frameDoc != NULL)
				{
					long totalLeftOffset = 0;
					long totalTopOffset = 0;
					
					CComPtr<IHTMLElement> offsetElement = hitTestElement;
					while(offsetElement != NULL)
					{
						long leftOffset = 0;
						long topOffset  = 0;
						
						offsetElement->get_offsetLeft(&leftOffset);
						offsetElement->get_offsetTop(&topOffset);

						totalLeftOffset += leftOffset;
						totalTopOffset	+= topOffset;

						CComPtr<IHTMLElement> parentOffsetElement;
						offsetElement->get_offsetParent(&parentOffsetElement);

						offsetElement.Release();
						offsetElement = parentOffsetElement;
					}

					pt.x -= totalLeftOffset;
					pt.y -= totalTopOffset;

					isFrame = TRUE;
					doc.Release();

					CComPtr<IDispatch> unk;
					frameDoc->get_Document(&unk);
					CComQIPtr<IHTMLDocument2> frameDocument(unk);
					doc = frameDocument;
				}
			}
		}
		
		tempElement.Release();
		tempElement = hitTestElement;

	}while(isFrame);

	tempElement.CopyTo(element);

	return *element != NULL;
}

BOOL CAveHostWindow::IsIeWindow(HWND hwnd)
{
	if(NULL == wndIE || !wndIE.IsWindow())
		return FALSE;

	return hwnd == wndIE || wndIE.IsChild(hwnd);
}

LRESULT CAveHostWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CAveHostWindow::OnNCHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(!(flags & ITEM_FLAG_CLICKTHRU))
	{
		bHandled = FALSE;
		return 0;
	}

	return 0;
}

LRESULT CAveHostWindow::OnExitSizeMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	::InvalidateRect(listView, NULL, FALSE);
	return 0;
}

HRESULT CAveHostWindow::GoToUrl(const CString& url)
{
	if(NULL == web)
		return E_FAIL;

	this->url = url;

	CComVariant v;    // empty VARIANT
	return	web->Navigate (CComBSTR(url) , &v, &v, &v, &v );
}