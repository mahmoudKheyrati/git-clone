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

void addSelectFileEntry(struct SelectedList *list, struct FileSelectEntry item);

void expandSelectedList(struct SelectedList *list);
void initSelectedList(struct SelectedList *list, int initSize) ;

void saveSelectList(struct SelectedList* list, String path, String filename);
struct SelectedList* getSelectedList(String path, String filename);

void clearSelectedDb();


