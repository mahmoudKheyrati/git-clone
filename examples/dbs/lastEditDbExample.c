#include "lastEditDbExample.h"

void writeToEditListExample(){

    struct LastEditList *list = malloc(sizeof(struct LastEditList));
    initLastEditList(list, 20);
//// write to db
    struct FileEditEntry entry = {.fileAddress="file1.txt", .lastEdit="this is all about time",.status=FILE_ADDED};
    struct FileEditEntry entry2 = {.fileAddress="file2.txt",.status=FILE_ADDED};
    struct FileEditEntry entry3 = {.fileAddress="file3.txt",.status=FILE_ADDED};
    strcpy(entry.lastEdit,getLastModifiedOfFile("./","Hasher.jar"));
    strcpy(entry2.lastEdit,getLastModifiedOfFile("./","Hasher.jar"));
    strcpy(entry3.lastEdit,getLastModifiedOfFile("./","Hasher.jar"));

    addLastEditEntry(list, entry);
    addLastEditEntry(list, entry2);
    addLastEditEntry(list, entry3);
    String path[3]={"dbs","lastEditDb"};
    makeDirectories(path,2);
    saveEditList(list,"./dbs/lastEditDb", "editDb.txt");

}
void readFromEditDbExample(){

    //read from db
    struct LastEditList *list2 = getLastEditList("./dbs/lastEditDb", "editDb.txt");
    for (int i = 0; i < list2->length; ++i) {
        struct FileEditEntry current= list2->items[i];
        print("%s %s %i\n",current.fileAddress, current.lastEdit, current.status);
    }
}




