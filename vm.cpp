//
// Created by 0x822a5b87 on 2022/6/19.
//

#include "vm.hpp"

#include <utility>
#include "obj.hpp"

vm::~vm()
{
	std::cout << "exit vm" << std::endl;
}

vm::vm()
{
	std::cout << "start vm" << std::endl;

	this->root                  = nullptr;
	this->sp                    = 0;
	this->currentNumOfObjects   = 0;
	this->triggerGcNumOfObjects = INITIAL_GC_THRESHOLD;
}

std::shared_ptr<Object> vm::push(std::shared_ptr<Object> obj)
{
	require(this->sp < STACK_MAX, std::string("stack overflow"));
	this->stack[this->sp++] = std::move(obj);
	return this->stack[this->sp];
}

std::shared_ptr<Object> vm::pushPrimitive(int value)
{
	auto object = newObject(ObjectType::PRIMITIVE);
	object->value = value;
	return push(object);
}

std::shared_ptr<Object> vm::pushPair(std::shared_ptr<Object> tail, std::shared_ptr<Object> head)
{
	auto object = newObject(ObjectType::REFERENCE);
	object->tail = std::move(tail);
	object->head = std::move(head);
	push(object);
	return object;
}

std::shared_ptr<Object> vm::newObject(ObjectType objectType)
{
	if (currentNumOfObjects == triggerGcNumOfObjects)
	{
		gc();
	}

	auto obj = std::shared_ptr<Object>(new Object{});
	obj->type = objectType;
	obj->next = root;
	root = obj;
	obj->marked = false;

	currentNumOfObjects++;

	return obj;
}

void vm::gc()
{
	for (size_t i = 0; i < sp; ++i)
	{
		if (stack[i] != nullptr)
		{
			mark(stack[i]);
		}
	}
}

void vm::del(size_t index)
{
	require(index >= 0 && index < STACK_MAX, std::string("error index"));
	stack[index] = nullptr;
	currentNumOfObjects--;
}

void vm::require(bool cond, const std::string& message)
{
	if (!cond)
	{
		std::cout << message << std::endl;
		std::exit(0);
	}
}

void vm::mark(const std::shared_ptr<Object>& obj)
{
	if (obj == nullptr)
	{
		return;
	}
	if (obj->marked)
	{
		return;
	}
	obj->marked = true;
	if (obj->type == ObjectType::REFERENCE)
	{
		mark(obj->head);
		mark(obj->tail);
	}
}
