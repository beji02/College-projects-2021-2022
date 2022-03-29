#pragma once
#include "common.h"
#include "service.h"

class Console
{
private:
	Service& Serv;
public:
	Console(Service& Serv) : Serv{ Serv } {};
	
	void ShowUI();
	void AddUI();
	void ShowListUI();
	void DeleteUI();
	void UpdateUI();
	void FindUI();
	void FilterUI();
	void SortUI();
};

