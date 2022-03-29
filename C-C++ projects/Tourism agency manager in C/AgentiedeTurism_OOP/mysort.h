#pragma once
#include "oferta.h"

typedef int(*FctComparare)(ElemType* e1, ElemType* e2);

void sort_fnct(List* l, FctComparare cmp);

void testSortare2();
