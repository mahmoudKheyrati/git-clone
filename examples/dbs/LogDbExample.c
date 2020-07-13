#include "LogDbExample.h"

String str(){
    return "1735aedf2f9d92d73d2c805d8c2d924a";
}
void writeToLogListExample() {

    struct LogList *list = malloc(sizeof(struct LogList));
    initLogList(list, 20);
//// write to db
    String id = str();
    String date = getDate();

    struct LogEntry entry = {.id=id,.title="firstCommit",.description="something else",.__commitPath="path/to/commit",.__commit_filename="commit filename"};
    struct LogEntry entry2 = {.id=id,.title="secondCommit",.description="something else",.__commitPath="path/to/commit",.__commit_filename="commit filename"};
    struct LogEntry entry3 = {.id=id,.title="thirdCommit",.description="something else",.__commitPath="path/to/commit",.__commit_filename="commit filename"};
    strcpy(entry.date,date);
    strcpy(entry2.date,date);
    strcpy(entry3.date,date);


    addLogEntry(list, entry);
    addLogEntry(list, entry2);
    addLogEntry(list, entry3);

    String path[2] = {"dbs", "logDb"};
    makeDirectories(path, 2);
    saveLogList(list, "./dbs/logDb", "logDb.txt");

}

void readFromLogDbExample() {

    //read from db
    struct LogList *list2 = getLogList("./dbs/logDb", "logDb.txt");
    for (int i = 0; i < list2->length; ++i) {
        struct LogEntry current = list2->items[i];
        print("%s %s %s %s %s %s\n", current.id, current.title, current.description, current.date,current.__commitPath,current.__commit_filename);
    }
}




