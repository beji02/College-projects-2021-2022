#include "console.h"


/*
1. Magazin
Creați o aplicație care permite:										
· gestiunea unei liste de produse. Produs: nume, tip, preț, producător	DONE
· adăugare, ștergere, modificare și afișare produse						DONE
· căutare produs														DONE
· filtrare produse după: preț, nume, producător							DONE
· sortare produse după: nume, preț, tip+nume							DONE
*/



void Console::AddUI()
{
	string nume, tip, producator;
	int pret;
	cout << "Nume produs: "; cin >> nume;
	cout << "Tip produs: "; cin >> tip;
	cout << "Nume producator: "; cin >> producator;
	cout << "Pret: "; cin >> pret;

	try
	{
		Serv.Add(nume, tip, producator, pret);
		cout << "Produs adaugat cu succes!\n";
	}
	catch(exception e)
	{
		cout << e.what();
	}
}
void ShowList(const vector<Product>& ListOfProducts)
{
	if (ListOfProducts.empty())
		throw exception("Lista este goala!\n");
	printf("%-20s%-20s%-20s%-20s%-20s\n", "ID", "Nume", "Tip", "Producator", "Pret");
	printf("--------------------------------------------------------------------------------------------\n");
	for (const auto& el : ListOfProducts)
		printf("%-20d%-20s%-20s%-20s%-20d\n", el.GetId(), el.GetName().c_str(), el.GetType().c_str(), el.GetProducer().c_str(), el.GetPrice());
}
void Console::ShowListUI()
{
	try
	{
		vector<Product> retList = Serv.GetList();
		ShowList(retList);
	}
	catch (exception e)
	{
		cout << e.what();
	}
}
void Console::DeleteUI()
{
	int id;
	cout << "ID produs: "; cin >> id;

	try
	{
		Serv.Remove(id);
		cout << "Produs sters cu succes!\n";
	}
	catch (exception e)
	{
		cout << e.what();
	}
}
void Console::UpdateUI()
{
	string nume, tip, producator;
	int pret, id;
	
	cout << "Id produs: "; cin >> id;
	cout << "Nume nou: "; cin >> nume;
	cout << "Tip nou: "; cin >> tip;
	cout << "Nume producator nou: "; cin >> producator;
	cout << "Pret nou: "; cin >> pret;

	try
	{
		Serv.Update(id, nume, tip, producator, pret);
		cout << "Produs modificat cu succes!\n";
	}
	catch (exception e)
	{
		cout << e.what();
	}
}
void Console::FindUI()
{
	string nume;

	cout << "Nume produs: "; cin >> nume;
	try
	{
		Product product = Serv.Find(nume);
		cout << "Exista " << product.GetName() << " la " << product.GetPrice()<<" lei.\n";
	}
	catch (exception e)
	{
		cout << e.what();
	}
}
void Console::FilterUI()
{
	int filterType;
	vector<Product> retList;
	cout << "Filtrare dupa pret(1), nume(2), producator(3): "; cin >> filterType;
	if (filterType == 1)
	{
		int pret;
		cout << "Pret: "; cin >> pret;
		retList = Serv.FilterPrice(pret);
	}
	else
	if (filterType == 2)
	{
		string nume;
		cout << "Nume produs: "; cin >> nume;
		retList = Serv.FilterName(nume);
	}
	else
	if (filterType == 3)
	{
		string producator;
		cout << "Nume producator: "; cin >> producator;
		retList = Serv.FilterProducer(producator);
	}
	else
		return;
	
	try
	{
		ShowList(retList);
	}
	catch (exception e)
	{
		cout << e.what();
	}

}
void Console::SortUI()
{
	int sortType;
	cout << "Sortare dupa pret(1), nume(2), tip+nume(3): "; cin >> sortType;
	try
	{
		Serv.SortList(sortType);
	}
	catch (exception e)
	{
		cout << e.what();
	}
}


void Console::ShowUI()
{
	vector<string> funcs{
		"exit(0)", "add(1)", "show(2), delete(3), update(4), find(5), fitrare(6), sortare(7)"
	};
	int input;

	while (true)
	{
		for (auto const& el : funcs)
			cout << el << " ";
		cout << "\nComanda ta: "; cin >> input;

		switch (input)
		{
			case 0: return;
			case 1: AddUI(); break;
			case 2: ShowListUI(); break;
			case 3: DeleteUI(); break;
			case 4: UpdateUI(); break;
			case 5: FindUI(); break;
			case 6: FilterUI(); break;
			case 7: SortUI(); break;
			default: break;
		}
		system("pause");
		system("cls");
	}
}
