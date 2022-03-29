#pragma once

typedef struct
{
	char* Type;
	char* Destination;

	struct
	{
		int Day, Month, Year;
	} DepartureDate;

	int Price;
	int Id;
}__Offer, * Offer;

/*creeaza o oferta noua*/
Offer CreateOffer(int Id, char* Type, char* Destination, int Day, int Month, int Year, int Price);
/*copiaza o oferta noua*/
Offer CopyOffer(Offer Off);
/*distruge o oferta*/
void DestroyOffer(Offer Off);
/*verifica daca 2 oferte sunt egale*/
int IsEqual(Offer Off1, Offer Off2);

/*ia tipul ofertei*/
const char* GetType(Offer Off);
/*ia destinatia ofertei*/
const char* GetDestination(Offer Off);
/*ia ziua ofertei*/
int GetDay(Offer Off);
/*ia luna ofertei*/
int GetMonth(Offer Off);
/*ia anul ofertei*/
int GetYear(Offer Off);
/*ia pretul ofertei*/
int GetPrice(Offer Off);
/*ia idul ofertei*/
int GetId(Offer Off);



void __TestOffer();