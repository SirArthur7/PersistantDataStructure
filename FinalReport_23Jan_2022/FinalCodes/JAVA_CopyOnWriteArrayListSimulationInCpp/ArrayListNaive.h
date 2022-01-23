//
//  ArrayListNaive.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 30/12/21.
//

#ifndef ArrayListNaive_h
#define ArrayListNaive_h
#include "headers_precossesor.h"

template <class T>
class ArrayListNaive {
private:
    T* arr;
    size_t size;
    
public:
    ArrayListNaive():size(0),arr(nullptr){}
    ~ArrayListNaive();
    
    void add(T);
    void iterate_print();
    T accumult();
};

template<class T>
void ArrayListNaive<T>::add(T e)
{
    ++size;
    if(arr==nullptr)
        arr = (T*)malloc(sizeof(T));
    else{
        arr = (T*)realloc(arr, size * sizeof(T));
        
    }
    
    assert(arr!=nullptr);
    arr[size-1] = e;
}

template<class T>
void ArrayListNaive<T>::iterate_print()
{
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

template<class T>
T ArrayListNaive<T>::accumult()
{
    T s = 0;
    for(int i=0;i<size;i++){s+=arr[i];}
    return s;
}

template<class T>
ArrayListNaive<T>::~ArrayListNaive()
{
    if(arr!=nullptr)
        free(arr);
}

#endif /* ArrayListNaive_h */
