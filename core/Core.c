#include <sys/time.h>
#include "Core.h"
#include "stdio.h"
#include "stdlib.h"


String getDate() {
    String dateString = (char *) malloc(sizeof(char) * 30);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateString, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
            tm.tm_min, tm.tm_sec);
    return dateString;
}

long int getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    print("%li\n", tv.tv_sec);

}

String rangeSelect(String string , int start , int end){
    String result = (String)malloc(sizeof(char)*(end-start+1));
    int index = 0 ;
    for (int i = start; i <= end; ++i) {
        result[index++]= string[i];
    }
    result[index]='\0';
    return result;
}

