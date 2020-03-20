#include "Directory.h"
#include <Windows.h>
#include <atlstr.h>

#include <stdio.h>
#include <io.h>
#include <conio.h>


#include "File.h"
#include "Debug.h"



Directory::Directory(const Directory& _Other) // 이프로그램이 실행된 위치를 자신의 경로로 설정
{
	PathSetting(_Other.fullPath);	
}
Directory::Directory(const wchar_t* _Path)
{
	PathSetting(_Path);
	FileCheck();
}

Directory::Directory()
{
	wchar_t Arr[1000];
	GetCurrentDirectoryW(1000, Arr);
	fullPath = Arr;	
}


Directory::~Directory()
{
}


std::wstring Directory::GetFolderName()
{
	std::wstring folderName = fullPath;

	size_t curCount = folderName.find_last_of(L"\\", fullPath.size());
	folderName.replace(0, curCount + 1, L"");

	return folderName;
}

void Directory::ReplaceToParentPath()
{
	size_t curCount = fullPath.find_last_of(L"\\", fullPath.size());
	fullPath.replace(curCount, fullPath.size(), L"");
}

bool Directory::MoveDirectory(const wchar_t* _FolderName)
{
	std::wstring findPath = fullPath + L"\\" + _FolderName;

	if (false == IO::ExistFile(findPath.c_str()))
	{
		assert(false);
		return false;
	}
	fullPath = findPath;

	return true;
}

bool Directory::ExistFileInDir(const wchar_t* _FileName)
{
	return IO::ExistFile( (fullPath + L"\\" +_FileName).c_str() );
}

std::vector<std::wstring> Directory::GetDirectories()
{
	std::vector<std::wstring> Directories;
	std::wstring search = fullPath + L"\\*.*";
	_wfinddata_t findData;
	LONG handle = (LONG)_wfindfirst(search.c_str(), &findData);
	
	if (handle == -1)
	{
		assert(false);
		return Directories;
	}
	int result = 0;
	
	do
	{
		if (0 == IO::ExistFile(findData.name))
		{			
			Directories.push_back(findData.name);			
		}
		result = _wfindnext(handle, &findData);
		
	} while (result != -1);

	
	
	return Directories;	
}


void Directory::GetAllFileName(std::vector<File>& _FileNames, const wchar_t* _FileExt)
{
	std::string Path = CW2A(fullPath.c_str()).m_psz;
	std::string Ex = CW2A(_FileExt).m_psz;
	Path.append("\\");
	Path.append(Ex);

	std::string PlusPath = CW2A(fullPath.c_str()).m_psz;
	PlusPath.append("\\");

	_finddata_t fd;
	intptr_t handle;
	int result = 1;
	handle = _findfirst(Path.c_str(), &fd);
	//현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		if ('.' != fd.name[0])
		{
			_FileNames.push_back(File(CA2W((PlusPath + fd.name).c_str()).m_psz));
		}
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}