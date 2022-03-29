#pragma once
#include "repository.h"

typedef struct {
	DynamicArray repo;
}Service;

/// <summary>
/// Creeaza un nou obiect de tipul service.
/// </summary>
/// <param name="repo"> - repositoriul in care se memoreaza informatii despre participanti.</param>
/// <returns> un nou obiect de tipul service.</returns>
Service createService(DynamicArray repo);

/// <summary>
/// Adauga un nou participant in lista.
/// </summary>
/// <param name="sv"> - serviceul care contine informatii despre lista curenta.</param>
/// <param name="Nume"> - numele noului participant.</param>
/// <param name="Prenume"> - prenumele noului participant.</param>
/// <param name="Scor"> - scorul noului participant.</param>
/// <returns> 1 daca participantul a fost adaugat cu succes, 0 altfel.</returns>
int serviceAdd(Service sv, char Nume[100], char Prenume[100], int Scor);

/// <summary>
/// Schimba informatiile despre un anumit participant din lista.
/// </summary>
/// <param name="sv">
/// - serviceul care contine informatii despre lista curenta.
/// </param>
/// <param name="Nume">
/// - numele participantului.
/// </param>
/// <param name="Prenume">
/// - prenumele participantului.
/// </param>
/// <param name="Scor">
/// - noul scor al participantului.
/// </param>
/// <returns>
/// 1 daca scorul participantului a fost schimbat cu succes, 0 altfel.
/// </returns>
int serviceEdit(Service sv, char Nume[100], char Prenume[100], int Scor);

/// <summary>
///	Sterge un participant din lista.
/// </summary>
/// <param name="sv">
/// - serviceul care contine informatii despre lista.
/// </param>
/// <param name="Nume">
/// - numele participantului.
/// </param>
/// <param name="Prenume">
/// - prenumele participantului.
/// </param>
/// <returns>
/// 1 daca participantul a fost sters cu succes, 0 altfel.
/// </returns>
int serviceDelete(Service sv, char Nume[100], char Prenume[100]);

/// <summary>
/// Filtreaza dupa un anumit tipar lista de participanti.
/// </summary>
/// <param name="sv">
/// - serviceul care contine informatii despre lista.
/// </param>
/// <param name="Filtru">
/// - filtrul care se aplica listei.
/// </param>
/// <param name="participanti">
/// - lista de participanti filtrata, returnata.
/// </param>
/// <param name="n">
/// - numarul de elemente din lista filtrata, returnat.
/// </param>
/// <returns>
/// 1 daca s-a putut aplica filtrul, 0 altfel.
/// </returns>
int serviceFilter(Service sv, char Filtru[100], DynamicArray retArray);

/// <summary>
/// Sorteaza lista de participanti dupa un anumit tipar.
/// </summary>
/// <param name="sv">
/// - serviceul care contine lista de participanti.
/// </param>
/// <param name="SortType">
/// - tiparul dupa care se sorteaza.
/// </param>
/// <param name="participanti">
/// - lista de participanti sortata, returnata.
/// </param>
/// <param name="n">
/// - numarul de elementele din lista, returnat.
/// </param>
/// <returns>
/// 1 daca tiparul a putut fi aplicat, 0 altfel.
/// </returns>
int serviceSort(Service sv, char SortType[100], DynamicArray retArray);

/// <summary>
/// Adauga niste participanti in lista.
/// </summary>
/// <param name="sv">
/// - serviceul care contine lista de participanti.
/// </param>
void serviceAddSome(Service sv);



void TestService(void);