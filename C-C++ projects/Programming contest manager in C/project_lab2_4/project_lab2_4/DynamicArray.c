#include "DynamicArray.h"
#include <assert.h>
#include <stdlib.h> 
#include <crtdbg.h> 

void __ResizeArray(DynamicArray Array)
{
	Array->Size *= 2;
	ElementType aux;
	ElementType* newPointer = (ElementType*)malloc(sizeof(ElementType) * Array->Size);
	if (newPointer == NULL)
		return;

	for (int i = 0; i < Array->Count; i++)
	{
		aux = (ElementType)Array->Elements[i];
		newPointer[i] = aux;
	}

	free(Array->Elements);
	Array->Elements = newPointer;
}
DynamicArray CreateArray(void)
{
	DynamicArray array;
	array = (DynamicArray)malloc(sizeof(__DynamicArray));
	if (array == NULL)
		return array;
	array->Size = 1;
	array->Count = 0;

	array->Elements = (ElementType*)malloc(sizeof(ElementType) * array->Size);
	return array;
}
void DestroyArray(DynamicArray Array)
{
	free(Array->Elements);
	free(Array);
}

void Insert(DynamicArray Array, ElementType NewElement)
{
	if (Array->Count == Array->Size)
		__ResizeArray(Array);

	Array->Elements[Array->Count++] = NewElement;
}
int Delete(DynamicArray Array, int Position)
{
	if (Position >= Array->Count)
		return -1;

	Array->Count--;
	Array->Elements[Position] = Array->Elements[Array->Count];
	return 0;
}

ElementType GetElement(DynamicArray Array, int Position)
{
	return Array->Elements[Position];
}

int GetLength(DynamicArray Array)
{
	return Array->Count;
}
int GetSize(DynamicArray Array)
{
	return Array->Size;
}

Iterator GetIterator(DynamicArray Array)
{
	Iterator iterator = (Iterator)malloc(sizeof(__Iterator));
	if (iterator == NULL)
		return iterator;
	iterator->Position = 0;
	iterator->Array = Array;

	return iterator;
}
ElementType Element(Iterator Iterator)
{
	return Iterator->Array->Elements[Iterator->Position];
}
int Valid(Iterator Iterator)
{
	if (Iterator->Position >= Iterator->Array->Count)
		return 0;
	return 1;
}
void Next(Iterator Iterator)
{
	Iterator->Position++;
}
void DestroyIterator(Iterator Iterator)
{
	free(Iterator);
}

void Sort(DynamicArray Array, FctComparare compare)
{
	for (int i = 0; i < Array->Count; i++)
	{
		for (int j = i + 1; j < Array->Count; j++)
		{
			int retVal = compare(Array->Elements[i], Array->Elements[j]);
			if (retVal > 0)
			{
				ElementType aux = Array->Elements[i];
				Array->Elements[i] = Array->Elements[j];
				Array->Elements[j] = aux;
			}
		}
	}
}
int __MyCompare(ElementType p1, ElementType p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;
	int vala = *a;
	int valb = *b;
	return vala > valb;
}
void __TestSort(void)
{
	DynamicArray dynamicArray = CreateArray();
	int i, value[10] = { 0 };
	for (i = 0; i < 10; i++)
	{
		value[i] = i;
		Insert(dynamicArray, &value[i]);
	}
	Sort(dynamicArray, __MyCompare);
	Iterator iterator = GetIterator(dynamicArray);
	i = 0;
	while (Valid(iterator))
	{
		assert(value[i] == *(int*)Element(iterator));
		i++;
		Next(iterator);
	}
	DestroyIterator(iterator);
	DestroyArray(dynamicArray);
}

void __TestCreateDestroyArray(void)
{
	DynamicArray dynamicArray = CreateArray();
	
	assert(GetLength(dynamicArray) == 0);
	assert(GetSize(dynamicArray) == 1);
	
	DestroyArray(dynamicArray);
}
void __TestInsertArray(void)
{
	DynamicArray dynamicArray = CreateArray();
	int* value = malloc(sizeof(int));
	if (value == NULL)
		return;
	*value = 2;
	ElementType el = value;

	Insert(dynamicArray, el);
	assert(GetLength(dynamicArray) == 1);	
	assert(GetSize(dynamicArray) == 1);

	Insert(dynamicArray, el);
	assert(GetLength(dynamicArray) == 2);
	assert(GetSize(dynamicArray) == 2);

	Insert(dynamicArray, el);
	assert(GetLength(dynamicArray) == 3);
	assert(GetSize(dynamicArray) == 4);

	free(value);
	DestroyArray(dynamicArray);
}
void __TestDeleteArray(void)
{
	DynamicArray dynamicArray = CreateArray();
	int value = 2;

	Insert(dynamicArray, &value);
	assert(Delete(dynamicArray, 0) == 0);
	assert(GetLength(dynamicArray) == 0);
	assert(Delete(dynamicArray, 0) == -1);

	DestroyArray(dynamicArray);
}
void __TestIteratorArray(void)
{
	DynamicArray dynamicArray = CreateArray();
	int i, value[10]={0};
	for (i = 0; i < 10; i++)
	{
		value[i] = i * 5;
		Insert(dynamicArray, &value[i]);
	}

	Iterator iterator = GetIterator(dynamicArray);
	i = 0;
	while (Valid(iterator))
	{
		assert(value[i] == *(int*)Element(iterator));
		i++;
		Next(iterator);
	}
	DestroyIterator(iterator);
	DestroyArray(dynamicArray);
}
void __TestGetElement(void)
{
	DynamicArray dynamicArray = CreateArray();
	int value = 2;

	Insert(dynamicArray, &value);
	int el = *(int*)GetElement(dynamicArray, 0);
	assert(el == value);

	DestroyArray(dynamicArray);
}

void TestDynamicArray(void)
{
	__TestSort();
	__TestCreateDestroyArray();
	__TestInsertArray();
	__TestDeleteArray();
	__TestIteratorArray();
	__TestGetElement();
	assert(!_CrtDumpMemoryLeaks());
}