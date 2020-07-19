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
    list->size *= 2;
}

void addCommitFileEntry(struct CommitList *list, struct CommitFileEntry item) {
    if (list->length == list->size) {
        expandCommitList(list);
    }
    list->items[list->length++] = item;
}

void saveCommitList(struct CommitList *list, String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "wb");
    fwrite(&list->size, 1, sizeof(int), file);
    fwrite(&list->length, 1, sizeof(int), file);
    fwrite(list->items, list->length, sizeof(struct CommitFileEntry), file);
    fclose(file);

}

struct CommitList *getCommitList(String path, String filename) {
    int size = 0;
    struct CommitList *list = malloc(sizeof(struct CommitList));
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "rb");
    fread(&size, 1, sizeof(int), file);
    initCommitList(list, size ? size : 20);
    fread(&list->length, 1, sizeof(int), file);
    fread(list->items, list->length, sizeof(struct CommitFileEntry), file);
    fclose(file);

    return list;
}




