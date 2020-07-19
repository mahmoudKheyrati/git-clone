#include "App.h"
/**
 * get all files and folders listed in jit.ignore file as a list of string
 * @param n size of given array stored here
 * @return
 */
String * getIgnoredList(int * n){
    String rawText = readFile2(IGNORED_FILE_ADDRESS);
    int rawLen = strlen(rawText);
    int size = 0 ;
    for (int i = 0; i < rawLen; ++i) {
        if(rawText[i]=='\n') size++;
    }
    FILE * file = fopen(IGNORED_FILE_ADDRESS , "r+");

    String *list = malloc(sizeof(String)* size);
    for (int j = 0; j < size ; ++j) {
        String line = malloc(MAX_LINE_SIZE);
        line[0]='\0';
        fgets(line,MAX_LINE_SIZE, file);
        line[strlen(line)-1]='\0';
        list[j]= line;
    }
    *n= size;
    return list;
}
/**
 * get list of files exclude ignored files and folders
 * @param n
 * @return
 */
String *getAllFilesInRoot(int *n) {
    int skipToGetRelativePath = strlen(readFile2(CURRENT_PATH_FILE_ADDRESS));
    system("dir /s /b /o:gn /a-d > .\\.JIT\\allfiles.tmp");
    String wholeString = readFile("./", ".\\.JIT\\allfiles.tmp");
    long int len = strlen(wholeString);
    long int count = 0;
    for (long int i = 0; i < len; ++i) {
        if (wholeString[i] == '\n') {
            count++;
        }
    }
    int ignoredCount = 0 ;
    String * ignoredList = getIgnoredList(&ignoredCount);
    free(wholeString);
    FILE * file = fopen(".\\.JIT\\allfiles.tmp","r+");
    String *result = malloc(sizeof(String *) * (count + 1));
    long int index = 0;
    for (long int j = 0; j < count ; ++j) {
        String line = malloc(MAX_LINE_SIZE);
        line[0]='\0';
        fgets(line,MAX_LINE_SIZE, file);
        // ignore .JIT files
        if(strstr(line,"\\.JIT\\")!=NULL) continue;
        // ignore .ignore files / folders
        int isContinue = 0 ;
        for (int i = 0; i < ignoredCount; ++i) {
//            print("ignored line : %s\n", ignoredList[i]);
            if(strstr(line,ignoredList[i])!=NULL){
                // continue outer loop
                isContinue= 1;
            }
        }
        if(isContinue) continue;
        line[strlen(line)-1]='\0';
        line+=skipToGetRelativePath;
        result[index++] = line;

//        print("%li ) %s\n",j, result[index-1]);
    }
    *n = index;
    fclose(file);
    return result;
}
/**
 * determine changing of files
 * @return
 */
struct LastEditList *getChangedFiles() {

    //read from db
    struct LastEditList *currentEditList = malloc(sizeof(struct LastEditList));
    initLastEditList(currentEditList,20);
    currentEditList = getLastEditList(".\\.JIT\\DBS\\LAST_EDIT", "LAST_EDIT.db");

    int filesListSize = 0;
    String *filesList = getAllFilesInRoot(&filesListSize);

    for (int j = 0; j < filesListSize; ++j) {
        int isFind = 0;
        int index = 0;
        for (int i = 0; i < currentEditList->length; ++i) {

            if (strcmp(filesList[j], currentEditList->items[i].fileAddress) == 0) {
                isFind = 1;
                index = i;
                break;
            }
        }

        if (isFind) {
            //find already exists in the last commits
            if (strcmp(currentEditList->items[index].lastEdit, getLastModifiedOfFile2(filesList[j])) == 0) {
                //don't edit
                currentEditList->items[index].status = FILE_NO_CHANGE;
            } else {
                //file edited
                if (isFileExist2(filesList[j]) == 0) {
                    currentEditList->items[index].status = FILE_REMOVED;

                } else {
                    currentEditList->items[index].status = FILE_EDITED;
                }
                strcpy(currentEditList->items[index].lastEdit, getLastModifiedOfFile2(filesList[j]));

            }
        } else {
//            print("add new file :\t %s \n", filesList[j]);
            currentEditList->items[index].status = FILE_ADDED;
            struct FileEditEntry entry = {.status=FILE_ADDED};
            strcpy(entry.fileAddress, filesList[j]);
            strcpy(entry.lastEdit, getLastModifiedOfFile2(filesList[j]));
            addLastEditEntry(currentEditList, entry);

        }
    }


    return currentEditList;

}
/**
 * track files and get status
 * @param edited
 * @param added
 * @param deleted
 * @param editSize
 * @param addSize
 * @param deleteSize
 * @return
 */
struct LastEditList *
trackFiles(String *edited, String *added, String *deleted, int *editSize, int *addSize, int *deleteSize) {
    int eSize = 0;
    int aSize = 0;
    int dSize = 0;
    struct LastEditList *list = getChangedFiles();
    for (int j = 0; j < list->length; ++j) {
        struct FileEditEntry entry = list->items[j];
        switch (entry.status) {
            case FILE_EDITED:
                print("edited : %s\n", entry.fileAddress);
                edited[eSize++] = entry.fileAddress;
                break;
            case FILE_ADDED:
                print("added : %s\n", entry.fileAddress);
                added[aSize++] = entry.fileAddress;
                break;
            case FILE_NO_CHANGE:
                print("no change : %s\n", entry.fileAddress);
                break;
            case FILE_REMOVED:
                print("removed : %s\n", entry.fileAddress);
                deleted[dSize++] = entry.fileAddress;
                break;
        }
    }
    *editSize = eSize;
    *addSize = aSize;
    *deleteSize = dSize;
    return list;
    // if you wanna save
//    String path[2]={"dbs","lastEditDb"};
//    makeDirectories(path,2);
//    saveEditList(list,"./dbs/lastEditDb", "editDb.txt");

}

short int getChangedFileStatus(String filename){
    struct LastEditList * editList = malloc(sizeof(struct LastEditList));
    initLastEditList(editList,20);
    editList= getLastEditList(DB_LAST_EDIT_PATH,DB_LAST_EDIT_DB_NAME);
    for (int i = 0; i < editList->length; ++i) {
        if(strcmp(filename,editList->items[i].fileAddress)==0){
            return editList->items[i].status;
        }
    }
    return -1;
}