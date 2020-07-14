#include "hasherExample.h"


void hashStringExample(){
    String string="this is some string\n that represent in two lines of string";
    String result = hashString(string);
    print("%s\n",result);
}
void hashFileExample(){
    String path="./";
    String filename="git.cbp";
    String result = hashFile(path,filename);
    print("%s\n",result);
}
