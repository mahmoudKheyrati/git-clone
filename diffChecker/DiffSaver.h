#pragma once

#include "../core/Core.h"
#include "StringDiffChecker.h"

void diffSaver(struct DifferenceList * list, String path , String filename);

struct DifferenceList* diffReader(String path, String filename);