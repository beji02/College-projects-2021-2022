#include "service.h"
#include "domain.h"
#include "repository.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h> 



Service createService(DynamicArray repo)
{
	Service sv = { repo };
	return sv;
}

int serviceAdd(Service sv, char Nume[100], char Prenume[100], int Scor)
{
	Participant p = CreateParticipant(Nume, Prenume, Scor);
	int ret = searchParticipant(sv.repo, p);
	if (ret == 1)
	{
		DestroyParticipant(p);
		return 0;
	}
		

	insertParticipant(sv.repo, p);
	return 1;
}
void serviceAddSome(Service sv)
{
	serviceAdd(sv, "Bejan", "Andrei", 100);
	serviceAdd(sv, "Andrei", "Maria", 99);
	serviceAdd(sv, "Bugnar", "Catalin", 97);
	serviceAdd(sv, "Bugnar", "Andreea", 96);
}
int serviceEdit(Service sv, char Nume[100], char Prenume[100], int Scor)
{
	Participant p = CreateParticipant(Nume, Prenume, Scor);
	int ret = searchParticipant(sv.repo, p);
	if (ret == 0)
	{
		DestroyParticipant(p);
		return 0;
	}
		

	deleteParticipant(sv.repo, p);
	insertParticipant(sv.repo, p);
	return 1;
}
int serviceDelete(Service sv, char Nume[100], char Prenume[100])
{
	Participant p = CreateParticipant(Nume, Prenume, 0);
	int ret = searchParticipant(sv.repo, p);
	if (ret == 0)
	{
		DestroyParticipant(p);
		return 0;
	}
		

	deleteParticipant(sv.repo, p);
	DestroyParticipant(p);
	return 1;
}

int serviceFilter(Service sv, char Filtru[100], DynamicArray retArray)
{
	if (strchr(Filtru, '*') != NULL)
	{
		char c = Filtru[0];

		Iterator iterator = GetIterator(sv.repo);
		while (Valid(iterator))
		{
			Participant p = Element(iterator);
			if (strchr(p->Nume, c) - p->Nume == 0)
				Insert(retArray, p);
			Next(iterator);
		}
		DestroyIterator(iterator);
		return 1;
	}
	else
		if (strchr(Filtru, '<') != NULL)
		{
			int value = atoi(Filtru + 1);

			Iterator iterator = GetIterator(sv.repo);
			while (Valid(iterator))
			{
				Participant p = Element(iterator);
				if (p->Scor < value)
					Insert(retArray, p);
				Next(iterator);
			}
			DestroyIterator(iterator);
			return 1;
		}
	return 0;
}

// functii de comparare posibile care returneaza > 0 daca ordinea participantiilor nu e corecta
// p1-primul participant care se compara
// p2-al doilea participant care se compara
int compare1(Participant p1, Participant p2)
{
	return strcmp(p1->Nume, p2->Nume);
}
int compare2(Participant p1, Participant p2)
{
	return strcmp(p2->Nume, p1->Nume);
}
int compare3(Participant p1, Participant p2)
{
	return p1->Scor - p2->Scor;
}
int compare4(Participant p1, Participant p2)
{
	return p2->Scor - p1->Scor;
}

// functie care returneaza functia potrivita de comparare in functie de tiparul introdus
// SortType-tiparul de sortare preluat de la utilizator
FctComparare getCompareFunc(char SortType[100])
{
	if (strstr(SortType, "nume") != NULL)
	{
		if (strchr(SortType, '<') != NULL)
			return compare1;
		return compare2;
	}
	else
	{
		if (strchr(SortType, '<') != NULL)
			return compare3;
		return compare4;
	}
}
int serviceSort(Service sv, char SortType[100], DynamicArray retArray)
{
	if (strstr(SortType, "nume") == NULL && strstr(SortType, "scor") == NULL ||
		strchr(SortType, '<') == NULL && strchr(SortType, '>') == NULL)
		return 0;

	int len = GetLength(sv.repo);
	/*
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (compareFunc(SortType, sv.repo->Elements[i], sv.repo->Elements[j]) > 0)
			{
				Participant aux;
				aux = sv.repo->Elements[i];
				sv.repo->Elements[i] = sv.repo->Elements[j];
				sv.repo->Elements[j] = aux;
			}
		}
		Insert(retArray, sv.repo->Elements[i]);
	}*/
	FctComparare f = getCompareFunc(SortType);
	Sort(sv.repo, f);
	for(int i=0; i<len; i++)
		Insert(retArray, sv.repo->Elements[i]);

	return 1;
}

