#pragma once
#include <string>
#include <vector>
#include <map>
#include <assert.h>

#include "SmartPtr.h"
//bool m_Up;
//bool m_UpAway; // 이녀석만 true
//bool m_Down;
//bool m_Press;

//눌렸다 안눌렸다.
//프레임으로 치면

//눌린다 땐다
// bool 지금 한순간 눌렸다. 1프레임동안 true가 되는 변수//down
// bool 계속 눌리고 있다. 지속적으로 눌리고 있다		//press

//자신이 필요한 것만 만들고
//bool 안눌려있다. -> 지속적으로 떼어져 있다. // upAway
//bool 떈순간 -> 1프레임만 떗다				  // up

//bool이 리턴된다.
// 동시키도 가능하게 'A' + 'B'

// if(ture == HINPU::GetUpAway(L"Fire"))
// if(ture == HINPU::GetPress(L"Fire"))
// if(ture == HINPU::GetUp(L"Fire"))
// if(ture == HINPU::GetDown(L"Fire"))
// 총알 쏘는 코드 사용



class Input 
{
#pragma region DesInerClass
private:
	//class Destructor
	//{
	//public:
	//	~Destructor()
	//	{
	//		Input::InputEnd();
	//	}
	//};
	//static Destructor destoructor;
	//friend Destructor;
#pragma endregion
private:
	class Key : public ControlBlock
	{
	private: 
		friend Input;

	public:
		std::vector<int> keyArray;

		bool up;		
		bool down;
		bool press;
		bool notPress; //notPressed // upAway
		

	public:
		bool IsKeyCheck(); // 키체크하는 구간
		void Update();	   // 키체크하는구간

	private:
		Key();
		~Key();
	};

private:
	static std::map<std::wstring, My_Ptr<Key>> allKeyMap;
	static std::map<std::wstring, My_Ptr<Key>>::iterator keyStart;
	static std::map<std::wstring, My_Ptr<Key>>::iterator keyEnd;

	//static void InputEnd();

private:
	static My_Ptr<Key> FindKey(const wchar_t* _Name);

public:
	static void Update();

public:
	static My_Ptr<Key> newKey;

	template<typename ...Rest>
	static void CreateKey(const wchar_t* _Name, Rest ..._Arg)
	{
		newKey = FindKey(_Name);

		if (nullptr != newKey)
		{
			assert(false);
		}

		newKey = new Key();

		newKey->keyArray.reserve(sizeof...(_Arg));
		PushKey(_Arg...);

		allKeyMap.insert(std::map<std::wstring, My_Ptr<Key>>::value_type(_Name, newKey));
	}

	template<typename ...Rest>
	static void PushKey(int _Key, Rest ..._Arg)
	{
		newKey->keyArray.push_back(_Key);
		PushKey(_Arg...);
	}


	static void PushKey()
	{
		//
	}

public:
	static bool Up(const wchar_t* _Name);
	static bool Down(const wchar_t* _Name);
	static bool Press(const wchar_t* _Name);
	static bool NotPress(const wchar_t* _Name);

public:
	Input();
	~Input();
};

