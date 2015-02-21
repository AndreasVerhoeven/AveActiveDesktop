// AveActiveDesktopHost.cpp : Implementation of CAveActiveDesktopHost

#include "stdafx.h"
#include "AveActiveDesktopHost.h"

#include "AveRegFuncs.h"

#include <uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

CAveActiveDesktopHost* CAveActiveDesktopHost::theHost = NULL;


BOOL IsChildOrSelf(HWND parent, HWND child)
{
	return parent == child || ::IsChild(parent, child);
}

STDMETHODIMP CAveActiveDesktopHost::Initialize ( 
  LPCITEMIDLIST pidlFolder,
  LPDATAOBJECT pDataObj,
  HKEY hProgID )
{
	if(!hasInitialized)
		InternalInitialize();

	if(NULL == pidlFolder)
		return E_INVALIDARG;

	if(0 == pidlFolder->mkid.cb)
		return S_OK;

	return E_INVALIDARG;
}

// Initializes the DesktopEffects object by firing up the hooks
// and loading the previously used Effect.
HRESULT CAveActiveDesktopHost::InternalInitialize()
{
	if(hasInitialized)
		return S_OK;

	theHost = this;

	// Get the path of the EXE application we are running in
	// and determine if we are running inside the DebugHost application
	// by checking against the filename of the DebugHost exe.
	WCHAR path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	const WCHAR* fileName = PathFindFileName(path);
	isInDebugHost = _wcsicmp(fileName, DEBUGHOST_FILENAME) == 0;

	// Up the ref count, so we will never get unloaded once loaded:
	// This is vital, since the shell calls Release() on the IContextMenu
	// object, which would set our refcount to zero, thereby destroying this
	// object.
	// XXX, Strong Object Registration will do that for us, also.
	//AddRef();

	CComPtr<IUnknown> unknown;
	this->QueryInterface(IID_IUnknown, (void**)&unknown);
	RegisterActiveObject(unknown, CLSID_AveActiveDesktopHost, ACTIVEOBJECT_STRONG, &rotHandle);

	hasInitialized = TRUE;

	_CheckSettingsAndKickStart();

	return S_OK;
}

HRESULT CAveActiveDesktopHost::_CheckSettingsAndKickStart()
{
	CString htmlBackground = AveRegFuncs::ReadString(HKEY_CURRENT_USER, AVE_ACTIVEDESKTOP_REG_KEY, L"HTMLBackground", L"");
	if(!htmlBackground.IsEmpty())
	{
		SetHTMLBackground(CComBSTR(htmlBackground));
	}

	return S_OK;
}

void CAveActiveDesktopHost::_ClearItems()
{
	for(size_t i = 0; i < windows.size(); ++i)
	{
		if(windows[i] != NULL && windows[i]->IsWindow())
		{
			windows[i]->DestroyWindow();
		}

		delete windows[i];
	}

	windows.clear();
}

void CAveActiveDesktopHost::_RemoveItem(CAveHostWindow* item)
{
	// XXX implement later
}

CAveHostWindow* CAveActiveDesktopHost::_AddItem(const WCHAR* url, RECT* itemRc, DWORD flags)
{
	RECT rc = {0};
	if(itemRc != NULL)
	{
		rc = *itemRc;
	}
	else
	{
		DWORD msgPos = GetMessagePos();
		POINT pt = {GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos)};
		::SetRect(&rc, pt.x, pt.y, 400, 300);
	}

	CAveHostWindow* window = CAveHostWindow::Construct(listView, defView, url, rc, flags);
	windows.push_back(window);

	return window;
}

HRESULT CAveActiveDesktopHost::Start()
{
	if(isRunning)
		return E_FAIL;

	HRESULT hRes = SubclassDesktop();
	if(FAILED(hRes))
		return hRes;

	InstallHooks();

	isRunning = TRUE;

	SetWindowTheme(listView, L"", L"");
	::InvalidateRect(listView, NULL, TRUE);


	CListViewCtrl w = listView;
	w.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0);
	//w.SetExtendedListViewStyle(0, LVS_EX_DOUBLEBUFFER);
	w.SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	w.Detach();

	marquee.AddMarqueeToListView(listView);

	return S_OK;
}

HRESULT CAveActiveDesktopHost::Stop()
{
	if(!isRunning)
		return E_FAIL;

	_ClearItems();

	HWND oldListView = listView;

	HRESULT hRes = UnsubclassDesktop();
	if(FAILED(hRes))
		return hRes;

	UninstallHooks();

	
	SetWindowTheme(oldListView, L"Explorer", NULL);
	::SetWindowRgn(oldListView, NULL, TRUE);
	::InvalidateRect(oldListView, NULL, TRUE);

	if(marquee.IsWindow())
		marquee.DestroyWindow();

	theHost->iconRegionCache.Clear();

	isRunning = FALSE;

	return hRes;
}


// Wrapper Subclass procedure for HandleListViewMessage
LRESULT CALLBACK ListViewSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR dwData)
{
	if(dwData != NULL)
	{
		CAveActiveDesktopHost* host = (CAveActiveDesktopHost*)dwData;
		BOOL handled=FALSE;
		LRESULT lRes = host->HandleListViewMessage(hwnd, msg, wParam, lParam, handled);
		if(handled)
			return lRes;
	}

	return DefSubclassProc(hwnd, msg, wParam, lParam);
}


