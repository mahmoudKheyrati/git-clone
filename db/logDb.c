#include "logDb.h"


void initLogList(struct LogList *list, int initSize) {
    struct LogEntry *items = malloc(sizeof(struct LogEntry) * initSize);
    list->size = initSize;
    list->length = 0;
    list->items = items;
}

void expandLogList(struct LogList *list) {
    struct LogEntry *items = malloc(sizeof(struct LogEntry) * list->size * 2);
    for (int i = 0; i < list->length; ++i) {
        items[i] = list->items[i];
    }
    free(list->items);
    list->items = items;
    list->size *= 2;
}

void addLogEntry(struct LogList *list, struct LogEntry item) {
    if (list->length == list->size) {
        expandLogList(list);
    }
    list->items[list->length++] = item;
}

void saveLogList(struct LogList *list, String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "wb");
    fwrite(&list->size, 1, sizeof(int), file);
    fwrite(&list->length, 1, sizeof(int), file);
    fwrite(list->items, list->length, sizeof(struct LogEntry), file);
    fclose(file);

}

struct LogList *getLogList(String path, String filename) {
    int size = 0;
    struct LogList *list = malloc(sizeof(struct LogList));
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "rb");
    fread(&size, 1, sizeof(int), file);
    initLogList(list, size ? size : 20);
    fread(&list->length, 1, sizeof(int), file);
    fread(list->items, list->length, sizeof(struct LogEntry), file);
    fclose(file);

    return list;
}



