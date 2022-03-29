#include "Libraries.h"
#include "Offer.h"

Offer CreateOffer(int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price)
{
	Offer newOff;
	newOff = (Offer)malloc(sizeof(__Offer));
	if (newOff != NULL)
	{
		newOff->Type = (char*)malloc(sizeof(char) * (strlen(Type) + 1));
		if (newOff->Type != NULL)
			strcpy(newOff->Type, Type);

		newOff->Destination = (char*)malloc(sizeof(char) * (strlen(Destination) + 1));
		if (newOff->Destination != NULL)
			strcpy(newOff->Destination, Destination);

		newOff->DepartureDate.Day = Day;		
		newOff->DepartureDate.Month = Month;
		newOff->DepartureDate.Year = Year;

		newOff->Price = Price;
		newOff->Id = Id;
	}
	return newOff;
}
Offer CopyOffer(Offer Off)
{
	Offer newOff;
	newOff = (Offer)malloc(sizeof(__Offer));
	if (newOff != NULL)
	{
		newOff->Type = (char*)malloc(sizeof(char) * (strlen(Off->Type) + 1));
		if (newOff->Type != NULL)
			strcpy(newOff->Type, Off->Type);

		newOff->Destination = (char*)malloc(sizeof(char) * (strlen(Off->Destination) + 1));
		if (newOff->Destination != NULL)
			strcpy(newOff->Destination, Off->Destination);

		newOff->DepartureDate.Day = Off->DepartureDate.Day;
		newOff->DepartureDate.Month = Off->DepartureDate.Month;
		newOff->DepartureDate.Year = Off->DepartureDate.Year;

		newOff->Price = Off->Price;
		newOff->Id = Off->Id;
	}
	return newOff;
}
void DestroyOffer(Offer Off)
{
	free(Off->Destination);
	free(Off->Type);
	free(Off);
}

const char* GetType(Offer Off)
{
	return Off->Type;
}
const char* GetDestination(Offer Off)
{
	return Off->Destination;
}
int GetDay(Offer Off)
{
	return Off->DepartureDate.Day;
}
int GetMonth(Offer Off)
{
	return Off->DepartureDate.Month;
}
int GetYear(Offer Off)
{
	return Off->DepartureDate.Year;
}
int GetPrice(Offer Off)
{
	return Off->Price;
}
int GetId(Offer Off)
{
	return Off->Id;
}

int IsEqual(Offer Off1, Offer Off2)
{
	return GetId(Off1) == GetId(Off2);
}

void __TestCreateGettersCopyDestroy()
{
	Offer offer = CreateOffer(1, "Munte", "Everest", 22, 9, 2022, 10000);
	Offer copyOffer = CopyOffer(offer);

	assert(strcmp(GetType(offer), "Munte") == 0);
	assert(strcmp(GetDestination(offer), "Everest") == 0);
	assert(GetDay(offer) == 22);
	assert(GetMonth(offer) == 9);
	assert(GetYear(offer) == 2022);
	assert(GetPrice(offer) == 10000);
	assert(GetId(offer) == 1);
	DestroyOffer(offer);

	assert(strcmp(GetType(copyOffer), "Munte") == 0);
	assert(strcmp(GetDestination(copyOffer), "Everest") == 0);
	assert(GetDay(copyOffer) == 22);
	assert(GetMonth(copyOffer) == 9);
	assert(GetYear(copyOffer) == 2022);
	assert(GetPrice(copyOffer) == 10000);
	assert(GetId(copyOffer) == 1);

	DestroyOffer(copyOffer);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestOffer()
{
	__TestCreateGettersCopyDestroy();
}