//
// Created by 0x822a5b87 on 2022/6/19.
//

#include <iostream>
#include "obj.hpp"

// as a considering of simplify, We only declared two kinds of objects
enum class ObjectType
{
	PRIMITIVE,
	REFERENCE
};


void Object::printObject(Object *object)
{
	switch (object->type)
	{
		case ObjectType::PRIMITIVE:
			std::cout << object->value << std::endl;
			break;
		case ObjectType::REFERENCE:
			std::cout << "(";
			Object::printObject(object->head);
			std::cout << ", ";
			Object::printObject(object->tail);
			std::cout << ")";
			break;
	}
}
