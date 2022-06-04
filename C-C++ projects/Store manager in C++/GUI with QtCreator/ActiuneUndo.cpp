#include "ActiuneUndo.h"

void __TestClassUndoAdauga()
{
	Product p("Portocale", "Fructe", 10, "Grecia");
	Repository repo;
	repo.Insert(p);
	assert(repo.GetAll().size() == 1);
	unique_ptr<ActiuneUndo> a = make_unique<UndoAdauga>(repo, p);
	a->doUndo();
	assert(repo.GetAll().size() == 0);
}
void __TestClassUndoSterge()
{
	Product p("Portocale", "Fructe", 10, "Grecia");
	Repository repo;
	repo.Insert(p);
	assert(repo.GetAll().size() == 1);
	unique_ptr<ActiuneUndo> a = make_unique<UndoSterge>(repo, p);
	repo.Delete(p);
	assert(repo.GetAll().size() == 0);
	a->doUndo();
	assert(repo.GetAll().size() == 1);
}
void __TestClassUndoModifica()
{
	Product p("Portocale", "Fructe", 10, "Grecia");
	Repository repo;
	repo.Insert(p);
	assert(repo.GetAll().size() == 1);
	unique_ptr<ActiuneUndo> a = make_unique<UndoModifica>(repo, p);
	repo.Delete(p);
	Product p2(p.GetId(), "Mere", "Fructe", 10, "Grecia");
	repo.Insert(p2);
	assert(repo.GetAll().size() == 1 && repo.GetAll()[0].GetName() == "Mere");
	a->doUndo();
	assert(repo.GetAll().size() == 1 && repo.GetAll()[0].GetName() == "Portocale");
}


void TestClassesUndo()
{
	__TestClassUndoAdauga();
	__TestClassUndoSterge();
	__TestClassUndoModifica();
	assert(!_CrtDumpMemoryLeaks());
}
