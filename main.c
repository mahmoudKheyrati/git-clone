#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"

int main(int argc, String *argv) {
    String * ar =malloc(sizeof(String *)*10);
    ar[0]="git";
    ar[1]="status";


    runCli(2,ar);
//    trackFilesExample();
    return 0;
}