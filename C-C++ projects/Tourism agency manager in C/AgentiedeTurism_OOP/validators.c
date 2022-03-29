#include "oferta.h"
#include "operatii.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int validate(ElemType offer)
{
	if (strcmp(offer.tip, "") == 0 || strcmp(offer.tip, " ") == 0)
	{
		printf("Eroare: tipul ofertei este vid!\n");
		distruge_oferta(&offer);
		return 0;
	}

	if (strcmp(offer.destinatie, "") == 0 || strcmp(offer.destinatie, " ") == 0)
	{
		printf("Eroare: destinatia ofertei este vida!\n");
		distruge_oferta(&offer);
		return 0;
	}

	if (offer.datap.zi < 1 || offer.datap.zi>31)
	{
		printf("Eroare: Ziua trebuie sa fie un numar intre 1 si 31.\n");
		distruge_oferta(&offer);
		return 0;
	}

	if (offer.datap.luna < 1 || offer.datap.luna > 12)
	{
		printf("Eroare: Luna trebuie sa fie un numar intre 1 si 12.\n");
		distruge_oferta(&offer);
		return 0;
	}

	if (offer.datap.an < 2020)
	{
		printf("Eroare: An invalid.\n");
		distruge_oferta(&offer);
		return 0;
	}

	return 1;	

}

void testValidate()
{
	Oferta offer;
	offer = creeaza("", "Italia", 125, 21, 2, 2022);

	printf("*****Teste la validatori:\n");
	assert(validate(offer) == 0);

	offer = creeaza("mare", "", 400, 15, 6, 2022);

	assert(validate(offer) == 0);

	offer = creeaza("citybreak", "Paris", 1000, 35, 5, 2022);

	assert(validate(offer) == 0);

	offer = creeaza("munte", "Elvetia", 1800, 10, 13, 2022);

	assert(validate(offer) == 0);

	offer = creeaza("mare", "Maldives", 8870, 24, 8, 2004);

	assert(validate(offer) == 0);

	offer = creeaza("city break", "Budapesta", 300, 7, 11, 2022);

	assert(validate(offer) == 1);
	printf("*****Teste la validatori*******");

	distruge_oferta(&offer);

}