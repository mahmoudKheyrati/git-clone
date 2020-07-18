#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"
#include "examples/color.h"
#include "examples/dbs/LogDbExample.h"
#include "examples/diffCheckerExamples/finalExample.h"

int main(int argc, String *argv) {
    String *ar = malloc(sizeof(String *) * 10);
    ar[0] = "git";
    ar[1] = "diff";
    ar[2] = "b83ad67c0c443724cbed2ab80850a545.CMT";
    ar[3] = "add.txt";

    runCli(argc, argv);
    return 0;
}