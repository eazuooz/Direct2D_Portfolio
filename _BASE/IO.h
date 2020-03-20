#pragma once
// io input output의 약자
// 파일입출력 함수나 아니면 헤더라면
// 대부분 io 라는 
// img Texture

#include <iostream>
#include <io.h>

#include <string>




//System.IO 네임 스페이스에는 파일 및 데이터 스트림에 대한 
//읽기 및 쓰기를 허용하는 형식과 기본 파일 및 디렉터리 지원을 제공하는 형식이 포함되어 있습니다.
class IO	//input output
{
public:
	static bool ExistFile(const char*    _FileName);
	static bool ExistFile(const wchar_t* _FileName);

protected:
	std::wstring fullPath;

public:
	void PathSetting(const wchar_t* _Path);
	void PathSetting(const std::wstring& _Path);

public:
	bool FileCheck();

public:
	inline const wchar_t* GetFullPath()
	{
		return fullPath.c_str();
	}

	inline std::wstring GetFullPathString()
	{
		return fullPath;
	}

	inline int GetFullPathSize()
	{
		return (int)fullPath.size();
	}

protected:
	std::wstring GetFileName();

public:
	IO() {}
	~IO() {}
};

