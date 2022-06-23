//
// Created by 0x822a5b87 on 2022/6/19.
//

#include <iostream>
#include "vm.hpp"

void test1()
{
	vm vm_instance;

	for (int i = 0; i < 8; ++i)
	{
		vm_instance.pushPrimitive(i);
	}

	assert(vm_instance.currentNumOfObjects == 8);


	for (int i = 8; i < 11; ++i)
	{
		vm_instance.pushPrimitive(i);
	}

	vm_instance.del(0);
	vm_instance.del(1);
	vm_instance.del(2);
	vm_instance.del(9);
	vm_instance.del(10);

	for (int i = 11; i < 15; ++i)
	{
		vm_instance.pushPrimitive(i);
	}

	assert(vm_instance.currentNumOfObjects == 10);

	vm_instance.gc();
	assert(vm_instance.currentNumOfObjects == 10);


	assert(vm_instance.stack[0] == nullptr);
	assert(vm_instance.stack[1] == nullptr);
	assert(vm_instance.stack[2] == nullptr);
	assert(vm_instance.stack[3]->marked);
	assert(vm_instance.stack[4]->marked);
	assert(vm_instance.stack[5]->marked);
	assert(vm_instance.stack[6]->marked);
	assert(vm_instance.stack[7]->marked);
	assert(vm_instance.stack[8]->marked);
	assert(vm_instance.stack[9] == nullptr);
	assert(vm_instance.stack[10] == nullptr);
	assert(vm_instance.stack[11]->marked);
	assert(vm_instance.stack[12]->marked);
	assert(vm_instance.stack[13]->marked);
	assert(vm_instance.stack[14]->marked);
}

void test2()
{
	vm vm_instance;
	auto _0 = vm_instance.pushPrimitive(0);
	auto _1 = vm_instance.pushPrimitive(1);
	auto _2 = vm_instance.pushPrimitive(2);
	auto _3 = vm_instance.pushPrimitive(3);
	auto _4 = vm_instance.pushPrimitive(4);
	auto _5 = vm_instance.pushPrimitive(5);

	auto _6 = vm_instance.pushPair(_0, _1);
	auto _7 = vm_instance.pushPair(_2, _3);

	assert(vm_instance.currentNumOfObjects == 8);

	vm_instance.del(6);
	vm_instance.gc();
	// vm_instance[6] should be collect
	assert(vm_instance.currentNumOfObjects == 7);
	assert(vm_instance.stack[6] == nullptr);

	vm_instance.del(2);
	vm_instance.del(3);
	vm_instance.gc();
	// vm_instance[7] still contains a reference to vm_instance[2] and vm_instance[3], so currentNumOfObjects still 6
	assert(vm_instance.currentNumOfObjects == 7);

	vm_instance.del(7);
	assert(vm_instance.currentNumOfObjects == 4);
}

int main(int argc, char **argv)
{
	test1();
	test2();

	return 0;
}