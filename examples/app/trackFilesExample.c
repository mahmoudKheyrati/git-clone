#include "trackFilesExample.h"


void trackFilesExample(){
    String *edited = malloc(100 * sizeof(String *));
    String *added = malloc(100 * sizeof(String *));
    String *deleted = malloc(100 * sizeof(String *));
    int eSize = 0;
    int aSize = 0;
    int dSize = 0;

    struct LastEditList* list = trackFiles(edited,added,deleted,&eSize,&aSize,&dSize);
    for (int i = 0; i < eSize; ++i) {
        print("eee : %s\n", edited[i]);
    }
//    saveEditList(list,"./dbs/lastEditDb", "editDb.txt");

}
