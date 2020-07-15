#include "cli/cli.h"
#include "diffChecker/stringDiffSolver.h"
#include "examples/diffCheckerExamples/createBaseOnChangesExamples.h"
int main(int argc, String *argv) {
//    createSingleFileWithChangesExample();
//    runCli(argc,argv);
    String A = "abcd";
    String B = "ab";




    A= readFile("./test","old.txt");
    B=readFile("./test","new.txt");

    long int lenA = strlen(A);
    long int lenB = strlen(B);


    int** lookupTable = createLookupTable(A,B);
    struct DifferenceList* differenceList = parsLookUpTable(lookupTable,A,B,lenA,lenB);

    struct DifferenceList *list = differenceList;
    struct DifferenceList *list2 = StringDiffChecker(A, B);

    diffSaver(list, "./test", "myChanges.txt");
    struct DifferenceList* changeList = diffReader("./test","myChanges.txt");
    nextSequenceGenerator(A,changeList,"./created","basedOnChanges.txt");



}