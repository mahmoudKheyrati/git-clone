#include "db.h"

enum Boolean saveCustomConfigDatabase(struct ConfigDbEntry *entry, String path, String filename) {
    if (isFolderExist(path)==False){
        int folderCount = 0 ;
        String * splited= splitPath(path,&folderCount);
        makeDirectories(splited,folderCount);

    }
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "wb");
    if (!file) {
        return False;
    }
    fwrite(entry, 1, sizeof(struct ConfigDbEntry), file);
    fclose(file);
    return True;
}

enum Boolean saveConfigDatabase(String path, String filename) {
    struct ConfigDbEntry dbEntry = {{DB_LOG_PATH, DB_LOG_DB_NAME}, {DB_COMMITS_PATH},
                                    {DB_LAST_EDIT_PATH, DB_LAST_EDIT_DB_NAME}, OBJECTS_FOLDER_PATH};
    if (isFolderExist(path)==False){
        int folderCount = 0 ;
        String * splited= splitPath(path,&folderCount);
        makeDirectories(splited,folderCount);

    }
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "wb");
    if (!file) {
        return False;
    }
    fwrite(&dbEntry, 1, sizeof(struct ConfigDbEntry), file);
    fclose(file);
    return True;
}

enum Boolean loadConfigDatabase(String path, String filename) {
    configDatabase= malloc(sizeof(struct ConfigDbEntry));
    String fileAddress = fileAddressMaker(path, filename);
    FILE *file = fopen(fileAddress, "rb");
    if (!file) {
        return False;
    }
    fread(configDatabase, 1, sizeof(struct ConfigDbEntry), file);
    fclose(file);
    return True;
}


