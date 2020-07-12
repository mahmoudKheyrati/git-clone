#pragma once

#include "../core/Core.h"
#include "string.h"

// always insert from b , deletion from a
enum DIFF_TYPE {
    DELETE = -1, EQUAL, INSERT
};
struct DifferencePoint {
    short int diffType;
    long int start;
    long int end;
    String insertedValue;
    long int insertedLen;

};
struct DifferenceList {
    int length;
    struct DifferencePoint *differencePoints;
    int size;
};
void initList(struct DifferenceList * list , int initSize);
void expandList(struct DifferenceList *list);
void add(struct DifferenceList * list , struct DifferencePoint point);

struct DifferenceList * StringDiffChecker(String stringA, String stringB) ;

