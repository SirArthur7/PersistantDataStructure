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
    for(int i = 1; i <= no_of_input; i++)
        modify(PersArr, rand()%(*PersArr).latestVersion+1, rand()%MAXSIZE, rand());
}

//  consecutive Modifcation / simulating Partial Peristence
void consecutiveStore(Array *PersArr, int no_of_input){
    for(int i = 1; i <= no_of_input; i++)
        modify(PersArr,PersArr->latestVersion, rand()%MAXSIZE, rand());
}


// randomRetrieve
void randomRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++)
        retrieve(*PersArr, (rand()%(*PersArr).latestVersion)+1, rand()%MAXSIZE);
}

// consceutiveRetrieve
void consceutiveRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++)
        retrieve(*PersArr, (*PersArr).latestVersion+1-i, rand()%MAXSIZE);
}
/////////////////////



int main(int argc, const char * argv[]) {
    // insert code here...
    
    int * arr;
    Array PersArr;
    int size = MAXSIZE;
    arr = (int *)malloc((size+1)*sizeof(int));
    init(&PersArr, arr, size);
    consecutiveStore (&PersArr, 20);
    
    randomRetrieve (&PersArr, 10); // 7381.49 N
    displayList(PersArr, PersArr.latestVersion);
    // timing ends
    free(arr);
    
    return 0;
}
