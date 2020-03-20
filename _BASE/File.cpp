#include "File.h"
#include <Windows.h>

#include "Debug.h"


File::File(const wchar_t* _FileName)
{
	PathSetting(_FileName);
}

File::File(const std::wstring& _Path)
{
	PathSetting(_Path);
}

File::File()
{

}

File::~File()
{
}


bool File::CheckExtension(const wchar_t* _Ext)
{
	std::wstring Ext = _Ext;
	size_t CheckComma = Ext.find(L".");

	if (CheckComma >= Ext.size())
	{
		Ext = L"." + Ext;
	}

	size_t CheckExt = fullPath.find(Ext.c_str());
	if (CheckExt >= fullPath.size())
	{
		return false;
	}

	return true;
}

std::wstring File::GetFileName()
{
	return IO::GetFileName();
}

std::vector<std::wstring> File::GetAllFileName()
{
	std::vector<std::wstring> FileName;
	std::wstring search = fullPath + L"\\*.*";
	_wfinddata_t findData;
	LONG handle = (LONG)_wfindfirst(search.c_str(), &findData);

	if (handle == -1)
	{
		assert(false);
		return FileName;
	}
	int result = 0;

	do
	{
		if (0 == IO::ExistFile(findData.name))
		{
			FileName.push_back(findData.name);
		}
		result = _wfindnext(handle, &findData);

	} while (result != -1);



	return FileName;
}

