#pragma once

#include "string.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"

#define ROOT_FOLDER_NAME "./.JIT"

#define DB_ROOT ROOT_FOLDER_NAME"/db"
#define DB_LOG_PATH DB_ROOT"LOG"
#define DB_LOG_DB_NAME "LOG_DB.db"

#define DB_COMMITS_PATH DB_ROOT"/COMMITS"

#define DB_LAST_EDIT_PATH DB_ROOT"/LAST_EDIT"
#define DB_LAST_EDIT_DB_NAME "LAST_EDIT.db"

#define OBJECTS_FOLDER_PATH ROOT_FOLDER_NAME"/OBJECTS"

#define DEFAULT_CONFIG_PATH ROOT_FOLDER_NAME
#define DEFAULT_CONFIG_FILENAME "CONFIG"


struct ConfigDbAddress {
    String path;
    String dbName;
};
struct ConfigDbEntry {
    struct ConfigDbAddress logDb;
    struct ConfigDbAddress commitsDb;
    struct ConfigDbAddress lastEditDb;
    String objectsFolder;
};

/**
 * global config entry
 */
struct ConfigDbEntry *configDatabase;

enum Boolean loadConfigDatabase(String path, String filename);
enum Boolean saveConfigDatabase(String path, String filename);
enum Boolean saveCustomConfigDatabase(struct ConfigDbEntry* entry, String path, String filename);