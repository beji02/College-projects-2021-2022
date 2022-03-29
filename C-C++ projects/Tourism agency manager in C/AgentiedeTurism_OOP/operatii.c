#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "oferta.h"
#include "operatii.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysort.h"

void adauga(Service* service, ElemType offer)
{
	if (service->l.lng == service->l.cap)
		redim(&service->l);

	service->l.elems[service->l.lng] = offer;
	service->l.lng++;
}

void actualizare(Service* service, int poz, ElemType offer)
{
	distruge_oferta(&service->l.elems[poz]);
	service->l.elems[poz] = offer;
}

void sterge(Service* service, int poz)
{
	distruge_oferta(&(service->l.elems[poz]));

	for (int i = poz; i < service->l.lng - 1; i++)
		service->l.elems[i] = service->l.elems[i + 1];
	service->l.lng--;

	//distruge_oferta(&(service->l.elems[service->l.lng + 1]));
}

List* filtrare_pret(List l, int pret, List* filtered)
{
	filtered->lng = 0;
	for(int i=0; i<l.lng; i++)
		if (l.elems[i].pret <= pret)
		{
			if (filtered->lng == filtered->cap)
				redim(filtered);
			filtered->elems[filtered->lng] = l.elems[i];
			filtered->lng++;
			//printf("brooo: %d\n", filtered->elems[filtered->lng-1].pret);
		}
	return filtered;
}

List* filtrare_dest_tip(List l, char string[], int option, List* filtered)
{
	filtered->lng = 0;
	if (option == 1) {
		for (int i = 0; i < l.lng; i++)
			if (strcmp(l.elems[i].tip, string)==0)
			{
				if (filtered->lng == filtered->cap)
					redim(filtered);
				filtered->elems[filtered->lng] = l.elems[i];
				filtered->lng++;
			}
	}
	else {
		for (int i = 0; i < l.lng; i++)
			if (strcmp(l.elems[i].destinatie, string) == 0)
			{
				if (filtered->lng == filtered->cap)
					redim(filtered);
				filtered->elems[filtered->lng] = l.elems[i];
				filtered->lng++;
			}
	}

	return filtered;
}

//d) Vizualizare oferete ordonat dupa pret, destinatie(crescator / descrescator)
List sorting(List l, char option[50], bool reversed)
{	
	ElemType aux;
	List sorted;
	//creeaza_dinamic(&sorted);
	sorted = l;
	for(int i=0; i<l.lng-1; i++)
		for(int j=i+1; j<l.lng; j++)
			if (reversed == false)
			{
				if(strcmp(option, "pret") == 0)
					if (sorted.elems[i].pret >= sorted.elems[j].pret)
					{
						aux = sorted.elems[i];
						sorted.elems[i] = sorted.elems[j];
						sorted.elems[j] = aux;
					}
				if (strcmp(option, "destinatie") == 0)
					if (strcmp(sorted.elems[i].destinatie, sorted.elems[j].destinatie) > 0)
					{
						aux = sorted.elems[i];
						sorted.elems[i] = sorted.elems[j];
						sorted.elems[j] = aux;
					}
			}
			else {
				if (strcmp(option, "pret") == 0)
					if (sorted.elems[i].pret <= sorted.elems[j].pret)
					{
						aux = sorted.elems[i];
						sorted.elems[i] = sorted.elems[j];
						sorted.elems[j] = aux;
					}
				if (strcmp(option, "destinatie") == 0)
					if (strcmp(sorted.elems[i].destinatie, sorted.elems[j].destinatie) < 0)
					{
						aux = sorted.elems[i];
						sorted.elems[i] = sorted.elems[j];
						sorted.elems[j] = aux;
					}
			}
	
	return sorted;
	
}

void EmptyList(Service* service)
{
	service->l.lng = 0;
}


void InitList(Service* service)
{
	ElemType offer;
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(service, offer);
	
	offer = creeaza("city break", "Paris", 2750, 6, 6, 2022);
	adauga(service, offer);
	
	offer = creeaza("mare", "Antalya", 1900, 18, 8, 2022);
	adauga(service, offer);
	
	offer = creeaza("munte", "Elvetia", 2750, 27, 12, 2022);
	adauga(service, offer);
	
	offer = creeaza("city break", "Budapesta", 400, 22, 2, 2022);
	adauga(service, offer);
}

ElemType creeaza(char t[], char d[], int newpret, int newzi, int newluna, int newan)
{
	ElemType oferta;
	oferta.destinatie = malloc((strlen(d) + 1) * sizeof(char));
	oferta.tip = malloc((strlen(t) + 1) * sizeof(char));

	if (oferta.destinatie && oferta.tip) {
		strcpy_s(oferta.tip, strlen(t) + 1, t);
		strcpy_s(oferta.destinatie, strlen(d) + 1, d);
		oferta.pret = newpret;
		oferta.datap.zi = newzi;
		oferta.datap.luna = newluna;
		oferta.datap.an = newan;
	}
	return oferta;
}

ElemType get_offer(Service* service, int poz)
{
	ElemType offer;
	offer = service->l.elems[poz];
	return offer;
}

int size(Service* service)
{
	return service->l.lng;
}

int cmpPret(ElemType* e1, ElemType* e2)
{
	if (e1->pret >= e2->pret)
		return 1;
	return 0;
}

