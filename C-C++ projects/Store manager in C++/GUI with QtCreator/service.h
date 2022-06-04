#pragma once
#include "repository.h"
#include "product.h"
#include "ShoppingCart.h"
#include "ActiuneUndo.h"

class Service
{
private:
	Repository& Repo;
	vector<unique_ptr<ActiuneUndo>> UndoList;
public:
	ShoppingCart Cart;
	/*initializeaza un service*/
	Service(Repository& Repo) :Repo{ Repo }, Cart{ Repo } {};
	/*adauga un nou produs*/
	void Add(const string& Name, const string& Type, const string& Producer, const int& Price);
	/*returneaza lista de produse*/
	const VectorDinamic<Product>& GetList() const;
	/*adauga cateva elemente in lista*/
	void AddSome();
	/*sterge un produs dupa id*/
	void Remove(const int& Id);
	/*actualizeaza un produs*/
	void Update(const int& Id, const string& Name, const string& Type, const string& Producer, const int& Price);
	/*cauta un produs*/
	const Product& Find(const string& Name) const;
	/*filtreaza dupa pret lista*/
	const VectorDinamic<Product> FilterPrice(const int& Price) const;
	/*filtreaza dupa nume lista*/
	const VectorDinamic<Product> FilterName(const string& Name) const;
	/*filtreaza dupa producator lista*/
	const VectorDinamic<Product> FilterProducer(const string& Producer) const;
	/*sorteaza lista dupa un tipar*/
	void SortList(const int& SortType);
	/*genereaza un nou cart cu un numar de produse aleatorii*/
	void GenerateCart(int NoProducts);
	/*sterge toate produsele care au pretul mai mic decat cel dat*/
	const VectorDinamic<Product> FilterLess(int Price);
	/*realizeaza operatia de undo*/
	void Undo();
};

void TestService();