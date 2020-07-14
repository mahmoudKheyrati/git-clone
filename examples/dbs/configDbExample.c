#include "configDbExample.h"

void loadConfigDbExample() {
    loadConfigDatabase(DEFAULT_CONFIG_PATH, DEFAULT_CONFIG_FILENAME);
    print("%s %s %s",configDatabase->logDb.path,configDatabase->logDb.dbName,configDatabase->objectsFolder);
}

void saveConfigDbExamples() {
    saveConfigDatabase(DEFAULT_CONFIG_PATH, DEFAULT_CONFIG_FILENAME);
}