int cmpDestinatie(ElemType* e1, ElemType* e2)
{
	return (strcmp(e1->destinatie, e2->destinatie));
}

List sortbypret(List l)
{
	List sorted;
	sorted = l;
	sort_fnct(&sorted, cmpPret);
	return sorted;	
}

List sortbydest(List l)
{
	List sorted;
	sorted = l;
	sort_fnct(&sorted, cmpDestinatie);
	return sorted;
}

void testGetOffer()
{
	Service service;
	Service* p = &service;
	creeaza_dinamic(&(p->l));
	ElemType offer;
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(p, offer);

	offer = creeaza("munte", "Elvetia", 700, 15, 12, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 2750, 6, 6, 2022);
	adauga(p, offer);

	ElemType found_offer;
	found_offer = get_offer(p, 1);
	assert(found_offer.pret == 700);

	distruge(&p->l);
}

void testCreeaza()
{
	ElemType offer;
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	assert(strcmp(offer.tip, "mare") == 0);
	assert(strcmp(offer.destinatie, "Roma") == 0);
	assert(offer.pret == 1200);
	assert(offer.datap.zi == 21);
	assert(offer.datap.luna == 2);
	assert(offer.datap.an == 2022);
	distruge_oferta(&offer);

}

void testAdauga()
{
	Service service;
	Service* p=&service;
	creeaza_dinamic(&(p->l));
	ElemType offer;
	assert(service.l.lng == 0);
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(p, offer);
	assert(service.l.lng == 1);
	assert(size(p) == 1);
	assert(service.l.elems[0].pret == 1200);
	distruge(&p->l);
}

void testSterge()
{
	Service service;
	Service* p = &service;
	ElemType offer;
	creeaza_dinamic(&(p->l));
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(p, offer);
	
	offer = creeaza("munte", "Elvetia", 700, 15, 12, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 2750, 6, 6, 2022);
	adauga(p, offer);

	assert(p->l.lng == 3);
	sterge(p, 1);
	assert(p->l.lng == 2);
	sterge(p, 0);
	assert(p->l.lng == 1);
	assert(strcmp(p->l.elems[0].tip, "city break") == 0);

	distruge(&p->l);
}


void testActualizare()
{
	Service service;
	Service* p = &service;
	ElemType offer;
	creeaza_dinamic(&(p->l));
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 2750, 6, 6, 2022);
	adauga(p, offer);

	offer = creeaza("munte", "Elvetia", 700, 15, 12, 2022);

	assert(p->l.elems[1].pret == 2750);
	assert(strcmp(p->l.elems[1].destinatie, "Paris")==0);

	actualizare(p, 1, offer);
	
	assert(p->l.elems[1].pret == 700);
	assert(strcmp(p->l.elems[1].destinatie, "Elvetia")==0);

	distruge(&p->l);

}

void testFiltrare()
{
	Service service;
	Service* p = &service;
	ElemType offer;
	creeaza_dinamic(&(p->l));
	offer = creeaza("mare", "Roma", 1200, 21, 2, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 2750, 6, 6, 2022);
	adauga(p, offer);

	offer = creeaza("mare", "Antalya", 1900, 18, 8, 2022);
	adauga(p, offer);

	offer = creeaza("munte", "Elvetia", 2750, 27, 12, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Budapesta", 2750, 22, 2, 2022);
	adauga(p, offer);

	offer = creeaza("city break", "Paris", 3000, 17, 9, 2022);
	adauga(p, offer);

	List filtered;
	creeaza_dinamic(&filtered);
	List* f;
	f = filtrare_pret(p->l, 2000, &filtered);
	assert(filtered.lng == 2);
	assert(strcmp(filtered.elems[1].destinatie, "Antalya") == 0);
	free(f->elems);

	List filtered2;
	creeaza_dinamic(&filtered2);
	List* f2;
	f2 = filtrare_dest_tip(p->l, "city break", 1, &filtered2);
	assert(filtered2.lng == 3);
	assert(strcmp(filtered2.elems[1].destinatie, "Budapesta") == 0);
	assert(strcmp(filtered2.elems[0].tip, "city break") == 0);
	free(f2->elems);

	List filtered3;
	creeaza_dinamic(&filtered3);
	List* f3;
	f3 = filtrare_dest_tip(service.l, "Paris", 2, &filtered3);
	assert(filtered3.lng == 2);
	assert(filtered3.elems[1].datap.zi == 17);
	free(f3->elems);

	distruge(&p->l);
}


void testInitList()
{
	Service service;
	Service* p = &service;
	creeaza_dinamic(&(p->l));
	InitList(p);
	
	assert(p->l.lng == 5);
	distruge(&p->l);
}

void testSortare()
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
	sorted = sorting(p->l, "pret", false);
	assert(sorted.elems[0].pret == 300);

	sorted = sorting(p->l, "pret", true);
	assert(sorted.elems[0].pret == 5780);

	sorted = sorting(p->l, "destinatie", false);
	assert(strcmp(sorted.elems[0].destinatie, "Antalya") == 0);

	sorted = sorting(p->l, "destinatie", true);
	assert(strcmp(sorted.elems[0].destinatie, "Paris") == 0);

	//List* listt = &sorted;
	
	distruge(&p->l);
}
