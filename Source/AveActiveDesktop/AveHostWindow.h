#pragma once

#define ITEM_FLAG_CLICKTHRU		(1 << 0)
#define ITEM_FLAG_FULLSCREEN	(1 << 1)

#include "AxWinHostWindowAggregator.h"

class CAveHostWindow :
	public CWindowImpl<CAveHostWindow>
{
public:
	CAveHostWindow(void);
	~CAveHostWindow(void);

	CComObject<CAxWinHostWindowAggregator>* axHost;
	
	HWND listView;

	DWORD flags;
	CString url;

	CAxWindow wndIE;
	CComPtr<IWebBrowser2> web;

	static CAveHostWindow* Construct(HWND listView, HWND parent, const CString& url, const RECT& rc, DWORD flags);

	BOOL hitTest(int x, int y, IHTMLElement** element);
	BOOL IsIeWindow(HWND hwnd);

	BEGIN_MSG_MAP(CAveHostWindow)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnWindowPosChanging)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
		MESSAGE_HANDLER(WM_EXITSIZEMOVE, OnExitSizeMove)

	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNCHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnExitSizeMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	HRESULT GoToUrl(const CString& url);

};
