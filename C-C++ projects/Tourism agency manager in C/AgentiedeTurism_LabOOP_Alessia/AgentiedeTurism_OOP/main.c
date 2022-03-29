/*
* Cerinte generale:
Creati o aplicatie modulara in C.
Se cere interfata utilizator de tip consola.
Datele introduse de utilizator trebuie validate. 
Folositi athitectura stratificata.
Folositi dezvoltare dirijata de teste (Test Driven Development)
Fiecare metoda din aplicatie trebuie specificat si testat.
Implementati vector dinamic pentru lucru cu liste:
    - in prima saptamana puteti folosi reprezentarea cu un struct ( un vector static si lungime in el)
    - pana in saptamana 2 trebuie folosit alocare dinamica (sa acomodeze oricate elemente)
* 
9. Agentie de turism

Creati o aplicatie care permite gestiunea ofertelor de la o agentie de turism.

Fiecare oferta are: tip (munte, mare, city break), destinatie, data plecare, pret

Aplicatia permite:

 a) Adaugarea de noi oferte.

 b) Actualizare oferte

 c) Stergere oferta

 d) Vizualizare oferete ordonat dupa pret, destinatie (crescator/descrescator)

 e) Vizualizare oferta filtrate dupa un criteriu (destinatie, tip, pret)
*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Offer.h"
#include "Repository.h"
#include "Service.h"
#include "ConsoleUI.h"
#include "OfferValidator.h"

void RunTests()
{
    __TestDynamicArray();
    __TestOffer();
    __TestRepository();
    __TestService();
    __TestValidate();
}


void RunApp()
{
    Repository repository = CreateRepository();
    AddSome(repository);
    Service service; service.Repo = repository;
    Console console; console.Serv = service;
    ShowMenu(console);
    DestroyRepository(repository);
}
int main()
{   
    RunTests();
    RunApp();

    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    
	return 0;
}