// Wrapper Subclass procedure for HandleDefViewMessage
LRESULT CALLBACK DefViewSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR dwData)
{
	if(dwData != NULL)
	{
		CAveActiveDesktopHost* host = (CAveActiveDesktopHost*)dwData;
		BOOL handled=FALSE;
		LRESULT lRes = host->HandleDefViewMessage(hwnd, msg, wParam, lParam, handled);
		if(handled)
			return lRes;
	}

	return DefSubclassProc(hwnd, msg, wParam, lParam);
}

HRESULT CAveActiveDesktopHost::SubclassDesktop()
{
	if(listView != NULL || defView != NULL)
		return E_FAIL;
	
	HWND progman = FindWindow(L"progman", isInDebugHost ? L"FakeDesktop" : NULL);
	if(NULL == progman)
		return FALSE;

	defView = FindWindowEx(progman, NULL, L"SHELLDLL_DefView", NULL);
	if(NULL == defView)
		return E_FAIL;

	listView = FindWindowEx(defView, NULL, L"SysListView32", NULL);
	if(NULL == listView)
	{
		defView = NULL;
		return E_FAIL;
	}

	PostMessage(listView, WM_NULL, 0, 0);
	
	BOOL hasSubclassed = SetWindowSubclass(listView, ListViewSubclassProc, 1, (DWORD_PTR)this);
	if(!hasSubclassed)
	{
		defView = NULL;
		listView = NULL;
		return E_FAIL;
	}

	hasSubclassed = SetWindowSubclass(defView, DefViewSubclassProc, 1, (DWORD_PTR)this);
	if(!hasSubclassed)
	{
		RemoveWindowSubclass(listView, ListViewSubclassProc, 1);
		defView = NULL;
		listView = NULL;
		return E_FAIL;
	}

	return S_OK;
}


HRESULT CAveActiveDesktopHost::UnsubclassDesktop()
{
	if(NULL == listView || NULL == defView)
		return E_FAIL;

	RemoveWindowSubclass(listView, ListViewSubclassProc, 1);
	RemoveWindowSubclass(defView, DefViewSubclassProc, 1);

	listView = NULL;
	defView = NULL;

	return S_OK;
}


void UnselectAllFromListView(HWND listView)
{
	int count = ListView_GetItemCount(listView);
	for(int i = 0; i < count; ++i)
	{
		ListView_SetItemState(listView, i, 0, LVIS_SELECTED);
	}
}

LRESULT CAveActiveDesktopHost::HandleDefViewMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(WM_NOTIFY == msg)
	{
		LPNMLISTVIEW pnmv = (LPNMLISTVIEW) lParam;
		if(pnmv != NULL && pnmv->hdr.code == LVN_MARQUEEBEGIN)
		{
			bHandled = TRUE;
			return marquee.OnMarqueeBegin(0, (LPNMHDR)lParam, bHandled);
		}
	}

	return 0;
}

LRESULT CAveActiveDesktopHost::HandleListViewMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	static BOOL isRecurring = FALSE;

	if(WM_WINDOWPOSCHANGING == msg)
	{
		WINDOWPOS* wp = (WINDOWPOS*)lParam;
		wp->hwndInsertAfter = HWND_TOPMOST;
		wp->flags &= ~SWP_NOZORDER;
	}
	else if(WM_ERASEBKGND == msg)
	{
		bHandled = TRUE;
		if(isRecurring)
		{
			AVETRACE(L"Recurring EraseBkgnd\n");
			return 1;
		}

		AVETRACE(L"EraseBkgnd Region\n");

		isRecurring = TRUE;

		BOOL isEqualRegion = FALSE;

		HRGN newRegion = _CalcListViewRegion(hwnd, (HDC)wParam);

		HRGN currentRegion = ::CreateRectRgn(0, 0, 0, 0);
		int regionType = ::GetWindowRgn(hwnd, currentRegion);
		if (regionType != ERROR) 
		{
			isEqualRegion = EqualRgn(newRegion, currentRegion);
		}
		::DeleteObject(currentRegion);


		if(isEqualRegion || !::SetWindowRgn(hwnd, newRegion, TRUE))
		{
			::DeleteObject(newRegion);
		}
		else
		{
			AVETRACE(L"New Region\n");
		}

		isRecurring = FALSE;

		return 1;
	}
	else if(WM_PAINT == msg)
	{
		
		AVETRACE(L"WM_PAINT");
		if(theHost->msgHook)
		{
			AVETRACE(L" (msgHook)");
		}
		AVETRACE(L"\n");

		

		bHandled = TRUE;
		PAINTSTRUCT ps = {0};
		HDC dc = BeginPaint(hwnd, &ps);

		if(isRecurring)
		{
			AVETRACE(L"Recurring WM_PAINT\n");
			EndPaint(hwnd, &ps);
			::ValidateRect(hwnd, &ps.rcPaint);
			return 0;
		}		

		isRecurring = TRUE;
		
		_DrawListViewManually(hwnd, wParam != NULL ? (HDC)wParam : dc);

		EndPaint(hwnd, &ps);

		::ValidateRect(hwnd, &ps.rcPaint);

		isRecurring = FALSE;

	}

	return 0;
}




