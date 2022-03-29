#include "Libraries.h"
#include "Service.h"
#include "Repository.h"
#include "Offer.h"
#include "OfferValidator.h"



int Adauga(Service Sv, int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price)
{
	Offer off = CreateOffer(Id, Type, Destination, Day, Month, Year, Price);
	if (Validate(off) == 0)
	{
		DestroyOffer(off);
		return -1;
	}
	
	if (SearchRepository(Sv.Repo, off) == 1)
	{
		DestroyOffer(off);
		return -2;
	}

	InsertRepository(Sv.Repo, off);
	DestroyOffer(off);
	return 0;
}
int Actualizare(Service Sv, int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price)
{
	Offer off = CreateOffer(Id, Type, Destination, Day, Month, Year, Price);
	if (Validate(off) == 0)
	{
		DestroyOffer(off);
		return -1;
	}
	if (SearchRepository(Sv.Repo, off) == 0)
	{
		DestroyOffer(off);
		return -2;
	}

	UpdateRepository(Sv.Repo, off);

	DestroyOffer(off);
	return 0;
}
int Stergere(Service Sv, int Id)
{
	Offer off = CreateOffer(Id, "", "", 0, 0, 0, 0);
	if (SearchRepository(Sv.Repo, off) == 0)
	{
		DestroyOffer(off);
		return -2;
	}

	DeleteRepository(Sv.Repo, off);
	DestroyOffer(off);
	return 0;
}

int __F0(ElementType Off1, ElementType Off2)
{
	return GetId(Off1) > GetId(Off2);
}
int __F1(ElementType Off1, ElementType Off2)
{
	return GetPrice(Off1) > GetPrice(Off2);
}
int __F2(ElementType Off1, ElementType Off2)
{
	return GetPrice(Off1) < GetPrice(Off2);
}
int __F3(ElementType Off1, ElementType Off2)
{
	return strcmp(GetDestination(Off1), GetDestination(Off2)) > 0;
}
int __F4(ElementType Off1, ElementType Off2)
{
	return strcmp(GetDestination(Off1), GetDestination(Off2)) < 0;
}
CompareElementFct __GetCompareFunction(int Option, int Option2)
{
	if (Option == 0)
		if (Option2 == 0)
			return __F1;
		else
			return __F2;
	else
	if(Option == 1)
		if (Option2 == 0)
			return __F3;
		else
			return __F4;
	else
		return __F0;
}
DynamicArray Sortare(Service Sv, int Option, int Option2)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	CompareElementFct __compare = __GetCompareFunction(Option, Option2);
	Sort(list, __compare);
	return list;
}

DynamicArray FilterPrice(Service Sv, int Price)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	DynamicArray filteredList = CreateArray(list->CopyFunction, list->DestroyFunction);

	int len = GetLength(list);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(list, i);
		if (GetPrice(offer) == Price)
			Insert(filteredList, offer);
	}
	DestroyArray(list);
	return filteredList;
}
DynamicArray FilterType(Service Sv, char* Type)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	DynamicArray filteredList = CreateArray(list->CopyFunction, list->DestroyFunction);

	int len = GetLength(list);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(list, i);
		if (strcmp(GetType(offer), Type) == 0)
			Insert(filteredList, offer);
	}
	DestroyArray(list);
	return filteredList;
}
DynamicArray FilterDestination(Service Sv, char* Destination)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	DynamicArray filteredList = CreateArray(list->CopyFunction, list->DestroyFunction);

	int len = GetLength(list);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(list, i);
		if (strcmp(GetDestination(offer), Destination) == 0)
			Insert(filteredList, offer);
	}
	DestroyArray(list);
	return filteredList;
}
DynamicArray FilterYear(Service Sv, int Year)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	DynamicArray filteredList = CreateArray(list->CopyFunction, list->DestroyFunction);

	int len = GetLength(list);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(list, i);
		if (GetYear(offer) == Year)
			Insert(filteredList, offer);
	}
	DestroyArray(list);
	return filteredList;
}



