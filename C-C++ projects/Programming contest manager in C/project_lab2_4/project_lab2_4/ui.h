#pragma once
#include "service.h"

typedef struct {
	Service service;
}Ui;

/// <summary>
/// Creeaza un nou UI.
/// </summary>
/// <param name="sv">
/// - serviceul care rezolva cerintele utilizatorului.
/// </param>
/// <returns>
/// Ui ce contine informatii despre service.
/// </returns>
Ui createUi(Service sv);

/// <summary>
/// Afiseaza meniul cu functionalitati.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiShowMenu(void);

/// <summary>
/// Preia comanda de la utilizator.
/// </summary>
/// <param name="ui">
/// - uiul care contine informatii despre serviceul folosit.
/// </param>
void uiSelectCommand(Ui ui);

