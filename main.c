#include <stdio.h>
#include <stdlib.h>
#include "cli/cli.h"
#include "core/Core.h"
#include "examples/color.h"
#include "examples/getListOFAllFiles.h"
#include "diffChecker/StringDiffChecker.h"


void findLastEdit(){
    int fileCount;
    String * files = getFilesInDirectory(".\\",&fileCount);
    for (int j = 0; j < fileCount; ++j) {
        print("- %s \n", files[j]);
    }
    return;
    int size = 0 ;
    String * folders = getFoldersInDirectory(".",&size);
    for (int i = 0; i < size; ++i) {
        int fileCount;
        String * files = getFilesInDirectory("./",&fileCount);
        for (int j = 0; j < fileCount; ++j) {
            print("- %s \n", files[j]);
        }
        print("%s\n",folders[i]);
    }
}
int main(int argc, String *argv) {

//    runCli(argc, argv);
    String A = "ABCABBA";
    String B= "CBABAC";

    long int lenA = strlen(A);
    long int lenB= strlen(B);

    struct DifferenceList * list = StringDiffChecker("ABCABBA", "CBABAC");

    for (int i = 0; i < list->length; ++i) {
        struct DifferenceSequence currentSequence = list->differenceSequences[i];
//        print("%i \t (%li, %li ) -> (%li , %li)\n",currentSequence.Type, currentSequence.start.x, currentSequence.start.y, currentSequence.end.x,currentSequence.end.y );

        struct DifferenceSequence nextSequence = list->differenceSequences[i+1];
        if (currentSequence.Type == INSERT) {
//            print("insert %i-%i\n");
//            for (int j = currentSequence.start.y; j < currentSequence.end.y; ++j) {
//                print("%c",B[j]);
//            }
            for (int k = 0; k < currentSequence.end.y- currentSequence.start.y; ++k) {
                print("%c",currentSequence.data[k]);
            }
        }
        if (currentSequence.Type == DELETE) {
//            print("delete\n");
        }
        long diffX =nextSequence.start.x-  currentSequence.end.x;
        long diffY =nextSequence.start.y-  currentSequence.end.y;
        if(diffX==diffY ){
            for (int j = currentSequence.end.x; j < nextSequence.start.x; ++j) {
                print("%c", A[j]);
            }
//            print("equlity happend at %li\n", currentSequence.end.x);
            continue;
        }
    }


    return 0 ;
//    String A = "ABCABBA";
//    String B = "CBABAC";
//    print("select : %s\n", rangeSelect(A, 2, 5));
////    return 0;
//
//
//    struct DifferencePoint p1 = {.diffType = DELETE, .start=0, .end=1,};
//    struct DifferencePoint p2 = {.diffType = EQUAL, .start=2, .end=2,};
//    struct DifferencePoint p3 = {.diffType = INSERT, .start=3, .end=3, .insertedValue="c", .insertedLen=1};
//    struct DifferencePoint p4 = {.diffType = EQUAL, .start=4, .end=5,};
//    struct DifferencePoint p5 = {.diffType = DELETE, .start=6, .end=6,};
//    struct DifferencePoint p6 = {.diffType = EQUAL, .start=7, .end=7,};
//    struct DifferencePoint p7 = {.diffType = INSERT, .start=8, .end=8, .insertedValue="c", .insertedLen=1};
//
//    struct DifferenceList *list = malloc(sizeof(struct DifferenceList));
//    initList(list, 2);
//    add(list, p1);
//    add(list, p2);
//    add(list, p3);
//    add(list, p4);
//    add(list, p5);
//    add(list, p6);
//    add(list, p7);
//
////    for (int i = 0; i < list->length; ++i) {
////        struct DifferencePoint point = list->differencePoints[i];
////        print("% -5i  %-5li to % 5li %s \n", point.diffType, point.start, point.end, point.insertedValue);
////    }
//    char c[100] ;
//    String selected;
//    for (int i = 0; i < list->length; ++i) {
//        struct DifferencePoint point = list->differencePoints[i];
//        switch (point.diffType){
//            case DELETE:
//                break;
//            case EQUAL:
////                for (int j = point.start; j <= point.end; ++j) {
////                    print("%c", A[j]);
////                }
////                selected= rangeSelect(A, point.start, point.end);
//                print("fucked up ");
//                strcat(c,selected );
////                free(selected);
//                break;
//            case INSERT:
////                print("%s", point.insertedValue);
//                strcat(c,point.insertedValue);
//                break;
//        }
//
//    }
//    print("%s \n", c );
//    free(list->differencePoints);
//    free(list);

    return 0;
}