void __testServiceAddSome(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	serviceAddSome(sv);
	assert(repo->Count == 4);

	destroyRepository(repo);
}
void __testServiceAdd(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	assert(serviceAdd(sv, "Ana", "Maria", 11) == 1);
	assert(serviceAdd(sv, "Ana", "Maria", 11) == 0);

	destroyRepository(repo);
}
void __testServiceEdit(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	serviceAdd(sv, "Ana", "Maria", 11);
	serviceAdd(sv, "Andrei", "Maria", 11);

	assert(serviceEdit(sv, "Ana", "Maria", 11) == 1);
	assert(serviceEdit(sv, "Ane", "Maria", 11) == 0);
	assert(serviceEdit(sv, "Andrei", "Maria", 11) == 1);

	destroyRepository(repo);
}
void __testServiceDelete(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	serviceAdd(sv, "Ana", "Maria", 11);
	serviceAdd(sv, "Andrei", "Maria", 11);

	assert(serviceDelete(sv, "Ana", "Maria") == 1);
	assert(serviceDelete(sv, "Ana", "Maria") == 0);
	assert(serviceDelete(sv, "Andrei", "Maria") == 1);
	assert(serviceDelete(sv, "Andrei", "Maria") == 0);

	destroyRepository(repo);
}
void __testServiceFilter(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	serviceAdd(sv, "Ana", "Maria", 9);
	serviceAdd(sv, "Andrei", "Maria", 11);
	serviceAdd(sv, "BAndrei", "Maria", 12);

	DynamicArray retArray = CreateArray();
	assert(serviceFilter(sv, "A*", retArray) == 1);
	assert(retArray->Count == 2);
	assert(((Participant)retArray->Elements[0])->Scor == 9);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "B*", retArray) == 1);
	assert(retArray->Count == 1);
	assert(((Participant)retArray->Elements[0])->Scor == 12);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "C*", retArray) == 1);
	assert(retArray->Count == 0);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "<100", retArray) == 1);
	assert(retArray->Count == 3);
	assert(((Participant)retArray->Elements[0])->Scor == 9);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "<8", retArray) == 1);
	assert(retArray->Count == 0);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "<9", retArray) == 1);
	assert(retArray->Count == 0);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "<10", retArray) == 1);
	assert(retArray->Count == 1);
	DestroyArray(retArray);
	
	retArray = CreateArray();
	assert(serviceFilter(sv, "pisici", retArray) == 0);
	DestroyArray(retArray);
	
	destroyRepository(repo);
}
void __testServiceSort(void)
{
	DynamicArray repo = createRepository();
	Service sv = createService(repo);

	serviceAdd(sv, "Andrei", "Maria", 12);
	serviceAdd(sv, "Ana", "Maria", 9);
	serviceAdd(sv, "BAndrei", "Maria", 11);

	DynamicArray retArray = CreateArray();

	assert(serviceSort(sv, "nume <", retArray)==1);
	assert(retArray->Count == 3);
	assert(((Participant)retArray->Elements[0])->Nume[0] == 'A');
	assert(((Participant)retArray->Elements[2])->Nume[0] == 'B');
	DestroyArray(retArray);

	retArray = CreateArray();
	assert(serviceSort(sv, "nume >", retArray) == 1);
	assert(((Participant)retArray->Elements[0])->Nume[0] == 'B');
	assert(((Participant)retArray->Elements[2])->Nume[0] == 'A');
	DestroyArray(retArray);

	retArray = CreateArray();
	assert(serviceSort(sv, "scor <", retArray) == 1);
	assert(((Participant)retArray->Elements[0])->Nume[0] == 'A');
	assert(((Participant)retArray->Elements[0])->Nume[0] == 'A');
	DestroyArray(retArray);

	retArray = CreateArray();
	assert(serviceSort(sv, "scor >", retArray) == 1);
	assert(((Participant)retArray->Elements[0])->Nume[0] == 'A');
	assert(((Participant)retArray->Elements[1])->Nume[0] == 'B');
	assert(((Participant)retArray->Elements[2])->Nume[0] == 'A');
	DestroyArray(retArray);

	retArray = CreateArray();
	assert(serviceSort(sv, "pisici <", retArray) == 0);
	assert(serviceSort(sv, "nume =", retArray) == 0);
	DestroyArray(retArray);

	destroyRepository(repo);
	
}

void TestService(void)
{
	__testServiceAddSome();
	__testServiceAdd();
	__testServiceEdit();
	__testServiceDelete();
	__testServiceFilter();
	__testServiceSort();
	assert(!_CrtDumpMemoryLeaks());
}