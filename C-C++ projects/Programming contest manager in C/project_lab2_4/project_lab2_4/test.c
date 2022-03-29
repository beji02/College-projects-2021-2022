#include "test.h"
#include "repository.h"
#include "service.h"
#include "stdio.h"
#include "DynamicArray.h"
#include "domain.h"

void runTests(void)
{
	TestDomain();
	printf("DomainTest passed\n");

	TestDynamicArray();
	printf("ArrayTest passed\n");
	
	TestRepository();
	printf("RepositoryTest passed\n");
	
	TestService();
	printf("ServiceTest passed\n");
	printf("\n");
}