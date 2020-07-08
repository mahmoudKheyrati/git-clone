#include <stdlib.h>
#include "hasherExample.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"

void hashExample(){

    // hash string with the help of java jar file
    String outputName = "tempHashCode.out.txt";
    String content = "this is some content about hashing 93948394";

    String command = malloc(1000* sizeof(char));
    sprintf(command,"java -jar Hasher.jar \"%s\" > %s",content,outputName);
    system(command);
    String hashCode = readFile("./", outputName);
    print("%s\n", hashCode);
    free(hashCode);
    free(command);
    deleteFile("./", outputName);
}
