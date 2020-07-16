#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"
#include "examples/color.h"
int main(int argc, String *argv) {

//    getChangedFiles();
    ////////////////////////////////////////
//    int size = 0 ;
//    String * files = getAllFilesInRoot(&size);
//    for (long int i = 0; i < size; ++i) {
//        print("%li - %s\n",i, files[i]);
//    }
//    return 0;
    String *ar = malloc(sizeof(String *) * 10);
    ar[0] = "git";
    ar[1] = "status";
    ar[2] = ".\\test\\addedNewFile.txt";
//    print("%i \n%i\n",isFolderExist("./dbs/selected"), isFolderExist(".\\dbs\\selected"));
//    String source = ".";
//    String destination = malloc(100 * sizeof(char));
//    destination = PREV_STATE_PATH;
////    deepCopy(".","hffghf");
//    fileCopy(".\\test", ".\\path", "old.txt");
//    chooseColor();
//    runCli(1,ar);
    runCli(argc, argv);
//    trackFilesExample();
    return 0;
}