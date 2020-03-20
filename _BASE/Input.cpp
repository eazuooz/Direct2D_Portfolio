#include "Input.h"
#include <Windows.h>


My_Ptr<Input::Key> Input::newKey = nullptr;
std::map<std::wstring, My_Ptr<Input::Key>>			  Input::allKeyMap;
std::map<std::wstring, My_Ptr<Input::Key>>::iterator Input::keyStart;
std::map<std::wstring, My_Ptr<Input::Key>>::iterator Input::keyEnd;

//Input::Destructor Input::destoructor;


#pragma region INPUT::KEY
Input::Key::Key() : up(false), down(false), press(false), notPress(true)
{

}

Input::Key::~Key()
{

}

bool Input::Key::IsKeyCheck() // 키체크하는 구간
{
	for (size_t i = 0; i < keyArray.size(); ++i)
	{
		if (0 == GetAsyncKeyState(keyArray[i]))
		{
			return false;
		}
	}

	return true;
}

void Input::Key::Update()	   // 키체크하는구간
{
	if (true == IsKeyCheck()) //특정키가 눌려져있는 경우
	{
		if (true == notPress) //지금 안눌려져 있다.
		{
			up			= false;
			down		= true;
			press		= true;
			notPress	= false;
		}
		else  //지금 눌러져있다.
		{
			up			= false;
			down		= false;
			press		= true; 
			notPress	= false;
		}
	}
	else //특정키가 눌려져 있지 않은 경우
	{
		if (true == press)	// 눌러져 있다
		{					//키가 눌렸는가 ? 노 이전프레임에도 키가 눌렷는가 ? yes
			up			= true;
			down		= false;
			press		= false;
			notPress	= true;
		}
		else //눌러져있지않다
		{
			up			= false;
			down		= false;
			press		= false;
			notPress	= true;
		}
	}
}





#pragma endregion
//////////////////////////
#pragma region INPUT
//void Input::InputEnd()
//{
//	keyStart = allKeyMap.begin();
//	keyEnd = allKeyMap.end();
//
//	for (; keyStart != keyEnd; ++keyStart)
//	{
//		if (nullptr != keyStart->second)
//		{
//			delete keyStart->second;
//			keyStart->second = nullptr;
//		}
//	}
//
//}

Input::Input()
{
}


Input::~Input()
{
}

My_Ptr<Input::Key> Input::FindKey(const wchar_t* _Name)
{
	std::map<std::wstring, My_Ptr<Key>>::iterator FindIter = allKeyMap.find(_Name);

	if (FindIter == allKeyMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void Input::Update()
{
	keyStart = allKeyMap.begin();
	keyEnd = allKeyMap.end();

	for (; keyStart != keyEnd; ++keyStart)
	{
		keyStart->second->Update();
	}
}

bool Input::Up(const wchar_t* _Name)
{
	My_Ptr<Input::Key> key = FindKey(_Name);

	if (nullptr == FindKey)
	{
		assert(false);
	}

	return key->up;
}

bool Input::Down(const wchar_t* _Name)
{
	My_Ptr<Input::Key> key = FindKey(_Name);

	if (nullptr == FindKey)
	{
		assert(false);
	}

	return key->down;
}

bool Input::Press(const wchar_t* _Name)
{
	My_Ptr<Input::Key> key = FindKey(_Name);

	if (nullptr == FindKey)
	{
		assert(false);
	}

	return key->press;
}

bool Input::NotPress(const wchar_t* _Name)
{
	My_Ptr<Input::Key> key = FindKey(_Name);

	if (nullptr == FindKey)
	{
		assert(false);
	}

	return key->notPress;
}



#pragma endregion


