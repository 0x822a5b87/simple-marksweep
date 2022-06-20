//
// Created by 0x822a5b87 on 2022/6/19.
//

#ifndef SIMPLE_MARK_SWEEP_OBJ_HPP
#define SIMPLE_MARK_SWEEP_OBJ_HPP

typedef int primitive;

enum class ObjectType;

class Object
{
public:
	ObjectType type;
	bool       marked;
	Object     *next;

	union
	{
		int value;

		struct
		{
			Object *head;
			Object *tail;
		};
	};

	static void printObject(Object *object);
};


#endif //SIMPLE_MARK_SWEEP_OBJ_HPP
