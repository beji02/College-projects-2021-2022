#pragma once
#include <malloc.h>
#include <stdlib.h>

typedef struct
{
	int zi, luna, an;
}dataplecare;

typedef struct
{
	char* tip;
	char* destinatie;
	dataplecare datap;
	int pret;
}Oferta;

typedef Oferta ElemType;

typedef struct
{
	ElemType* elems;
	int lng;
	int cap;
}List;


/*
Valideaza o oferta inainte de a fi adaugata
Verifica daca tipul si destinatia sunt vide sau daca data calendaristica este gresita.
1<=zi<=31
1<=luna<=12
2020<=an
*/
int validate(ElemType offer);

/*Constructor, destructor, redimensionare*/
void creeaza_dinamic(List* l);

void distruge(List* l);

void distruge_oferta(ElemType* offer);

void redim(List* l);

/* Teste pt validator */
void testValidate();