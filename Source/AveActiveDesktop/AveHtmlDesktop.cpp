// AveHtmlDesktop.cpp : Implementation of CAveHtmlDesktop

#include "stdafx.h"
#include "AveHtmlDesktop.h"


// CAveHtmlDesktop

HRESULT CAveHtmlDesktop::_GetHost(IAveActiveDesktopHost** host)
{
	if(NULL == host)
		return E_POINTER;

	*host = NULL;
	
	CComPtr<IUnknown> unknownHost;
	HRESULT hRes = GetActiveObject(CLSID_AveActiveDesktopHost, NULL, &unknownHost);
	if(FAILED(hRes) || NULL == unknownHost)
		return E_FAIL;

	return unknownHost->QueryInterface(host);
}

STDMETHODIMP CAveHtmlDesktop::Set(BSTR urlOrFile)
{
	CComPtr<IAveActiveDesktopHost> host;
	HRESULT hRes = _GetHost(&host);
	if(FAILED(hRes) || NULL == host)
		return E_FAIL;

	return host->SetHTMLBackground(urlOrFile);
}

STDMETHODIMP CAveHtmlDesktop::get_IsActive(VARIANT_BOOL* pVal)
{
	CComPtr<IAveActiveDesktopHost> host;
	HRESULT hRes = _GetHost(&host);
	if(FAILED(hRes) || NULL == host)
		return E_FAIL;

	return host->get_IsRunning(pVal);

}
