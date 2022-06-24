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
	stack[sp++] = std::move(obj);
	return this->stack[this->sp - 1];
}

std::shared_ptr<Object> vm::pushPrimitive(int value)
{
	auto object = newObject(ObjectType::PRIMITIVE);
	object->value = value;
	return push(object);
}

std::shared_ptr<Object> vm::pushPair(const std::shared_ptr<Object>& tail, const std::shared_ptr<Object>& head)
{
	auto object = newObject(ObjectType::REFERENCE);
	object->tail = tail;
	tail->count++;
	object->head = head;
	head->count++;
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
	obj->count = 1;
	obj->type = objectType;
	obj->next = root;
	root = obj;
	obj->marked = false;

	currentNumOfObjects++;

	return obj;
}

void vm::gc()
{
	markAll();
	clearList();
	compact();
}

void vm::del(size_t index)
{
	require(index >= 0 && index < STACK_MAX, std::string("error index"));
	deleteObj(stack[index]);
}

void vm::deleteObj(std::shared_ptr<Object>& obj)
{
	if (obj == nullptr)
	{
		return;
	}
	obj->count--;
	if (obj->count == 0)
	{
		deleteObj(obj->head);
		deleteObj(obj->tail);
		currentNumOfObjects--;
		obj.reset();
	}
}

void vm::require(bool cond, const std::string& message)
{
	if (!cond)
	{
		std::cout << message << std::endl;
		std::exit(0);
	}
}

void vm::markAll()
{
	for (size_t i = 0; i < sp; ++i)
	{
		if (stack[i] != nullptr)
		{
			mark(stack[i]);
		}
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

void vm::clearList() const
{
	for (auto ptr = root; ptr != nullptr; ptr = ptr->next)
	{
		auto next = ptr->next;
		while (next != nullptr && next->count == 0)
		{
			next = next->next;
		}
		ptr->next = next;
	}
}

void vm::compact()
{
	int prevSp = sp;
	size_t currentPos = 0;
	for (size_t livePos = 0; livePos < sp; livePos++)
	{
		if (stack[livePos] != nullptr && stack[livePos]->count != 0)
		{
			stack[currentPos++] = stack[livePos];
		}
	}
	for (size_t collectPos = currentPos; collectPos < sp; collectPos++)
	{
		stack[collectPos].reset();
	}
	sp = currentPos;
	std::cout << "before compact : " << prevSp << ", after compact : " << sp  << std::endl;
}

