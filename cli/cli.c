#include "cli.h"

#define SELECT_DB_NAME "SELECTED.DB"

void initCli();

void statusCli();

void selectCli(String filename);

void unSelectCli(String filename);

void commitCli(String title, String description);

void logCli();

void resetCli(String commitId);

void stashCli(String commitId);

void stashPopCli();

void help();

void runCli(int argc, String *argv) {
    String mainCommand = argv[1];
//    print("%s\n", mainCommand);
    if (!mainCommand) return;
    if (strcmp(mainCommand, "init") == 0) {
        initCli();

    } else if (strcmp(mainCommand, "status") == 0) {
        statusCli();

    } else if (strcmp(mainCommand, "select") == 0) {
        selectCli(argv[2]);
    } else if (strcmp(mainCommand, "unselect") == 0) {
        unSelectCli(argv[2]);
    } else if (strcmp(mainCommand, "commit") == 0) {
        commitCli(argv[2], argv[3]);
    } else if (strcmp(mainCommand, "log") == 0) {
        logCli();
    } else if (strcmp(mainCommand, "reset") == 0) {
        resetCli(argv[2]);
    } else if (strcmp(mainCommand, "stash") == 0) {
        if (strcmp(argv[2], "pop") == 0) {
            stashPopCli();
        } else {
            stashCli(argv[2]);
        }
    } else {
        // anything else , use need help
        help();
    }

}

void initCli() {
    // init first commit and project structure
    if (!isFolderExist(ROOT_FOLDER_NAME)) {
        //create all folders we needed
        mkdirs(ROOT_FOLDER_NAME);
        mkdirs(DB_ROOT);
        mkdirs(DB_LOG_PATH);
        mkdirs(DB_COMMITS_PATH);
        mkdirs(DB_LAST_EDIT_PATH);
        mkdirs(DB_SELECTED_FILE_PATH);
        mkdirs(OBJECTS_FOLDER_PATH);
        mkdirs(DEFAULT_CONFIG_PATH);
        mkdirs(PREV_STATE_PATH);
        mkdirs(FIRST_STATE_PATH);
        mkdirs(SINGLE_HASH_FILE_PATH);

        deepCopy(".", PREV_STATE_PATH, ROOT_FOLDER_NAME);
        deepCopy(".", FIRST_STATE_PATH, ROOT_FOLDER_NAME);
        String command = malloc(40 * sizeof(char));
        sprintf(command, "cd > %s", CURRENT_PATH_FILE_ADDRESS);
        system(command);
        free(command);

        // select all files
//        struct LastEditList *list = getChangedFiles();
//        struct SelectedList * selectedList = malloc(sizeof(struct SelectedList));
//        initSelectedList(selectedList,20);
//        selectedList = getSelectedList(DB_SELECTED_FILE_PATH, DB_SELECTED_FILENAME);
//        printColored("\n\n\tmodified files : \n", COLOR_LIGHT_BLUE);
//        for (int i = 0; i < list->length; ++i) {
//                list->items[i].status= FILE_ADDED;
//            struct FileSelectEntry entry = {.isSelect=True};
//            strcpy(entry.fileAddress, list->items[i].fileAddress);
//            addSelectFileEntry(selectedList, entry);
//        }
//        saveEditList(list,DB_LAST_EDIT_PATH,DB_LAST_EDIT_DB_NAME);
//        saveSelectList(selectedList,DB_SELECTED_FILE_PATH,DB_SELECTED_FILENAME);
//
//
//        commitCli("init jit", "initialize first commit");
    }


}

