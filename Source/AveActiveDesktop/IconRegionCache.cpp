#include "StdAfx.h"
#include "IconRegionCache.h"

CIconRegionCache::CIconRegionCache(void)
{
}

CIconRegionCache::~CIconRegionCache(void)
{
	Clear();
}

HRGN CIconRegionCache::Lookup(HIMAGELIST imgList, int index, UINT state, UINT flags)
{
	CacheMap::iterator existingEntryIter = cache.find(index);
	if(existingEntryIter != cache.end())
	{
		return existingEntryIter->second->rgn.m_hRgn;
	}

	return NULL;
}


HRGN CIconRegionCache::Add(HRGN iconRegion, HIMAGELIST imgList, int index, UINT state, UINT flags)
{
	CacheMap::iterator existingEntryIter = cache.find(index);
	if(existingEntryIter != cache.end())
	{
		delete existingEntryIter->second;
		cache.erase(existingEntryIter);
	}

	CIconRegionCacheEntry* entry = new CIconRegionCacheEntry;
	entry->rgn.Attach(iconRegion);

	cache.insert(std::make_pair(index, entry));

	return 0;
}

void CIconRegionCache::Clear()
{
	for(CacheMap::iterator iter = cache.begin(); iter != cache.end(); ++iter)
	{
		delete iter->second;
	}

	cache.clear();
}