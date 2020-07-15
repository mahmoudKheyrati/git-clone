#pragma once

#include "../core/Core.h"
#include "../db/db.h"
#include "../diffChecker/diffChecker.h"

struct LastEditList *  getChangedFiles();
struct LastEditList* trackFiles(String * edited , String * added , String * deleted , int *editSize, int *addSize, int *deleteSize );
short int getChangedFileStatus(String filename);
//void getChangedFiles();