//#define DO_CACHE_ICONS

HRGN CAveActiveDesktopHost::RegionFromImageListIcon(RECT& rcIcon, HIMAGELIST imgList, int index, UINT state, UINT flags)
{
	const DWORD alphaTreshold = 0;
	int cx = 0;
	int cy = 0;
	ImageList_GetIconSize(imgList, &cx, &cy);
	int w = rcIcon.right - rcIcon.left;
	int h = rcIcon.bottom - rcIcon.top;
	int l = rcIcon.left + w/2 - cx/2;
	int t = rcIcon.top + h/2 - cy/2;

#ifdef DO_CACHE_ICONS
	HRGN cachedRegion = theHost->iconRegionCache.Lookup(imgList, index, state, flags);
	if(cachedRegion != NULL)
	{
		HRGN reg = ::CreateRectRgn(0, 0, 0, 0);
		::CombineRgn(reg, reg, cachedRegion, RGN_OR);
		::OffsetRgn(reg, l, t);
		return reg;
	}
#endif

	HDC tmpDC = CreateCompatibleDC(NULL);

	BITMAPV5HEADER bi	= {0};
	bi.bV5Size			= sizeof(BITMAPV5HEADER);
    bi.bV5Width			= cx;
    bi.bV5Height		= cy;
    bi.bV5Planes		= 1;
    bi.bV5BitCount		= 32;
    bi.bV5Compression	= BI_BITFIELDS;
    bi.bV5RedMask		= 0x00FF0000;
    bi.bV5GreenMask		= 0x0000FF00;
    bi.bV5BlueMask		= 0x000000FF;
    bi.bV5AlphaMask		= 0x00000000;

	DWORD* iconBits = NULL;
	HBITMAP tmpBmp = CreateDIBSection(tmpDC, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&iconBits, NULL, 0);
	SelectObject(tmpDC, tmpBmp);

	if(NULL == iconBits)
	{
		DeleteDC(tmpDC);
		return NULL;
	}

	UINT nOvlImageMask = state & LVIS_OVERLAYMASK;
	ImageList_DrawEx(imgList, index, tmpDC, 0, 0, cx, cy, CLR_NONE, CLR_NONE, ILD_TRANSPARENT|nOvlImageMask | flags);


	int maxSize = sizeof(RGNDATAHEADER) + (sizeof(RECT)*cx*cy);
	LPBYTE bytes = new BYTE[maxSize];
	memset(bytes, 0, maxSize);
	RGNDATAHEADER* hdr = (RGNDATAHEADER*)bytes;
	hdr->dwSize = sizeof(RGNDATAHEADER);
	hdr->iType = RDH_RECTANGLES;
	LPBYTE ptr = bytes + sizeof(RGNDATAHEADER);

	RECT* rcs = (RECT*)ptr;

	DWORD* iconLine = iconBits;
	DWORD stride = cy;

	for(int y = 0; y < cy; ++y)
	{
		DWORD* iconPtr = iconLine;
		for(int x = 0; x < cx; ++x)
		{
			DWORD pixel = *iconPtr++;
			BOOL isOpaque = ((pixel & 0xFF000000)>>24) > alphaTreshold;
			if(isOpaque)
			{
#ifdef DO_CACHE_ICONS
				rcs->left	= x;
				rcs->top	= (cy - y -1);
				rcs->right	= x + 1;
				rcs->bottom	= (cy - y -1) + 1;
#else
				rcs->left	= l + x;
				rcs->top	= t + (cy - y -1);
				rcs->right	= l + x + 1;
				rcs->bottom	= t + (cy - y -1) + 1;
#endif

				hdr->rcBound.left = min(hdr->rcBound.left, rcs->left);
				hdr->rcBound.top = min(hdr->rcBound.top, rcs->top);
				hdr->rcBound.right = max(hdr->rcBound.right, rcs->right);
				hdr->rcBound.bottom = max(hdr->rcBound.bottom, rcs->bottom);

				rcs++;
				hdr->nCount++;
			}
		}

		iconLine += stride;
	}

	DeleteObject(tmpBmp);
	DeleteDC(tmpDC);

	HRGN iconReg = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT)*hdr->nCount), (RGNDATA*)bytes);

	delete[] bytes;

#ifdef DO_CACHE_ICONS
	theHost->iconRegionCache.Add(iconReg, imgList, index, state, flags);

	HRGN reg = ::CreateRectRgn(0, 0, 0, 0);
	::CombineRgn(reg, reg, cachedRegion, RGN_OR);
	::OffsetRgn(reg, l, t);
	return reg;
#else
	return iconReg;
#endif

	
}

#define LV_ML_DT_FLAGS  (DT_TOP | DT_NOPREFIX | DT_EDITCONTROL | DT_CENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_END_ELLIPSIS)
#define LV_FL_DT_FLAGS  (DT_TOP | DT_NOPREFIX | DT_EDITCONTROL | DT_CENTER | DT_WORDBREAK | DT_NOCLIP)


