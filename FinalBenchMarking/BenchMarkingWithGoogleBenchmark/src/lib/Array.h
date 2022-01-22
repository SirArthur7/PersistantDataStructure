//
//  Array.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 11/01/22.
//

#ifndef Array_h
#define Array_h
#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include "util.h"
#define MAXSIZE 100000
#define MAXVERSION 100000
#define SENTINEL -1
using namespace std;


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




void RandomUserInput(Array **A)
{
    
}

arrayNode * createValue (int value, int vers, int pre){
    arrayNode * temp;
    temp = (arrayNode *)malloc(sizeof(arrayNode));
    if(temp == NULL) return temp;

    temp->preVersion = pre;
    temp->val = value;
    temp->version = vers;
    temp->next = NULL;

    return temp;
}

void deleteArray(Array *arr){
    for(int i = 0; (*arr).list[i] != NULL; i++){
        // arrayNode * head = arr.list[i];
        (*arr).list[i] = NULL;
        // while(head != NULL){
        //     arrayNode *temp = head;
        //     head = head->next;
        //     free(temp);
        // }
    }
}

void init (Array *arr,int n){
    deleteArray(arr);
    //int n;
    //printf("Enter number of values in array\n");
    //scanf("%d", &n);
    int i;

    
    for(i = 0; i<n; i++){
        int val;
        val = 2*i;
        //val = rand()%100;
        //scanf("%d", &val);
        (*arr).list[i] = createValue(val, 1, 0);
    }

    (*arr).list[i] = createValue(SENTINEL, 1, 0);
    (*arr).latestVersion = 1;
    (*arr).versionTrack[1] = 0;
}

void modify (Array *arr, int version, int pos, int newVal){
    (*arr).latestVersion++;
    (*arr).versionTrack[(*arr).latestVersion] = version;
    arrayNode * temp = createValue (newVal, (*arr).latestVersion, version);
    temp->next = (*arr).list[pos];
    (*arr).list[pos] = temp;
}

int retrieve(Array arr, int vers, int pos){
    arrayNode * temp = arr.list[pos];
    while(temp->version > vers){
        temp = temp->next;
    }
    while (1==1){
        if(temp->version == vers) return temp->val;
        else if (temp->version > vers){
            temp=temp->next;
        }
        else if (temp->version < vers){
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

void deleteElem(Array *arr, int vers, int pos){
    (*arr).latestVersion ++;
    (*arr).versionTrack[(*arr).latestVersion] = vers;
    while(1 == 1){
        int nextVal = retrieve((*arr), vers, pos+1);
        arrayNode * temp = createValue(nextVal , (*arr).latestVersion, vers);
        temp->next = (*arr).list[pos];
        (*arr).list[pos] = temp;
        if(nextVal == SENTINEL) return;
        pos ++;
    }
}

void insertElem(Array *arr, int vers, int pos, int newVal){
    (*arr).latestVersion++;
    (*arr).versionTrack[(*arr).latestVersion] = vers;
    arrayNode * temp = createValue(newVal , (*arr).latestVersion, vers);
    temp->next = (*arr).list[pos];
    (*arr).list[pos] = temp;
    pos++;

    while(1 == 1){
        int nextVal = retrieve((*arr), vers, pos-1);
        arrayNode * temp = createValue(nextVal , (*arr).latestVersion, vers);
        temp->next = (*arr).list[pos];
        (*arr).list[pos] = temp;
        if(nextVal == SENTINEL) return;
        pos ++;
    }
}

void displayList(Array arr, int vers){
    for(int i = 0; ; i++){
        int val = retrieve(arr, vers, i);
        if(val != SENTINEL) printf("%d ", val);
        else break;
    }
    printf("\n");
}

int dummyIter(Array arr, int vers){
    for(int i = 0; ; i++){
        int val = retrieve(arr, vers, i);
        if(val != SENTINEL){}
        else break;
    }
    return 1;
}

#endif /* Array_h */
