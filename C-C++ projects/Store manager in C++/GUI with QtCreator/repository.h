#pragma once
#include "common.h"
#include "product.h"
class Repository
{
private:
	VectorDinamic<Product> Products;
public:
	/*copieaza un repozitory*/
	Repository(const Repository& Repo) : Products{ Repo.Products } {};
	/*constructor*/
	Repository() {};
	/*insereaza un nou produs in lista*/
	void Insert(const Product& NewProduct);
	/*cauta un produs in lista (dupa id)*/
	bool Search(const Product& Pr) const;
	/*returneaza lista de produse*/
	const VectorDinamic<Product>& GetAll() const;
	/*sterge un produs din lista*/
	void Delete(const Product& Pr);
	/*sorteaza lista dupa o functie de comparare*/
	void Sort(const bool(*CompareFunc)(const Product& P1, const Product& P2));
};

void TestRepository();