// In the future, we might start caching stuff
HRGN CAveActiveDesktopHost::_CalcListViewRegion(HWND hwnd, HDC dc)
{
	HDC outDc = dc;
	
	HRGN reg = CreateRectRgn(0, 0, 0, 0);


	LOGFONT lf = {0};
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), (PVOID)&lf, 0);
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT oldFont = (HFONT) SelectObject(outDc, hFont);

	int count = ListView_GetItemCount(hwnd);
	for(int i = 0; i < count; ++i)
	{
		RECT rcIcon = {0}, rcLabel = {0};
		ListView_GetItemRect(hwnd, i, &rcIcon, LVIR_ICON);
		if(true)
		{
			LVITEM item = {0};
			item.mask = LVIF_IMAGE | LVIF_STATE;
			item.iItem = i;
			ListView_GetItem(hwnd, &item);
			HIMAGELIST imgList = ListView_GetImageList(hwnd, LVSIL_NORMAL);

			DWORD flags = 0;
			UINT state = ListView_GetItemState(hwnd, i, LVIS_CUT | LVIS_DROPHILITED | LVIS_FOCUSED | LVIS_SELECTED | LVIS_OVERLAYMASK);
				
			DWORD fgColor = CLR_DEFAULT;
			if(state & LVIS_CUT)
			{
				flags |= ILD_BLEND50;
				fgColor = CLR_NONE;
			}

			if(state & LVIS_DROPHILITED)
				flags |= ILD_SELECTED;
			/*if(state & LVIS_FOCUSED)
				flags |= ILD_SELECTED;*/
			if(state & LVIS_SELECTED)
				flags |= ILD_SELECTED;

			int cx = 0;
			int cy = 0;
			ImageList_GetIconSize(imgList, &cx, &cy);
			int w = rcIcon.right - rcIcon.left;
			int h = rcIcon.bottom - rcIcon.top;
			int l = rcIcon.left + w/2 - cx/2;
			int t = rcIcon.top + h/2 - cy/2;

			HRGN regIcon = RegionFromImageListIcon(rcIcon, imgList, item.iImage, state, flags);
			CombineRgn(reg, reg, regIcon, RGN_OR);
			DeleteObject(regIcon);
		}

		ListView_GetItemRect(hwnd, i, &rcLabel, LVIR_LABEL);

		if(true)
		{
			WCHAR wText[1024] = {0};
			ListView_GetItemText(hwnd, i, 0, wText, 1024);
				

			DWORD flags = 0;
			UINT state = ListView_GetItemState(hwnd, i, LVIS_FOCUSED | LVIS_SELECTED);
			if((state & LVIS_FOCUSED) | (state & LVIS_SELECTED))
				flags = LV_FL_DT_FLAGS;
			else
				flags = LV_ML_DT_FLAGS;
			
			if((state & LVIS_SELECTED))
			{
				SetBkMode(outDc, OPAQUE);
				SetBkColor(outDc, GetSysColor(COLOR_HIGHLIGHT));
				SetTextColor(outDc, GetSysColor(COLOR_HIGHLIGHTTEXT));
			}
			else
			{
				SetBkMode(outDc, OPAQUE);
				SetBkColor(outDc, GetSysColor(COLOR_DESKTOP));
				if(GetSysColor(COLOR_DESKTOP) == GetSysColor(COLOR_WINDOWTEXT))
				{
					SetTextColor(outDc, RGB(255,255,255));
				}
				else
				{
					SetTextColor(outDc, GetSysColor(COLOR_WINDOWTEXT));
				}
			}

			
			RECT rcRealLabel = rcLabel;
			if((state & LVIS_SELECTED))
			{	
				DrawText(outDc, wText, -1, &rcRealLabel, flags | DT_CALCRECT);
				
			}
			else
			{
				DrawShadowText(outDc, wText, -1, &rcRealLabel, flags | DT_CALCRECT, RGB(255,255,255), RGB(0,0,0), 2,2);
			}

			int w = rcRealLabel.right - rcRealLabel.left;
			rcRealLabel.left = rcLabel.left + (rcLabel.right - rcLabel.left)/2 - w/2 -1;
			rcRealLabel.right = rcRealLabel.left + w+1;

			HRGN regLabel = CreateRectRgnIndirect(&rcRealLabel);
			CombineRgn(reg, reg, regLabel, RGN_OR);
			::DeleteObject(regLabel);
		}
	}

	SelectObject(outDc, oldFont);
	DeleteObject(hFont);

	return reg;
}

#define DO_NOT_CLEAR_ICON_BG_IF_IE_WINDOW_IS_BENEATH 
//#define DO_NOT_CLEAR_LABEL_BG_IF_IE_WINDOW_IS_BENEATH 
#define DO_PAINT_IE_BG
//#define DO_PAINT_DEFVIEW_BG

