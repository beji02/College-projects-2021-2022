#pragma once
#include "Repository.h"
#include "Offer.h"

typedef struct
{
	Repository Repo;
	int kID;
}Service;

/*adauga un nou element*/
int Adauga(Service Sv, int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price);
/*actualizeaza un element din lista de oferte*/
int Actualizare(Service Sv, int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price);
/*sterge o oferta*/
int Stergere(Service Sv, int Id);

/*realizeaza operatia de undo*/
int Undo(Service Sv);

/*sorteaza elementele din lista*/
DynamicArray Sortare(Service Sv, int Option, int Option2);
/*returneaza o lista filtrata dupa pret*/
DynamicArray FilterPrice(Service Sv, int Price);
/*returneaza o lista filtrata dupa tip*/
DynamicArray FilterType(Service Sv, char* Type);
/*returneaza o lista filtrata dupa dest*/
DynamicArray FilterDestination(Service Sv, char* Destination);
/*returneaza o lista filtrata dupa an*/
DynamicArray FilterYear(Service Sv, int Year);
/*returneaza 1 daca exista cel putin 2 oferte cu proprietatea ceruta altfel 0*/
int Exista(Service Sv, char* Dest, int Price);
