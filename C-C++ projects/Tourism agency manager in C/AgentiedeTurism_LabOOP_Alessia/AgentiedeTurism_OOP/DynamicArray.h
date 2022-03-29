#pragma once
typedef void* ElementType;


typedef int(*CompareElementFct)(ElementType E1, ElementType E2);
typedef ElementType(*CopyElementFct)(ElementType E);
typedef void(*DestroyElementFct)(ElementType E);

typedef struct
{
	int Size;
	int Count;
	ElementType* Elements;
	CopyElementFct CopyFunction;
	DestroyElementFct DestroyFunction;

}__DynamicArray;
typedef __DynamicArray* DynamicArray;








/// <summary>
/// Creeaza un nou array
/// </summary>
/// <param name="CopyFunction">-Functia prin care se poate copia un element al arrayului</param>
/// <param name="DestroyFunction">-Functia prin care se poate distruge un element al arrayului</param>
/// <returns>Noul array creat</returns>
DynamicArray CreateArray(CopyElementFct CopyFunction, DestroyElementFct DestroyFunction);
/// <summary>
/// Copiaza complet un array
/// </summary>
/// <param name="Array">-Arrayul care trebuie copiat</param>
/// <returns>Copia arrayului</returns>
DynamicArray CopyArray(DynamicArray Array);
/// <summary>
/// Distruge un array si elibereaza memoria
/// </summary>
/// <param name="Array">-Arrayul care trebuie distrus</param>
void DestroyArray(DynamicArray Array);
/// <summary>
/// Insereaza un nou element in array
/// </summary>
/// <param name="Array">-Arrayul in care se va insera copia elementului</param>
/// <param name="E">-Elementul care se doreste inserat</param>
void Insert(DynamicArray Array, ElementType E);
/// <summary>
/// Sterge un element de pe pozitie in array
/// </summary>
/// <param name="Array">-Arrayul din care se doreste stergerea</param>
/// <param name="Position">-Pozitia din array de pe care se sterge elementul</param>
void Delete(DynamicArray Array, int Position);
/// <summary>
/// Numarul de elemente din array
/// </summary>
/// <param name="Array">-Arrayul a carui lungime se afla</param>
/// <returns>-Lungimea arrayului</returns>
int GetLength(DynamicArray Array);
/// <summary>
/// Returneaza un element din array 
/// </summary>
/// <param name="Array">-Arrayul din care se ia elementul</param>
/// <param name="Position">-Pozitia din array de pe care se ia elementul</param>
/// <returns>Elementul returnat</returns>
const ElementType GetElement(DynamicArray Array, int Position);
/// <summary>
/// Sorteaza arrayul folosind functia de comparare
/// </summary>
/// <param name="Array">-Arrayul care trebuie sortat</param>
/// <param name="CompareFunction">-Functia de comparare a elementelor</param>
void Sort(DynamicArray Array, CompareElementFct CompareFunction);








void __ResizeArray(DynamicArray Array);
void __TestDynamicArray();
