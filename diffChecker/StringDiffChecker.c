#include "StringDiffChecker.h"
#include "../core/Core.h"
#include "stdlib.h"
#include "stdio.h"

void initList(struct DifferenceList * list , int initSize){
    struct DifferencePoint *points = malloc(sizeof(struct DifferencePoint)* initSize);
    list->size= initSize;
    list->length=0;
    list->differencePoints= points;
}
void expandList(struct DifferenceList *list){
    struct DifferencePoint * points = malloc(sizeof(struct DifferencePoint) * list->size*2);
    for (int i = 0; i < list->length; ++i) {
        points[i]= list->differencePoints[i];
    }
    free(list->differencePoints);
    list->differencePoints= points;
}
void add(struct DifferenceList * list , struct DifferencePoint point){
    if(list->length == list->size){
        expandList(list);
    }
    list->differencePoints[list->length++]=point;
}


struct DifferenceList * StringDiffChecker(String stringA, String stringB) {
    int lenA = strlen(stringA);
    int lenB = strlen(stringB);
    int len = lenA + lenB;

    int V[10];
    V[1]=0;
    int outerBreak = 0 ;
    for (int d = 0; d < len; ++d) {
        for (int k = -d; k <= d  ; k+=2) {
            // down or right?
            int  down = ( k == -d || ( k != d && V[ k - 1 ] < V[ k + 1 ] ) );

            int kPrev = down ? k + 1 : k - 1;

            // start point
            int xStart = V[ kPrev ];
            int yStart = xStart - kPrev;

            // mid point
            int xMid = down ? xStart : xStart + 1;
            int yMid = xMid - k;

            // end point
            int xEnd = xMid;
            int yEnd = yMid;

            // follow diagonal
            int snake = 0;
            while ( xEnd < lenA && yEnd < lenB && stringA[ xEnd ] == stringB[ yEnd ] ) {
                print("** eq : (%i , %i )\n", xEnd,yEnd);
                xEnd++; yEnd++; snake++;
            }

            // save end point
            V[ k ] = xEnd;

            // check for solution
            if ( xEnd >= lenA && yEnd >= lenB ){
                /* solution has been found */
                print("( %i , %i ) (%i , %i )\n", xStart, yStart, xEnd,yEnd);
                if(xEnd==lenA&& yEnd==lenB){
                    print("the end\n");
                    outerBreak = 1;
                    break;
                }
            }
        }
        if(outerBreak) break;
    }

//    for (int i = 0; i < 10; ++i) {
//        print("%i\n",V[i]);
//    }

}
