#include "StringDiffChecker.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"

#define MAX_VERTEX 10000
#define INIT_LIST_SIZE 20

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

struct EqualPoint{
    int startX, startY, endX, endY
};
void parser(struct EqualPoint * points , int size,String oldString , String newString,int maxX, int maxY){
    struct DifferenceList *list = malloc(sizeof(struct DifferenceList));
    initList(list,INIT_LIST_SIZE);



    if(points[0].startX== 0){
        //update
        print("update\t");
        print("(%i , %i) -> (%i , %i)\n", 0 , 0, points[0].startX, points[0].startY);
    }else if (points[0].startY== 0){
        //delete
        print("delete\t");
        print("(%i , %i) -> (%i , %i)\n", 0 , 0, points[0].startX, points[0].startY);
    }


    for (int i = 1; i < size; ++i) {
        struct EqualPoint firstSequence=points[i - 1];
        struct EqualPoint secondSequence= points[i];
        if(firstSequence.endX== secondSequence.startX){
            //update
            print("update\t");
            print("(%i , %i) -> (%i , %i)\n", firstSequence.endX , firstSequence.endY, secondSequence.startX, secondSequence.startY);
        }else if (firstSequence.endY == secondSequence.startY){
            //delete
            print("delete\t");
            print("(%i , %i) -> (%i , %i)\n", firstSequence.endX , firstSequence.endY, secondSequence.startX, secondSequence.startY);
        }
    }
    if(points[size-1].endX == maxX){
        //update
        print("update\t");
        print("(%i , %i) -> (%i , %i)\n", points[size-1].endX , points[size-1].endY, maxX, maxY);
    }else if (points[size-1].endY == maxY){
        //delete
        print("delete\t");
        print("(%i , %i) -> (%i , %i)\n", points[size-1].endX , points[size-1].endY, maxX, maxY);
    }


}
struct DifferenceList *StringDiffChecker(String stringA, String stringB) {
    int lenA = strlen(stringA);
    int lenB = strlen(stringB);
    int len = lenA + lenB;

   int equalSequenceCount = 0 ;
   struct EqualPoint *points= malloc(sizeof(struct EqualPoint)*1000);

    int vertex[MAX_VERTEX];
    vertex[1] = 0;
    for (int d = 0; d < len; ++d) {
        int finalX = 0, finalY = 0, sequenceLen = 0;
        for (int k = -d; k <= d; k += 2) {
            // down or right?
            int down = (k == -d || (k != d && vertex[k - 1] < vertex[k + 1]));

            int prev = down ? k + 1 : k - 1;

            // start point
            int xStart = vertex[prev];
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
                if (xEnd > finalX || yEnd > finalY) {
                    finalX = xEnd;
                    finalY = yEnd;
                    sequenceLen = prev;
                }
//                print("(%i , %i ) -> (%i , %i )\n(%c , %c )\n.................................\n", xStart, yStart, xEnd, yEnd, stringA[yEnd],
//                      stringA[xEnd]);
            }

            // save end point
            vertex[k] = xEnd;

            // check for solution
            if (xEnd >= lenA && yEnd >= lenB) {
//                /* solution has been found */
                print("find\n");
                parser(points, equalSequenceCount,lenA,lenB);
                return NULL;
            }
        }
        int startX = finalX - sequenceLen;
        int startY = finalY - sequenceLen;
        if (!(startX == finalX && startY == finalY)) {
            print("equal : (%i , %i) -> (%i , %i)\n", startX, startY, finalX, finalY);
            struct EqualPoint point={.startX=startX,.startY=startY, .endX=finalX,.endY=finalY};
            points[equalSequenceCount++]= point;
        }
    }
}