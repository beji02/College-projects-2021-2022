#pragma once
#include "common.h"
#include "observer.h"
#include "product.h"
#include "repository.h"

class ShoppingCart: public Observable
{
private:
	const Repository& Repo;
	vector<Product> List;

	/*verifica daca produsele din cos mai exista, in caz contrar le scoate*/
	void VerifyIntegrity();
public:
	/*constructorul principal*/
	ShoppingCart(const Repository& Repo) : Repo{ Repo } {};
	/*constructorul care da optiunea de a genera un nr de produse aleatoare*/
	ShoppingCart(const Repository& Repo, int NoOfProducts);

	/*copierea unui Cart*/
	const ShoppingCart& operator=(const ShoppingCart& Cart)
	{
		List = Cart.List;
        notify();
		return *this;
	}

	/*adauga un produs dupa nume in cos*/
	void Add(const string Name);
	/*elibereaza cosul*/
	void Empty();
	/*exporta sub numele dat produsele din cos*/
	void Export(const string NameOfFile);
	/*returneaza lista de produse din cos*/
	const vector<Product>& GetAll();
	/*calculeaza totalul produselor*/
	int GetTotal();
};

void TestShoppingCart();
