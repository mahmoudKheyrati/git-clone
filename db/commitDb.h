#pragma once


#include "../core/Core.h"

enum COMMIT_FILE_STATUS {
    REMOVED_FILE = -1, CHANGED_FILE , ADD_NEW_FILE
};

//struct CommitFileEntry {
//    String id;
//    String fileAddress;
//    char date[30];
//    short int status;
//};
struct CommitFileEntry {
    char id[40];
    char fileAddress[200];
    char date[30];
    short int status;
};

struct CommitList {
    long size;
    long length;
    struct CommitFileEntry *items;
};

struct CommitList* getCommitList(String path, String filename);
void saveCommitList(struct CommitList* list, String path, String filename);
void addCommitFileEntry(struct CommitList *list, struct CommitFileEntry item) ;
void initCommitList(struct CommitList *list, int initSize);
void expandCommitList(struct CommitList *list);
