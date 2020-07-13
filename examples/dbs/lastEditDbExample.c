#include "lastEditDbExample.h"

void writeToEditListExample(){

    struct LastEditList *list = malloc(sizeof(struct LastEditList));
    initLastEditList(list, 20);
//// write to db
    struct FileEditEntry entry = {.filename="file1.txt", .path="./path/to/file",.lastEdit="this is all about time",.status=FILE_AVAILABLE};
    struct FileEditEntry entry2 = {.filename="file2.txt", .path="./path/to/file",.status=FILE_AVAILABLE};
    struct FileEditEntry entry3 = {.filename="file3.txt", .path="./path/to/file",.status=FILE_AVAILABLE};
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
        print("%s %s %s %i\n",current.filename, current.path, current.lastEdit, current.status);
    }
}




