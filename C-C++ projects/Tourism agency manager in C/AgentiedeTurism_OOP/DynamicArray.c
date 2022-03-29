#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>
#include <crtdbg.h> 
#include <stdio.h>

DynamicArray CreateArray(CopyElementFct CopyFunction, DestroyElementFct DestroyFunction)
{
	DynamicArray array = (DynamicArray)malloc(sizeof(__DynamicArray));
	if (array != NULL)
	{
		array->Count = 0;
		array->Size = 1;
		array->Elements = (ElementType*)malloc(sizeof(ElementType) * array->Size);
		array->CopyFunction = CopyFunction;
		array->DestroyFunction = DestroyFunction;
	}
	return array;
}
DynamicArray CopyArray(DynamicArray Array)
{
	DynamicArray newArray = CreateArray(Array->CopyFunction, Array->DestroyFunction);
	for (int i = 0; i < Array->Count; i++)
		Insert(newArray, Array->Elements[i]);
	return newArray;
}
void DestroyArray(DynamicArray Array)
{
	for (int i = 0; i < Array->Count; i++)
		Array->DestroyFunction(Array->Elements[i]);
	free(Array->Elements);
	free(Array);
}

void Insert(DynamicArray Array, ElementType E)
{
	ElementType newElement = Array->CopyFunction(E);
	if (Array->Count >= Array->Size)
		__ResizeArray(Array);
	Array->Elements[Array->Count++] = newElement;
}
void Delete(DynamicArray Array, int Position)
{
	if (Array->Count <= Position)
		return;
	ElementType deletedElement = Array->Elements[Position];
	for (int i = Position; i < Array->Count; i++)
	{
		Array->Elements[i] = Array->Elements[i + 1];
	}
	Array->Count--;
	Array->DestroyFunction(deletedElement);
}

int GetLength(DynamicArray Array)
{
	return Array->Count;
}
const ElementType GetElement(DynamicArray Array, int Position)
{
	return Array->Elements[Position];
}

void Sort(DynamicArray Array, CompareElementFct CompareFunction)
{
	for (int i = 0; i < Array->Count; i++)
	{
		for (int j = i + 1; j < Array->Count; j++)
		{
			int retVal = CompareFunction(Array->Elements[i], Array->Elements[j]);
			if (retVal > 0)
			{
				ElementType aux = Array->Elements[i];
				Array->Elements[i] = Array->Elements[j];
				Array->Elements[j] = aux;
			}
		}
	}
}

void __ResizeArray(DynamicArray Array)
{
	Array->Size *= 2;
	Array->Elements = (ElementType*)realloc(Array->Elements, sizeof(ElementType) * Array->Size);
}






int __TestCompareFct(ElementType p1, ElementType p2)
{
	int a = *(int*)p1;
	int b = *(int*)p2;
	return a > b;
}
ElementType __TestCopyFct(ElementType p)
{
	int* newP = malloc(sizeof(int));
	if (newP != NULL)
	{
		*newP = *(int*)p;
	}

	return newP;
}
void __TestDestroyFct(ElementType p)
{
	free(p);
}

ElementType __TestCopyFct2(ElementType List)
{
	DynamicArray list = List;
	DynamicArray copyList = CopyArray(list);

	return copyList;
}
void __TestDestroyFct2(ElementType List)
{
	DynamicArray list = List;
	DestroyArray(list);
}





void __TestSort(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);

	int v[10];
	for (int i = 0; i < 10; i++)
	{
		v[i] = -i;
		Insert(dynamicArray, &v[i]);
	}
	Sort(dynamicArray, __TestCompareFct);
	for (int i = 0; i < 10; i++)
	{
		assert(v[9 - i] == *(int*)GetElement(dynamicArray, i));
	}

	DestroyArray(dynamicArray);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestCreateDestroyArray(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);

	assert(GetLength(dynamicArray) == 0);

	DestroyArray(dynamicArray);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestInsertArray(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);

	int v[10];
	for (int i = 0; i < 10; i++)
	{
		v[i] = i % 5;
		Insert(dynamicArray, &v[i]);
	}
	for (int i = 0; i < dynamicArray->Count; i++)
	{
		assert(v[i] == *(int*)GetElement(dynamicArray, i));
	}

	DestroyArray(dynamicArray);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestDeleteArray(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);
	int value = 2;

	Insert(dynamicArray, &value);
	Delete(dynamicArray, 0);
	assert(GetLength(dynamicArray) == 0);
	Delete(dynamicArray, 0);

	DestroyArray(dynamicArray);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestGetElement(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);
	int value = 2;

	Insert(dynamicArray, &value);
	int el = *(int*)GetElement(dynamicArray, 0);
	assert(el == value);

	DestroyArray(dynamicArray);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestCopyArray(void)
{
	DynamicArray dynamicArray = CreateArray(__TestCopyFct, __TestDestroyFct);
	int a = 2, b = 3, c = 2;

	Insert(dynamicArray, &a);
	Insert(dynamicArray, &b);
	Insert(dynamicArray, &c);

	DynamicArray dynamicArray2 = CopyArray(dynamicArray);

	assert(dynamicArray2->Count == 3);
	assert(*(int*)GetElement(dynamicArray2, 0) == 2);
	assert(*(int*)GetElement(dynamicArray2, 1) == 3);
	assert(*(int*)GetElement(dynamicArray2, 2) == 2);

	DestroyArray(dynamicArray);
	DestroyArray(dynamicArray2);

	assert(!_CrtDumpMemoryLeaks());
}
void __TestArrayOfArrays(void)
{
	DynamicArray list1 = CreateArray(__TestCopyFct, __TestDestroyFct);
	DynamicArray list2 = CreateArray(__TestCopyFct, __TestDestroyFct);
	DynamicArray listOfList = CreateArray(__TestCopyFct2, __TestDestroyFct2);

	int a = 2, b = 3;

	Insert(list1, &a);
	Insert(list2, &b);

	Insert(listOfList, list1);
	Insert(listOfList, list2);

	DynamicArray copyListOfList = CopyArray(listOfList);
	assert(GetLength(copyListOfList) == 2);
	assert(GetLength(GetElement(copyListOfList, 0)) == 1);
	assert(GetLength(GetElement(copyListOfList, 1)) == 1);


	DestroyArray(copyListOfList);
	DestroyArray(listOfList);
	DestroyArray(list1);
	DestroyArray(list2);
	assert(!_CrtDumpMemoryLeaks());
}

void __TestDynamicArray(void)
{
	__TestSort();
	__TestCreateDestroyArray();
	__TestInsertArray();
	__TestDeleteArray();
	__TestGetElement();
	__TestCopyArray();
	__TestArrayOfArrays();
}