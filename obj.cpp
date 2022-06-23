//
// Created by 0x822a5b87 on 2022/6/19.
//

#include <iostream>
#include "obj.hpp"


void Object::printObject(Object *object)
{
	switch (object->type)
	{
		case ObjectType::PRIMITIVE:
			std::cout << object->value << std::endl;
			break;
		case ObjectType::REFERENCE:
			std::cout << "(";
			Object::printObject(object->head.get());
			std::cout << ", ";
			Object::printObject(object->tail.get());
			std::cout << ")";
			break;
	}
}

Object::~Object()
{
	std::cout << "destroy object value : " << value << std::endl;
}
