#pragma once

#include "string.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"
#include "commitDb.h"
#include "lastEditDb.h"
#include "logDb.h"
#include "selectedDb.h"

#define ROOT_FOLDER_NAME ".JIT"

#define DB_ROOT ROOT_FOLDER_NAME"\\DBS"
#define DB_LOG_PATH DB_ROOT"\\LOG"
#define DB_LOG_DB_NAME "LOG_DB.db"

#define DB_COMMITS_PATH ROOT_FOLDER_NAME"\\COMMITS"

#define DB_LAST_EDIT_PATH DB_ROOT"\\LAST_EDIT"
#define DB_LAST_EDIT_DB_NAME "LAST_EDIT.db"

#define DB_SELECTED_FILE_PATH DB_ROOT"\\SELECTED"
#define DB_SELECTED_FILENAME "SELECTED.db"

#define OBJECTS_FOLDER_PATH ROOT_FOLDER_NAME"\\OBJECTS"

#define DEFAULT_CONFIG_PATH ROOT_FOLDER_NAME
#define DEFAULT_CONFIG_FILENAME "CONFIG"

#define PREV_STATE_PATH ROOT_FOLDER_NAME"\\PREV_STATE"

#define FIRST_STATE_PATH ROOT_FOLDER_NAME"\\FIRST_STATE"

#define CURRENT_PATH_FILE_ADDRESS ROOT_FOLDER_NAME"\\CURRENT.PATH.TMP"

#define ALL_HASHES_FILE_ADDRESS ROOT_FOLDER_NAME"\\TMP\\ALL_HASHES.TMP"

#define TMP_PATH ROOT_FOLDER_NAME"\\TMP\\"

#define OLD_STRING_PATH ROOT_FOLDER_NAME"\\TMP\\OLD"

#define SINGLE_HASH_FILE_PATH ROOT_FOLDER_NAME"\\TMP\\HASH\\"
#define SINGLE_HASH_FILE_ADDRESS SINGLE_HASH_FILE_PATH"hash.tmp"



#define IGNORED_FILE_ADDRESS "jit.ignore"





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