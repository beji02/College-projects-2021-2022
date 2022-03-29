#include "oferta.h"
#include "operatii.h"
#include "mysort.h"
#include <assert.h>
#include <string.h>

void sort_fnct(List* l, FctComparare cmp)
{
	ElemType aux;
	for(int i=0; i< l->lng-1; i++)
		for (int j = i + 1; j < l->lng; j++)
			if (cmp(&l->elems[i], &l->elems[j]) > 0)
			{
				aux = l->elems[i];
				l->elems[i] = l->elems[j];
				l->elems[j] = aux;
			}
}

void testSortare2()
{
	Service service;
	Service* p = &service;
	creeaza_dinamic(&(p->l));
	ElemType offer;
	EmptyList(p);

	offer = creeaza("mare", "Antalya", 1200, 21, 2, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 5780, 6, 6, 2022);
	adauga(p, offer);

	offer = creeaza("munte", "Elvetia", 300, 15, 12, 2022);
	adauga(p, offer);

	assert(p->l.lng == 3);

	List sorted;
	sorted = p->l;
	sorted = sortbypret(p->l);
	assert(sorted.elems[0].pret == 300);

	sorted = sortbydest(p->l);
	assert(strcmp(sorted.elems[0].destinatie, "Antalya") == 0);

	distruge(&p->l);
}