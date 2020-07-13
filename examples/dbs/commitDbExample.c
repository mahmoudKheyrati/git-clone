#include "commitDbExample.h"


void writeToCommitListExample() {

    struct CommitList *list = malloc(sizeof(struct CommitList));
    initCommitList(list, 20);
//// write to db
    String id = "1735aedf2f9d92d73d2c805d8c2d924a";
    String date = getDate();

    struct CommitFileEntry entry= {.id=id,.path="path/to/changedFile",.filename="changedFile1.txt",.status=ADD_NEW_FILE};
    struct CommitFileEntry entry2= {.id=id,.path="path/to/changedFile",.filename="changedFile2.txt",.status=REMOVED_FILE};
    struct CommitFileEntry entry3= {.id=id,.path="path/to/changedFile",.filename="changedFile3.txt",.status=CHANGED_FILE};
    strcpy(entry.date,date);
    strcpy(entry2.date,date);
    strcpy(entry3.date,date);


    addCommitFileEntry(list, entry);
    addCommitFileEntry(list, entry2);
    addCommitFileEntry(list, entry3);

    String path[2] = {"dbs", "commitDb"};
    makeDirectories(path, 2);
    saveCommitList(list, "./dbs/commitDb", "commitDb.txt");

}

void readFromCommitDbExample() {

    //read from db
    struct CommitList *list2 = getCommitList("./dbs/commitDb", "commitDb.txt");
    for (int i = 0; i < list2->length; ++i) {
        struct CommitFileEntry current = list2->items[i];
        print("%s %s %s %s %i\n", current.id, current.path,current.filename,current.date, current.status);
    }
}




