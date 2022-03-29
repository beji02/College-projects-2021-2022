#pragma once
#include "Offer.h"

/*
Valideaza o oferta inainte de a fi adaugata
Verifica daca tipul si destinatia sunt vide sau daca data calendaristica este gresita.
1<=zi<=31
1<=luna<=12
2020<=an
*/
int Validate(Offer offer);
void __TestValidate();