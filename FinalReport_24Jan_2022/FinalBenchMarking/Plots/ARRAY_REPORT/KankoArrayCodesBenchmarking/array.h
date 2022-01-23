#include<stdlib.h>
#include<stdio.h>
#define MAXSIZE 100
#define MAXVERSION 66666
#define SENTINEL -1

typedef struct arrayNode{
    int val;
    int version;
    int preVersion;
    struct arrayNode * next;
} arrayNode;

typedef struct Array{
    int latestVersion;
    int versionTrack[MAXVERSION];
    arrayNode * list[MAXSIZE];
} Array;

arrayNode * createValue (int value, int vers){
    arrayNode * temp;
    temp = (arrayNode *)malloc(sizeof(arrayNode));
    if(temp == NULL) return temp;

    temp->val = value;
    temp->version = vers;
    temp->next = NULL;

    return temp;
}

int init(Array *PersArr, int * arr, int size){
    for(int i = 0; i<MAXSIZE; i++){
        if(i<size){
            arrayNode * temp = createValue(arr[i], 1);
            (*PersArr).list[i] = temp;
        } else if(i == size){
            arrayNode * temp = createValue(SENTINEL, 1);
            (*PersArr).list[i] = temp;
        } else {
            (*PersArr).list[i] = NULL;
        } 
    }

    (*PersArr).versionTrack[1] = 0;
    (*PersArr).latestVersion = 1;
    
    return 1;
}

int modify (Array *arr, int version, int pos, int newVal){
    (*arr).latestVersion++;
    (*arr).versionTrack[(*arr).latestVersion] = version;

    arrayNode * temp = createValue (newVal, (*arr).latestVersion);
    temp->next = (*arr).list[pos];
    (*arr).list[pos] = temp;

    return (*arr).latestVersion;
}

int retrieve(Array arr, int vers, int pos){
    arrayNode * temp = arr.list[pos];
    while(temp->version > vers){    //future, relative to the requested version 
        temp = temp->next;
    }
    while (1==1){                    
        if(temp->version == vers) return temp->val;
        else if (temp->version > vers){
            temp=temp->next;
        }
        else if (temp->version < vers){         //this version is in the past, relative to requested version, so need to see history of requested version
            vers = arr.versionTrack[vers];
        }
    }
    return temp->val;
}

int size(Array arr, int vers){
    int count = 0;
    while (retrieve(arr, vers, count) != SENTINEL){
        count ++;
    }
    return count;   
}


//extra functions
//inserting and deleting elements from a particular position


// void deleteElem(Array *arr, int vers, int pos){
//     (*arr).latestVersion ++;
//     (*arr).versionTrack[(*arr).latestVersion] = vers;
//     while(1 == 1){ 
//         int nextVal = retrieve((*arr), vers, pos+1);
//         arrayNode * temp = createValue(nextVal , (*arr).latestVersion, vers);
//         temp->next = (*arr).list[pos];
//         (*arr).list[pos] = temp;
//         if(nextVal == SENTINEL) return;
//         pos ++;
//     }
// }


// void insertElem(Array *arr, int vers, int pos, int newVal){
//     (*arr).latestVersion++;
//     (*arr).versionTrack[(*arr).latestVersion] = vers;
//     arrayNode * temp = createValue(newVal , (*arr).latestVersion, vers);
//     temp->next = (*arr).list[pos];
//     (*arr).list[pos] = temp;
//     pos++;

//     while(1 == 1){ 
//         int nextVal = retrieve((*arr), vers, pos-1);
//         arrayNode * temp = createValue(nextVal , (*arr).latestVersion, vers);
//         temp->next = (*arr).list[pos];
//         (*arr).list[pos] = temp;
//         if(nextVal == SENTINEL) return;
//         pos ++;
//     }
// }

void displayList(Array arr, int vers){
    printf("Version %d: ", vers);
    for(int i = 0; ; i++){
        int val = retrieve(arr, vers, i);
        if(val != SENTINEL) printf("%d ", val);
        else break;
    }
}
