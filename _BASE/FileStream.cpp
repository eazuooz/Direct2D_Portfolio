
#include "FileStream.h"
#include <assert.h>

///////////////////////////////// BASE FILE

// FPen
FileStream::FileStream(const char* _FileName, const char* _Mode) : file(nullptr)
{
	// W가 아니라면
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}
	fopen_s(&file, _FileName, _Mode);
}

FileStream::FileStream(const wchar_t* _FileName, const wchar_t* _Mode) : file(nullptr)
{
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}

	_wfopen_s(&file, _FileName, _Mode);
}

FileStream::~FileStream()
{
	if (nullptr != file)
	{
		fclose(file);
	}
}

#pragma region BINARY
///////////////////////////////// WB
FileWBStream::FileWBStream(const char* _FileName)
	: FileStream(_FileName, "wb") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileWBStream::FileWBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"wb") {}

///////////////////////////////// RB
FileRBStream::FileRBStream(const char* _FileName)
	: FileStream(_FileName, "rb") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileRBStream::FileRBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"rb") {}
#pragma endregion

#pragma region TEXT
///////////////////////////////// WB
FileWTStream::FileWTStream(const char* _FileName)
	: FileStream(_FileName, "wt") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileWTStream::FileWTStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"wt") {}

///////////////////////////////// RB
FileRTStream::FileRTStream(const char* _FileName)
	: FileStream(_FileName, "rt") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileRTStream::FileRTStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"rt") {}
#pragma endregion

