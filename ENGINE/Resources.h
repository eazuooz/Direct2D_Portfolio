#pragma once
#include <SmartPtr.h>
#include <Path.h>
#include <Name.h>
#include <File.h>
#include <unordered_map>	//hash table more faster than std::map

#include "GraphicDevice.h"

class Resources : public ControlBlock, public Name
{
private:
	template<typename T>	//class template	클래스템플릿 기반으로 템플릿클래스를 만들어낸다.
	class ResourceMgr
	{
	public:
		static std::unordered_map<std::wstring, My_Ptr<T>> resourceMap;
		

	public:
		//template<typename T>
		static My_Ptr<T> Find(const std::wstring& _Key)	// template function
		{
			typename std::unordered_map<std::wstring, My_Ptr<T>>::iterator  FindIter = resourceMap.find(_Key);
			//const auto& FindIter = resourceMap.find(_Key);

			if (FindIter == resourceMap.end())
			{
				return nullptr;
			}

			return FindIter->second;
		}

		template<typename... _Types>	//function template
		static My_Ptr<T> Load(const std::wstring& _Path, _Types&&... _Args)
		{
			File NewFile = _Path;
			std::wstring FileName = NewFile.GetFileName();

			if (nullptr != Find(FileName))
			{
				BOOM;
				return nullptr;
			}

			T* NewResource = new T();
			NewResource->SetName(FileName);
			NewResource->FileSetting(_Path);
			if (false == NewResource->Load(_Args...))
			{
				BOOM;
				return nullptr;
			}
			resourceMap.insert(std::unordered_map<std::wstring, My_Ptr<T>>::value_type(FileName, NewResource));

			return NewResource;
		}

		template<class... _Types>
		static My_Ptr<T> LoadToKey(const std::wstring& _Key, const std::wstring& _Path, _Types&&... _Args)
		{
			if (nullptr != Find(_Key))
			{
				BOOM;
				return nullptr;
			}

			T* NewResource = new T();
			// 키의 타입을 봐서 키가 wstring이 아니라면
			// char*
			// wchar_t* 가 아니라면 문자열이 아니라면
			NewResource->SetName(_Key);
			NewResource->FileSetting(_Path);
			if (false == NewResource->Load(_Args...))
			{
				BOOM;
				return nullptr;
			}


			resourceMap.insert(std::unordered_map<std::wstring, My_Ptr<T>>::value_type(_Key, NewResource));

			return NewResource;
		}

		template<typename... _Types>
		static My_Ptr<T> Create(const std::wstring& _Key, _Types&&... _Args)
		{
			if (nullptr != Find(_Key))
			{
				BOOM;
				return nullptr;
			}

			T* NewResource = new T();
			NewResource->SetName(_Key);
			if (false == NewResource->Create(_Args...))
			{
				BOOM;
				return nullptr;
			}
			resourceMap.insert(std::unordered_map<std::wstring, My_Ptr<T>>::value_type(_Key, NewResource));

			return NewResource;
		}
	};

public:
	template<typename T>
	static My_Ptr<T> Find(const std::wstring& _Key)
	{
		return ResourceMgr<T>::Find(_Key);
	}

	template<typename T, class... _Types>
	static My_Ptr<T> Create(const std::wstring& _Key, _Types&&... _Args)
	{
		return ResourceMgr<T>::Create(_Key, _Args...);
	}

	template<typename T, class... _Types>
	static My_Ptr<T> Load(const std::wstring& _Key, _Types&&... _Args)
	{
		return ResourceMgr<T>::Load(_Key, _Args...);
	}
	
	template<typename T, class... _Types>
	static My_Ptr<T> LoadToKey(const std::wstring& _Key, const std::wstring& _Path, _Types&&... _Args)
	{
		return ResourceMgr<T>::LoadToKey(_Key, _Path, _Args...);
	}

protected:
	File file;

public:
	void FileSetting(const wchar_t* _Path)
	{
		file.PathSetting(_Path);
	}

	void FileSetting(const std::wstring& _Path)
	{
		file.PathSetting(_Path.c_str());
	}

public:
	Resources();
	~Resources();
};

template<typename T>
std::unordered_map<std::wstring, My_Ptr<T>> Resources::ResourceMgr<T>::resourceMap = std::unordered_map<std::wstring, My_Ptr<T>>();