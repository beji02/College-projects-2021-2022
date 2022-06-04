 #include "service.h"
#include "common.h"

void Service::Add(const string& Name, const string& Type, const string& Producer, const int& Price)
{
	if (Name.empty() || Type.empty() || Producer.empty())
		throw InvalidInput("Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n");
	else
	if (Price <= 0)
		throw InvalidInput("Produs invalid. Pretul trebuie sa fie > 0.\n");
	Product pr = Product(Name, Type, Price, Producer);
	Repo.Insert(pr);

	unique_ptr<ActiuneUndo> a = make_unique<UndoAdauga>(Repo, pr);
	UndoList.push_back(move(a));
}
const VectorDinamic<Product>& Service::GetList() const
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
		throw NoProductWithId("Nu exista un produs cu acest ID.\n");
	
	const auto& retVector = Repo.GetAll();
	auto it = find_if(retVector.begin(), retVector.end(), [Id](Product pr)->bool {return pr.GetId() == Id;});

	unique_ptr<ActiuneUndo> a = make_unique<UndoSterge>(Repo, *it);
	UndoList.push_back(move(a));
	Repo.Delete(product);
}
void Service::Update(const int& Id, const string& Name, const string& Type, const string& Producer, const int& Price)
{
	Product product(Id, Name, Type, Price, Producer);
	const bool retValue = Repo.Search(product);
	if (retValue == false)
		throw NoProductWithId("Nu exista un produs cu acest ID.\n");

	if (Name.empty() || Type.empty() || Producer.empty())
		throw InvalidInput("Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n");
	else
	if (Price <= 0)
		throw InvalidInput("Produs invalid. Pretul trebuie sa fie > 0.\n");
	
	const auto& retVector = Repo.GetAll();
	auto it = find_if(retVector.begin(), retVector.end(), [Id](Product pr)->bool {return pr.GetId() == Id;});

	unique_ptr<ActiuneUndo> a = make_unique<UndoModifica>(Repo, *it);
	UndoList.push_back(move(a));

	Repo.Delete(product);
	Repo.Insert(product);
}
const Product& Service::Find(const string& Name) const
{
	if (Name.empty())
		throw InvalidInput("Produs invalid. Numele produsului trebuie sa fie nevid.\n");
	const auto& retVector = Repo.GetAll();
	
	auto it = find_if(retVector.begin(), retVector.end(), [Name](Product pr)->bool {return pr.GetName() == Name;});
	if (it != retVector.end())
		return *it;

	/*for (auto& pr : retVector)
	{
		if (pr.GetName() == Name)
			return pr;
	}*/
	string s = "Nu exista " + Name + ". Ne pare rau!\n";
	throw NoProductWithName(s.c_str());
}

const VectorDinamic<Product> Service::FilterLess(int Price)
{
	VectorDinamic<Product> list = Repo.GetAll();
	//VectorDinamic<Product> filteredList(list.size());
	auto it = remove_if(list.begin(), list.end(), [Price](Product pr) ->bool {return pr.GetPrice() >= Price;});
	
	list.resize(distance(list.begin(), it));

	if (list.size() == 0)
		throw NoProductWithPrice("Nu exista niciun produs cu pret mai mic decat cel dat!\n");
	return list;
}


const VectorDinamic<Product> Service::FilterPrice(const int& Price) const
{
	const VectorDinamic<Product>& list = Repo.GetAll();
	VectorDinamic<Product> filteredList(list.size());
	auto it = copy_if(list.begin(), list.end(), filteredList.begin(), [Price](Product pr) ->bool {return pr.GetPrice() == Price;});
	//for (const auto& el : list)
	//	if (el.GetPrice() == Price)
	//		filteredList.push_back(el);
	filteredList.resize(distance(filteredList.begin(), it));
	return filteredList;
}
const VectorDinamic<Product> Service::FilterName(const string& Name) const
{
	const VectorDinamic<Product>& list = Repo.GetAll();
	VectorDinamic<Product> filteredList(list.size());
	auto it = copy_if(list.begin(), list.end(), filteredList.begin(), [Name](Product pr) ->bool {return pr.GetName() == Name;});
	/*for (const auto& el : list)
		if (el.GetName() == Name)
			filteredList.push_back(el);*/
	filteredList.resize(distance(filteredList.begin(), it));
	return filteredList;
}
const VectorDinamic<Product> Service::FilterProducer(const string& Producer) const
{
	const VectorDinamic<Product>& list = Repo.GetAll();
	VectorDinamic<Product> filteredList(list.size());
	auto it = copy_if(list.begin(), list.end(), filteredList.begin(), [Producer](Product pr) ->bool {return pr.GetProducer() == Producer;});
	/*for (const auto& el : list)
		if (el.GetProducer() == Producer)
			filteredList.push_back(el);*/
	filteredList.resize(distance(filteredList.begin(), it));
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
		throw InvalidSortType("Tip de sortare invalid.\n");
	auto compFunc = GetCompFunc(SortType);
	Repo.Sort(compFunc);
}



