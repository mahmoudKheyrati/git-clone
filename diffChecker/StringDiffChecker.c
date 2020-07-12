#include "StringDiffChecker.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"

#define MAX_VERTEX 10000

void initList(struct DifferenceList *list, int initSize) {
    struct DifferencePoint *points = malloc(sizeof(struct DifferencePoint) * initSize);
    list->size = initSize;
    list->length = 0;
    list->differencePoints = points;
}

void expandList(struct DifferenceList *list) {
    struct DifferencePoint *points = malloc(sizeof(struct DifferencePoint) * list->size * 2);
    for (int i = 0; i < list->length; ++i) {
        points[i] = list->differencePoints[i];
    }
    free(list->differencePoints);
    list->differencePoints = points;
}

void add(struct DifferenceList *list, struct DifferencePoint point) {
    if (list->length == list->size) {
        expandList(list);
    }
    list->differencePoints[list->length++] = point;
}


struct DifferenceList *StringDiffChecker(String stringA, String stringB) {
    int lenA = strlen(stringA);
    int lenB = strlen(stringB);
    int len = lenA + lenB;


    int V[MAX_VERTEX];
    V[1] = 0;
    for (int d = 0; d < len; ++d) {
        int sx = 0, sy = 0, sequenceLen = 0;
        for (int k = -d; k <= d; k += 2) {
            // down or right?
            int down = (k == -d || (k != d && V[k - 1] < V[k + 1]));

            int prev = down ? k + 1 : k - 1;

            // start point
            int xStart = V[prev];
            int yStart = xStart - prev;

            // mid point
            int xMid = down ? xStart : xStart + 1;
            int yMid = xMid - k;

            // end point
            int xEnd = xMid;
            int yEnd = yMid;

            // follow diagonal
            int snake = 0;
            while (xEnd < lenA && yEnd < lenB && stringA[xEnd] == stringB[yEnd]) {

                xEnd++;
                yEnd++;
                snake++;
                if (xEnd > sx || yEnd > sy) {
                    sx = xEnd;
                    sy = yEnd;
                    sequenceLen = prev;
                }
//                print("(%i , %i ) -> (%i , %i )\n(%c , %c )\n.................................\n", xStart, yStart, xEnd, yEnd, stringA[yEnd],
//                      stringA[xEnd]);
            }

            // save end point
            V[k] = xEnd;

            // check for solution
            if (xEnd >= lenA && yEnd >= lenB) {
//                /* solution has been found */
                print("find");
                return NULL;
            }
        }
        if (!(sx - sequenceLen == sx && sy - sequenceLen == sy)) {

            print("(%i , %i) -> (%i , %i)\n", sx - sequenceLen, sy - sequenceLen, sx, sy);
        }
//        print("----------------------------------------------------\n");

    }
}