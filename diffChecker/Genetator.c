#include "Genetator.h"


String nextSequenceGenerator(String oldString , struct DifferenceList *differenceList, String outputPath, String filename){
    String fileAddress = fileAddressMaker(outputPath, filename);
//    print("gen fileadd : %s\n",fileAddress);
    FILE* file = fopen(fileAddress,"w");
//    print("gen diff len : %i\n", differenceList->length);

    for (int i = 0; i < differenceList->length; ++i) {
        struct DifferenceSequence currentSequence = differenceList->differenceSequences[i];
//        print("gen : %i \t (%li, %li ) -> (%li , %li)\n",currentSequence.Type, currentSequence.start.x, currentSequence.start.y, currentSequence.end.x,currentSequence.end.y );

        struct DifferenceSequence nextSequence = differenceList->differenceSequences[i + 1];
        if (currentSequence.Type == INSERT) {
//            print("gen before for : %li %li\n",currentSequence.end.y, currentSequence.start.y);
            for (long int k = 0; k < currentSequence.end.y - currentSequence.start.y; ++k) {
//                print("%c",currentSequence.data[k]);
                fprintf(file,"%c", currentSequence.data[k]);
            }
        }
        if (currentSequence.Type == DELETE) {}

        long diffX = nextSequence.start.x - currentSequence.end.x;
        long diffY = nextSequence.start.y - currentSequence.end.y;
        if (diffX == diffY) {
            for (int j = currentSequence.end.x; j < nextSequence.start.x; ++j) {
                fprintf(file, "%c", oldString[j]);
            }
            continue;
        }
    }
    fclose(file);

}
