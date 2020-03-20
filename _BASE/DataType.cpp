#include "DataType.h"
#include <iostream>


DataType::DataType() : info(nullptr)
{
}


DataType::~DataType()
{
}

void DataType::TypeSetting()
{
	info = &typeid(*this);
	//std::cout << info->name() << std::endl;
}
