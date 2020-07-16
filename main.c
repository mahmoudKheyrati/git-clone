#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"
#include "examples/color.h"
#include "examples/dbs/LogDbExample.h"
int main(int argc, String *argv) {
//    struct LogEntry logEntry = {};
//    strcpy(logEntry.date, getDate());
//    strcpy(logEntry.id, "commitFilename");
//    strcpy(logEntry.title, "title");
//    strcpy(logEntry.date, "description");
//    struct LogList *logList = malloc(sizeof(struct LogList));
//    initLogList(logList,20);
//    addLogEntry(logList,logEntry);
//    saveLogList(logList,DB_LOG_PATH,DB_LOG_DB_NAME);
//    initLogList(logList,20);
//    logList = getLogList(DB_LOG_PATH,DB_LOG_DB_NAME);
//    print("len : %i\n", logList->length);
//    for (int i = 0; i < logList->length; ++i) {
//        print("%s %s %s %s",logList->items[i].id,logList->items[i].title,logList->items[i].description,logList->items[i].date);
//    }






//    struct LogList * logList = malloc(sizeof(struct LogList));
//    initLogList(logList, 20);
//    logList = getLogList(DB_LOG_PATH, DB_LOG_DB_NAME);
//    for (int i = 0; i < logList->length; ++i) {
//        struct LogEntry entry = logList->items[i];
//        print("%s %s %s %s \n",entry.id, entry.title, entry.description,entry.date);
//    }

//    writeToLogListExample();
//    readFromLogDbExample();

//    getChangedFiles();
    ////////////////////////////////////////
//    int size = 0 ;
//    String * files = getAllFilesInRoot(&size);
//    for (long int i = 0; i < size; ++i) {
//        print("%li - %s\n",i, files[i]);
//    }
//    return 0;
    String *ar = malloc(sizeof(String *) * 10);
    ar[0] = "git";
    ar[1] = "log";
    ar[2] = "title";
    ar[3] = "desription";
//    ar[2] = ".\\test\\addedNewFile.txt";
//    print("%i \n%i\n",isFolderExist("./dbs/selected"), isFolderExist(".\\dbs\\selected"));
//    String source = ".";
//    String destination = malloc(100 * sizeof(char));
//    destination = PREV_STATE_PATH;
////    deepCopy(".","hffghf");
//    fileCopy(".\\test", ".\\path", "old.txt");
//    chooseColor();
//    print("%s\n",SINGLE_HASH_FILE_ADDRESS);
//    runCli(4,ar);
    runCli(argc, argv);
//    trackFilesExample();
    return 0;
}