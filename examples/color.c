#include "color.h"
#include "../core/Core.h"
#include "stdio.h"

void chooseColor(){
    String content = "this is a line that I wanna colored!\n";
    for (int i = 0; i < 255; ++i) {
        changeConsoleColor(i);
        printf("%i )\t %s", i, content);
    }
    printf("Hello, World!\n");
}