void Service::GenerateCart(int NoProducts)
{
	Cart = ShoppingCart(Repo, NoProducts);
}

void Service::Undo()
{
	if (UndoList.empty())
		throw NoUndoOperation("Nu se poate efectua undo!\n");

	unique_ptr<ActiuneUndo> a = move(UndoList.back());
	UndoList.pop_back();
	a->doUndo();
}

void __TestUndoServ()
{
	Repository repo;
	Service service(repo);
	service.AddSome();

	service.Add("KIWI", "Fructe", "Greece", 100);
	Product pr = service.Find("KIWI");
	service.Update(pr.GetId(), pr.GetName(), pr.GetType(), pr.GetProducer(), 10);
	
	assert(service.Find("KIWI").GetPrice() == 10);
	
	service.Undo();
	assert(service.Find("KIWI").GetPrice() == 100);
	service.Remove(pr.GetId());
	assert(service.GetList().size() == 4);
	service.Undo();
	assert(service.GetList().size() == 5);
	service.Undo();
	assert(service.GetList().size() == 4);
	service.Undo();
	assert(service.GetList().size() == 3);
	service.Undo();
	assert(service.GetList().size() == 2);
	service.Undo();
	assert(service.GetList().size() == 1);
	service.Undo();
	assert(service.GetList().size() == 0);
	try
	{
		service.Undo();
		assert(false);
	}
	catch (NoUndoOperation e)
	{
		assert(true);
	}
}


void __TestAdd()
{
	Repository repo;
	Service service(repo);

	service.Add("Portocale", "Fructe", "Italy", 100);
	VectorDinamic<Product> retVector = repo.GetAll();
	assert(retVector.size() == 1);
	
	try
	{
		service.Add("", "Fructe", "Italy", 101);
		assert(false);
	} 
	catch(InvalidInput e)
	{
		string s = "Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n";
		assert(s == e.what());
	}

	try
	{
		service.Add("Ana", "Fructe", "Italy", -100);
		assert(false);
	}
	catch (InvalidInput e)
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
	catch (NoProductWithId e)
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
	catch (NoProductWithId e)
	{
		string s = "Nu exista un produs cu acest ID.\n";
		assert(e.what() == s);
	}

	try {
		service.Update(id, "", "Fructe", "Italy", 10);
		assert(false);
	}
	catch (InvalidInput e)
	{
		string s = "Produs invalid. Numele produsului, Tipul si Producatorul trebuie sa fie nevide.\n";
		assert(e.what() == s);
	}

	try {
		service.Update(id, "Portocale", "Fructe", "Italy", -1);
		assert(false);
	}
	catch (InvalidInput e)
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
	catch (NoProductWithName e)
	{
		string s = "Nu exista Mere. Ne pare rau!\n";
		assert(e.what() == s);
	}

	try {
		service.Find("");
		assert(false);
	}
	catch (InvalidInput e)
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
	catch (InvalidSortType e)
	{
		assert(true);
	}
}
void __TestCart()
{
	Repository repo;
	Service service(repo);
	service.AddSome();
	service.GenerateCart(3);
	assert(service.Cart.GetAll().size() == 3);
}
void __TestFilterLess()
{
	Repository repo;
	Service service(repo);

	service.AddSome();
	service.AddSome();

	auto v = service.FilterLess(4);
	assert(v.size() == 4);
	try
	{
		service.FilterLess(0);
		assert(false);
	}
	catch(NoProductWithPrice e)
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
	__TestCart();
	__TestFilterLess();
	__TestUndoServ();

	assert(!_CrtDumpMemoryLeaks());
}