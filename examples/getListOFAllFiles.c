#include "../core/Core.h"
#include "getListOFAllFiles.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
void getAllFiles(String path){
    print("%s\n",path);
    int directoryCount = 0 ;
    int filesCount = 0 ;
    String * files = getFilesInDirectory(path,&filesCount);
    String *directories = getFoldersInDirectory(path,&directoryCount);
    for (int i = 0; i < filesCount; ++i) {
        print("\t\t%s\n",files[i]);
    }
    for (int j = 2; j < directoryCount; ++j) {
        String newPath = malloc(100);
        sprintf(newPath,"%s/%s",path,directories[j]);
        getAllFiles(newPath);
        free(newPath);
    }
    print("\n\n");
    if(directoryCount==0) return;

}
