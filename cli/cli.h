#pragma once

#include "../app/App.h"
#include "../diffChecker/stringDiffSolver.h"
#include <windows.h>
#include <dirent.h>

#define COMMIT_ID_SIZE 9
#define TITLE_SIZE 60
#define DESCRIPTION_SIZE 120

#define COLOR_BLACK 0
#define COLOR_WHITE 15
#define COLOR_BLOCK_WHITE 240
#define COLOR_YELLOW 14
#define COLOR_LIGHT_BLUE 11
#define COLOR_RED 4
#define COLOR_BLOCK_GREEN 47
#define COLOR_BLOCK_YELLOW 224
#define COLOR_BLOCK_BLUE 159
#define COLOR_BLOCK_RED 79
#define COLOR_GREEN 10


void runCli(int argc, String *argv);

void changeConsoleColor(int colorCode);

void printColored(String content, int colorCode);


void initCli();

void statusCli();

void selectCli(String filename);

void unSelectCli(String filename);

void commitCli(String title, String description);

void logCli();

void resetCli(String commitId);

void stashCli(String commitId);

void stashPopCli();

void help();

void getCommitDetailCli(String commitId);

void diffViewerCli(String commitId, String filename);

void push(String repoName);
