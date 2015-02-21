// AveHtmlBackgroundMenuHandler.cpp : Implementation of CAveHtmlBackgroundMenuHandler

#include "stdafx.h"
#include "AveHtmlBackgroundMenuHandler.h"


// CAveHtmlBackgroundMenuHandler
STDMETHODIMP CAveHtmlBackgroundMenuHandler::Initialize (LPCITEMIDLIST pidlFolder,LPDATAOBJECT pDataObj,HKEY hProgID)
{
	if(NULL == htmlDesktop)
	{
		htmlDesktop.CoCreateInstance(CLSID_AveHtmlDesktop);
	}

	if(NULL == htmlDesktop)
		return E_FAIL;

	if(NULL == pidlFolder)
		return E_INVALIDARG;

	if(0 == pidlFolder->mkid.cb)
		return S_OK;

	return E_INVALIDARG;
}





HRESULT CAveHtmlBackgroundMenuHandler::QueryContextMenu (
  HMENU hmenu, UINT uMenuIndex, UINT uidFirstCmd,
  UINT uidLastCmd, UINT uFlags )
{
	// our item is not the default one, thus do not display when only the default item is requested.
	if(uFlags & CMF_DEFAULTONLY)
		return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );

	UINT uNumItems = 0;

	VARIANT_BOOL isActive = VARIANT_FALSE;
	htmlDesktop->get_IsActive(&isActive);

	CString toggleStartStopMenuText;
	toggleStartStopMenuText.LoadString(isActive != VARIANT_FALSE ? IDS_MENUSTOP : IDS_MENUSTART);
	InsertMenu ( hmenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, toggleStartStopMenuText);
	uNumItems += 1;

  //CString configureMenuText;
  //configureMenuText.LoadString(IDS_MENUCONFIGURE);
  //InsertMenu ( hmenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd+1, configureMenuText);

 
  return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 1 );
}


HRESULT CAveHtmlBackgroundMenuHandler::GetCommandString (
  UINT_PTR idCmd, UINT uFlags, UINT* pwReserved,
  LPSTR pszName, UINT cchMax )
{
	return E_NOTIMPL;
}

HRESULT CAveHtmlBackgroundMenuHandler::SelectHtmlFile(HWND hwnd, BOOL unsetIfCancel)
{
	CString url = L"";
	CFileDialog dlg(TRUE, L".html", L"", 4|2, L"HTML Files(*.html;*.htt;*.htm)\0*.html;*.htt;*.htm\0All Files(*.*)\0*.*\0\0");
	if(dlg.DoModal())
	{
		url = dlg.m_szFileName;
	}

	if(url.IsEmpty() && unsetIfCancel)
		return S_OK;

	HRESULT hRes = htmlDesktop->Set(CComBSTR(url));
	if(FAILED(hRes))
	{
		MessageBox(hwnd, L"Could not start ActiveDesktop", L"AveActiveDesktop", MB_ICONERROR);
	}

	return hRes;
}

HRESULT CAveHtmlBackgroundMenuHandler::InvokeCommand (
  LPCMINVOKECOMMANDINFO pCmdInfo)
{
// If lpVerb really points to a string, ignore this function call and bail out.
	if(0 != HIWORD(pCmdInfo->lpVerb))
		return E_INVALIDARG;

	VARIANT_BOOL isActive = VARIANT_FALSE;
	htmlDesktop->get_IsActive(&isActive);
 
	switch(LOWORD(pCmdInfo->lpVerb))
	{
		case 0:
			if(isActive != VARIANT_FALSE)
			{
				htmlDesktop->Set(L"");
			}
			else
			{
				SelectHtmlFile(pCmdInfo->hwnd, TRUE);
			}
			
			return S_OK;

		default:
			return E_INVALIDARG;
	}
}