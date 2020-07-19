#include "DiffSaver.h"


void diffSaver(struct DifferenceList * list, String path , String filename){
//    for (int i = 0; i < list->length; ++i) {
//        struct DifferenceSequence cur = list->differenceSequences[i];
////        print("saver : ");
////        print("(%li, %li) -> (%li, %li)\n",cur.start.x,cur.start.y,cur.end.x,cur.end.y);
//
//    }
//    print("-----------------\n\n");
    String fileAddress = fileAddressMaker(path, filename);
    FILE * file = fopen(fileAddress,"wb");
    fwrite(&list->size,1 , sizeof( int),file);
    fwrite(&list->length,1 , sizeof( int),file);
    fwrite(list->differenceSequences,list->length, sizeof(struct DifferenceSequence),file);

//    for (int i = 0; i < list->length; ++i) {
//        fwrite(&list->differenceSequences[i],1, sizeof(struct DifferenceSequence), file);
//
//    }
    fclose(file);


}

struct DifferenceList* diffReader(String path, String filename){
    struct DifferenceList *list= malloc(sizeof(struct DifferenceList));
    int size = 0 ;
    String fileAddress = fileAddressMaker(path, filename);
    FILE * file = fopen(fileAddress,"rb");
    fread(&size,1 , sizeof( int),file);
    initList(list,size?size:20);
    fread(&list->length,1 , sizeof( int),file);
//    print("diff reader : %i , %i\n", list->size, list->length);

    fread(list->differenceSequences,list->length, sizeof(struct DifferenceSequence),file);
    fclose(file);
//    for (int j = 0; j < list->length; ++j) {
//        struct DifferenceSequence currentSequence = list->differenceSequences[j];
//
////        print("r - %i \t (%li, %li ) -> (%li , %li)\n",currentSequence.Type, currentSequence.start.x, currentSequence.start.y, currentSequence.end.x,currentSequence.end.y );
//
//    }
    return list;

}
