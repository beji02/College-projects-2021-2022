#include "Repository.h"
#include "Libraries.h"





ElementType __CopyOffer(ElementType E)
{
	Offer off = E;
	Offer copyOff = CopyOffer(off);

	return copyOff;
}
void __DestroyOffer(ElementType E)
{
	Offer off = E;
	DestroyOffer(off);
}
ElementType __CopyList(ElementType E)
{
	DynamicArray list = E;
	DynamicArray copyList = CopyArray(list);

	return copyList;
}
void __DestroyList(ElementType E)
{
	DynamicArray list = E;
	DestroyArray(list);
}



Repository CreateRepository()
{
	Repository newRepo = (Repository)malloc(sizeof(__Repository));
	if (newRepo != NULL)
	{
		newRepo->List = CreateArray(__CopyOffer, __DestroyOffer);
		newRepo->UndoList = CreateArray(__CopyList, __DestroyList);
	}
	return newRepo;
}
void DestroyRepository(Repository Repo)
{
	DestroyArray(Repo->UndoList);
	DestroyArray(Repo->List);
	free(Repo);
}





void InsertRepository(Repository Repo, Offer Off)
{
	Insert(Repo->UndoList, Repo->List);
	Insert(Repo->List, Off);
}
int SearchRepository(Repository Repo, Offer Off)
{
	int len = GetLength(Repo->List);
	for (int i = 0; i < len; i++)
	{
		Offer off = GetElement(Repo->List, i);
		if (IsEqual(off, Off))
			return 1;
	}
	return 0;
}
void DeleteRepository(Repository Repo, Offer Off)
{
	int len = GetLength(Repo->List);
	for (int i = 0; i < len; i++)
	{
		Offer off = GetElement(Repo->List, i);
		if (IsEqual(off, Off))
		{
			Insert(Repo->UndoList, Repo->List);
			Delete(Repo->List, i);
			return;
		}
	}
}
void UpdateRepository(Repository Repo, Offer Off)
{
	Insert(Repo->UndoList, Repo->List);
	int len = GetLength(Repo->List);
	for (int i = 0; i < len; i++)
	{
		Offer off = GetElement(Repo->List, i);
		if (IsEqual(off, Off))
		{
			Delete(Repo->List, i);
			break;
		}
	}
	Insert(Repo->List, Off);
}
DynamicArray GetAllRepository(Repository Repo)
{
	return CopyArray(Repo->List);
}
int UndoRepository(Repository Repo)
{
	if (GetLength(Repo->UndoList) == 0)
		return -1;
	int pos = GetLength(Repo->UndoList) - 1;
	DynamicArray arrayFromUndo = CopyArray(GetElement(Repo->UndoList, pos));
	Delete(Repo->UndoList, pos);
	DestroyArray(Repo->List);
	Repo->List = arrayFromUndo;
	return 0;
}

void AddSome(Repository Repo)
{
	Offer off = CreateOffer(1, "citybreak", "Italia", 26, 6, 2022, 6000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(2, "citybreak", "Franta", 20, 5, 2022, 4000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(3, "citybreak", "Polonia", 14, 3, 2022, 1000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(4, "munte", "Romania", 10, 2, 2022, 1000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(5, "munte", "Austria", 1, 1, 2022, 2000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(6, "mare", "Grecia", 10, 8, 2022, 2000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(7, "mare", "Turcia", 12, 9, 2022, 3000);
	Insert(Repo->List, off);
	DestroyOffer(off);
	off = CreateOffer(8, "mare", "Turcia", 10, 9, 2021, 2000);
	Insert(Repo->List, off);
	DestroyOffer(off);
}





void __TestCreateDestroy()
{
	Repository repo = CreateRepository();
	assert(repo->List != NULL);
	assert(repo->UndoList != NULL);
	AddSome(repo);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestInsertRepository()
{
	Repository repo = CreateRepository();
	Offer off = CreateOffer(1, "", "", 1, 1, 1, 1);
	
	InsertRepository(repo, off);
	assert(GetLength(repo->List) == 1);
	assert(GetLength(repo->UndoList) == 1);
	DestroyOffer(off);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestSearchRepository()
{
	Repository repo = CreateRepository();
	Offer off = CreateOffer(1, "", "", 1, 1, 1, 1);
	Offer off2 = CreateOffer(2, "", "", 1, 1, 1, 1);

	InsertRepository(repo, off);
	assert(SearchRepository(repo, off) == 1);
	assert(SearchRepository(repo, off2) == 0);
	
	DestroyOffer(off);
	DestroyOffer(off2);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestDeleteRepository()
{
	Repository repo = CreateRepository();
	Offer off = CreateOffer(1, "", "", 1, 1, 1, 1);
	Offer off1 = CreateOffer(2, "", "", 1, 1, 1, 1);

	InsertRepository(repo, off1);
	InsertRepository(repo, off);

	DeleteRepository(repo, off);
	
	assert(GetLength(repo->List) == 1);
	assert(GetLength(repo->UndoList) == 3);

	DestroyOffer(off);
	DestroyOffer(off1);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestUpdateRepository()
{
	Repository repo = CreateRepository();
	Offer off = CreateOffer(1, "", "", 1, 1, 1, 1);
	Offer off1 = CreateOffer(1, "", "", 1, 1, 1, 1000);
	Offer off2 = CreateOffer(2, "", "", 1, 1, 1, 1000);

	InsertRepository(repo, off2);
	InsertRepository(repo, off);
	UpdateRepository(repo, off1);

	assert(GetLength(repo->List) == 2);
	assert(GetLength(repo->UndoList) == 3);

	DestroyOffer(off);
	DestroyOffer(off1);
	DestroyOffer(off2);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}
void __TestUndoRepository()
{
	Repository repo = CreateRepository();
	Offer off = CreateOffer(1, "", "", 1, 1, 1, 1);
	Offer off1 = CreateOffer(2, "", "", 1, 1, 1, 1000);

	InsertRepository(repo, off);
	InsertRepository(repo, off1);

	assert(GetLength(repo->UndoList) == 2);
	assert(GetLength(repo->List) == 2);
	assert(UndoRepository(repo) == 0);
	assert(GetLength(repo->UndoList) == 1);
	assert(GetLength(repo->List) == 1);
	assert(UndoRepository(repo) == 0);
	assert(GetLength(repo->UndoList) == 0);
	assert(GetLength(repo->List) == 0);
	assert(UndoRepository(repo) == -1);

	DestroyOffer(off);
	DestroyOffer(off1);
	DestroyRepository(repo);
	assert(!_CrtDumpMemoryLeaks());
}


void __TestRepository()
{
	__TestCreateDestroy();
	__TestInsertRepository();
	__TestSearchRepository();
	__TestDeleteRepository();
	__TestUpdateRepository();
	__TestUndoRepository();
}