void CAveActiveDesktopHost::_DrawListViewManually(HWND hwnd, HDC dc)
{
	//HDC outDc = dc;
	RECT rc = {0};
	GetClipBox(dc, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	HBRUSH brush = CreateSolidBrush(RGB(0,0,0));

	CRect clientRect;
	::GetClientRect(hwnd, &clientRect);


	HDC outDc = ::CreateCompatibleDC(NULL);
	HBITMAP bmp = ::CreateCompatibleBitmap(dc, w, h);
	HBITMAP oldBmp = (HBITMAP) SelectObject(outDc, bmp);

	
	CRect rcAll(0,0, rc.right - rc.left, rc.bottom - rc.top);
	::FillRect(outDc, &rcAll, (HBRUSH)(INT_PTR)GetSysColor(COLOR_DESKTOP+1));

	LOGFONT lf = {0};
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), (PVOID)&lf, 0);
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT oldFont = (HFONT) SelectObject(outDc, hFont);

	POINT origOrg = {0};
	SetViewportOrgEx(outDc, - rc.left, -rc.top, &origOrg);

	HWND parent = ::GetParent(hwnd);
	if(IsWindow(parent) 
		//&& !(theHost->marquee.IsWindow() && theHost->marquee.IsWindowVisible())
	)
	{
#ifdef DO_PAINT_DEFVIEW_BG
		SendMessage(parent, WM_PRINT, (WPARAM)outDc, PRF_ERASEBKGND | PRF_CLIENT); 
#endif//DO_PAINT_DEFVIEW_BG

#ifdef DO_PAINT_IE_BG
		HWND ieHost = theHost->GetIeHost();
		if(::IsWindow(ieHost))
		{

			CComQIPtr<IViewObject> viewObject(theHost->windows[0]->web);
			if(viewObject != NULL)
			{
				HWND hwndIe = theHost->windows[0]->wndIE;
				CRect clientRect;
				::GetClientRect(hwndIe, &clientRect);

				HDC xDc = ::CreateCompatibleDC(NULL);
				HBITMAP xBmp = ::CreateCompatibleBitmap(CWindowDC(NULL), clientRect.Width(), clientRect.Height());
				SelectObject(xDc, xBmp);

				HRESULT hRes = OleDraw(viewObject, DVASPECT_CONTENT, xDc, &clientRect);

				::MapWindowPoints(hwndIe, hwnd, (LPPOINT)&clientRect, 2);	

				// Hopefully, GDI will intersect for us (a)
				BitBlt(outDc, clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height(), xDc, 0, 0, SRCCOPY);
				DeleteObject(xBmp);
				DeleteDC(xDc);
			}
		}
#endif//DO_PAINT_IE_BG

	}
	
	int count = ListView_GetItemCount(hwnd);
	for(int i = 0; i < count; ++i)
	{
		RECT rcIcon = {0}, rcLabel = {0};
		ListView_GetItemRect(hwnd, i, &rcIcon, LVIR_ICON);
		RECT rcIntersect = {0};
		BOOL doDrawIcon = ::IntersectRect(&rcIntersect, &rc, &rcIcon);

		if(doDrawIcon)
		{
			LVITEM item = {0};
			item.mask = LVIF_IMAGE | LVIF_STATE;
			item.iItem = i;
			ListView_GetItem(hwnd, &item);
			HIMAGELIST imgList = ListView_GetImageList(hwnd, LVSIL_NORMAL);

			DWORD flags = 0;
			UINT state = ListView_GetItemState(hwnd, i, LVIS_CUT | LVIS_DROPHILITED | LVIS_FOCUSED | LVIS_SELECTED | LVIS_OVERLAYMASK);
				
			DWORD fgColor = CLR_DEFAULT;
			if(state & LVIS_CUT)
			{
				flags |= ILD_BLEND50;
				fgColor = CLR_NONE;
			}

			if(state & LVIS_DROPHILITED)
				flags |= ILD_SELECTED;
			/*if(state & LVIS_FOCUSED)
				flags |= ILD_SELECTED;*/
			if(state & LVIS_SELECTED)
				flags |= ILD_SELECTED;

			int cx = 0;
			int cy = 0;
			ImageList_GetIconSize(imgList, &cx, &cy);
			int w = rcIcon.right - rcIcon.left;
			int h = rcIcon.bottom - rcIcon.top;
			int l = rcIcon.left + w/2 - cx/2;
			int t = rcIcon.top + h/2 - cy/2;

#ifndef DO_NOT_CLEAR_ICON_BG_IF_IE_WINDOW_IS_BENEATH

			RECT rcIconCoveringWindow = {0};
			for(size_t i = 0; i < windows.size(); ++i)
			{
				RECT winRc = {0};
				windows[i]->GetWindowRect(&winRc);
				::MapWindowPoints(NULL, hwnd, (LPPOINT)&winRc, 2);

				RECT rcIconIntersection = rcIcon;
				::IntersectRect(&rcIconIntersection, &rcIconIntersection, &winRc);

				::UnionRect(&rcIconCoveringWindow, &rcIconCoveringWindow, &rcIconIntersection);
			}

			SetBkColor(outDc, GetSysColor(COLOR_DESKTOP));
			ExtTextOut(outDc, 0, 0, ETO_OPAQUE, &rcIconCoveringWindow, L"", 0, 0);
#endif // DO_NOT_CLEAR_ICON_BG_IF_IE_WINDOW_IS_BENEATH
			

			//ImageList_DrawEx(imgList, item.iImage, outDc, l, t, cx, cy, CLR_NONE, fgColor, ILD_NORMAL | ILD_TRANSPARENT | flags);
			UINT nOvlImageMask = state & LVIS_OVERLAYMASK;
			ImageList_DrawEx(imgList, item.iImage, outDc, l, t, cx, cy, CLR_NONE, fgColor, ILD_TRANSPARENT|nOvlImageMask | flags);
		}

		ListView_GetItemRect(hwnd, i, &rcLabel, LVIR_LABEL);
		BOOL doDrawLabel = ::IntersectRect(&rcIntersect, &rc, &rcLabel);

		if(doDrawLabel)
		{
			WCHAR wText[1024] = {0};
			ListView_GetItemText(hwnd, i, 0, wText, 1024);

			DWORD flags = 0;
			UINT state = ListView_GetItemState(hwnd, i, LVIS_FOCUSED | LVIS_SELECTED);
			if((state & LVIS_FOCUSED) | (state & LVIS_SELECTED))
				flags = LV_FL_DT_FLAGS;
			else
				flags = LV_ML_DT_FLAGS;
			
			if((state & LVIS_SELECTED))
			{
				SetBkMode(outDc, TRANSPARENT);
				SetBkColor(outDc, GetSysColor(COLOR_HIGHLIGHT));
				SetTextColor(outDc, GetSysColor(COLOR_HIGHLIGHTTEXT));

				ExtTextOut(outDc, 0, 0, ETO_OPAQUE, &rcLabel, L"", 0, 0);
				DrawText(outDc, wText, -1, &rcLabel, flags);
			}
			else
			{
				//SetBkMode(outDc, OPAQUE);
				SetBkMode(outDc, TRANSPARENT);
				SetBkColor(outDc, GetSysColor(COLOR_DESKTOP));
				if(GetSysColor(COLOR_DESKTOP) == GetSysColor(COLOR_WINDOWTEXT))
				{
					SetTextColor(outDc, RGB(255,255,255));
				}
				else
				{
					SetTextColor(outDc, GetSysColor(COLOR_WINDOWTEXT));
				}

#ifndef DO_NOT_CLEAR_LABEL_IF_IE_WINDOW_IS_BENEATH

				RECT rcLabelCoveringWindow = {0};
				for(size_t i = 0; i < windows.size(); ++i)
				{
					RECT winRc = {0};
					windows[i]->GetWindowRect(&winRc);
					::MapWindowPoints(NULL, hwnd, (LPPOINT)&winRc, 2);

					RECT rcLabelIntersection = rcLabel;
					rcLabelIntersection.left -= 1;
					::IntersectRect(&rcLabelIntersection, &rcLabelIntersection, &winRc);

					::UnionRect(&rcLabelCoveringWindow, &rcLabelCoveringWindow, &rcLabelIntersection);
				}

				ExtTextOut(outDc, 0, 0, ETO_OPAQUE, &rcLabelCoveringWindow, L"", 0, 0);
#endif //DO_NOT_CLEAR_LABEL_IF_IE_WINDOW_IS_BENEATH

				DrawShadowText(outDc, wText, -1, &rcLabel, flags, RGB(255,255,255), RGB(0,0,0), 2,2);
			}
		}
	}

	SelectObject(outDc, oldFont);
	DeleteObject(hFont);

	if(dc != outDc)
	{
		SetViewportOrgEx(outDc, origOrg.x, origOrg.y, NULL);
		BitBlt(dc, rc.left, rc.top, w, h, outDc, 0, 0, SRCCOPY);

		::SelectObject(outDc, oldBmp);
		DeleteObject(bmp);
		DeleteDC(outDc);
		
	}

	DeleteObject(brush);
}

