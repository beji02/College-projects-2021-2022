#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "operatii.h"
#include "oferta.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Citeste de la tastatura date si le adauga in lista */
void adauga_ui(Service* service)
{
	char t[20], d[50];
	int pret, zi, luna, an;
	ElemType oferta;

	//gets_s(fake, sizeof(fake));

	printf("\nDati tipul ofertei: ");
	gets_s(t, sizeof(t));

	printf("Dati destinatia: ");
	gets_s(d, sizeof(d));

	printf("Dati pretul ofertei: ");
	scanf_s("%d", &pret);

	printf("Dati ziua de plecare: ");
	scanf_s("%d", &zi);

	printf("Dati luna de plecare: ");
	scanf_s("%d", &luna);

	printf("Dati anul de plecare: ");
	scanf_s("%d", &an);

	int valid;
	oferta = creeaza(t, d, pret, zi, luna, an);

	valid = validate(oferta);

	if (valid == 1)
	{
		adauga(service, oferta);
		printf("\nOferta a fost adaugata cu succes.\n");
	}
	else printf("\nOferta invalida nu a putut fi adaugata.\n");

}

/* Afiseaza lista din service */
void afiseaza(Service* service)
{
	if (size(service) == 0)
		printf("Lista este goala");
	else {
		printf("Lista este: \n");
		for (int i = 0; i < size(service); i++) {
			ElemType oferta = get_offer(service, i); //
			/*
			printf("%d) Tip: %s; Destinatie: %s; Pret: %d; ", i, service->lista[i].tip, service->lista[i].destinatie, service->lista[i].pret);
			printf("Data: %d.%d.%d \n", service->lista[i].datap.zi, service->lista[i].datap.luna, service->lista[i].datap.an); */
			printf("%d) Tip: %s; Destinatie: %s; Pret: %d; ", i, oferta.tip, oferta.destinatie, oferta.pret);
			printf("Data: %d.%d.%d \n", oferta.datap.zi, oferta.datap.luna, oferta.datap.an);
		}
	}
}

/* Afiseaza o lista oarecare (de ex filtered) */
void afiseaza_lista(List l)
{
	if (l.lng == 0)
		printf("Lista este goala");
	else {
		printf("Lista este: \n");
		for (int i = 0; i < l.lng; i++) {
			printf("%d) Tip: %s; Destinatie: %s; Pret: %d; ", i, l.elems[i].tip, l.elems[i].destinatie, l.elems[i].pret);
			printf("Data: %d.%d.%d \n", l.elems[i].datap.zi, l.elems[i].datap.luna, l.elems[i].datap.an);
		}
	}
}

void afiseaza_lista2(List* l)
{
	if (l->lng == 0)
		printf("Lista este goala");
	else {
		printf("Lista este: \n");
		for (int i = 0; i < l->lng; i++) {
			printf("%d) Tip: %s; Destinatie: %s; Pret: %d; ", i, l->elems[i].tip, l->elems[i].destinatie, l->elems[i].pret);
			printf("Data: %d.%d.%d \n", l->elems[i].datap.zi, l->elems[i].datap.luna, l->elems[i].datap.an);
		}
	}
}

/* Sterge din lista o oferta cu pozitia data */
void sterge_ui(Service* service)
{
	int id;
	printf("Dati id-ul ofertei de sters: ");
	scanf_s("%d", &id);
	if (id > service->l.lng)
		printf("Nu exista acest id in lista de oferte.\n");
	else {
			sterge(service, id);
			printf("Oferta a fost stearsa cu succes.\n");
	     }
}

/* Actualizeaza o oferta data prin pozitie cu o alta oferta data de la tastatura */
void actualizare_ui(Service* service)
{
	char t[20], d[50], fake[5];
	int pret, zi, luna, an, id;
	ElemType oferta;

	printf("Dati id-ul de actualizat: ");
	scanf_s("%d", &id);

	if (id > service->l.lng)
		printf("Nu exista acest id in lista de oferte.\n");
	else {
		gets_s(fake, sizeof(fake));

		printf("\nDati tipul nou de oferta: ");
		gets_s(t, sizeof(t));

		printf("Dati destinatia noua: ");
		gets_s(d, sizeof(d));

		printf("Dati pretul nou: ");
		scanf_s("%d", &pret);

		printf("Dati ziua de plecare: ");
		scanf_s("%d", &zi);

		printf("Dati luna de plecare: ");
		scanf_s("%d", &luna);

		printf("Dati anul de plecare: ");
		scanf_s("%d", &an);

		oferta = creeaza(t, d, pret, zi, luna, an);
		actualizare(service, id, oferta);
		printf("Oferta a fost actualizata cu succes.\n");
	}

}

