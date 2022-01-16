#include"array.h"
#include<stdio.h>

int main(){
    //initialise a array with which persistent array is created
    int * arr;
    int size;

    printf("Number of Elements: ");
    scanf("%d", &size);

    arr = (int *)malloc(size*sizeof(int));

    printf("Enter the Elements: ");
    for(int i = 0; i<size; i++){
        scanf("%d", arr+i);
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
    displayList(PersArr, 4);
    printf("\n");

}