// Steals the mouse or unsteals it by changing the capture
void CAveActiveDesktopHost::StealMouse(BOOL doSteal, UINT origMsg)
{
	HWND capHwnd = ::GetCapture();
	if(doSteal && (capHwnd == NULL || capHwnd == theHost->listView))
	{
		// we need to get the capture back, since someone thinks we are going to lose it otherwise.
		// Also send a WM_SETCURSOR to let the listview change the curosr back
		::SetCapture(theHost->listView);
		::SendMessage(theHost->listView, WM_SETCURSOR, (WPARAM)theHost->listView, MAKELPARAM(HTCLIENT, origMsg));
	}
	else
	{
		// We can only unsteal if the listview does not have the capture already
		if(capHwnd == theHost->listView)
			::ReleaseCapture();
	}
}

int CAveActiveDesktopHost::HitTestListView(const POINT& pt)
{
	LVHITTESTINFO info = {0};
	info.pt = pt;
	info.flags = LVHT_BELOW | LVHT_TOLEFT | LVHT_TORIGHT;
	return ListView_HitTest(listView, &info);
}

BOOL CAveActiveDesktopHost::IsIeWindow(HWND hwnd)
{
	for(size_t i = 0; i < theHost->windows.size(); ++i)
	{
		if(!theHost->windows[i]->IsWindow())
			continue;

		if(theHost->windows[i]->IsIeWindow(hwnd))
			return TRUE;
	}

	return FALSE;
}

