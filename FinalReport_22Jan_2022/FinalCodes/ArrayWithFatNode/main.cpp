//
//  main.cpp
//  FP_ARRAY
//
//  Created by DEBASMIT ROY on 21/01/22.
//

#include <iostream>
using namespace std;
#include "Array.h"

//////////////////////////////////////////////  target function
//  randomStore/Value_Modifcation
void randomStore(Array *PersArr, int no_of_input){
    for(int i = 1; i <= no_of_input; i++){
        modify(PersArr, rand()%(*PersArr).latestVersion+1, i%(MAXSIZE-1), 69);}
}

//  consecutive Modifcation / simulating Partial Peristence
void consecutiveStore(Array *PersArr, int no_of_input){
    for(int i = 1; i <= no_of_input; i++){
        cout<<rand()<<endl;
        modify(PersArr,PersArr->latestVersion, i%(MAXSIZE-1), i);}
}


// randomRetrieve
void randomRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++)
        retrieve(*PersArr, (rand()%(*PersArr).latestVersion)+1, rand()%(MAXSIZE-1));
}

// consceutiveRetrieve
void consceutiveRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++){
        cout<<rand()<<endl;
        retrieve(*PersArr, (*PersArr).latestVersion+1-i, rand()%(MAXSIZE-1));}
}
/////////////////////



int main(int argc, const char * argv[]) {
    // insert code here...
   

    int * arr;
        int size = 10;

        printf("Number of Elements: ");
        //scanf("%d", &size);

        arr = (int *)malloc(size*sizeof(int));

        printf("Enter the Elements: ");
        for(int i = 0; i<size; i++){
            arr[i] = i;
        }
        

        //Persistant array

        Array PersArr;
        printf("version %d created\n", init(&PersArr, arr, size));
        printf("version %d created\n", modify(&PersArr, 1, 2, 10));
        printf("version %d created\n", modify(&PersArr, 1, 3, 10));
        printf("version %d created\n", modify(&PersArr, 2, 3, 10));
        
        

        displayList(PersArr, 1);
        printf("\n");
        displayList(PersArr, 2);
        printf("\n");
        displayList(PersArr, 3);
        printf("\n");
        displayList(PersArr, PersArr.latestVersion);
        printf("\n");
    
    return 0;
}
