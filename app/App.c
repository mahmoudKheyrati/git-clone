#include "App.h"

String *getAllFilesInRoot(int *n) {
    system("dir /s /b /o:gn /a-d > junki.junki.out.some.tmp");
    String wholeString = readFile("./", "junki.junki.out.some.tmp");
    long int len = strlen(wholeString);
    long int count = 0;
    for (long int i = 0; i < len; ++i) {
        if (wholeString[i] == '\n') {
            count++;
        }
    }
    free(wholeString);
    FILE * file = fopen("junki.junki.out.some.tmp","r+");
    String *result = malloc(sizeof(String *) * (count + 1));
    long int index = 0;
    for (long int j = 0; j < count ; ++j) {
        String line = malloc(MAX_LINE_SIZE);
        line[0]='\0';
        fgets(line,MAX_LINE_SIZE, file);
        result[index++] = line;
        line[strlen(line)-1]='\0';
        print("%li ) %s\n",j, result[index-1]);
    }
    *n = index;
    fclose(file);
    return result;
}

String *getFilesList(String path, int *size) {
    String *list = malloc(100 * sizeof(String));
    int index = 0;

    int folderCount = 0;
    String *folders = getFoldersInDirectory(path, &folderCount);
    folders[index++] = "./test/old.txt";
    folders[index++] = "./test/new.txt";
    folders[index++] = "./test/myChanges.txt";
    folders[index++] = "./test/addedNewFile.txt";
    *size = 4;
    return folders;
//    if(folderCount==2) return;
    for (int i = 2; i < folderCount; ++i) {
//        print("%s\n",folders[i]);
//        print("\t");
        String newPath = malloc(1000);
        sprintf(newPath, "%s/%s", path, folders[i]);
//        print("%s\n",newPath);
//        test(newPath);
        int filesCount = 0;
        String *files = getFilesInDirectory(folders[i], &filesCount);
        for (int j = 0; j < filesCount; ++j) {
            String tmp = malloc(100);
            sprintf(tmp, "%s/%s", folders[i], files[j]);
            list[index++] = tmp;
//            print("\t%-30s\t\t",files[j]);
//            print("%s\n",getLastModifiedOfFile(folders[i],files[j]));
        }
    }
//    print("--------------\n");
//    int filesCount = 0 ;
//    String * files = getFilesInDirectory(".",&filesCount );
//    for (int i = 0; i < filesCount; ++i) {
//        String tmp = malloc(100);
//        sprintf(tmp,"%s/%s","./",files[i]);
//        list[index++]= tmp;
//        print("%s\n",files[i]);
//    }
    *size = index;
    return list;
}

struct LastEditList *getChangedFiles() {

    //read from db
    struct LastEditList *currentEditList = getLastEditList("./dbs/lastEditDb", "editDb.txt");

    int filesListSize = 0;
    String *filesList = getAllFilesInRoot(&filesListSize);
//    String *filesList = getFilesList(".", &filesListSize);
    for (int k = 0; k < filesListSize; ++k) {
//        print("%s\n", filesList[k]);
    }
//    return NULL;


    for (int j = 0; j < filesListSize; ++j) {
        print("we %s\n",filesList[j]);
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
            currentEditList->items[index].status = ADD_NEW_FILE;
            struct FileEditEntry entry = {.status=FILE_ADDED};
            strcpy(entry.fileAddress, filesList[j]);
            strcpy(entry.lastEdit, getLastModifiedOfFile2(filesList[j]));
            addLastEditEntry(currentEditList, entry);

        }
    }


    return currentEditList;

}

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
//                print("edited : %s\n", entry.fileAddress);
                edited[eSize++] = entry.fileAddress;
                break;
            case FILE_ADDED:
//                print("added : %s\n", entry.fileAddress);
                added[aSize++] = entry.fileAddress;
                break;
            case FILE_NO_CHANGE:
//                print("no change : %s\n", entry.fileAddress);
                break;
            case FILE_REMOVED:
//                print("removed : %s\n", entry.fileAddress);
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