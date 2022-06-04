#pragma once
#include "common.h"

template<typename TElem>
class IteratorVectorDinamic;

template<typename TElem>
class VectorDinamic {
private:
	int Size;
	int Count;
	TElem* Elements;

	/*realoca memorie in cazul in care s-au ocupat toate pozitiile*/
	void redim() {
		this->Size *= 2;
		TElem* newElements = new TElem[this->Size];
		for (int i = 0; i < this->Count; i++)
			newElements[i] = this->Elements[i];
		delete[] this->Elements;
		this->Elements = newElements;
	}

public:
	/*constructor*/
	VectorDinamic() {
		this->Size = 1;
		this->Count = 0;
		this->Elements = new TElem[1];
	}
	/*destructor*/
	~VectorDinamic() {
		delete[] this->Elements;
	}

	/*copy constructor*/
	VectorDinamic(const VectorDinamic& Other)
	{
		this->Size = Other.Size;
		this->Count = 0;
		this->Elements = new TElem[Size];

		for (int i = 0; i < Other.Count; i++)
			push_back(Other.Elements[i]);
	}
	
	/*assign operation*/
	VectorDinamic& operator=(const VectorDinamic& Other)
	{
		if (this == &Other) {
			return *this;//avoid self asignment problems
		}
		delete[]Elements;
		this->Size = Other.Size;
		this->Count = 0;
		this->Elements = new TElem[Size];
		for (int i = 0; i < Other.Count; i++)
			push_back(Other.Elements[i]);
		return *this;
	}

	/*returneaza numarul de elemente din vector*/
	int size() const {
		return this->Count;
	}
	/*returneaza true daca nu exista elemente in vector, altfel false*/
	bool empty() const
	{
		return Count == 0;
	}
	/*adauga un element la sfarsitul vectorului*/
	void push_back(TElem e) {
		if (this->Count == this->Size)
			this->redim();
		this->Elements[this->Count++] = e;
	}

	TElem& get(int Index)
	{
		return (*this)[Index];
	}
	void add(TElem newEl)
	{
		push_back(newEl);
	}

	/*defineste operatia de accesare prin indice*/
	TElem& operator[](int Index)
	{
		return Elements[Index];
	}
	const TElem& operator[](int Index) const 
	{
		return Elements[Index];
	}
	/*sterge un element indicat de iterator*/
	void erase(IteratorVectorDinamic<TElem> it)
	{
		for (int i = it.Position; i < Count-1; i++)
		{
			Elements[i] = Elements[i + 1];
		}
		Count--;
	}

	friend class IteratorVectorDinamic<TElem>;
	/*returneaza un iterator spre primul element din vector*/
	IteratorVectorDinamic<TElem> begin() const {
		return IteratorVectorDinamic<TElem>(*this);
	}
	/*returneaza un iterator spre pozitia de dupa ultimul element din vector*/
	IteratorVectorDinamic<TElem> end() const {
		return IteratorVectorDinamic<TElem>(*this, Count);
	}
};

void TestVectorDinamic();

template<typename TElem>
class IteratorVectorDinamic {
private:
	const VectorDinamic<TElem>& VectorRef;
	int Position = 0;
public:
	friend class VectorDinamic<TElem>;

	/*constructor*/
	IteratorVectorDinamic(const VectorDinamic<TElem>& Vector) : VectorRef(Vector) {}
	IteratorVectorDinamic(const VectorDinamic<TElem>& Vector, int Position) : VectorRef(Vector), Position(Position) {}

	/*defineste operatia de preluare a elementului spre care arata iteratorul*/
	TElem& operator*()
	{
		return VectorRef.Elements[Position];
	}
	/*defineste operatia de a trece la urmatorul element a iteratorului*/
	IteratorVectorDinamic& operator++()
	{
		Position++;
		return *this;
	}
	/*verifica daca 2 iteratori sunt egali*/
	bool operator==(const IteratorVectorDinamic& otherIterator)
	{
		return  this->Position == otherIterator.Position;
	}
	/*verifica daca 2 iteratori sunt diferiti*/
	bool operator!=(const IteratorVectorDinamic& otherIterator)
	{
		return !(*this == otherIterator);
	}

};
