#include "lastEditDb.h"

void initLastEditList(struct LastEditList *list, int initSize) {
    struct FileEditEntry *items = malloc(sizeof(struct FileEditEntry) * initSize);
    list->size = initSize;
    list->length = 0;
    list->items = items;
}

void expandLastEditList(struct LastEditList *list) {
    struct FileEditEntry *items = malloc(sizeof(struct FileEditEntry) * list->size * 2);
    for (int i = 0; i < list->length; ++i) {
        items[i] = list->items[i];
    }
    free(list->items);
    list->items = items;
    list->size *= 2;
}

void addLastEditEntry(struct LastEditList *list, struct FileEditEntry item) {
    if (list->length == list->size) {
        expandLastEditList(list);
    }
    list->items[list->length++] = item;
}

void saveEditList(struct LastEditList *list, String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "wb");
    fwrite(&list->size, 1, sizeof(int), file);
    fwrite(&list->length, 1, sizeof(int), file);
    fwrite(list->items, list->length, sizeof(struct FileEditEntry), file);
    fclose(file);

}

struct LastEditList *getLastEditList(String path, String filename) {
    int size = 0;
    struct LastEditList *list = malloc(sizeof(struct LastEditList));
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "rb");
    fread(&size, 1, sizeof(int), file);
    initLastEditList(list, size ? size : 20);
    fread(&list->length, 1, sizeof(int), file);
    fread(list->items, list->length, sizeof(struct FileEditEntry), file);
    fclose(file);

    return list;
}

void clearLastEditDb() {
    deleteFile(DB_LAST_EDIT_PATH, DB_LAST_EDIT_DB_NAME);
}

