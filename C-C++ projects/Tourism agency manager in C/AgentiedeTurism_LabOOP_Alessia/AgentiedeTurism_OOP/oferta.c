#pragma warning( disable : 6386 )
#include "oferta.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
Creeaza dinamic o lista cu o capacitate initiala de 1 si lungimea(nr elem) de 0*/
void creeaza_dinamic(List* l)
{
	l->elems = malloc(1 * sizeof(ElemType));
	l->cap = 1;
	l->lng = 0;
}

/* Distruge o singura oferta, dealocand charurile*/
void distruge_oferta(ElemType* offer)
{
	free(offer->destinatie);
	free(offer->tip);
}

/*Distruge o lista, dealocand fiecare element al ei in parte*/
void distruge(List* l)
{
	for (int i = 0; i < l->lng; i++) {
		distruge_oferta(&l->elems[i]);
	}
	free(l->elems);
	//free(l);
}

/*Redimensioneaza lista, creand una noua cu o capacitate dubla fata de cea anterioara si dealocand lista veche*/
void redim(List* l)
{
	int nCap = 2 * l->cap;
	ElemType* nElems = (ElemType*)malloc(nCap * sizeof(ElemType));

	if (nElems) {
		for (int i = 0; i < l->lng; i++) {
			
			nElems[i] = l->elems[i];
		}
		//dealocam memoria ocupata de vector
		free(l->elems);

		l->elems = nElems;
		l->cap = nCap;
	}
}