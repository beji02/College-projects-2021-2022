#include "Libraries.h"
#include "ConsoleUI.h"

/* Citeste de la tastatura date si le adauga in lista */
void AdaugaUI(Console Con)
{
	char t[20], d[50], fake[5];
	int id, pret, zi, luna, an;

	//gets_s(fake, sizeof(fake));

	printf("Dati idul ofertei: ");
	scanf_s("%d", &id);

	gets_s(fake, sizeof(fake));

	printf("Dati tipul ofertei: ");
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

	int retVal = Adauga(Con.Serv, id, t, d, zi, luna, an, pret);

	if (retVal == 0)
	{
		printf("Oferta a fost adaugata cu succes.\n");
	}
	else
		if (retVal == -1)
			printf("Oferta invalida nu a putut fi adaugata.\n");
		else
			printf("Exista deja o oferta cu acelasi id.\n");
}
/* Sterge din lista o oferta cu pozitia data */
void StergeUI(Console Con)
{
	int id;
	printf("Dati id-ul ofertei de sters: ");
	scanf_s("%d", &id);
	int retVal = Stergere(Con.Serv, id);
	if (retVal == -2)
		printf("Nu exista acest id in lista de oferte.\n");
	else {
		printf("Oferta a fost stearsa cu succes.\n");
	}
}
/* Actualizeaza o oferta data prin pozitie cu o alta oferta data de la tastatura */
void ActualizareUI(Console Con)
{
	char t[20], d[50], fake[5];
	int pret, zi, luna, an, id;

	printf("Dati id-ul de actualizat: ");
	scanf_s("%d", &id);

	gets_s(fake, sizeof(fake));

	printf("Dati tipul nou de oferta: ");
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

	int retVal = Actualizare(Con.Serv, id, t, d, zi, luna, an, pret);

	if (retVal == 0)
		printf("Oferta a fost actualizata cu succes.\n");
	else
	if (retVal == -2)
		printf("Nu exista acest id in lista de oferte.\n");
	else
		printf("Oferta invalida nu a putut fi adaugata.\n");
}
void __ShowList(DynamicArray Array)
{
	int len = GetLength(Array);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(Array, i);
		printf("%d. %s %s %d.%d.%d %d\n", GetId(offer), GetType(offer), GetDestination(offer),
			GetDay(offer), GetMonth(offer), GetYear(offer), GetPrice(offer));
	}
	printf("\n");
}
void SortareUI(Console Con)
{
	int option, option2 = 1;

	printf("Alegeti criteriul de sortare:  Pret(0) sau Destinatie(1): ");
	scanf_s("%d", &option);
	printf("Crescator(0) sau Descrescator(1): ");
	scanf_s("%d", &option2);

	DynamicArray retArray = Sortare(Con.Serv, option, option2);
	__ShowList(retArray);
	DestroyArray(retArray);
}
void UndoUI(Console Con)
{
	int retValue = Undo(Con.Serv);
	if (retValue == -1)
		printf("Nu se mai poate realiza undo!\n");
	else
		printf("Undo realizat cu succes!\n");
}
/* Filtreaza o lista dupa un criteriu dat */
void FiltrareUI(Console Con)
{
	char option[50], fake[5];
	DynamicArray retArray = NULL;

	printf("Alegeti criteriul de filtrare (pret, tip, destinatie, an): ");
	gets_s(option, sizeof(option));

	if (strcmp(option, "pret") == 0)
	{
		int pret;
		printf("Dati pretul: ");
		scanf_s("%d", &pret);
		retArray = FilterPrice(Con.Serv, pret);
		gets_s(fake, sizeof(fake));
	}
	else
	if (strcmp(option, "tip") == 0)
	{
		char tip[50];
		printf("Dati tipul: ");
		gets_s(tip, sizeof(tip));
		retArray = FilterType(Con.Serv, tip);
	}
	else
	if (strcmp(option, "destinatie") == 0)
	{
		char dest[50];
		printf("Dati destinatia: ");
		gets_s(dest, sizeof(dest));
		retArray = FilterDestination(Con.Serv, dest);
	}
	else
	if (strcmp(option, "an") == 0)
	{
		int an;
		printf("Dati anul: ");
		scanf_s("%d", &an);
		retArray = FilterYear(Con.Serv, an);
		gets_s(fake, sizeof(fake));
	}

	if (retArray != NULL)
	{
		__ShowList(retArray);
		DestroyArray(retArray);
	}
}
void ShowAllUI(Console Con)
{
	DynamicArray retArray = Sortare(Con.Serv, 2, 0);
	__ShowList(retArray);
	DestroyArray(retArray);
}

void ExistaUI(Console Con)
{
	char dest[50];
	int price;

	printf("Dati o destinatie: ");
	gets_s(dest, sizeof(dest));

	printf("Dati un pret: ");
	scanf_s("%d", &price);
	int retVal=Exista(Con.Serv, dest, price);
	if (retVal == 1)
		printf("Exista oferte.\n");
	else
		printf("Nu exista oferte.\n");
}

/* Consola aplicatiei */
void ShowMenu(Console Con)
{
	int ok = 1;
	char cmd[50], fake[5];
	while (ok)
	{
		printf("Comenzi disponibile: add, delete, update, filter, sort, show, undo, exista, exit\n");
		printf("Comanda dvs este: ");
		gets_s(cmd, sizeof(cmd));

		if (strcmp(cmd, "add") == 0) {
			AdaugaUI(Con);
			gets_s(fake, sizeof(fake));
		}
		else
		if (strcmp(cmd, "show") == 0)
			ShowAllUI(Con);
		else
		if (strcmp(cmd, "delete") == 0)
		{
			StergeUI(Con);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		else
		if (strcmp(cmd, "update") == 0)
		{
			ActualizareUI(Con);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		else
		if (strcmp(cmd, "filter") == 0)
		{
			FiltrareUI(Con);
		}
		else
		if (strcmp(cmd, "sort") == 0)
		{
			SortareUI(Con);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		else
		if(strcmp(cmd, "undo") == 0)
			UndoUI(Con);
		else
		if (strcmp(cmd, "exista") == 0)
		{
			ExistaUI(Con);
			gets_s(fake, sizeof(fake)); //imi citeste ultimu enter dat cand citesc in fct ca sa nu mi bage meniul de 2 ori
		}
		else
		if (strcmp(cmd, "exit") == 0)
			ok = 0;
	}
}