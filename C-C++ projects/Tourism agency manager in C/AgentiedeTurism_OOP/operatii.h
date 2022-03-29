#pragma once
#include "oferta.h"
#include <stdbool.h>

typedef struct
{
	List l;
	//validatori

}Service;

/*  Adauga o oferta in lista manageriata de service */
void adauga(Service* service, ElemType offer);

/* Actualizeaza lista curenta cu o oferta care inlocuieste o oferta veche, data prin pozitia ei in lista de oferte */
void actualizare(Service* service, int poz, ElemType offer);

/* Sterge o oferta din lista, data prin pozitia ei in lista */
void sterge(Service* service, int poz);

/* Initializeaza lista cu o lista vida, lungimea primind valoarea 0 */
void EmptyList(Service* service);

/* Initializeaza lista cu cateva oferte predefinite */
void InitList(Service* service);

/* Creeaza si returneaza o oferta
   Primeste parametrii de tip char si int, reprezentant tipul, destinatia, pretul si data */
ElemType creeaza(char t[], char d[], int newpret, int newzi, int newluna, int newan);

/* Returneaza oferta din lista service-ului in functie de pozitia data poz */
ElemType get_offer(Service* service, int poz);

/* Returneaza lungimea listei din service */
int size(Service* service);

/* Returneaza o lista filtrata dupa un pret int dat */
List* filtrare_pret(List l, int pret, List* filtered);

/* Returneaza o lista filtrata dupa un string dat
   Daca parametrul option este 1 atunci stringul se refera la tipul dat
   Daca parametrul option este 2 (sau orice inafara de 1) atunci stringul se refera la destinatie */
List* filtrare_dest_tip(List l, char string[], int option, List* filtered);

//Sorteaza o lista
List sorting(List l, char option[50], bool reversed);
//void sorting(List* sorted, List l, char option[50], bool reversed);

List sortbypret(List l);

List sortbydest(List l);

/* Functii care testeaza crearea, adaugarea, stergerea, actualizarea si filtrarea asupra unei liste din service */
void testGetOffer();
void testCreeaza();
void testAdauga();
void testSterge();
void testActualizare();
void testFiltrare();
void testInitList();
void testSortare();
