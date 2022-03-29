#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h> 
#include "test.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include <assert.h>


void runApp(void)
{
	DynamicArray repo = createRepository();
	Service service = createService(repo);
	Ui ui = createUi(service);

	serviceAddSome(service);

	while (1)
	{
		uiShowMenu();
		uiSelectCommand(ui);
	}

	destroyRepository(repo);
	exit(1);
}

int main(void)
{
	runTests();
	runApp();
	assert(!_CrtDumpMemoryLeaks());
}