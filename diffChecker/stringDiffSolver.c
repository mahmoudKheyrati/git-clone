#include "stringDiffSolver.h"
long int max(long int a , long int b){
    return a>b?a:b;
}
void createLookupTable(String firstString , String secondString){
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
            print("%i ",list[k][i]);
        }
        print("\n");
    }
}


