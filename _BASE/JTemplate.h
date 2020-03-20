#pragma once
#include <map>


class Template
{
public:
	template<typename T>
	static void MemoryInitZero(T& _Name)
	{
		memset(&_Name, 0, sizeof(T));
	}

	template<typename T>
	static void MemoryInit(T& _Name, T _Data)
	{
		memset(&_Name, _Data, sizeof(T));
	}

	template<typename TReturn, typename TKey, typename TMap>
	static TReturn* MapFindToPointer(TKey& _Key, TMap& _Map)
	{
		typename TMap::iterator FindIter = _Map.find(_Key);

		if (FindIter == _Map.end())
		{
			return nullptr;
		}
		return FindIter->second;
	}

private:
	Template() {};
	~Template() {};
};

