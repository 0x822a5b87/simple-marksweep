//
// Created by 0x822a5b87 on 2022/6/19.
//

#ifndef SIMPLE_MARK_SWEEP_VM_HPP
#define SIMPLE_MARK_SWEEP_VM_HPP

#include "iostream"
#include "obj.hpp"

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 8

class vm
{
public:
	std::shared_ptr<Object> stack[STACK_MAX]{};
	std::shared_ptr<Object> root;

	int sp;
	int currentNumOfObjects;
	int triggerGcNumOfObjects;

	vm();

	virtual ~vm();

	std::shared_ptr<Object> push(std::shared_ptr<Object>);

	std::shared_ptr<Object> pushPrimitive(int value);

	std::shared_ptr<Object> pushPair(const std::shared_ptr<Object>& tail, const std::shared_ptr<Object>& head);

	/**
	 * delete object which represent the object should be collect
	 * @param index
	 * @return
	 */
	void del(size_t index);

	void deleteObj(std::shared_ptr<Object>& obj);

	std::shared_ptr<Object> newObject(ObjectType objectType);

	void gc();

	void mark(const std::shared_ptr<Object>&);

	static void require(bool, const std::string&);
};


#endif //SIMPLE_MARK_SWEEP_VM_HPP
