#include "createBaseOnChangesExamples.h"


void createSingleFileWithChangesExample(){

    String A = "ABCABBA";
    String B = "CBABAC";

    A= readFile("./test","old.txt");
    B=readFile("./test","new.txt");


    long int lenA = strlen(A);
    long int lenB = strlen(B);

    struct DifferenceList *list = StringDiffChecker(A, B);
    diffSaver(list, "./test", "myChanges.txt");
    struct DifferenceList* changeList = diffReader("./test","myChanges.txt");
    nextSequenceGenerator(A,changeList,"./created","basedOnChanges.txt");

}
