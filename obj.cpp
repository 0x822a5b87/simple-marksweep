//
// Created by 0x822a5b87 on 2022/6/19.
//

#include <iostream>
#include "obj.hpp"


std::string Object::printObject(Object *object)
{
	if (object == nullptr)
	{
		return "nullptr";
	}
	std::string str;
	switch (object->type)
	{
		case ObjectType::PRIMITIVE:
			str += (std::to_string(object->value));
			break;
		case ObjectType::REFERENCE:
			str += "(";
			str += Object::printObject(object->head.get());
			str += ", ";
			str += Object::printObject(object->tail.get());
			str += ")";
			break;
	}
	return str;
}

Object::~Object()
{
	std::cout << "destroy object value : " << Object::printObject(this) << std::endl;
}
