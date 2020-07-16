#include "selectedDb.h"


void initSelectedList(struct SelectedList *list, int initSize) {
    struct FileSelectEntry *items = malloc(sizeof(struct FileSelectEntry) * initSize);
    list->size = initSize;
    list->length = 0;
    list->items = items;
}

void expandSelectedList(struct SelectedList *list) {
    struct FileSelectEntry *items = malloc(sizeof(struct FileSelectEntry) * list->size * 2);
    for (int i = 0; i < list->length; ++i) {
        items[i] = list->items[i];
    }
    free(list->items);
    list->items = items;
    list->size*=2;
}

void addSelectFileEntry(struct SelectedList *list, struct FileSelectEntry item) {
    if (list->length == list->size -1) {
        expandSelectedList(list);
    }
    list->items[list->length++] = item;
}

void saveSelectList(struct SelectedList* list, String path, String filename){
    String fileAddress = fileAddressMaker(path, filename);
    FILE* file = fopen(fileAddress, "wb");
    fwrite(&list->size,1 , sizeof( int),file);
    fwrite(&list->length,1 , sizeof( int),file);
    fwrite(list->items,list->length, sizeof(struct FileSelectEntry),file);
    fclose(file);

}

struct SelectedList* getSelectedList(String path, String filename){
    struct SelectedList *list= malloc(sizeof(struct SelectedList));
    initSelectedList(list,20);
    String fileAddress = fileAddressMaker(path, filename);
    FILE * file = fopen(fileAddress,"rb");
    fread(&list->size,1 , sizeof( int),file);
    fread(&list->length,1 , sizeof( int),file);
//    print("%i , %i\n", list->size, list->length);

//    struct FileSelectEntry entry;
//    fread(&entry,1, sizeof(struct FileSelectEntry), file);
//    print("single item %s\n", entry.fileAddress);

    fread(list->items,list->length, sizeof(struct FileSelectEntry),file);
    fclose(file);

    return list;
}

