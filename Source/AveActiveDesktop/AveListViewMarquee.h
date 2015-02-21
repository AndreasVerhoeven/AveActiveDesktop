#pragma once

typedef CWinTraits<WS_POPUPWINDOW, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_COMPOSITED> CAveListViewMarqueeTraits;

class CAveListViewMarquee : 
	public CWindowImpl<CAveListViewMarquee, CWindow, CAveListViewMarqueeTraits >
{
public:
   DECLARE_WND_CLASS(_T("AveListViewMarquee"));

   CListViewCtrl listView;
   UINT controlId; // used by the notify handler

	CPoint startPoint;
	CPoint prevPoint;

	CAveListViewMarquee()
	{
		controlId = 0;
	}

	BEGIN_MSG_MAP(CAveListViewMarquee)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)

		// custom message handler for notifications
		ALT_MSG_MAP(1)
			NOTIFY_HANDLER(controlId, LVN_MARQUEEBEGIN, OnMarqueeBegin);
   END_MSG_MAP()

	void AddMarqueeToListView(HWND hwnd)
	{
		listView = hwnd;
		controlId = listView.GetDlgCtrlID();

		Create(listView, rcDefault);
		if(IsWindow())
		{
			// Set alpha layer
			BYTE alpha = 75;
			::SetLayeredWindowAttributes(m_hWnd, RGB(0,0,0), alpha, LWA_ALPHA);
		}
	}

   LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
		Invalidate();
		UpdateWindow();
		ShowWindow(FALSE);

		return 0;
   }

   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
	   // get the current message pos, do not use GetCursorPos(), since that is async
		DWORD msgPos = GetMessagePos();
		POINT pt = {GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos)};

		prevPoint = pt;

		// get the selection rectangle and ensure
		CRect rcSel(pt, startPoint);//pt.x, pt.y, startPoint.x, startPoint.y);
		if( rcSel.left > rcSel.right )
		{
			std::swap(rcSel.left, rcSel.right);
		}

		if( rcSel.top > rcSel.bottom ) 
		{
			std::swap(rcSel.top, rcSel.bottom);
		}

		CRect rcListViewSelectionRect = rcSel;
		::MapWindowPoints(NULL, listView, (LPPOINT)&rcListViewSelectionRect, 2);

		int count = listView.GetItemCount();
		for( int i = 0; i < count; ++i)
		{
			 // use the icon rectangle for selection hit testing
			CRect rcItem;
			listView.GetItemRect(i, &rcItem, LVIR_ICON);

			// if the marquee rectangle is inside the item, than select it if it isn't 
			// selected yet, otherwise, deselect it if it isn't deselected yet.
			CRect rcTemp;
			if(rcTemp.IntersectRect(&rcItem, &rcListViewSelectionRect))
			{
				if(listView.GetItemState(i, LVIS_SELECTED) == 0)
				{
					listView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				}
			}
			else 
			{
				if(listView.GetItemState(i, LVIS_SELECTED) != 0) 
				{
					listView.SetItemState(i, 0, LVIS_SELECTED);
				}
			}
		}

		// update the marquee view
		SetWindowPos(NULL, &rcSel, SWP_NOZORDER);
		UpdateWindow();

		return 0;
   }

   LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
		ReleaseCapture();
		return 0;
   }

   LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
		OutputDebugString(L"Marqee WM_ERASEBKGND\n");

		CDCHandle dc = (HDC)wParam;

		CRect rcClient;
		GetClientRect(&rcClient);
		rcClient.InflateRect(1, 1, 1, 1);
		
		CBrush brush;
		COLORREF highlightColor = ::GetSysColor(COLOR_HIGHLIGHT);
		brush.CreateSolidBrush(highlightColor);

		CPen pen;
		COLORREF borderColor = RGB(0,0, 255);
		pen.CreatePen(PS_INSIDEFRAME, 1, borderColor);

		HPEN prevPen		= dc.SelectPen(pen);
		HBRUSH prevBrush	= dc.SelectBrush(brush);

		dc.Rectangle(&rcClient);

		dc.SelectPen(prevPen);
		dc.SelectBrush(prevBrush);

	  return 1;
   }

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
	  // We do everything in the erasebackground handler
	  CPaintDC dc(m_hWnd);
      return 0;
   }

   LRESULT OnMarqueeBegin(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
   {
      LPNMLISTVIEW pnmLV = (LPNMLISTVIEW) pnmh;
	  CPoint pt(pnmLV->ptAction);
	  ::ClientToScreen(pnmh->hwndFrom, &pt);
      startPoint = pt;
	  prevPoint = pt;

	  RECT rc = {0};
      SetWindowPos(HWND_BOTTOM, &rc, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_DEFERERASE);

      SetCapture();    

      return 1;
   } 
};
