#include "finalExample.h"
#include "../../diffChecker/stringDiffSolver.h"

void finalExample(){
    String A = "abcd";
    String B = "ab";

    A= readFile("./test/old","add.txt");
    B=readFile("./test","add.txt");
    print("A : %s\n", A);
    print("B : %s\n", B);

    long int lenA = strlen(A);
    long int lenB = strlen(B);

    print("len A : %li\n", lenA);
    print("len B : %li\n", lenB);


//    int** lookupTable = createLookupTable(A,B);
//    struct DifferenceList* differenceList = parsLookUpTable(lookupTable,A,B,lenA,lenB);
//
//    diffSaver(differenceList, ".\\test\\changes", "add.txt");
    //loader
    struct DifferenceList* changeList = diffReader(".\\test\\changes","change.txt");
    nextSequenceGenerator(A,changeList,".\\test\\basedOn","clone.txt");

//
//    struct DifferenceList* changeList2 = diffReader(".\\test\\changes","b.txt");
//    A = readFile2(".\\test\\basedOn\\tmp.txt");
//    nextSequenceGenerator(A,changeList2,".\\test\\basedOn","final.txt");

}