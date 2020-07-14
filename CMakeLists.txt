cmake_minimum_required(VERSION 3.15)
project(git C)


set(CMAKE_C_STANDARD 99)

add_executable(git main.c cli/cli.c cli/cli.h core/FileHelper.c core/FileHelper.h diffChecker/diffChecker.c diffChecker/diffChecker.h core/Core.c core/Core.h examples/color.c examples/color.h examples/getListOFAllFiles.c examples/getListOFAllFiles.h examples/hasherExample.c examples/hasherExample.h diffChecker/StringDiffChecker.c diffChecker/StringDiffChecker.h diffChecker/DiffSaver.c diffChecker/DiffSaver.h diffChecker/Genetator.c diffChecker/Genetator.h examples/diffCheckerExamples/createBaseOnChangesExamples.c examples/diffCheckerExamples/createBaseOnChangesExamples.h db/db.c db/db.h db/lastEditDb.c db/lastEditDb.h examples/dbs/lastEditDbExample.c examples/dbs/lastEditDbExample.h db/logDb.c db/logDb.h examples/dbs/LogDbExample.c examples/dbs/LogDbExample.h db/commitDb.c db/commitDb.h examples/dbs/commitDbExample.c examples/dbs/commitDbExample.h examples/dbs/configDbExample.c examples/dbs/configDbExample.h)