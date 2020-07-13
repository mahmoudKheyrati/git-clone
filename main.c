#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <sys/stat.h>
#include <time.h>
#include "cli/cli.h"
#include "core/Core.h"
#include "examples/color.h"
#include "examples/getListOFAllFiles.h"
#include "diffChecker/StringDiffChecker.h"
#include "diffChecker/DiffSaver.h"
#include "diffChecker/Genetator.h"
#include "examples/dbs/LogDbExample.h"
#include "examples/dbs/lastEditDbExample.h"
#include "examples/hasherExample.h"
#include "examples/dbs/commitDbExample.h"

int main(int argc, String *argv) {

//    runCli(argc, argv);
//    writeToCommitListExample();
    readFromCommitDbExample();
}