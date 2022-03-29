#pragma once
#include "DynamicArray.h"
#include "Offer.h"

typedef struct
{
	DynamicArray List;
	DynamicArray UndoList;
}__Repository, * Repository;


/*creeaza un repository*/
Repository CreateRepository();
/*distruge un repository*/
void DestroyRepository(Repository Repo);
/*insereaza un nou element in repository*/
void InsertRepository(Repository Repo, Offer Off);
/*cauta o oferta in repository*/
int SearchRepository(Repository Repo, Offer Off);
/*sterge un element din repository*/
void DeleteRepository(Repository Repo, Offer Off);
/*actualizeaza un repository*/
void UpdateRepository(Repository Repo, Offer Off);
/*realizeaza operatia de undo din repo*/
int UndoRepository(Repository Repo);
/*adauga cateva oferte in repo*/
void AddSome(Repository Repo);

/*ia toate ofertele din lista curenta*/
DynamicArray GetAllRepository(Repository Repo);

void __TestRepository();
