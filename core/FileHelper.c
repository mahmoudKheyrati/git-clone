#include "FileHelper.h"
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "Macros.h"
#include "stdio.h"
#include "string.h"
#include <sys/time.h>
#include <sys/stat.h>
#define MAX_LINE_SIZE 1000
#define MAX_RESULT_SIZE MAX_LINE_SIZE*999
#define MAX_FILE_RESULT_COUNT 9999
#define MAX_FILE_NAME 1000
#define FILE_FLAG 0
#define MODIFIED_TIME_LEN 21

String fileAddressMaker(String path, String filename);

/**
 * @ifnot free the string you causes memory leak
 * @param path directory of your file
 * @param filename filename
 * @return file data as a Text
 */
String readFile(String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);

    FILE *file = fopen(fileAddress, "r");
    if (!file) {
        return NULL;
    }
    // read file line by line
    String result = malloc(sizeof(char) * MAX_RESULT_SIZE);
    String line = malloc(sizeof(char) * MAX_LINE_SIZE);
    while ((line = fgets(line, MAX_LINE_SIZE, file))) {
        strcat(result, line);
    }
    free(fileAddress);
    free(line);
    fclose(file);
    return result;

}

/**
 *
 * @param path path/to/file
 * @param filename
 * @param content the content you want to write to the file
 * @return isSuccessful
 */
enum Boolean writeFile(String path, String filename, String content) {
    String fileAddress = fileAddressMaker(path, filename);

    FILE *file = fopen(fileAddress, "w");
    if (!file) {
        return False;
    }
    fputs(content, file);
    fclose(file);
    return True;

}

/**
 *
 * @param path path/to/file
 * @param filename
 * @param offset
 * @param content the content you want to write to the file
 * @param seekPointer offset calculate base on this entry. it can also be
 *        SEEK_SET , SEEK_END , SEEk_CUR
 * @return isSuccessful
 */
enum Boolean appendFile(String path, String filename, String content) {
    String fileAddress = fileAddressMaker(path, filename);

    FILE *file = fopen(fileAddress, "a");
    if (!file) {
        return False;
    }

    fprintf(file, content);
    fclose(file);
    return True;

}

/**
 * you should free the list that you given . items first
 * @param path path/to/file
 * @param n size of files
 * @return list of file names in path
 */
String *getFilesInDirectory(String path, int *n) {
    String *result = (String *) malloc(sizeof(String) * MAX_FILE_RESULT_COUNT);
    int resSize = 0;

    struct dirent *dir;
    DIR *pDir = opendir(path);

    if (pDir) {
        while ((dir = readdir(pDir)) != NULL) {
            if (dir->d_type == FILE_FLAG) {
                String filename = malloc(sizeof(char) * strlen(dir->d_name));
                strcpy(filename, dir->d_name);
                result[resSize++] = filename;
            }
        }
        closedir(pDir);
    }
    *n = resSize;
    return result;
}

/**
 * you should free the list that you given . items first
 * @param path path/to/file
 * @param n size of folders
 * @return list of folder names in path
 */
String *getFoldersInDirectory(String path, int *n) {
    String *result = (String *) malloc(sizeof(String) * MAX_FILE_RESULT_COUNT);
    int resSize = 0;

    struct dirent *dir;
    DIR *pDir = opendir(path);

    if (pDir) {
        while ((dir = readdir(pDir)) != NULL) {
            // check if the entry is folder
            if (dir->d_type != FILE_FLAG) {
                String filename = malloc(sizeof(char) * strlen(dir->d_name));
                strcpy(filename, dir->d_name);
                result[resSize++] = filename;
            }
        }
        closedir(pDir);
    }
    *n = resSize;
    return result;
}

/**
 * make hierarchy directories
 * @param path array of folder names {"path","to","file"}
 * @param n number of folder name
 * @return isSuccessful
 */
enum Boolean makeDirectories(String path[], int n) {
    String beforePath = malloc(sizeof(char) * MAX_LINE_SIZE);
    beforePath[0]='\0';
    enum Boolean isOk = True;
    for (int i = 0; i < n; ++i) {
        int status = mkdir(strcat(beforePath, path[i]));
        if (!status) {
            isOk = False;
        }
        strcat(beforePath, "/");
    }
    free(beforePath);
    return isOk;
}

/**
 * check if the file is exist or not
 * @param path
 * @param filename
 * @return 1 if exits and 0 for not exists
 */
enum Boolean isFileExist(String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);
    struct stat buffer;
    int notExist = stat(fileAddress, &buffer);
    return notExist ? False : True;

}

/**
 *
 * @param path path to file
 * @return is fileExits or not
 */
enum Boolean isFolderExist(String path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return True;
    } else if (ENOENT == errno) {
        //file not exist
        return False;
    }
    return False;
}
/**
 * get last modified of the file
 * @attention free the result of this function
 * @param path path/to/file
 * @param filename
 * @return last modified time of the file
 */
String getLastModifiedOfFile(String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);

    String result = malloc(MODIFIED_TIME_LEN * sizeof(char));
    struct stat attrib;
    stat(fileAddress, &attrib);
    char time[50];
    strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib.st_mtime));
    sprintf(result, "%s", time);
}

/**
 *
 * @param path file directory
 * @param filename
 * @return concat path/filename
 */
String fileAddressMaker(String path, String filename) {
    // create file address
    String fileAddress;
    fileAddress = (String) malloc(sizeof(char) * MAX_LINE_SIZE);
    strcpy(fileAddress, path);
    strcat(fileAddress, "\\");
    strcat(fileAddress, filename);
    return fileAddress;
}

/**
 * delete single file
 * @param filePath path/to/file
 * @param filename
 * @return is the file delete or not
 */
enum Boolean deleteFile(String filePath, String filename) {
    String fileAddress = fileAddressMaker(filePath, filename);
    int res = remove(fileAddress);
    return res ? False : True;
}

/**
 * split path by / for example path/to/file don't call with . or ./ in the beggining of it
 * @param path
 * @return string[] of folder names
 */
String * splitPath(String path,int* count){
    int folderCount = 0 ;
    int pathLen=strlen(path);
    for (int i = 0; i < pathLen; ++i) {
        if(path[i]=='/') folderCount++;
    }
    String *result = malloc(sizeof(char)*(folderCount+1));
    int resIndex= 0 ;
    char * token = strtok(path, "/");
    while( token != NULL ) {
        result[resIndex++]= token; //printing each token
        token = strtok(NULL, " ");
    }
    *count= folderCount+1;
    return result;
}