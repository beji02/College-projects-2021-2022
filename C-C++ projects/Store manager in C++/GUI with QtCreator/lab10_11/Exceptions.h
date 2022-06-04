#pragma once
#include "common.h"

using namespace std;

class MyException
{
protected:
	string Message;
public:
	MyException(const char* Message) : Message{ Message } {}

	string what() const
	{
		return Message;
	}
};

class InvalidInput : public MyException 
{
public:
	InvalidInput(const char* Message) : MyException(Message) {};
};
class NoProductWithId : public MyException
{
public:
	NoProductWithId(const char* Message) : MyException(Message) {};
};
class NoProductWithName : public MyException
{
public:
	NoProductWithName(const char* Message) : MyException(Message) {};
};
class InvalidSortType : public MyException 
{
public:
	InvalidSortType(const char* Message) : MyException(Message) {};
};
class EmptyList : public MyException
{
public:
	EmptyList(const char* Message) : MyException(Message) {};
};
class CorruptedFile : public MyException
{
public:
	CorruptedFile(const char* Message) : MyException(Message) {};
};
class NoProductWithPrice : public MyException
{
public:
	NoProductWithPrice(const char* Message) : MyException(Message) {};
};
class NoUndoOperation : public MyException
{
public:
	NoUndoOperation(const char* Message) : MyException(Message) {};
};