int Exista(Service Sv, char* Dest, int Price)
{
	DynamicArray list = GetAllRepository(Sv.Repo);
	DynamicArray filteredList = CreateArray(list->CopyFunction, list->DestroyFunction);

	int len = GetLength(list);
	for (int i = 0; i < len; i++)
	{
		Offer offer = GetElement(list, i);
		if (GetPrice(offer) < Price && strcmp(GetDestination(offer), Dest) == 0)
			Insert(filteredList, offer);
	}
	DestroyArray(list);
	int n = GetLength(filteredList);
	DestroyArray(filteredList);
	return n >=2;
}



int Undo(Service Sv)
{
	return UndoRepository(Sv.Repo);
}



void __TestExista()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;

	Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000);
	Adauga(service, 2, "idk", "idk", 1, 1, 2022, 1000);
	Adauga(service, 3, "idk", "idk", 1, 1, 2022, 1000);

	assert(Exista(service, "idk", 1001) == 1);
	assert(Exista(service, "idk", 1000) == 0);
	assert(Exista(service, "id", 1001) == 0);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}

void __TestAdauga()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;
	
	assert(Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000) == 0);
	assert(Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000) == -2);
	assert(Adauga(service, 1, "idk", "idk", 1, 1, 2, 1000) == -1);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestActualizare()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;

	Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000);
	assert(Actualizare(service, 1, "idk", "idk", 1, 1, 2022, 2000)== 0);
	assert(Actualizare(service, 1, "idk", "idk", 1, 1, 2, 2000) == -1);
	assert(Actualizare(service, 0, "idk", "idk", 1, 1, 2022, 2000) == -2);


	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestStergere()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;

	Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000);
	assert(Stergere(service, 1) == 0);
	assert(Stergere(service, 1) == -2);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestSortare()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;

	Adauga(service, 1, "idk", "ab", 1, 1, 2022, 10);
	Adauga(service, 2, "idk", "ba", 1, 1, 2022, 100);
	Adauga(service, 3, "idk", "ca", 1, 1, 2022, 1000);
	
	DynamicArray retArray = Sortare(service, 0, 0);
	assert(GetId(GetElement(retArray, 0)) == 1);
	DestroyArray(retArray);

	retArray = Sortare(service, 0, 1);
	assert(GetId(GetElement(retArray, 0)) == 3);
	DestroyArray(retArray);

	retArray = Sortare(service, 1, 0);
	assert(GetId(GetElement(retArray, 0)) == 1);
	DestroyArray(retArray);

	retArray = Sortare(service, 1, 1);
	assert(GetId(GetElement(retArray, 0)) == 3);
	DestroyArray(retArray);

	retArray = Sortare(service, 2, 0);
	assert(GetId(GetElement(retArray, 0)) == 1);
	DestroyArray(retArray);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestFilter()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;

	Adauga(service, 1, "idk", "ab", 1, 1, 2022, 10);
	Adauga(service, 2, "idk", "ba", 1, 1, 2022, 100);
	Adauga(service, 3, "idk", "ca", 1, 1, 2022, 100);

	DynamicArray retArray = FilterPrice(service, 100);
	assert(GetLength(retArray) == 2);
	DestroyArray(retArray);

	retArray = FilterType(service, "idk");
	assert(GetLength(retArray) == 3);
	DestroyArray(retArray);

	retArray = FilterDestination(service, "ab");
	assert(GetLength(retArray) == 1);
	DestroyArray(retArray);

	retArray = FilterYear(service, 2022);
	assert(GetLength(retArray) == 3);
	DestroyArray(retArray);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestUndo()
{
	Repository repository = CreateRepository();
	Service service; service.Repo = repository;
	
	Adauga(service, 1, "idk", "idk", 1, 1, 2022, 1000);
	Adauga(service, 2, "idk", "idk", 1, 1, 2022, 1000);
	Adauga(service, 3, "idk", "idk", 1, 1, 2022, 1000);
	
	assert(Undo(service) == 0);	
	assert(Undo(service) == 0);
	assert(Undo(service) == 0);
	assert(Undo(service) == -1);

	DestroyRepository(repository);
	assert(!_CrtDumpMemoryLeaks());
}

void __TestService()
{
	__TestAdauga();
	__TestActualizare();
	__TestStergere();
	__TestSortare();
	__TestFilter();
	__TestUndo();
	__TestExista();
}
