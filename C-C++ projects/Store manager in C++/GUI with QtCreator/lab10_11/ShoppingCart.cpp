#include "ShoppingCart.h"

void ShoppingCart::VerifyIntegrity()
{
	const auto& retVector = Repo.GetAll();
	vector<Product> actualList;

	for (auto el : List)
	{
		string name = el.GetName();
		auto it = find_if(retVector.begin(), retVector.end(), [name](Product pr)->bool {return pr.GetName() == name;});
		
		if (it != retVector.end())
		{
			actualList.push_back(el);
		}
	}
	List = actualList;
}
void ShoppingCart::Add(const string Name)
{
	const auto& retVector = Repo.GetAll();

	auto it = find_if(retVector.begin(), retVector.end(), [Name](Product pr)->bool {return pr.GetName() == Name;});
	if (it != retVector.end())
	{
		Product pr = *it;
		List.push_back(pr);
	}
	else
		throw NoProductWithName("Nu exista un produs cu acest nume!\n");
    notify();
}
void ShoppingCart::Empty()
{
	List.clear();
    notify();
}
ShoppingCart::ShoppingCart(const Repository& Repo, int NoOfProducts) : Repo {Repo}
{
	const auto& retVector = Repo.GetAll();
	if (retVector.size() == 0)
		throw EmptyList("Nu exista niciun element in lista.\n");
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand((unsigned int) seed);
	
	while (NoOfProducts--)
	{
		int randomNumber = rand() % retVector.size();
		Product pr = retVector[randomNumber];
		List.push_back(pr);
	}
    notify();
}
void ShoppingCart::Export(const string NameOfFile)
{
	VerifyIntegrity();
    ofstream fout("D:\\Oop\\lab10_11\\" + NameOfFile);
	if (!fout.is_open())
		throw CorruptedFile("Nu se poate scrie in fisier!\n");
	for (const auto& el : List)
	{
		fout << el.GetId() << "," << el.GetName() << "," << el.GetPrice() 
			 << "," << el.GetProducer() << "," << el.GetType() << "\n";
	}
	fout.close();
}
const vector<Product>& ShoppingCart::GetAll()
{
	VerifyIntegrity();
	return List;
}
int ShoppingCart::GetTotal()
{
	VerifyIntegrity();
	int totalSum = 0;

	for (auto el : List)
	{
		totalSum += el.GetPrice();
	}
	return totalSum;
}


void __TestCreateShoppingCart()
{
	Repository repo;
	try
	{
		ShoppingCart spc3 = ShoppingCart(repo, 10);
		assert(false);
	}
	catch (EmptyList e)
	{
		assert(true);
	}

	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);
	assert(spc.GetAll().size() == 0);

	ShoppingCart spc2 = ShoppingCart(repo, 10);
	
	auto a = ShoppingCart(repo);
	a = spc2;
	assert(a.GetAll().size() == 10);

	const auto& retVector = spc2.GetAll();
	assert(retVector.size() == 10);
	auto first = retVector[0];
	for (const auto& el : retVector)
		if (el.GetName() != first.GetName())
			return;
}
void __TestAddCart()
{
	Repository repo;
	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);

	spc.Add("Mere");
	assert(spc.GetAll().size() == 1);
	spc.Add("Portocale");
	assert(spc.GetAll().size() == 2);

	try
	{
		spc.Add("mmmere");
	}
	catch (NoProductWithName e)
	{
		assert(true);
	}
	assert(spc.GetAll().size() == 2);
}
void __TestVerifyIntegrity()
{
	Repository repo;
	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);
	spc.Add(repo.GetAll()[0].GetName());
	assert(spc.GetAll().size() == 1);
	repo.Delete(repo.GetAll()[0]);
	assert(spc.GetAll().size() == 0);
}
void __TestEmpty()
{
	Repository repo;
	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);

	spc.Add("Mere");
	spc.Add("Portocale");

	spc.Empty();
	assert(spc.GetAll().size() == 0);
}
void __TestExport()
{
	Repository repo;
	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);

	spc.Add("Mere");
	spc.Add("Portocale");
	spc.Add("Portocale");

	spc.Export("__testExport.txt");
	ifstream fin("__testExport.txt");
	int k = 0;
	string s;
	while (!fin.eof())
	{
		getline(fin, s);
		k++;
	}
	fin.close();
	assert(k == 4);
	remove("__testExport.txt");

	try
	{
		spc.Export("immutable");
		assert(false);
	}
	catch (CorruptedFile e)
	{
		assert(true);
	}
}
void __TestGetTotal()
{
	Repository repo;
	repo.Insert(Product("Portocale", "Fructe", 5, "Italia"));
	repo.Insert(Product("Mere", "Fructe", 3, "Italia"));
	repo.Insert(Product("Rosi", "Legume", 4, "Grecia"));
	repo.Insert(Product("Castraveti", "Legume", 3, "Romania"));

	ShoppingCart spc = ShoppingCart(repo);

	spc.Add("Mere");
	spc.Add("Portocale");
	spc.Add("Portocale");

	assert(spc.GetTotal() == 13);

	repo.Delete(repo.GetAll()[0]);
	assert(spc.GetTotal() == 3);
}


void TestShoppingCart()
{
	__TestCreateShoppingCart();
	__TestAddCart();
	__TestVerifyIntegrity();
	__TestEmpty();
	__TestExport();
	__TestGetTotal();
	assert(!_CrtDumpMemoryLeaks());
}
