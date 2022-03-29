#include "OfferValidator.h"
#include "Offer.h"
#include "Libraries.h"

int Validate(Offer offer)
{
	if (strcmp(offer->Type, "") == 0 || strcmp(offer->Type, " ") == 0)
	{
		//printf("Eroare: tipul ofertei este vid!\n");
		return 0;
	}

	if (strcmp(offer->Destination, "") == 0 || strcmp(offer->Destination, " ") == 0)
	{
		//printf("Eroare: destinatia ofertei este vida!\n");
		return 0;
	}

	if (offer->DepartureDate.Day < 1 || offer->DepartureDate.Day>31)
	{
		//printf("Eroare: Ziua trebuie sa fie un numar intre 1 si 31->\n");
		return 0;
	}

	if (offer->DepartureDate.Month < 1 || offer->DepartureDate.Month > 12)
	{
		//printf("Eroare: Luna trebuie sa fie un numar intre 1 si 12->\n");
		return 0;
	}

	if (offer->DepartureDate.Year < 2020)
	{
		//printf("Eroare: An invalid.\n");
		return 0;
	}

	return 1;

}
void __TestValidate()
{
	Offer offer;
	offer = CreateOffer(1, "", "Italia", 21, 2, 2022, 125);

	//printf("*****Teste la validatori:\n");
	assert(Validate(offer) == 0);
	DestroyOffer(offer);
	offer = CreateOffer(1, "mare", "", 15, 6, 2022, 400);

	assert(Validate(offer) == 0);
	DestroyOffer(offer);
	offer = CreateOffer(1, "citybreak", "Paris", 35, 5, 2022, 1000);


	assert(Validate(offer) == 0);
	DestroyOffer(offer);
	offer = CreateOffer(1, "munte", "Elvetia", 10, 13, 2022, 1800);

	assert(Validate(offer) == 0);
	DestroyOffer(offer);
	offer = CreateOffer(1, "mare", "Maldives", 24, 8, 2004, 8870);

	assert(Validate(offer) == 0);
	DestroyOffer(offer);
	offer = CreateOffer(1, "city break", "Budapesta", 7, 11, 2022, 300);

	assert(Validate(offer) == 1);
	//printf("*****Teste la validatori*******");
	DestroyOffer(offer);
	assert(!_CrtDumpMemoryLeaks());
}