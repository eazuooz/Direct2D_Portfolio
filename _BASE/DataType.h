#pragma once
#include <typeinfo>

// C++ 
// RTTI 리얼 타임 타입 인포
// RTTI 리얼 타임 타입 아이덴티테이션
// 연산자가 있다.
// type_info Data = typeid(자료형 혹은 식별자)

class DataType
{
private:
	const type_info* info;

public:
	void TypeSetting();


public:
	bool CompareType(const type_info* _Info)
	{
		return info == _Info;
	}

	template<typename T>
	bool CompareType()
	{
		return info == &typeid(T);
	}

	bool CompareType(const DataType& _Name)
	{
		return info == _Name.info;
	}

public:
	DataType();
	virtual ~DataType();
};

