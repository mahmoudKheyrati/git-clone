#include "cli/cli.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
#include "examples/app/trackFilesExample.h"
#include "examples/color.h"
#include "examples/dbs/LogDbExample.h"
#include "examples/diffCheckerExamples/finalExample.h"

int main(int argc, String *argv) {
//    finalExample();
    runCli(argc, argv);
    return 0;
}