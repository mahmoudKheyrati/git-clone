#pragma once

#include "../core/Core.h"

#define MAX_FILE_ENTRY_ITEM_LEN 200

struct FileSelectEntry{
    char fileAddress[MAX_FILE_ENTRY_ITEM_LEN];
    short int isSelect;
};

struct SelectedList{
    long size;
    long length;
    struct FileSelectEntry* items;
};

void addLastEditEntry(struct LastEditList *list, struct FileEditEntry item);

void expandLastEditList(struct LastEditList *list);
void initLastEditList(struct LastEditList *list, int initSize) ;

void saveEditList(struct LastEditList* list, String path, String filename);
struct LastEditList* getLastEditList(String path, String filename);


