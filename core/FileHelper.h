#pragma once

#include "Macros.h"
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include <sys/time.h>
#include "../app/App.h"

#define MAX_LINE_SIZE 1000
#define MAX_RESULT_SIZE MAX_LINE_SIZE*999
#define MAX_FILE_RESULT_COUNT 9999
#define MAX_FILE_NAME 1000
#define FILE_FLAG 0
#define MODIFIED_TIME_LEN 21

#define MAX_LINES_READ_LINE_SUPPORT 1000
#define MAX_FILE_ADDRESS_READLINE 150

#define TMP_RESULT_ADDRESS ROOT_FOLDER_NAME"\\COPY_TMP.TMP"

String readFile(String path, String filename);

String readFile2(String fileAddress);

String *readLines(String path, String filename, int *n);

enum Boolean writeFile(String path, String filename, String content);

enum Boolean appendFile(String path, String filename, String content);

String *getFilesInDirectory(String path, int *n);

String *getFoldersInDirectory(String path, int *n);

enum Boolean makeDirectories(String path[], int n);

enum Boolean isFileExist(String path, String filename);

enum Boolean isFileExist2(String fileAddress);

enum Boolean isFolderExist(String path);

enum Boolean deleteFile(String filePath, String filename);

enum Boolean deleteFile2(String fileAddress);

String getLastModifiedOfFile(String path, String filename);

String getLastModifiedOfFile2(String fileAddress);

String fileAddressMaker(String path, String filename);

String *splitPath(String path, int *count);

void mkdirs(String path);

String extractFileNameWithFileAddress(String fileAddress);

String extractFilePathWithFileAddress(String fileAddress);

void deepCopy(String source , String destination,String exclude);

void fileCopy(String source, String destination, String filename);

