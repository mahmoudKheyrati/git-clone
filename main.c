#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"
#include "examples/color.h"
#include "examples/dbs/LogDbExample.h"
#include "examples/diffCheckerExamples/finalExample.h"

int main(int argc, String *argv) {

//    struct LastEditList *currentList = malloc(sizeof(struct LastEditList));
//    initLastEditList(currentList,20);
//    currentList= getLastEditList(".\\.JIT\\DBS\\LAST_EDIT", "LAST_EDIT.db");
//    print("len : %li\n", currentList->length);
//    for (int i = 0; i < currentList->length; ++i) {
//        print("%s\n",currentList->items[i].fileAddress);
//    }
//    // fill the list
//    //get files
//    int filesSize = 0 ;
//    String * files = getAllFilesInRoot(&filesSize);
//    print("files size : %i\n",filesSize);
//    for (int j = 0; j < filesSize; ++j) {
//        print("files : %s\n", files[j]);
//        struct FileEditEntry entry = {.status=FILE_ADDED};
//        strcpy(entry.fileAddress, files[j]);
//        strcpy(entry.lastEdit, getLastModifiedOfFile2(files[j]));
//        print("\t%s - %s - %i \n",entry.fileAddress,entry.lastEdit, entry.status);
//        addLastEditEntry(currentList,entry);
//    }
//    print("\n\n\n****after listing files\n\n\n");
//    saveEditList(currentList,".\\.JIT\\DBS\\LAST_EDIT", "LAST_EDIT.db" );
//    print("after saving \n\n");
//    struct LastEditList * afterList = malloc(sizeof(struct LastEditList));
//    initLastEditList(afterList,20);
//    afterList = getLastEditList(".\\.JIT\\DBS\\LAST_EDIT", "LAST_EDIT.db");
//    print("-- len : %li\n", afterList->length);
//    for (int i = 0; i < afterList->length; ++i) {
//        print("--- ) %s\n",afterList->items[i].fileAddress);
//    }

//    struct LastEditList *list = getChangedFiles();
//    print("after get list \n");
//    printColored("\n\n\tmodified files : \n", COLOR_LIGHT_BLUE);
//    for (int i = 0; i < list->length; ++i) {
//        if (list->items[i].status == FILE_EDITED) {
//            print("\t\t\t\tedited : %s\n", list->items[i].fileAddress);
//        }
//    }
//    printColored("\n\n\tnew files : \n", COLOR_GREEN);
//    for (int i = 0; i < list->length; ++i) {
//        if (list->items[i].status == FILE_ADDED) {
//            print("\t\t\t\tadded : %s\n", list->items[i].fileAddress);
//            list->items[i].status=FILE_NO_CHANGE;
//        }
//    }
//    printColored("\n\n\tdeleted files : \n", COLOR_RED);
//    for (int i = 0; i < list->length; ++i) {
//        if (list->items[i].status == FILE_REMOVED) {
//            print("\t\t\t\tdeleted : %s\n", list->items[i].fileAddress);
//            list->items[i].status=FILE_NO_CHANGE;
//
//        }
//    }
//
//////
//    saveEditList(list,".\\.JIT\\DBS\\LAST_EDIT", "LAST_EDIT.db");
//////
//////
//    return 0;




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
    ar[1] = "reset";
    ar[2] = "f566a90baaf879b151adb9acbc37b954.CMT";
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
    runCli(4,ar);
//    runCli(argc, argv);
//    trackFilesExample();
    return 0;
}