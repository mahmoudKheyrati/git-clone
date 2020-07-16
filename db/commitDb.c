#include "commitDb.h"


void initCommitList(struct CommitList *list, int initSize) {
    struct CommitFileEntry *items = malloc(sizeof(struct CommitFileEntry) * initSize);
    list->size = initSize;
    list->length = 0;
    list->items = items;
}

void expandCommitList(struct CommitList *list) {
    struct CommitFileEntry *items = malloc(sizeof(struct CommitFileEntry) * list->size * 2);
    for (int i = 0; i < list->length; ++i) {
        items[i] = list->items[i];
    }
    free(list->items);
    list->items = items;
    list->size*=2;
}

void addCommitFileEntry(struct CommitList *list, struct CommitFileEntry item) {
    if (list->length == list->size) {
        expandCommitList(list);
    }
    list->items[list->length++] = item;
}

void saveCommitList(struct CommitList* list, String path, String filename){
    String fileAddress = fileAddressMaker(path, filename);
    FILE* file = fopen(fileAddress, "wb");
    fwrite(&list->size,1 , sizeof( int),file);
    fwrite(&list->length,1 , sizeof( int),file);
    fwrite(list->items,list->length, sizeof(struct CommitFileEntry),file);
    fclose(file);

}

struct CommitList* getCommitList(String path, String filename){
    struct CommitList *list= malloc(sizeof(struct CommitList));
    initCommitList(list,20);
    String fileAddress = fileAddressMaker(path, filename);
    FILE * file = fopen(fileAddress,"rb");
    fread(&list->size,1 , sizeof( int),file);
    fread(&list->length,1 , sizeof( int),file);
//    print("%i , %i\n", list->size, list->length);

//    struct CommitFileEntry entry;
//    fread(&entry,1, sizeof(struct CommitFileEntry), file);
//    print("single item %s\n", entry.fileAddress);

    fread(list->items,list->length, sizeof(struct CommitFileEntry),file);
    fclose(file);

    return list;
}




