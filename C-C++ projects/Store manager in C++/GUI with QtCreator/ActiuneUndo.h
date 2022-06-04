#pragma once
#include "common.h"
#include "product.h"
#include "repository.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};
};

// polimorfism
class UndoAdauga : public ActiuneUndo
{
public:
	Product p;
	Repository& Repo;

	UndoAdauga(Repository& Repo, Product p) :Repo{ Repo }, p{ p } {};

	void doUndo() override
	{
		Repo.Delete(p);
	}

	~UndoAdauga() override 
	{

	};
};
class UndoSterge : public ActiuneUndo
{
public:
	Product p;
	Repository& Repo;

	UndoSterge(Repository& Repo, Product p) :Repo{ Repo }, p{ p } {};

	void doUndo() override
	{
		Repo.Insert(p);
	}

	//~UndoSterge() override {};
};
class UndoModifica : public ActiuneUndo
{
public:
	Product p;
	Repository& Repo;

	UndoModifica(Repository& Repo, Product p) :Repo{ Repo }, p{ p } {};

	void doUndo() override
	{
		Repo.Delete(p);
		Repo.Insert(p);
	}

	//~UndoModifica() override {};
};

void TestClassesUndo();