/* Filtreaza o lista dupa un criteriu dat */
void filtrare_ui(Service* service)
{
	char option[50];
	List filtered;
	creeaza_dinamic(&filtered);
	printf("\nAlegeti criteriul de filtrare: ");
	gets_s(option, sizeof(option));

	if (strcmp(option, "pret") == 0)
	{
		int pret;
		printf("Dati pretul: ");
		scanf_s("%d", &pret);
		List* f;
		f = filtrare_pret(service->l, pret, &filtered);
		afiseaza_lista2(f);
		//afiseaza_lista(filtrare_pret(service->l, pret));
	    //distruge(f);
		free(f->elems);
	}
	
	if (strcmp(option, "tip") == 0)
	{
		char tip[50];
		printf("Dati tipul: ");
		gets_s(tip, sizeof(tip));
		List* f;
		f = filtrare_dest_tip(service->l, tip, 1, &filtered);
		afiseaza_lista2(f);
		free(f->elems);
		//filtered = filtrare_dest_tip(service->l, tip, 1);
		//afiseaza_lista(filtered);
		//afiseaza_lista(filtrare_dest_tip(service->l, tip, 1));
		//distruge(&filtered);
	}
	
	if (strcmp(option, "destinatie") == 0)
	{
		char dest[50];
		printf("Dati destinatia: ");
		gets_s(dest, sizeof(dest));
		List* f;
		f = filtrare_dest_tip(service->l, dest, 2, &filtered);
		afiseaza_lista2(f);
		free(f->elems);
		//filtered = filtrare_dest_tip(service->l, dest, 2);
		//afiseaza_lista(filtered);
		//afiseaza_lista(filtrare_dest_tip(service->l, dest, 2));
		//distruge(&filtered);
	}
	/*
	if (strcmp(option, "destinatie") == 0)
	{
		char dest[50];
		printf("Dati destinatia: ");
		gets_s(dest, sizeof(dest));
		//filtered = filtrare_dest_tip(service->l, dest, 2);
		//afiseaza_lista(filtered);
		afiseaza_lista(filtrare_dest_tip(service->l, dest, 2));
		//distruge(&filtered);
	}*/
	//distruge(&filtered);
}


void sortare_ui(Service* service)
{
	char option[50];
	int option2 = 1;
	//List sorted;

	printf("\nAlegeti criteriul de sortare: ");
	gets_s(option, sizeof(option));
	printf("\nCrescator(1) sau Descrescator(2): ");
	scanf_s("%d", &option2);

	bool reversed;
	if (option2 == 1)
		reversed = false;
	else reversed = true;

	//sorted = sorting(service->l, option, reversed);
	//sorting(&sorted, service->l, option, reversed);
	//afiseaza_lista(sorted);
	afiseaza_lista(sorting(service->l, option, reversed));	
}

void sortare_2_ui(Service* service)
{
	char option[50];
	//int option2 = 1;
	//List sorted;

	printf("\nAlegeti criteriul de sortare: ");
	gets_s(option, sizeof(option));
	//printf("\nCrescator(1) sau Descrescator(2): ");
	//scanf_s("%d", &option2);

	/*bool reversed;
	if (option2 == 1)
		reversed = false;
	else reversed = true;*/

	//sorted = sorting(service->l, option, reversed);
	//sorting(&sorted, service->l, option, reversed);
	//afiseaza_lista(sorted);
	if(strcmp(option, "pret")==0)
		afiseaza_lista(sortbypret(service->l));
	if (strcmp(option, "destinatie") == 0)
		afiseaza_lista(sortbydest(service->l));
}


/* Consola aplicatiei */
void Console(Service* service)
{
	creeaza_dinamic(&service->l);
	InitList(service);
	int ok = 1;
	char cmd[50], fake[5];
	while (ok)
	{	
		printf("\nComenzi disponibile: add, delete, update, filter, sort, sort2, show_all, exit\n");
		printf("Comanda dvs este: ");
		gets_s(cmd, sizeof(cmd));

		if (strcmp(cmd, "add")==0) {
			adauga_ui(service);
			gets_s(fake, sizeof(fake));
		}
		if (strcmp(cmd, "show_all")==0)
			afiseaza(service);
		if (strcmp(cmd, "delete") == 0)
		{
			sterge_ui(service);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		if (strcmp(cmd, "update") == 0)
		{
			actualizare_ui(service);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		
		if (strcmp(cmd, "filter") == 0)
		{
			filtrare_ui(service);
		}
		
		if (strcmp(cmd, "sort") == 0)
		{
			sortare_ui(service);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}

		if (strcmp(cmd, "sort2") == 0)
		{
			sortare_2_ui(service);
		}
		
		if (strcmp(cmd, "exit") == 0)
			ok = 0;
	}

	distruge(&service->l);
}