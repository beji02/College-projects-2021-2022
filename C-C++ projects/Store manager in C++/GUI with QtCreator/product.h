#ifndef PRODUCT_H
#define PRODUCT_H
#include "common.h"

class Product
{
private:
	static int NewId;
	int Id;
	string Name;
	string Type;
	int Price;
	string Producer;
public:
	/*ia idul produsului*/
	const int& GetId() const
	{
		return Id;
	}
	/*ia numele produsului*/
	const string& GetName() const
	{
		return Name;
	}
	/*ia tipul produsului*/
	const string& GetType() const
	{
		return Type;
	}
	/*ia pretul produsului*/
	const int& GetPrice() const
	{
		return Price;
	}
	/*ia producatorul produsului*/
	const string& GetProducer() const
	{
		return Producer;
	}
	
	Product()
	{

	}

	Product(const Product& pr) : Id{pr.Id}, Name{pr.Name}, Type{pr.Type}, Price{pr.Price}, Producer{pr.Producer}{}

	/*creeaza un produs cu nume, tip, pret, producator*/
	Product(const string& Name, const string& Type, const int& Price, const string& Producer)
		: Id{ NewId }, Name{ Name }, Type{ Type }, Price{ Price }, Producer{ Producer } {NewId++;}
	
	/*creeaza un produs cu id, nume, tip, pret, producator*/
	Product(const int& Id, const string& Name, const string& Type, const int& Price, const string& Producer)
		: Id{ Id }, Name{ Name }, Type{ Type }, Price{ Price }, Producer{ Producer } {}

	/*defineste relatie de egalitate intre produse (cand au acelasi id)*/
	bool operator==(const Product& OtherProduct) const
	{
		return Id == OtherProduct.GetId();
	}
};

void TestProduct();
#endif
