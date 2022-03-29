#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include "domain.h"
#include <stdio.h>


/// <summary>
/// Partea de ui a comenzii de iesire.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiExit(Ui ui)
{
	printf("The end!\n");
	destroyRepository(ui.service.repo);
	exit(0);
}

/// <summary>
/// Partea de ui pentru adaugarea unui nou participant.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiAdd(Ui ui)
{
	char Nume[100], Prenume[100];
	int Scor;
	
	printf("Nume: ");
	int retVal = scanf("%s", Nume);
	if (retVal == 0)
		return;
	printf("Prenume: ");
	retVal = scanf("%s", Prenume);
	if (retVal == 0)
		return;
	printf("Scor: ");
	retVal = scanf("%d", &Scor);
	if (retVal == 0)
		return;
	int ret = serviceAdd(ui.service, Nume, Prenume, Scor); 
	if (ret == 1)
		printf("Participant adaugat cu succes!\n");
	else
		printf("Eroare la adaugarea participantului.\n");
}

/// <summary>
/// Partea de ui pentru modificarea informatiilor despre un participant.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiEdit(Ui ui)
{
	char Nume[100], Prenume[100];
	int Scor;

	printf("Nume: ");
	int retVal = scanf("%s", Nume);
	if (retVal == 0)
		return;
	printf("Prenume: ");
	retVal = scanf("%s", Prenume);
	if (retVal == 0)
		return;
	printf("Scor: ");
	retVal = scanf("%d", &Scor);
	if (retVal == 0)
		return;
	int ret = serviceEdit(ui.service, Nume, Prenume, Scor);
	if (ret == 1)
		printf("Scor editat cu succes!\n");
	else
		printf("Eroare la editare.\n");
}

/// <summary>
/// Partea de ui pentru stergerea unui participant.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiDelete(Ui ui)
{
	char Nume[100], Prenume[100];

	printf("Nume: ");
	int retVal = scanf("%s", Nume);
	if (retVal == 0)
		return;
	printf("Prenume: ");
	retVal = scanf("%s", Prenume);
	if (retVal == 0)
		return;
	int ret = serviceDelete(ui.service, Nume, Prenume);
	if (ret == 1)
		printf("Participant sters cu succes!\n");
	else
		printf("Eroare la stergere.\n");
}

/// <summary>
/// Partea de ui pentru filtrarea listei de participanti.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiFilter(Ui ui)
{
	char Filtru[100];
	printf("Introduceti un filtrul(ex. <10 sau A*): ");

	int retVal = scanf("%s", Filtru);
	if (retVal == 0)
		return;
	DynamicArray retArray = CreateArray();
	int ret = serviceFilter(ui.service, Filtru, retArray);
	if (ret == 0)
		printf("Filtru incorect\n");
	else
	if (retArray->Count == 0)
	{
		printf("Lista participantilor cu filtrul aplicat este goala!\n");
	}
	else
	{
		printf("Lista participantilor cu filtrul aplicat:\n");
		for (int i = 0; i < retArray->Count; i++)
			printf("%d. %s %s %d\n", i+1, 
				((Participant)retArray->Elements[i])->Nume,
				((Participant)retArray->Elements[i])->Prenume,
				((Participant)retArray->Elements[i])->Scor);
	}
	DestroyArray(retArray);
}

/// <summary>
/// Partea de ui pentru sortarea listei.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiSort(Ui ui)
{
	char SortType[100];
	printf("Cum vreti sa sortati (ex. nume<, scor> etc.): ");

	int retVal = scanf("%s", SortType);
	if (retVal == 0)
		return;
	DynamicArray retArray = CreateArray();
	int ret = serviceSort(ui.service, SortType, retArray);
	if (ret == 0)
		printf("Tip de sortare incorecta!\n");
	else
	if (retArray->Count == 0)
	{
		printf("Lista sortata a participantilor este goala!\n");
	}
	else
	{
		printf("Lista sortata a participantilor:\n");
		for (int i = 0; i < retArray->Count; i++)
			printf("%d. %s %s %d\n", i + 1,
				((Participant)retArray->Elements[i])->Nume,
				((Participant)retArray->Elements[i])->Prenume,
				((Participant)retArray->Elements[i])->Scor);
	}
	DestroyArray(retArray);
}


Ui createUi(Service sv)
{
	Ui ui = { sv };
	return ui;
}
void uiShowMenu(void)
{
	int kComenzi = 6;
	char comenzi[][30] = {
		"0. exit aplication",
		"1. add participant",
		"2. edit participant",
		"3. delete participant",
		"4. filter",
		"5. sort",
	};
	for (int i = 0; i < kComenzi; i++)
		printf("%s\n", comenzi[i]);
	printf("Command number: ");
}
void uiSelectCommand(Ui ui)
{
	int index;
	int retVal = scanf("%d", &index);
	if (retVal == 0)
		return;
	if(index == -1)
		printf("Not a number!\n");
	else
		switch (index)
		{
			case 0:
				uiExit(ui);
				break;
			case 1:
				uiAdd(ui);
				break;
			case 2:
				uiEdit(ui);
				break;
			case 3:
				uiDelete(ui);
				break;
			case 4:
				uiFilter(ui);
				break;
			case 5:
				uiSort(ui);
				break;
			default:
				printf("Not a valid command number\n");
				break;
		}
	system("pause");
	system("cls");
}