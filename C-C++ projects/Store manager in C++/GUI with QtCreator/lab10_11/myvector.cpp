#include "common.h"
//#include "myvector.h"
#include <exception>
#include "product.h"
#include "Pet.h"

#undef VectorDinamic

using namespace std;

//void VectorDinamic::redim() {
//	this->Size *= 2;
//	TElem* newElements = new TElem[this->Size];
//	for (int i = 0; i < this->Count; i++)
//		newElements[i] = this->Elements[i];
//	delete[] this->Elements;
//	this->Elements = newElements;
//}
//VectorDinamic::VectorDinamic() {
//	this->Size = 1;
//	this->Count = 0;
//	this->Elements = new TElem[1];
//}
//VectorDinamic::~VectorDinamic() {
//	delete[] this->Elements;
//}
//int VectorDinamic::size() const {
//	return this->Count;
//}
//void VectorDinamic::push_back(TElem e) {
//	if (this->Count == this->Size)
//		this->redim();
//	this->Elements[this->Count++] = e;
//}
//TElem& VectorDinamic::operator[](int Index)
//{
//	return Elements[Index];
//}
//void VectorDinamic::erase(IteratorVectorDinamic it)
//{
//	for (int i = it.Position; i < Count; i++)
//	{
//		Elements[i] = Elements[i + 1];
//	}
//	Count--;
//}
//
//
//
//IteratorVectorDinamic VectorDinamic::begin() {
//	return IteratorVectorDinamic(*this);
//}
//IteratorVectorDinamic VectorDinamic::end() {
//	return IteratorVectorDinamic(*this, Count);
//}
//
//IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& Vector) : VectorRef(Vector){}
//IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& Vector, int Position) : VectorRef(Vector), Position(Position){}
//
//
//TElem& IteratorVectorDinamic::operator*()
//{
//	return VectorRef.Elements[Position];
//}
//IteratorVectorDinamic& IteratorVectorDinamic::operator++()
//{
//	Position++;
//	return *this;
//}
//bool IteratorVectorDinamic::operator==(const IteratorVectorDinamic& otherIterator)
//{
//	return  this->Position == otherIterator.Position;
//}
//bool IteratorVectorDinamic::operator!=(const IteratorVectorDinamic& otherIterator)
//{
//	return !(*this == otherIterator);
//}


template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	double totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.getPrice();
	}
	Pet p{ "total","tt",totalPrice };
	v.add(p);
	return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
	for (int i = 0; i < cate; i++) {
		Pet p{ std::to_string(i) + "_type",std::to_string(i) + "_spec",i + 10.0 };
		v.add(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addPets(v, 100);
	assert(v.size() == 100);
	assert(v.get(50).getType() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(50).getType() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(50).getType() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50).getType() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addPets(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}
template <typename MyVector>
void __TestAllProf() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}





void __TestCreateVector()
{
	VectorDinamic<int> v;
	assert(v.size() == 0);
	assert(v.empty() == true);
}
void __TestPushBack()
{
	VectorDinamic<int> v;
	for (int i = 1; i <= 3; i++)
		v.push_back(i);
	assert(v.size() == 3);
}
void __TestCreateIterator()
{
	VectorDinamic<int> v;
	IteratorVectorDinamic<int> it(v);
	IteratorVectorDinamic<int> it2(v, 10);
}
void __TestOperatorsIterator()
{
	VectorDinamic<int> v;
	v = v;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	IteratorVectorDinamic<int> it(v);
	assert(*it == 1);
	++it;
	assert(*it == 2);
	IteratorVectorDinamic<int> it2(v, 2);
	assert(it != it2);
	++it;
	assert(it == it2);

}
void __TestBeginEnd()
{
	VectorDinamic<int> v;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	int k = 0;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		k++;
		assert(*it == k);
	}
	k = 0;
	for (const auto& el : v)
	{
		k++;
		assert(el == k);
	}
}
void __TestAccessVector()
{
	VectorDinamic<int> v;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	v[1] = 0;
	assert(v[1] == 0);
}
void __TestErase()
{
	VectorDinamic<int> v;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	v.erase(v.begin());
	assert(*(v.begin()) == 2);
}
void __TestVectorWithProducts()
{
	Product pr = Product("Mere", "Fruct", 5, "Italy");
	VectorDinamic<Product> v;
	for (int i = 1; i <= 2; i++)
		v.push_back(pr);
	v.erase(v.begin());
	assert((*v.begin()).GetPrice() == 5);

	
	VectorDinamic<Product>& a = v;
	for (const auto& el : a)
	{
		assert(el.GetPrice() == 5);
	}
	
	VectorDinamic<Product> a2 = v;
	for (const auto& el : a2)
	{
		assert(el.GetPrice() == 5);
	}

	VectorDinamic<Product> a3 = a;
	for (const auto& el : a3)
	{
		assert(el.GetPrice() == 5);
	}

	const VectorDinamic<Product>& b = v;
	for (const auto& el : b)
	{
		assert(el.GetPrice() == 5);
	}
}


void TestVectorDinamic()
{
	__TestCreateVector();
	__TestPushBack();
	__TestCreateIterator();
	__TestOperatorsIterator();
	__TestBeginEnd();
	__TestAccessVector();
	__TestErase();
	__TestVectorWithProducts();
	__TestAllProf<VectorDinamic<Pet>>();
	assert(!_CrtDumpMemoryLeaks());
}
