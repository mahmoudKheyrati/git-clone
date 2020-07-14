#pragma once

#include "../core/Core.h"

// always insert from b , deletion from a
enum DIFF_TYPE {
    DELETE = -1, EQUAL, INSERT
};

struct Point {
    long x, y;
};
struct DifferenceSequence {
    short int Type;
    struct Point start;
    struct Point end;
    String data;
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
    struct DifferenceSequence *differenceSequences;
    int size;
};

struct EqualPoint {
    int startX, startY, endX, endY;
    String data;
};


void initList(struct DifferenceList *list, int initSize);

void expandList(struct DifferenceList *list);

void add(struct DifferenceList *list, struct DifferenceSequence sequence);

struct DifferenceList *StringDiffChecker(String stringA, String stringB);

struct DifferenceList *
parser(struct EqualPoint *points, int size, String oldString, String newString, int maxX, int maxY);