LRESULT CALLBACK CAveActiveDesktopHost::GetMsgHookProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	MSG* msg = (MSG*)lParam;
	if(nCode < 0 || NULL == msg)
	{
		return CallNextHookEx(theHost->msgHook, nCode, wParam, lParam);
	}

	// we would get WM_PAINTS unlimitely because of the changing focus
	// when an item was selected if we show our custom marquee
	if(theHost->marquee.IsWindow() && theHost->marquee.IsWindowVisible())
	{
		UnhookWindowsHookEx(theHost->msgHook);
		theHost->msgHook = NULL;
		return 0;
	}

	HHOOK nextHook = NULL;

	// This hook is only active if we need to steal mouse down messages.
	if(msg->message >= WM_MOUSEFIRST || msg->message <= WM_MOUSELAST)
	{
		// check if a listview item is under the mouse.
		POINT pt = {GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)};	
		::MapWindowPoints(msg->hwnd, theHost->listView, &pt, 1);
		int hitResult = theHost->HitTestListView(pt);

		if(GetKeyState(VK_LBUTTON) >= 0 && GetKeyState(VK_RBUTTON) >= 0 && GetKeyState(VK_MBUTTON) >= 0 && hitResult == -1)
		{
			// if the mouse is no longer down and we are not over a listview item, stop stealing mouse messages, so
			// also don't pass on to the other hooks.
			UnhookWindowsHookEx(theHost->msgHook);
			theHost->msgHook = NULL;
		}
		else
		{
			// Otherwise, pass it on to the other hooks.
			nextHook = theHost->msgHook;
		}

		// reroute this mouse message to the listview, so messages that normally
		// go through because of the windows region in place now go routed to the listview.
		HWND ieHwnd = theHost->GetIeHost();
		if(IsChildOrSelf(ieHwnd, msg->hwnd))
		{
			msg->hwnd = theHost->listView;
			msg->lParam = MAKELPARAM(LOWORD(pt.x), LOWORD(pt.y));
		}
	}
	else
	{
		// no mouse message, always pass on to the next hook
		nextHook = theHost->msgHook;
	}

	// Special case (reverse engineered from ActiveDesktop assembly code) for mousehover activation:
	// unsteal the mouse capture if the mouse is hovering over the listview and no button is down.
	if(nextHook == NULL || (msg->message == WM_MOUSEHOVER && msg->hwnd == theHost->listView &&
		!(msg->wParam & MK_LBUTTON | MK_RBUTTON | MK_MBUTTON)))
	{
		theHost->StealMouse(FALSE, 0);
	}

	if(nextHook)
		return CallNextHookEx(nextHook, nCode, wParam, (LPARAM)msg);
	else
		return 0;

}

BOOL CAveActiveDesktopHost::ShouldStealMouse(HWND hwnd, const POINT& pt)
{
	BOOL needsMouse = FALSE;

	// We need to steal the mouse capture if no of the Ie host
	// windows has an element that wants it. E.g., if the mouse is over
	// a button or a link, that ie window wants to handle the mouse down events,
	// so we cannot steal the capture to the listview.
	for(size_t i = 0; !needsMouse && i < windows.size(); ++i)
	{
		if(!windows[i]->IsWindow())
			continue;

		if(windows[i]->IsIeWindow(hwnd))
		{
			CComPtr<IHTMLElement> element;
			windows[i]->hitTest(pt.x, pt.y, &element);
			if(element != NULL)
			{
				do
				{
					needsMouse = DoesElementNeedMouse(element);
					if(!needsMouse)
					{
						CComPtr<IHTMLElement> parent;
						element->get_parentElement(&parent);
						element.Release();
						element = parent;
					}
				}while(!needsMouse && element != NULL);
			}
		}
	}

	return !needsMouse;
}

HWND CAveActiveDesktopHost::GetIeHost()
{
	return windows.size() > 0 ? windows[0]->m_hWnd : NULL;
}

