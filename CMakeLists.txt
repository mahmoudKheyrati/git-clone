cmake_minimum_required(VERSION 3.15)
project(git C)


set(CMAKE_C_STANDARD 99)

add_executable(git main.c cli/cli.c cli/cli.h core/FileHelper.c core/FileHelper.h diffChecker/diffChecker.c diffChecker/diffChecker.h core/Core.c core/Core.h examples/color.c examples/color.h examples/getListOFAllFiles.c examples/getListOFAllFiles.h examples/hasherExample.c examples/hasherExample.h)