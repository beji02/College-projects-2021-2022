#include "domain.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h> 


int IsEqual(Participant p1, Participant p2)
{
	if (strcmp(p1->Nume, p2->Nume) == 0 &&
		strcmp(p1->Prenume, p2->Prenume) == 0)
		return 1;
	return 0;
}
Participant CreateParticipant(char* Nume, char* Prenume, int Scor)
{
	Participant p;
	p = (Participant)malloc(sizeof(__Participant));
	if (p == NULL)
		return p;
	
	p->Nume = (char*)malloc((strlen(Nume)+1) * sizeof(char));
	p->Prenume = (char*)malloc((strlen(Prenume) + 1) * sizeof(char));
	if (p->Nume == NULL)
		return p;
	if (p->Prenume == NULL)
		return p;
	strcpy(p->Nume, Nume);
	strcpy(p->Prenume, Prenume);
	p->Scor = Scor;

	return p;
}
void DestroyParticipant(Participant Part)
{
	free(Part->Nume);
	free(Part->Prenume);
	free(Part);
}


void __TestCreateDestroyParticipant(void)
{
	Participant p = CreateParticipant("Ana", "Maria", 10);
	Participant p1 = CreateParticipant("Bejan", "Andrei", 100);
	
	assert(strcmp(p->Nume, "Ana") == 0);
	assert(strcmp(p->Prenume, "Maria") == 0);
	assert(p->Scor == 10);

	assert(strcmp(p1->Nume, "Bejan") == 0);
	assert(strcmp(p1->Prenume, "Andrei") == 0);
	assert(p1->Scor == 100);

	DestroyParticipant(p);
	DestroyParticipant(p1);
}
void __TestEqualityParticipant(void)
{
	Participant p = CreateParticipant("Ana", "Maria", 10);
	Participant p1 = CreateParticipant("Bejan", "Andrei", 100);
	Participant p2 = CreateParticipant("Bejan", "Andrei", 10);

	assert(IsEqual(p, p1) == 0);
	assert(IsEqual(p, p2) == 0);
	assert(IsEqual(p1, p2) == 1);

	DestroyParticipant(p);
	DestroyParticipant(p1);
	DestroyParticipant(p2);
}

void TestDomain(void)
{
	__TestCreateDestroyParticipant();
	__TestEqualityParticipant();
	assert(!_CrtDumpMemoryLeaks());
}