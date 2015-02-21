// AveActiveDesktop.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "AveActiveDesktop.h"
#include "dlldatax.h"


#include "AveRegFuncs.h"
#include "AveActiveDesktopHost.h"


#define BOOTKICK_HOST

BOOL ShouldNotRunInExplorer()
{
	return AveRegFuncs::ReadInt(HKEY_CURRENT_USER, AVE_ACTIVEDESKTOP_REG_KEY, L"DoNotLoadInExplorer", 0) != 0;
}

BOOL IsRunningInExplorer()
{
	WCHAR path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	const WCHAR* fileName = PathFindFileName(path);
	return _wcsicmp(fileName, L"explorer.exe") == 0 || _wcsicmp(fileName, L"verclsid.exe") == 0;
}

BOOL IsRunningInDebugHost()
{
	WCHAR path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	const WCHAR* fileName = PathFindFileName(path);
	return _wcsicmp(fileName, L"AveEffectDebugHost.exe") == 0;
}

class CAveActiveDesktopModule : public CAtlDllModuleT< CAveActiveDesktopModule >
{
public :
	DECLARE_LIBID(LIBID_AveActiveDesktopLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AVEACTIVEDESKTOP, "{202F4EB3-9C02-48F0-866B-D30EE2AA4B2F}")
};

CAveActiveDesktopModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if(!CheckTimeBomb())
		return FALSE;

#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hr = PrxDllCanUnloadNow();
    if (hr != S_OK)
        return hr;
#endif
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	static bool isRecurringCall = false;

	if(!CheckTimeBomb())
		return E_FAIL;

#ifdef BOOTKICK_HOST
	// Boot kick for now :)
	if(!isRecurringCall && IsRunningInExplorer())
	{
		isRecurringCall = true;

		if(!CAveActiveDesktopHost::hasHost())
		{
			CComPtr<IAveActiveDesktopHost> host;
			host.CoCreateInstance(CLSID_AveActiveDesktopHost);
			CComQIPtr<IShellExtInit> shellExtInit(host);
			if(shellExtInit != NULL)
			{
				shellExtInit->Initialize(NULL, NULL, NULL);
			}
		}

		isRecurringCall = false;
	}
#endif//BOOTKICK_HOST

	//if(!IsRunningInExplorer() && ::IsEqualCLSID(rclsid, CLSID_AveActiveDesktopHost))
	//	return E_FAIL;

#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	if(!CheckTimeBomb())
		return E_FAIL;

	AveRegFuncs::WriteString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\explorer\\SharedTaskScheduler", 
			L"{C3E638A6-4610-4029-99CC-04353C212FC1}", L"AveActiveDesktopLauncher");

    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
#endif
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	SHDeleteValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\explorer\\SharedTaskScheduler", 
			L"{C3E638A6-4610-4029-99CC-04353C212FC1}");

	HRESULT hr = _AtlModule.DllUnregisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
    if (FAILED(hr))
        return hr;
    hr = PrxDllUnregisterServer();
#endif
	return hr;
}