// This mouse hook checks whether we need to give the focus back to the listview
LRESULT CALLBACK CAveActiveDesktopHost::MouseHookProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	MOUSEHOOKSTRUCT* mhs = (MOUSEHOOKSTRUCT*)lParam;
	if(nCode >= 0 /*==HC_ACTION*/ && mhs != NULL && mhs->hwnd != theHost->listView && ::IsWindowVisible(theHost->listView) 
		&& (!theHost->marquee.IsWindow() || !theHost->marquee.IsWindowVisible())
		)
	{
		HWND ieHwnd = theHost->GetIeHost();
		HWND hitWindow = NULL;
		POINT listviewPt = mhs->pt;
		BOOL stealMouse = FALSE;

		// get the window under the mouse and possibly the listview item under the mouse
		hitWindow = WindowFromPoint(mhs->pt);
		::ScreenToClient(theHost->listView, &listviewPt);
		int hitItem = theHost->HitTestListView(listviewPt);

		BOOL isMouseDownMessage = wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN;

		BOOL ieDoesNotNeedMouse = theHost->ShouldStealMouse(mhs->hwnd, mhs->pt);

		// We always want to steal
		BOOL shouldSteal = FALSE;
		if(isMouseDownMessage)
		{
			// we actually want the desktops menu always to popup so, we always steal right-mouse button clicks
			
			shouldSteal = (wParam == WM_RBUTTONDOWN) || ieDoesNotNeedMouse;
		}

		// We want to steal the mouse capture if the cursor is actually over a listview item,
		// but nobody has the capture or if it's a mousedown operation that not needs to go
		// to the ie window
		BOOL isOverItemWithoutCapture = (GetCapture() == NULL && (hitItem != -1) && (hitWindow == NULL || hitWindow == theHost->listView));
		stealMouse = shouldSteal || isOverItemWithoutCapture;

		
		if(theHost->msgHook == NULL)
		{
			// we do not yet have a hook, so if we need to reroute
			// mouse message to our window to keep on stealing the focus
			// we need to setup a getmsg hook, that's the place where we can rewrite
			// the target of the actual mouse message,
			// but we do this only if the mouse is positioned on the IE window
			if(hitWindow != NULL && IsChildOrSelf(ieHwnd, hitWindow))
			{
				if(stealMouse)
				{
					theHost->StealMouse(TRUE, (UINT)wParam);
					DWORD currentThread = GetCurrentThreadId();
					theHost->msgHook	= SetWindowsHookEx(WH_GETMESSAGE, GetMsgHookProc, NULL, currentThread);
				}
				else if(ieDoesNotNeedMouse)
				{
					::PostMessage(theHost->listView, WM_SETCURSOR, (WPARAM)theHost->listView, MAKELPARAM(HTCLIENT, wParam));
				}
			}
			
		}
		else
		{
			// we already do have a hook, so stealing the mouse capture should be enough, or,
			// if we don't need to steal it again, fake a WM_SETCURSOR so we get the listviews cursor
			if(stealMouse)
			{
				StealMouse(TRUE, (UINT)wParam);
			}
			else
			{
				::SendMessage(theHost->listView, WM_SETCURSOR, (WPARAM)theHost->listView, MAKELPARAM(HTCLIENT, wParam));
			}
		}
	}

	return CallNextHookEx(theHost->mouseHook, nCode, wParam, lParam);
}

HRESULT CAveActiveDesktopHost::InstallHooks()
{
	if(mouseHook != NULL)
		return E_FAIL;

	DWORD currentThread = GetCurrentThreadId();

	mouseHook	= SetWindowsHookEx(WH_MOUSE, MouseHookProc, NULL, currentThread);
	

	return S_OK;
}

HRESULT CAveActiveDesktopHost::UninstallHooks()
{
	if(NULL == mouseHook)
		return E_FAIL;

	UnhookWindowsHookEx(mouseHook);

	mouseHook	= NULL;
	msgHook		= NULL;

	return S_OK;
}

// checks if an HTML elements needs to get the mouse
BOOL CAveActiveDesktopHost::DoesElementNeedMouse(IHTMLElement* element)
{
	if(NULL == element)
		return FALSE;

	const WCHAR* mouseElements[] = {
					L"a",
					L"anchor",
					L"applet",
					L"button",
					L"embed",
					L"select",
					L"textarea",
					//L"form",
					//L"iframe",					
					L"input",
					L"object",
					L"plugin",
					L"plugins",
	};

	CComBSTR tag;
	element->get_tagName(&tag);
	if(NULL == tag)
		return FALSE;

	CComVariant onclickHandler;
	HRESULT hRes = element->get_onclick(&onclickHandler);
	if(SUCCEEDED(hRes) && onclickHandler.vt == VT_DISPATCH && onclickHandler.pdispVal != NULL)
	{
		return TRUE;
	}

	for(size_t i = 0; i < _countof(mouseElements); ++i)
	{
		if(_wcsicmp(mouseElements[i], (const WCHAR*)tag) == 0)
			return TRUE;
	}

	return FALSE;
}
STDMETHODIMP CAveActiveDesktopHost::SetHTMLBackground(BSTR urlOrFile)
{
	HRESULT hRes = S_OK;


	CString url = urlOrFile != NULL ? urlOrFile : L"";
	if(!url.IsEmpty())
	{
		if(!isRunning)
		{
			hRes = Start();
			if(FAILED(hRes))
				return hRes;
		}

		if(windows.size() == 0)
		{
			CRect rc; // dummy rect
			_AddItem(url, &rc, ITEM_FLAG_FULLSCREEN); 
		}
		else
		{
			windows[0]->GoToUrl(url);
		}
	}
	else
	{
		if(isRunning)
		{
			Stop();
		}
	}

	AveRegFuncs::WriteString(HKEY_CURRENT_USER, AVE_ACTIVEDESKTOP_REG_KEY, L"HTMLBackground", url);

	return S_OK;
}

STDMETHODIMP CAveActiveDesktopHost::get_IsRunning(VARIANT_BOOL* pVal)
{
	if(NULL == pVal)
		return E_POINTER;

	*pVal = isRunning ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}
