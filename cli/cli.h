#pragma once

#include "../core/Core.h"

#define COLOR_WHITE 240
#define COLOR_YELLOW 14
#define COLOR_LIGHT_BLUE 11
#define COLOR_RED 4
#define COLOR_BLOCK_GREEN 47
#define COLOR_BLOCK_YELLOW 224
#define COLOR_BLOCK_BLUE 159
#define COLOR_BLOCK_RED 79
//#define COLOR_WHITE 7
//#define COLOR_YELLOW 6
//#define COLOR_LIGHT_BLUE 1
//#define COLOR_RED 12
//#define COLOR_BLOCK_GREEN 3
//#define COLOR_BLOCK_YELLOW 2
//#define COLOR_BLOCK_BLUE 9
//#define COLOR_BLOCK_RED 4
//#define COLOR_CYAN 11

void runCli(int argc, String *argv);

void changeConsoleColor(int colorCode);

void printColored(String content, int colorCode);
