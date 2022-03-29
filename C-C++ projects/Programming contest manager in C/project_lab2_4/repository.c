#include "repository.h"
#include <stdlib.h>
#include <assert.h>
#include "DynamicArray.h"
#include <crtdbg.h> 







DynamicArray createRepository(void)
{
	DynamicArray newRepository = CreateArray();
	return newRepository;
}
void destroyRepository(DynamicArray repository)
{
	for (int i = 0; i < repository->Count; i++)
		DestroyParticipant(repository->Elements[i]);
	DestroyArray(repository);
}

void insertParticipant(DynamicArray repository, Participant NewParticipant)
{
	Insert(repository, NewParticipant);
}
int searchParticipant(DynamicArray repository, Participant participant)
{
	Iterator iterator = GetIterator(repository);
	while (Valid(iterator))
	{
		Participant p = Element(iterator);
		if (IsEqual(p, participant))
		{
			DestroyIterator(iterator);
			return 1;
		}
			
		Next(iterator);
	}
	DestroyIterator(iterator);

	return 0;
}
void deleteParticipant(DynamicArray Repository, Participant participant)
{
	int i = 0;

	Iterator iterator = GetIterator(Repository);
	while (Valid(iterator))
	{
		Participant p = Element(iterator);
		if (IsEqual(p, participant))
			break;
		i++;
		Next(iterator);
	}
	DestroyIterator(iterator);

	if (i < GetLength(Repository))
	{
		Participant p = GetElement(Repository, i);
		DestroyParticipant(p);
		Delete(Repository, i);
	}
}






void __testCreateDestroyRepository(void)
{
	DynamicArray repo = createRepository();
	assert(GetLength(repo) == 0);
	destroyRepository(repo);
}
void __testInsertParticipant(void)
{
	DynamicArray repo = createRepository();
	Participant p = CreateParticipant("Bejan", "Andrei", 10);
	Participant p1 = CreateParticipant("Bejan", "Andrei", 10);
	Participant p2 = CreateParticipant("Bejan", "Andrei", 10);

	insertParticipant(repo, p);
	assert(GetLength(repo) == 1);
	
	insertParticipant(repo, p1);
	assert(GetLength(repo) == 2);
	
	insertParticipant(repo, p2);
	assert(GetLength(repo) == 3);

	destroyRepository(repo);
}
void __testSearchParticipant(void)
{
	DynamicArray repo = createRepository();
	Participant p = CreateParticipant("Bejan", "Andrei", 10);
	Participant p2 = CreateParticipant("Beji", "Andrei", 8);

	insertParticipant(repo, p);
	assert(searchParticipant(repo, p2) == 0);
	assert(searchParticipant(repo, p) == 1);

	DestroyParticipant(p2);
	destroyRepository(repo);
}
void __testDeleteParticipant(void)
{
	DynamicArray repo = createRepository();
	Participant p = CreateParticipant("Bejan", "Andrei", 10);
	Participant p2 = CreateParticipant("Beji", "Andrei", 8);

	insertParticipant(repo, p2);
	insertParticipant(repo, p);		
	assert(GetLength(repo) == 2);

	deleteParticipant(repo, p);
	assert(GetLength(repo) == 1);
	
	deleteParticipant(repo, p2);
	assert(GetLength(repo) == 0);

	destroyRepository(repo);
}





void TestRepository(void)
{
	__testCreateDestroyRepository();	
	__testInsertParticipant();	
	__testSearchParticipant();
	__testDeleteParticipant();	
	assert(!_CrtDumpMemoryLeaks());
}

