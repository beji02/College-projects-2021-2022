#include "product.h"

int Product::NewId = 0;


void __TestCreateProduct()
{
	Product product("Portocale", "Fruct", 5, "Italy");
	assert(product.GetId() == 0);
	assert(product.GetName() == "Portocale");
	assert(product.GetType() == "Fruct");
	assert(product.GetPrice() == 5);
	assert(product.GetProducer() == "Italy");

	product = Product(1, "Portocale", "Fruct", 5, "Italy");
	assert(product.GetId() == 1);
	assert(product.GetName() == "Portocale");
	assert(product.GetType() == "Fruct");
	assert(product.GetPrice() == 5);
	assert(product.GetProducer() == "Italy");
}
void __TestEqual()
{
	Product product("Portocale", "Fruct", 5, "Italy");
	Product product2("Portocale", "Fruct", 5, "Italy");
	assert(!(product == product2));
	assert(product == product);
}

void TestProduct()
{
	__TestCreateProduct();
	__TestEqual();
	_CrtDumpMemoryLeaks();
}