#include "service.h"


void Service::Add(const string& Name, const string& Type, const string& Producer, const int& Price)
{
	if (Name.empty() || Type.empty() || Producer.empty())
		throw exception("Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n");
	else
	if (Price <= 0)
		throw exception("Produs invalid. Pretul trebuie sa fie > 0.\n");
	Repo.Insert(Product(Name, Type, Price, Producer));
}
const vector<Product>& Service::GetList() const
{
	return Repo.GetAll();
}
void Service::AddSome()
{
	Add("Portocale", "Fructe", "Italia", 5);
	Add("Mere", "Fructe", "Italia", 3);
	Add("Rosi", "Legume", "Grecia", 4);
	Add("Castraveti", "Legume", "Romania", 3);
}
void Service::Remove(const int& Id)
{
	Product product(Id, "", "", 0, "");
	const bool retValue = Repo.Search(product);
	if (retValue == false)
		throw exception("Nu exista un produs cu acest ID.\n");
	Repo.Delete(product);
}
void Service::Update(const int& Id, const string& Name, const string& Type, const string& Producer, const int& Price)
{
	Product product(Id, Name, Type, Price, Producer);
	const bool retValue = Repo.Search(product);
	if (retValue == false)
		throw exception("Nu exista un produs cu acest ID.\n");

	if (Name.empty() || Type.empty() || Producer.empty())
		throw exception("Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n");
	else
	if (Price <= 0)
		throw exception("Produs invalid. Pretul trebuie sa fie > 0.\n");
	Repo.Delete(product);
	Repo.Insert(product);
}
const Product& Service::Find(const string& Name) const
{
	if (Name.empty())
		throw exception("Produs invalid. Numele produsului trebuie sa fie nevid.\n");
	const auto& retVector = Repo.GetAll();
	for (auto& pr : retVector)
	{
		if (pr.GetName() == Name)
			return pr;
	}
	string s = "Nu exista " + Name + ". Ne pare rau!\n";
	throw exception(s.c_str());
}

const vector<Product> Service::FilterPrice(const int& Price) const
{
	const vector<Product>& list = Repo.GetAll();
	vector<Product> filteredList;
	for (const auto& el : list)
		if (el.GetPrice() == Price)
			filteredList.push_back(el);
	return filteredList;
}
const vector<Product> Service::FilterName(const string& Name) const
{
	const vector<Product>& list = Repo.GetAll();
	vector<Product> filteredList;
	for (const auto& el : list)
		if (el.GetName() == Name)
			filteredList.push_back(el);
	return filteredList;
}
const vector<Product> Service::FilterProducer(const string& Producer) const
{
	const vector<Product>& list = Repo.GetAll();
	vector<Product> filteredList;
	for (const auto& el : list)
		if (el.GetProducer() == Producer)
			filteredList.push_back(el);
	return filteredList;
}


//de ce nu pot pune tipul direct in fata functie si trebuie sa creez un typedef
typedef const bool(*CompFunc)(const Product& P1, const Product& P2);
CompFunc GetCompFunc(const int& SortType)
{
	if(SortType == 1)
		return [](const Product& P1, const Product& P2)->const bool {return P1.GetPrice() < P2.GetPrice();};
	else
	if (SortType == 2)
	return [](const Product& P1, const Product& P2)->const bool {return P1.GetName() < P2.GetName();};
	else
		return [](const Product& P1, const Product& P2)->const bool {return P1.GetType() == P2.GetType() ? P1.GetName() < P2.GetName() : P1.GetType() < P2.GetType();};
	
}
void Service::SortList(const int& SortType)
{
	if (SortType < 1 || SortType > 3)
		throw exception("Tip de sortare invalid.\n");
	auto compFunc = GetCompFunc(SortType);
	Repo.Sort(compFunc);
}



void __TestAdd()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	vector<Product> retVector = repo.GetAll();
	assert(retVector.size() == 1);
	
	try
	{
		service.Add("", "Fructe", "Italy", 101);
		assert(false);
	}
	catch(exception e)
	{
		string s = "Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n";
		assert(s == e.what());
	}

	try
	{
		service.Add("Ana", "Fructe", "Italy", -100);
		assert(false);
	}
	catch (exception e)
	{
		string s = "Produs invalid. Pretul trebuie sa fie > 0.\n";
		assert(s == e.what());
	}
}
void __TestGetList()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	assert(service.GetList().size() == 1);
}
void __TestAddSome()
{
	Repository repo;
	Service service(repo);

	service.AddSome();
	assert(service.GetList().size() == 4);
}
void __TestRemove()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	int id = service.GetList()[0].GetId();
	service.Remove(id);
	assert(service.GetList().size() == 0);
	try {
		service.Remove(id);
		assert(false);
	}
	catch (exception e)
	{
		string s = "Nu exista un produs cu acest ID.\n";
		assert(e.what() == s);
	}
}
void __TestUpdate()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	int id = service.GetList()[0].GetId();
	service.Update(id, "Portocale", "Fructe", "Italy", 10);
	assert(service.GetList()[0].GetPrice() == 10);

	try {
		service.Update(0, "Portocale", "Fructe", "Italy", 10);
		assert(false);
	}
	catch (exception e)
	{
		string s = "Nu exista un produs cu acest ID.\n";
		assert(e.what() == s);
	}

	try {
		service.Update(id, "", "Fructe", "Italy", 10);
		assert(false);
	}
	catch (exception e)
	{
		string s = "Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n";
		assert(e.what() == s);
	}

	try {
		service.Update(id, "Portocale", "Fructe", "Italy", -1);
		assert(false);
	}
	catch (exception e)
	{
		string s = "Produs invalid. Pretul trebuie sa fie > 0.\n";
		assert(e.what() == s);
	}
}
void __TestFind()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	Product pr = service.Find("Portocale");
	assert(pr.GetPrice() == 100);

	try {
		service.Find("Mere");
		assert(false);
	}
	catch (exception e)
	{
		string s = "Nu exista Mere. Ne pare rau!\n";
		assert(e.what() == s);
	}

	try {
		service.Find("");
		assert(false);
	}
	catch (exception e)
	{
		string s = "Produs invalid. Numele produsului trebuie sa fie nevid.\n";
		assert(e.what() == s);
	}

}
void __TestFilter()
{
	Repository repo;
	Service service(repo);

	service.AddSome();
	service.AddSome();

	auto retList = service.FilterPrice(3);
	assert(retList.size() == 4);

	retList = service.FilterName("Portocale");
	assert(retList.size() == 2);

	retList = service.FilterProducer("Romania");
	assert(retList.size() == 2);
}
void __TestSortList()
{
	Repository repo;
	Service service(repo);

	service.AddSome();

	service.SortList(1);
	assert(service.GetList()[0].GetPrice() == 3);

	service.SortList(2);
	assert(service.GetList()[0].GetName() == "Castraveti");

	service.SortList(3);
	assert(service.GetList()[0].GetName() == "Mere");

	try
	{
		service.SortList(4);
		assert(false);
	}
	catch (exception e)
	{
		assert(true);
	}
}

void TestService()
{
	__TestAdd();
	__TestGetList();
	__TestAddSome();
	__TestRemove();
	__TestUpdate();
	__TestFind();
	__TestFilter();
	__TestSortList();

	assert(!_CrtDumpMemoryLeaks());
}