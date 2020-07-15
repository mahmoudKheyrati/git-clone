#pragma once

#include "../core/Core.h"
#include "StringDiffChecker.h"


int ** createLookupTable(String firstString , String secondString);

struct DifferenceList* parsLookUpTable(int ** list , String firstString, String secondString, long int m , long  int n);