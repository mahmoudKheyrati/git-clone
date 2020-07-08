#include "cli.h"
#include <windows.h>
#include <dirent.h>
#include "../core/Core.h"

/**
 * Changes cmd font color
 * @param colorCode
 */
void changeConsoleColor(int colorCode) {
    // color code between 0 to 255
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}


void printColord(String content, int colorCode) {
    changeConsoleColor(COLOR_WHITE);
    changeConsoleColor(colorCode);
    print("%s", content);
    changeConsoleColor(COLOR_WHITE);
}
