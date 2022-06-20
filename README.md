# simple-marksweep

a simple marksweep algorithm implement, inspired by [Baby’s First Garbage Collector](http://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/)

## obj

first of all, we need to define a `enum` to represent `object type`.
as a considering of simplify, We only declared two kinds of objects:

1. `PRIMITIVE` represent the type of `int`, `short` and so on.
2. `REFERENCE` represent the type of `object` contains two pointer, we can use it to represent `loop reference`.

```c++
enum class ObjectType
{
	PRIMITIVE,
	REFERENCE
};
```

and now we know that we need all variable in `Object`:

- `ObjectType type` the object type
- `boolean marked` does the object is marked as a reachable object
- `Object *next` the next object referenced by `this` which means if `this` is reachable object, `next` is reachable also.
- `object value` represent the object value
- `printObject` print object

## vm

> in this tutorial, the `vm` contains a **Object array** which represent the `stack`, and we allocate objects on the stack and trigger `gc` when appropriate.

so we need variables and functions listed below:

- `first Object` The first object in the linked list of all objects on the heap. everytime we allocate a new object, `newObject->next` point to firstObject and then we modify the firstObject point to new Object. thus we can traverse all objects in the stack.
- `numOfObject` the current object count in stack
- `maxNumOfObject` when numOfObjects >= maxNumOfObject we trigger the GC, **pay attention, we need to add or sub maxNumOfObject when appopriate.** otherwise the GC will triggered by every newObject or not triggered until the stack is expand too big.
- `object array` represent the stack.
- `mayTriggerGC` trigger GC if it is a appropriate timing.
- `push` simulate allocate object
- `pop` simulate the function exit which means the object is unreachable and should be collect when GC running
- `mark` mark the object as a 
- `markAll` mark all reachable object when GC running
- `sweep` sweep object not marked
- `gc` stop the world and running GC
- `newObject` create a object
- `pushInt` create a object represent a PRIMITIVE and push it into stack
- `pushReference` create a pair represent a REFERENCE and push it into stack





































