#include "repository.h"


void Repository::Insert(const Product& NewProduct)
{
	Products.push_back(NewProduct);
}
bool Repository::Search(const Product& Pr) const
{
	auto it = find_if(Products.begin(), Products.end(), [Pr](Product pr)->bool {return pr == Pr;});
	if (it != Products.end())
		return true;
	return false;
	/*for (auto& pr : Products)
	{
		if (pr == Pr)
			return true;
	}
	return false;*/
}
const VectorDinamic<Product>& Repository::GetAll() const
{
	return Products;
}

void Repository::Delete(const Product& Pr)
{
	auto it = find_if(Products.begin(), Products.end(), [Pr](Product pr)->bool {return pr == Pr;});
	if (it != Products.end())
		Products.erase(it);
	//Products = remove_if(Products.begin(), Products.end(), [Pr](Product pr)->bool {return pr == Pr;});
	/*for (auto it = Products.begin(); it != Products.end(); ++it)
	{
		if ((*it) == Pr) 
		{
			Products.erase(it);
			return;
		}
	}*/
}
void Repository::Sort(const bool(*CompareFunc)(const Product& P1, const Product& P2))
{
	sort(Products.begin(), Products.end(), CompareFunc);
	/*for (int i = 0; i < Products.size(); i++)
	{
		for (int j = i + 1; j < Products.size(); j++)
		{
			if (CompareFunc(Products[j], Products[i]))
			{
				auto aux = Products[i];
				Products[i] = Products[j];
				Products[j] = aux;
			}
		}
	}*/
}



void __TestCreate()
{
	Repository repo;
}
void __TestInsert()
{
	Repository repo;
	
	repo.Insert(Product("Portocale", "Fruct", 5, "Italy"));
	repo.Insert(Product("Mere", "Fruct", 5, "Italy"));
	repo.Insert(Product("Castraveti", "Legume", 5, "Italy"));
	repo.Insert(Product("Grau", "Cereale", 5, "Italy"));
	
	assert(repo.GetAll().size() == 4);
	assert(repo.GetAll()[0].GetName() == "Portocale");
	assert(repo.GetAll()[3].GetName() == "Grau");
}
void __TestSearch()
{
	Repository repo;
	Product product("Portocale", "Fruct", 5, "Italy");
	Product product2("Nup", "Fruct", 5, "Italy");
	
	repo.Insert(product);
	repo.Insert(Product("Mere", "Fruct", 5, "Italy"));
	repo.Insert(Product("Castraveti", "Legume", 5, "Italy"));
	repo.Insert(Product("Grau", "Cereale", 5, "Italy"));
	
	assert(repo.Search(product) == true);
	assert(repo.Search(product2) == false);
}
void __TestDelete()
{
	Repository repo;
	Product product("Mere", "Fruct", 5, "Italy");
	Product product2("Mere", "Fruct", 5, "Italy");

	repo.Insert(product);
	repo.Insert(product2);
	repo.Delete(product2);
	assert(repo.GetAll().size() == 1);

	repo.Delete(product);
	assert(repo.GetAll().size() == 0);
}
void __TestSort()
{
	Repository repo;

	repo.Insert(Product("Mere", "Fruct", 5, "Italy"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Italy"));
	repo.Insert(Product("Castraveti", "Cereale", 2, "Italy"));

	repo.Sort([](const Product& P1, const Product& P2)->const bool {return P1.GetPrice() < P2.GetPrice();});
	assert(repo.GetAll()[0].GetPrice() == 2);

	repo.Sort([](const Product& P1, const Product& P2)->const bool {return P1.GetName() < P2.GetName();});
	assert(repo.GetAll()[0].GetName() == "Castraveti");

	repo.Sort([](const Product& P1, const Product& P2)->const bool {return P1.GetName() == P2.GetName() ? P1.GetType() < P2.GetType() : P1.GetName() < P2.GetName();});
	assert(repo.GetAll()[0].GetType() == "Cereale");
}


void TestRepository()
{
	__TestCreate();
	__TestInsert();
	__TestSearch();
	__TestDelete();
	__TestSort();
	assert(!_CrtDumpMemoryLeaks());
}