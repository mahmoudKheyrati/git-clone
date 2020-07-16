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

void help();

void runCli(int argc, String *argv) {
    String mainCommand = argv[1];
    print("%s\n", mainCommand);
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
        String commitId = malloc(COMMIT_ID_SIZE * sizeof(char));
        scanf("%s ", commitId);
        resetCli(commitId);
    } else if (strcmp(mainCommand, "stash") == 0) {
        String commitId = malloc(COMMIT_ID_SIZE * sizeof(char));
        scanf("%s ", commitId);
        stashCli(commitId);
    } else {
        // anything else , use need help
        help();
    }

}

void initCli() {
    if (!isFolderExist(ROOT_FOLDER_NAME)) {
        // init first commit and project structure
        mkdirs(ROOT_FOLDER_NAME);
        deepCopy(".", PREV_STATE_PATH, ROOT_FOLDER_NAME);
        deepCopy(".", FIRST_STATE_PATH, ROOT_FOLDER_NAME);
        String command = malloc(40 * sizeof(char));
        sprintf(command, "cd > %s", CURRENT_PATH_FILE_ADDRESS);
        system(command);
        free(command);
        commitCli("init jit", "intialize first commit");
    }


}

void statusCli() {
    String *edited = malloc(100 * sizeof(String *));
    String *added = malloc(100 * sizeof(String *));
    String *deleted = malloc(100 * sizeof(String *));
    int eSize = 0;
    int aSize = 0;
    int dSize = 0;
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

    struct LastEditList *list = trackFiles(edited, added, deleted, &eSize, &aSize, &dSize);
    if (eSize == 0 && aSize == 0 && dSize == 0) {
        print("no changes happen\n");
        return;
    }
    if (eSize != 0) {
        print("modified files : \n");
//        printColored("modified files : \n",COLOR_LIGHT_BLUE);
        for (int i = 0; i < eSize; ++i) {
            String string = edited[i];
            print("\t\t\t");
//            printColored(string,COLOR_LIGHT_BLUE);
            print("%s", string);

            print("\n\n");
        }
    }

    if (aSize != 0) {
        print("added files : \n");
//        printColored("added files : \n",0);
        for (int i = 0; i < aSize; ++i) {
            String string = added[i];
            print("\t\t\t");
//            printColored(string,COLOR_BLOCK_GREEN);
            print("%s", string);
            print("\n\n");
        }
    }

    if (dSize != 0) {
        print("deleted files : \n");
//        printColored("deleted files : \n",COLOR_RED);
//        changeConsoleColor(COLOR_LIGHT_BLUE);
        for (int i = 0; i < dSize; ++i) {
            String string = deleted[i];
            print("\t\t\t");
//            changeConsoleColor(COLOR_BLOCK_GREEN);
            puts(string);
//            printColored(string,COLOR_RED);
            print("\n\n");
        }
    }
//        saveEditList(list,"./dbs/lastEditDb", "editDb.txt");

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
        print("this file is already selected.\n");
    } else {
        struct FileSelectEntry entry = {.isSelect=True};
        strcpy(entry.fileAddress, filename);
        addSelectFileEntry(list, entry);
        print("this file selected .\n");
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
    for (int i = 0; i < list->length; ++i) {
        struct FileSelectEntry current = list->items[i];
        if (strcmp(current.fileAddress, filename) == 0) {
            list->items[i].isSelect = False;
            saveSelectList(list, DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
            isFind = 1;
            break;
        }
    }
    if (isFind == True) {
        print("this file unselected.\n");
    } else {
        print("there isn't such file to unselect .\n");
    }
}

void commitCli(String title, String description) {
    // clean select db
    struct SelectedList *selectedList = malloc(sizeof(struct SelectedList));
    initSelectedList(selectedList, 20);
    selectedList = getSelectedList(DB_SELECTED_FILE_PATH, SELECT_DB_NAME);
    struct CommitList *commitList = malloc(sizeof(struct CommitList));
    initCommitList(commitList, 20);

    struct LogList *logList = malloc(sizeof(struct LogList));
    initLogList(logList, 20);
    mkdirs(DB_LOG_PATH);
    logList = getLogList(DB_LOG_PATH, DB_LOG_DB_NAME);


    // commit selected files
    for (int i = 0; i < selectedList->length; ++i) {
        // select all we needed ( selected files )
        if (selectedList->items[i].isSelect == True) {
            struct FileSelectEntry fileSelectEntry = selectedList->items[i];
            print("%s\n", fileSelectEntry.fileAddress);

            struct CommitFileEntry fileEntry = {.status=getChangedFileStatus(fileSelectEntry.fileAddress)};
            // write content to get hash code
            mkdirs(".\\.JIT\\TMP");
            FILE *file = fopen(".\\.JIT\\TMP\\TMP_TO_HASH.tmp", "w");
            fprintf(file, "%s%s%li", fileSelectEntry.fileAddress, getDate(), getCurrentTime());
            fclose(file);

            // hashing the file
            String hashCode = malloc(sizeof(char) * 100);
            hashCode = hashFile(".\\.JIT\\TMP", "TMP_TO_HASH.tmp");
//            print("hash code : %s\n", hashCode);
            //delete tmp file
            deleteFile2(".\\.JIT\\TMP\\TMP_TO_HASH.tmp");

            // filling file entry
            fileEntry.id = hashCode;
            strcpy(fileEntry.date, getLastModifiedOfFile2(fileSelectEntry.fileAddress));
            addCommitFileEntry(commitList, fileEntry);

            // create new object for changed file and store it

//            saveCommitList(commitList,OBJECTS_FOLDER_PATH,hashCode);
//
//            struct LogEntry logEntry = {.};



            free(hashCode);
        }
        // create commit hash code and push to commits and logs logs
    }
}

void logCli() {

}

void resetCli(String commitId) {

}

void stashCli(String commitId) {

}

void help() {
    print("\n\n");
    printColored("help: \n", COLOR_BLOCK_GREEN);
    print("\n");

    printColored(" status ", COLOR_BLOCK_BLUE);
    printColored("  -show status of the files in workspace\n", COLOR_YELLOW);
    print("\n");

    printColored(" select [filename] ", COLOR_BLOCK_BLUE);
    printColored("  -add file to current commit\n", COLOR_YELLOW);
    printColored("filename can has relative or absolute path\n", COLOR_YELLOW);
    print("\n");

    printColored(" unselect ", COLOR_BLOCK_BLUE);
    printColored("  -remove file from current commit\n", COLOR_YELLOW);
    printColored("filename can has relative or absolute path\n", COLOR_YELLOW);
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
