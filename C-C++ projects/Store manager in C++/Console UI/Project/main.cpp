#include "product.h"
#include "repository.h"
#include "console.h"
#include "service.h"

void TestAll()
{
	TestProduct();
	TestRepository();
	TestService();
}

void RunApp()
{
	Repository repo;
	Service serv(repo);
	serv.AddSome();
	Console console(serv);

	console.ShowUI();
}

int main()
{
	TestAll();
	RunApp();

	return 0;
}