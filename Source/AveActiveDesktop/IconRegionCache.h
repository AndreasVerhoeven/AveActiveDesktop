#pragma once

#include <map>

class CIconRegionCache
{
protected:

	typedef int cache_identifier_t;

	class CIconRegionCacheEntry
	{
	public:
		CRgn rgn;
	};

	typedef std::map<cache_identifier_t, CIconRegionCacheEntry*> CacheMap;

	CacheMap cache;

public:
	CIconRegionCache(void);
	~CIconRegionCache(void);

	HRGN Lookup(HIMAGELIST imgList, int index, UINT state, UINT flags);
	HRGN Add(HRGN iconRegion, HIMAGELIST imgList, int index, UINT state, UINT flags);
	void Clear();
};
