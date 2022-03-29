#pragma once
#include "repository.h"
#include "product.h"

class Service
{
private:
	Repository& Repo;
public:
	/*initializeaza un service*/
	Service(Repository& Repo) :Repo{ Repo } {}
	/*adauga un nou produs*/
	void Add(const string& Name, const string& Type, const string& Producer, const int& Price);
	/*returneaza lista de produse*/
	const vector<Product>& GetList() const;
	/*adauga cateva elemente in lista*/
	void AddSome();
	/*sterge un produs dupa id*/
	void Remove(const int& Id);
	/*actualizeaza un produs*/
	void Update(const int& Id, const string& Name, const string& Type, const string& Producer, const int& Price);
	/*cauta un produs*/
	const Product& Find(const string& Name) const;
	/*filtreaza dupa pret lista*/
	const vector<Product> FilterPrice(const int& Price) const;
	/*filtreaza dupa nume lista*/
	const vector<Product> FilterName(const string& Name) const;
	/*filtreaza dupa producator lista*/
	const vector<Product> FilterProducer(const string& Producer) const;
	/*sorteaza lista dupa un tipar*/
	void SortList(const int& SortType);
};

void TestService();