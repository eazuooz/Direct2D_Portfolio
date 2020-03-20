#pragma once
#include "IO.h"
#include <vector>


//단일 파일의 작성, 복사, 삭제, 이동 및 열기에 대한 메서드를 제공
//FILESTREAM객체를 만드는데 도움을준다

class File : public IO
{
public:
	//확장자 넣어주면 true
	bool CheckExtension(const wchar_t* _Ext);	//확장자 체크
	std::wstring GetFileName();

	std::vector<std::wstring> GetAllFileName();

public:	
	File(const wchar_t* _FileName);
	File(const std::wstring& _Path);
	File();
	~File();
};

