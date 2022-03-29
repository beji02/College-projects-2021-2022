#pragma once

typedef void* ElementType;
typedef int(*FctComparare)(ElementType e1, ElementType e2);

typedef struct
{
	int Size;
	int Count;
	ElementType* Elements;
}__DynamicArray, *DynamicArray;
typedef struct
{
	DynamicArray Array;
	int Position;
}__Iterator, *Iterator;



DynamicArray CreateArray(void);

/// <summary>
/// Distruge un obiect de tipul dynamic array
/// </summary>
/// <param name="Array">arrayul care trebuie distrus</param>
void DestroyArray(DynamicArray Array);

/// <summary>
/// insereaza un nou obiect de tip elementType in array
/// </summary>
/// <param name="Array">arrayul in care se insereaza</param>
/// <param name="NewElement">elementul care se insereaza</param>
void Insert(DynamicArray Array, ElementType NewElement);

/// <summary>
/// sterge un element de pe positia Position din array
/// </summary>
/// <param name="Array">arrayul din care se sterge</param>
/// <param name="Position">positia de pe care sa se stearga</param>
/// <returns></returns>
int Delete(DynamicArray Array, int Position);

/// <summary>
/// ia numarul de elemente din array
/// </summary>
/// <param name="Array">arrayul a carui lungime se cauta</param>
/// <returns>lungimea arrayului</returns>
int GetLength(DynamicArray Array);

/// <summary>
/// ia elementul de pe pozitia Position
/// </summary>
/// <param name="Array">arrayul din care se ia elementul</param>
/// <param name="Position">pozitia de pe care se ia elementul</param>
/// <returns>elementul gasit pe acea pozitie</returns>
ElementType GetElement(DynamicArray Array, int Position);

/// <summary>
/// creeaza un iterator peste un array
/// </summary>
/// <param name="Array">arrayul peste care se va itera</param>
/// <returns>iteratorul</returns>
Iterator GetIterator(DynamicArray Array);

/// <summary>
/// ia elementul spre care arata iteratorul
/// </summary>
/// <param name="Iterator">iteratorul folosit</param>
/// <returns>elementul spre care arata iteratorul</returns>
ElementType Element(Iterator Iterator);

/// <summary>
/// arata daca iteratorul arata spre un element valid
/// </summary>
/// <param name="Iterator">iteratorul folosit</param>
/// <returns>1 daca iteratorul este valid, 0 altfel</returns>
int Valid(Iterator Iterator);

/// <summary>
/// trece iteratorul la urmatorul element
/// </summary>
/// <param name="Iterator">iteratorul folosit</param>
void Next(Iterator Iterator);

/// <summary>
/// distruge obiectul de tip iterator
/// </summary>
/// <param name="Iterator">iteratorul care trebuie distrus</param>
void DestroyIterator(Iterator Iterator);

/// <summary>
/// sorteaza vectorul de elemente cu ajutorul functii de comparare
/// </summary>
/// <param name="Array">vectorul care se va sorta</param>
/// <param name="compare">functia de sortare</param>
void Sort(DynamicArray Array, FctComparare compare);

void TestDynamicArray(void);