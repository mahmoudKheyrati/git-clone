#include "stringDiffSolver.h"
#define MAX_SEQUENCE_SUPPORT 1000


long int max(long int a , long int b){
    return a>b?a:b;
}
int ** createLookupTable(String firstString , String secondString){
    long int lenFirst = strlen(firstString)+1;
    long int lenSecond = strlen(secondString)+1;
    int ** list = malloc(sizeof(int*)*lenSecond);
    for (int i = 0; i < lenSecond; ++i) {
        int* row = malloc(sizeof(int)* lenFirst);
        list[i]=row;
    }
    for (int i = 0; i < lenSecond; ++i) {
        for (int j = 0; j < lenFirst; ++j) {
            list[i][j]=0;
        }
    }
    for (int i = 1; i < lenSecond; ++i) {
        for (int j = 1; j < lenFirst; ++j) {
//            print("(%i , %i):%i    ",i,j,list[i][j]);
            if(firstString[j-1]==secondString[i-1]){
                list[i][j]=list[i-1][j-1]+1;
            }else{
                list[i][j]= max(list[i-1][j],list[i][j-1]);
            }
        }
//        print("\n");
    }

    for (int k = 0; k < lenSecond; ++k) {
        for (int i = 0; i < lenFirst; ++i) {
//            print("%i ",list[k][i]);
        }
//        print("\n");
    }

    return list;
}
struct DifferenceList* parsLookUpTable(int ** list , String firstString, String secondString, long int m , long  int n){
    long int _m=m;
    long int _n=n;
    struct EqualPoint *reversedPoints = malloc(sizeof(struct EqualPoint) * MAX_SEQUENCE_SUPPORT);
    struct EqualPoint *points = malloc(sizeof(struct EqualPoint) * MAX_SEQUENCE_SUPPORT);
    struct EqualPoint *mainPoints = malloc(sizeof(struct EqualPoint) * MAX_SEQUENCE_SUPPORT);
    int mainPointsSize = 0 ;
    int sequencesCount = 0 ;
    // iterate throw list start with bottom right corner of the lookup table
    //for last char
    if(list[n][m-1]==list[n-1][m]){
        //match point
//        print("(%li, %li) -> (%li, %li)\n",m-1,n-1,m,n);
        struct EqualPoint point = {.startX=m-1, .startY=n-1, .endX=m, .endY=n};
        reversedPoints[sequencesCount++]= point;
    }
    int detect=0;
    
    while (n!=0 && m!=0){

        if(list[n][m-1]==list[n-1][m]){
            //match point
//            print("(%li, %li) -> (%li, %li)\n",m-1,n-1,m,n);
            if(list[n][m]>list[n][m-1]){
                struct EqualPoint point = {.startX=m-1, .startY=n-1, .endX=m, .endY=n};
                reversedPoints[sequencesCount++]= point;

                m-=1;
                n-=1;
            }else{
                n-=1;
            }

        } else if (list[n][m-1]>list[n-1][m]){
            // remove
            m-=1;
        }else{
            //insert
            n-=1;
        }
    }

    // reverse the list
//    print("new alog:\n");
    for (int i = 0; i <sequencesCount ; ++i) {

        points[i]= reversedPoints[sequencesCount-i-1];
//        print("(%li, %li) -> (%li, %li)\n",points[i].startX,points[i].startY,points[i].endX,points[i].endY);
    }
//    print("------------\n");


    for (int k = 0; k < sequencesCount; ++k) {
        struct EqualPoint cur=points[k];
        struct EqualPoint next=points[k+1];
        long int startX = cur.startX;
        long int startY = cur.startY;
        long int count = 0 ;
        // matches
        while (cur.endX== next.startX && cur.endY==next.startY){
            cur = next;
            next=points[k+2+count];
            count++;
        }
        cur.startX = startX;
        cur.startY=startY;
        mainPoints[mainPointsSize++]=cur;

//        print("(%li, %li) -> (%li, %li)\n",cur.startX,cur.startY,cur.endX,cur.endY);


        k+=count;
    }


    return parser( mainPoints, mainPointsSize, firstString, secondString, _m, _n);

}
