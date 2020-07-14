#include "hasher.h"


String hashString(String string){
    // hash string with the help of java jar file
    String outputName = "tempHashCode.junk";

    String command = malloc((strlen(string)+50)* sizeof(char));
    sprintf(command,"java -jar Hasher.jar -s \"%s\" > %s",string,outputName);
    system(command);
    String hashCode = malloc(sizeof(char)*50);
    hashCode= readFile("./", outputName);
//    print("%s\n", hashCode);
    free(command);
    deleteFile("./", outputName);
    return hashCode;
}

String hashFile(String filePath, String filename){
    // hash string with the help of java jar file
    String fileAddress = fileAddressMaker(filePath, filename);

    String outputName = "tempHashCode.out.junk.txt";

    String command = malloc((strlen(fileAddress)+50)* sizeof(char));
    sprintf(command,"java -jar Hasher.jar -f %s > %s",fileAddress,outputName);
    system(command);
    String hashCode = malloc(sizeof(char)*50);
    hashCode= readFile("./", outputName);
//    print("%s\n", hashCode);
    free(command);
    deleteFile("./", outputName);
    return hashCode;
}