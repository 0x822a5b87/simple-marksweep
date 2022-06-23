//
// Created by 0x822a5b87 on 2022/6/19.
//

#ifndef SIMPLE_MARK_SWEEP_OBJ_HPP
#define SIMPLE_MARK_SWEEP_OBJ_HPP

typedef int primitive;

// as a considering of simplify, We only declared two kinds of objects
enum class ObjectType
{
	PRIMITIVE,
	REFERENCE
};


class Object
{
public:

	static void printObject(Object *object);

	virtual ~Object();

	ObjectType              type;
	bool                    marked;
	std::shared_ptr<Object> next;

	int value;

	struct
	{
		std::shared_ptr<Object> head;
		std::shared_ptr<Object> tail;
	};

};


#endif //SIMPLE_MARK_SWEEP_OBJ_HPP
