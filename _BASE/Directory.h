#pragma once
#include <vector>
#include <string>

#include "IO.h"
#include "File.h"
//디렉토리 복사, 이동, 이름바꾸기, 만들기 및 삭제와 같은 일반적인 작업에는 DIrectory클래스를 사용


class Directory: public IO
{
public:
	void ReplaceToParentPath();
	bool MoveDirectory(const wchar_t* _FolderName);
	bool ExistFileInDir(const wchar_t* _FileName);
	
public:	
	std::wstring GetFolderName();
	std::vector<std::wstring> GetDirectories();
	void GetAllFileName(std::vector<File>& _FileNames, const wchar_t* _FileExt);


public:
	Directory(const Directory& _Other); // 이프로그램이 실행된 위치를 자신의 경로로 설정
	Directory(const wchar_t* _Name);
	Directory();						// 경로가 지정된것 Directory(const wchar_t* _Name);
	~Directory();
};

