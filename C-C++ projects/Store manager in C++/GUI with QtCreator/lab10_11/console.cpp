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
	catch(InvalidInput e)
	{
		cout << e.what();
	}
}
void ShowList(const VectorDinamic<Product>& ListOfProducts)
{
	if (ListOfProducts.empty())
		throw EmptyList("Lista este goala!\n");
	printf("%-20s%-20s%-20s%-20s%-20s\n", "ID", "Nume", "Tip", "Producator", "Pret");
	printf("--------------------------------------------------------------------------------------------\n");
	for (const auto& el : ListOfProducts)
		printf("%-20d%-20s%-20s%-20s%-20d\n", el.GetId(), el.GetName().c_str(), el.GetType().c_str(), el.GetProducer().c_str(), el.GetPrice());
}
void Console::ShowListUI()
{
	try
	{
		VectorDinamic<Product> retList = Serv.GetList();
		ShowList(retList);
	}
	catch (EmptyList e)
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
	catch (NoProductWithId e)
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
	catch (NoProductWithId e)
	{
		cout << e.what();
	}
	catch (InvalidInput e)
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
	catch (InvalidInput e)
	{
		cout << e.what();
	}
	catch (NoProductWithName e)
	{
		cout << e.what();
	}
}
void Console::FilterUI()
{
	int filterType;
	VectorDinamic<Product> retList;
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
	catch (EmptyList e)
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
	catch (EmptyList e)
	{
		cout << e.what();
	}
	catch (InvalidSortType e)
	{
		cout << e.what();
	}
}
void Console::FilterByPriceUI()
{
	int price;
	cout << "Pret produs: "; cin >> price;
	
	try
	{
		ShowList(Serv.FilterLess(price));
	}
	catch (NoProductWithPrice e)
	{
		cout << e.what();
	}
}

void Console::UndoUI()
{
	try
	{
		Serv.Undo();
		cout << "Undo efectuat cu succes!\n";
	}
	catch (NoUndoOperation e)
	{
		cout << e.what();
	}
}

void Console::ShowCartUI()
{
	const auto& list = Serv.Cart.GetAll();
	const auto& price = Serv.Cart.GetTotal();
	if (list.empty())
	{
		cout << "Nu exista niciun produs in cart.\n";
		cout << "Costul este 0.\n";
	}
	else
	{
		ShowList(list);
		cout << "Costul este " << price << ".\n";
	}
}
void Console::AddCartUI()
{
	string nume;
	cout << "Nume produs: "; cin >> nume;

	try
	{
		Serv.Cart.Add(nume);
		cout << "Produs adaugat cu succes in cos!\n";
		const auto& price = Serv.Cart.GetTotal();
		cout << "Costul este " << price << ".\n";
	}
	catch (NoProductWithName e)
	{
		cout << e.what();
	}
}
void Console::GenerateCartUI()
{
	int nr_produse;
	cout << "Numar produse: "; cin >> nr_produse;
	try
	{
		Serv.GenerateCart(nr_produse);
		cout << "Cos generat cu succes!\n";
		const auto& price = Serv.Cart.GetTotal();
		cout << "Costul este " << price << ".\n";
	}
	catch (EmptyList e)
	{
		cout << e.what();
	}
}
void Console::ExportCartUI()
{
	string nume_fisier;
	cout << "Nume fisier de export: "; cin >> nume_fisier;
	try
	{
		Serv.Cart.Export(nume_fisier);
		cout << "Cosul a fost exportat cu succes.\n";
	}
	catch (CorruptedFile e)
	{
		cout << e.what();
	}
}
void Console::EmptyCartUI()
{
	Serv.Cart.Empty();
	cout << "Cosul a fost golit cu succes.\n";
	const auto& price = Serv.Cart.GetTotal();
	cout << "Costul este " << price << ".\n";
}


void Console::ShowUI()
{
	vector<string> funcs{
        "exit(0)", "add(1)," "show(2),"
        " delete(3), update(4), find(5),"
        " filtrare(6), sortare(7)\nshowCart(8),"
        " addCart(9), generateCart(10), exportCart(11),"
        " emptyCart(12)\nfilterByPrice(13), undo(14)"
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
			case 8: ShowCartUI(); break;
			case 9: AddCartUI(); break;
			case 10: GenerateCartUI(); break;
			case 11: ExportCartUI(); break;
			case 12: EmptyCartUI(); break;
			case 13: FilterByPriceUI(); break;
			case 14: UndoUI(); break;
			default: break;
		}
		system("pause");
		system("cls");
	}
}
