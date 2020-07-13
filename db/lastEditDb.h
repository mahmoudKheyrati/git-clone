#pragma once

#include "../core/Core.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

enum FileLastEditStatus{FILE_AVAILABLE, FILE_REMOVED};
struct FileEditEntry{
    char path[1000];
    char filename[1000];
    char lastEdit[1000];
    short int status;
};

struct LastEditList{
    long size;
    long length;
    struct FileEditEntry* items;
};

void addLastEditEntry(struct LastEditList *list, struct FileEditEntry item);

void expandLastEditList(struct LastEditList *list);
void initLastEditList(struct LastEditList *list, int initSize) ;

void saveEditList(struct LastEditList* list, String path, String filename);
struct LastEditList* getLastEditList(String path, String filename);

