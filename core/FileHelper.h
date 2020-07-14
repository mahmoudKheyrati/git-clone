#pragma once

#include "Macros.h"

String readFile(String path, String filename);

enum Boolean writeFile(String path, String filename, String content);

enum Boolean appendFile(String path, String filename, String content);

String *getFilesInDirectory(String path, int *n);

String *getFoldersInDirectory(String path, int *n);

enum Boolean makeDirectories(String path[], int n);

enum Boolean isFileExist(String path, String filename);

enum Boolean isFolderExist(String path);

enum Boolean deleteFile(String filePath, String filename);

String getLastModifiedOfFile(String path, String filename);

String fileAddressMaker(String path, String filename);

String * splitPath(String path,int* count);