void statusCli() {
    print("selected files : \n");
    struct SelectedList *selectedList = malloc(sizeof(struct SelectedList));
    initSelectedList(selectedList, 20);
    selectedList = getSelectedList(DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
    for (int j = 0; j < selectedList->length; ++j) {
        if (selectedList->items[j].isSelect == True) {
            print("\t\t\t");
            print("%s\n", selectedList->items[j].fileAddress);

        }
    }
    print("\n\n");

    struct LastEditList *list = getChangedFiles();
    printColored("\n\n\tmodified files : \n", COLOR_LIGHT_BLUE);
    for (int i = 0; i < list->length; ++i) {
        if (list->items[i].status == FILE_EDITED) {
            print("\t\t\t\tedited : %s\n", list->items[i].fileAddress);
        }
    }
    printColored("\n\n\tnew files : \n", COLOR_GREEN);
    for (int i = 0; i < 10; ++i) {
        if (list->items[i].status == FILE_ADDED) {
            print("\t\t\t\tadded : %s\n", list->items[i].fileAddress);
        }
    }
    printColored("\n\n\tdeleted files : \n", COLOR_RED);
    for (int i = 0; i < list->length; ++i) {
        if (list->items[i].status == FILE_REMOVED) {
            print("\t\t\t\tdeleted : %s\n", list->items[i].fileAddress);
        }
    }


//        saveEditList(list,DB_LAST_EDIT_PATH, DB_LAST_EDIT_DB_NAME);

}

void selectCli(String filename) {
    struct SelectedList *list = malloc(sizeof(struct SelectedList));
    initSelectedList(list, 20);
    if (isFolderExist(DB_SELECTED_FILE_PATH) == False) {
        String command = malloc(sizeof(char) * 100);
        sprintf(command, "mkdir %s", DB_SELECTED_FILE_PATH);
        system(command);
        free(command);
    }

    list = getSelectedList(DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
    int isFind = 0;
    for (int i = 0; i < list->length; ++i) {
        if (strcmp(list->items[i].fileAddress, filename) == 0) {
            isFind = 1;
            break;
        }
    }
    if (isFind == True) {
        print("this file is already selected\n");
    } else {
        if(isFileExist2(filename)==False){
            printColored("this file dosn't exists. please enter the correct file\n", COLOR_RED);
            return;
        }
        struct FileSelectEntry entry = {.isSelect=True};
        strcpy(entry.fileAddress, filename);
        addSelectFileEntry(list, entry);
        print("selected :\t\t%s\n", entry.fileAddress);
    }
    saveSelectList(list, DB_SELECTED_FILE_PATH, SELECT_DB_NAME);

}

void unSelectCli(String filename) {
    struct SelectedList *list = malloc(sizeof(struct SelectedList));
    initSelectedList(list, 20);
    if (isFolderExist(DB_SELECTED_FILE_PATH) == False) {
        String command = malloc(sizeof(char) * 100);
        sprintf(command, "mkdir %s", DB_SELECTED_FILE_PATH);
        system(command);
        free(command);
    }
    list = getSelectedList(DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
    int isFind = 0;
    int index = 0;
    for (int i = 0; i < list->length; ++i) {
        struct FileSelectEntry current = list->items[i];
        if (strcmp(current.fileAddress, filename) == 0) {
            list->items[i].isSelect = False;
            saveSelectList(list, DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
            isFind = 1;
            index = i;
            break;
        }
    }
    if (isFind == True) {
        print("unselected :\t\t%s\n", list->items[index].fileAddress);
    } else {
        print("there isn't such file to unselect\n");
    }
}

void commitCli(String title, String description) {
    struct SelectedList *selectedList = malloc(sizeof(struct SelectedList));
    initSelectedList(selectedList, 20);
    selectedList = getSelectedList(DB_SELECTED_FILE_PATH, SELECT_DB_NAME);

    if (selectedList->length == 0) {
        printColored("there is nothing to commit please select file(s) first \n", COLOR_RED);
        return;
    }

    struct CommitList *commitList = malloc(sizeof(struct CommitList));
    initCommitList(commitList, 20);

    struct LogList *logList = malloc(sizeof(struct LogList));
    initLogList(logList, 20);
    mkdirs(DB_LOG_PATH);
    logList = getLogList(DB_LOG_PATH, DB_LOG_DB_NAME);

    struct LastEditList *editList = malloc(sizeof(struct LastEditList));
    initLastEditList(editList, 20);
    editList = getLastEditList(DB_LAST_EDIT_PATH, DB_LAST_EDIT_DB_NAME);
//    editList = getChangedFiles();

    // commit selected files
    // for storing all file hashes to create commit hashcode
    FILE *allHashes = fopen(ALL_HASHES_FILE_ADDRESS, "w");

    // per each file
    for (int i = 0; i < selectedList->length; ++i) {
        // select all we needed ( selected files )
        if (selectedList->items[i].isSelect == False) continue;

        struct FileSelectEntry fileSelectEntry = selectedList->items[i];
//        print("%s\n", fileSelectEntry.fileAddress);

        struct CommitFileEntry fileEntry = {.status=getChangedFileStatus(fileSelectEntry.fileAddress)};
        // write content to get hash code
        mkdirs(SINGLE_HASH_FILE_PATH);
        FILE *file = fopen("hash.hash", "w");
        fprintf(file, "%s%s%li", fileSelectEntry.fileAddress, getDate(), getCurrentTime());
        fclose(file);
        // hashing the file
        String hashCode = malloc(sizeof(char) * 100);
        hashCode = hashFile2("hash.hash");

        hashCode[strlen(hashCode) - 1] = '\0';
        //delete tmp file
        deleteFile2("hash.hash");


        // create new object for changed file and store it
        String prevPath = malloc(1000 * sizeof(char));
        sprintf(prevPath, "%s\\%s", PREV_STATE_PATH, fileSelectEntry.fileAddress);

        // determine changes
        String A = readFile2(prevPath);
        String B = readFile2(fileSelectEntry.fileAddress);

        long int lenA = strlen(A);
        long int lenB = strlen(B);


        int **lookupTable = createLookupTable(A, B);
        struct DifferenceList *differenceList = parsLookUpTable(lookupTable, A, B, lenA, lenB);

        struct DifferenceList *list = differenceList;
        struct DifferenceList *list2 = StringDiffChecker(A, B);
        String objectFilename = malloc(70 * sizeof(char));
        sprintf(objectFilename, "%s.OBJ", hashCode);
        diffSaver(list, OBJECTS_FOLDER_PATH, objectFilename);

        // filling file entry
        //set status

        for (int j = 0; j < editList->length; ++j) {
            if (strcmp(editList->items[i].fileAddress, fileSelectEntry.fileAddress) == 0) {
                fileEntry.status = editList->items[i].status;
                break;
            }
        }

        strcpy(fileEntry.id, objectFilename);
        strcpy(fileEntry.fileAddress, fileSelectEntry.fileAddress);

//        fileEntry.id = objectFilename;
//        fileEntry.fileAddress = fileSelectEntry.fileAddress;
        strcpy(fileEntry.date, getLastModifiedOfFile2(fileSelectEntry.fileAddress));

        addCommitFileEntry(commitList, fileEntry);


        // write all hashed for generate commit hashcode
        fprintf(allHashes, "%s", hashCode);
//        free(hashCode);
    }
    fclose(allHashes);
    // create commit hashCode
    String commitHashCode = hashFile2(ALL_HASHES_FILE_ADDRESS);
    commitHashCode[strlen(commitHashCode) - 1] = '\0';
    String commitFilename = malloc(70 * sizeof(char));
    sprintf(commitFilename, "%s.CMT", commitHashCode);
    //saving commit
    saveCommitList(commitList, DB_COMMITS_PATH, commitFilename);
    //add to log list

    struct LogEntry logEntry = {};
    strcpy(logEntry.date, getDate());
    strcpy(logEntry.id, commitFilename);
    strcpy(logEntry.title, title);
    strcpy(logEntry.date, description);
//    logEntry.title = "title";
//    logEntry.description = "des";
//    logEntry.id = commitFilename;
    addLogEntry(logList, logEntry);
    saveLogList(logList, DB_LOG_PATH, DB_LOG_DB_NAME);

    // update prev state
    String fileAddressInPrevState = malloc(sizeof(char) * 300);

    for (int k = 0; k < editList->length; ++k) {
        struct FileEditEntry entry = editList->items[k];

        sprintf(fileAddressInPrevState, "%s//%s", PREV_STATE_PATH, entry.fileAddress);
        if (entry.status == FILE_EDITED || entry.status == FILE_ADDED) {
            // copy new file insted
            fileCopy(extractFilePathWithFileAddress(entry.fileAddress),
                     extractFilePathWithFileAddress(fileAddressInPrevState),
                     extractFileNameWithFileAddress(entry.fileAddress));

        } else if (entry.status == FILE_REMOVED) {
            // i don't know
            deleteFile2(fileAddressInPrevState);
        }
    }
    free(fileAddressInPrevState);
    // empty selected list
    clearSelectedDb();
    // save edit list
    saveEditList(editList, DB_LAST_EDIT_PATH, DB_LAST_EDIT_DB_NAME);
}

void logCli() {
    struct LogList *logList = malloc(sizeof(struct LogList));
    initLogList(logList, 20);
    logList = getLogList(DB_LOG_PATH, DB_LOG_DB_NAME);
    for (int i = 0; i < logList->length; ++i) {
        struct LogEntry entry = logList->items[i];
        print("%s %s %s %s \n", entry.id, entry.title, entry.description, entry.date);
    }


}

void resetCli(String commitId) {
    struct LogList *logList = malloc(sizeof(struct LogList));
    initLogList(logList, 20);
    logList = getLogList(DB_LOG_PATH, DB_LOG_DB_NAME);
    int isFind = 0;
    int index = 0;
    for (int i = 0; i < logList->length; ++i) {
        struct LogEntry entry = logList->items[i];
        if (strcmp(entry.id, commitId) == 0) {
//            print("find commit id\n");
            isFind = 1;
            index = i;
        }

    }
    if (isFind == False) {
        printColored("there isn't such commit id please enter the correct one!\n", COLOR_RED);
        return;
    }
    // copy first to prev
    deepCopy(FIRST_STATE_PATH, PREV_STATE_PATH, ROOT_FOLDER_NAME);
    for (int i = 0; i < index + 1; ++i) {
        struct LogEntry entry = logList->items[i];
        struct CommitList *commitList = malloc(sizeof(struct CommitList));
        initCommitList(commitList, 20);
        commitList = getCommitList(DB_COMMITS_PATH, entry.id);
        for (int j = 0; j < commitList->length; ++j) {
            struct CommitFileEntry commitFileEntry = commitList->items[j];
            print("%s %s %s %i\n", commitFileEntry.id, commitFileEntry.fileAddress, commitFileEntry.date,
                  commitFileEntry.status);
            if (commitFileEntry.status == ADD_NEW_FILE || commitFileEntry.status == CHANGED_FILE) {
                String prevStateAddress = malloc(sizeof(char) * 200);

                sprintf(prevStateAddress, "%s\\%s", PREV_STATE_PATH, commitFileEntry.fileAddress);

                if (commitFileEntry.status == FILE_EDITED) {
                    String A = readFile2(prevStateAddress);
                    struct DifferenceList *changeList = diffReader(OBJECTS_FOLDER_PATH, entry.id);
                    nextSequenceGenerator(A, changeList, extractFilePathWithFileAddress(commitFileEntry.fileAddress),
                                          extractFileNameWithFileAddress(commitFileEntry.fileAddress));
                } else {
                    String A = malloc(1 * sizeof(char));
                    A[0] = '\0';

                    struct DifferenceList *changeList = diffReader(OBJECTS_FOLDER_PATH, entry.id);
                    nextSequenceGenerator(A, changeList, extractFilePathWithFileAddress(commitFileEntry.fileAddress),
                                          extractFileNameWithFileAddress(commitFileEntry.fileAddress));

                }

            } else if (commitFileEntry.status == REMOVED_FILE) {
                //remove file
                deleteFile2(commitFileEntry.fileAddress);
            }

            deepCopy(".", PREV_STATE_PATH, ROOT_FOLDER_NAME);

        }
    }
}

void stashCli(String commitId) {
    deepCopy(".", ".\\.JIT\\STASH", ROOT_FOLDER_NAME);
    writeFile(".\\.JIT\\","IN_STASH.TMP","1");
    // reset
//    resetCli(commitId);

}

void stashPopCli() {
    String result = readFile(".\\.JIT\\","IN_STASH.TMP");
    print("%s",result);

    if (strcmp(result,"1")==0) {

        deepCopy(".\\.JIT\\STASH", ".", ROOT_FOLDER_NAME);
        writeFile(".\\.JIT\\","IN_STASH.TMP","0");
        system("cd .\\.JIT\\STASH &&  DEL /F/Q/S *.* > NUL");

    } else {
        printColored("you are not in stash mode!\n", COLOR_RED);
    }

}

void help() {
    print("\n\n");
    printColored("help: \n", COLOR_BLOCK_GREEN);
    print("\n");

    printColored(" status ", COLOR_BLOCK_BLUE);
    printColored("  -show status of the files in workspace\n", COLOR_YELLOW);
    print("\n");

    printColored(" select [fileAddress] ", COLOR_BLOCK_BLUE);
    printColored("  -add file to current commit\n", COLOR_YELLOW);
    printColored("fileAddress can has relative or absolute path\n", COLOR_YELLOW);
    print("\n");

    printColored(" unselect ", COLOR_BLOCK_BLUE);
    printColored("  -remove file from current commit\n", COLOR_YELLOW);
    printColored("fileAddress can has relative or absolute path\n", COLOR_YELLOW);
    print("\n");

    printColored(" commit [title, description] ", COLOR_BLOCK_BLUE);
    printColored("  -commit all changes and gives commit id in the format of hashcode\n", COLOR_YELLOW);
    printColored("commit id is first 8 chars of hashcode\n", COLOR_YELLOW);
    print("\n");

    printColored(" log ", COLOR_BLOCK_BLUE);
    printColored("  -show all commits with their commitId in the format of hashcode \n", COLOR_YELLOW);
    printColored("commit id is first 8 chars of hashcode\n", COLOR_YELLOW);
    print("\n");

    printColored(" reset ", COLOR_BLOCK_BLUE);
    printColored("  -go to commit with the help of commit id  \n", COLOR_YELLOW);
    printColored("Note : if you have stash you lose your data, to keep your stash you can use stash method\n",
                 COLOR_BLOCK_RED);
    print("\n");

    printColored(" stash [ commit id ] ", COLOR_BLOCK_BLUE);
    printColored("  -go to commit with the help of commit id without lose your stash \n", COLOR_YELLOW);
    printColored("commit id is first 8 chars of hashcode\n", COLOR_YELLOW);
    print("\n");

    printColored(" stash pop ", COLOR_BLOCK_BLUE);
    printColored("  -go back to your current workspace without lose any data in stash \n", COLOR_YELLOW);


}


/**
 * Changes cmd font color
 * @param colorCode
 */
void changeConsoleColor(int colorCode) {
    // color code between 0 to 255
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}


void printColored(String content, int colorCode) {
    changeConsoleColor(COLOR_WHITE);
    changeConsoleColor(colorCode);
    print("%s", content);
    changeConsoleColor(COLOR_WHITE);
}
