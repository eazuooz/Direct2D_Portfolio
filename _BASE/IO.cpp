#include "IO.h"
#include "Debug.h"


bool IO::ExistFile(const char* _FileName)
{
	return _access_s(_FileName, 0) == 0;
}

bool IO::ExistFile(const wchar_t* _FileName)
{
	return _waccess_s(_FileName, 0) == 0;
}

void IO::PathSetting(const wchar_t* _Path)
{
	fullPath = _Path;
	FileCheck();
}

void IO::PathSetting(const std::wstring& _Path)
{
	fullPath = _Path;
	FileCheck();
}

bool IO::FileCheck()
{
	if (false == ExistFile(fullPath.c_str()))
	{
		BOOM;
		return false;
	}
	return true;
}

std::wstring IO::GetFileName()
{
	std::wstring FolderName = fullPath;

	size_t CutCount = FolderName.find_last_of(L'\\', fullPath.size());
	FolderName.replace(0, CutCount + 1, L"");

	return FolderName;
}