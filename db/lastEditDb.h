#pragma once

#include "../core/Core.h"


#define MAX_FILE_ENTRY_ITEM_LEN 200

enum FileLastEditStatus{FILE_AVAILABLE, FILE_REMOVED};
struct FileEditEntry{
    char path[MAX_FILE_ENTRY_ITEM_LEN];
    char filename[MAX_FILE_ENTRY_ITEM_LEN];
    char lastEdit[MAX_FILE_ENTRY_ITEM_LEN];
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

