//
//  ArrayList_threadSafe.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 30/12/21.
//

#ifndef ArrayList_threadSafe_h
#define ArrayList_threadSafe_h
#include "headers_precossesor.h"

template <class T>
class ArrayListThreadSafe {
private:
    T* arr;
    size_t size;
    mutex g_mutex1,g_mutex2;  // shared var
public:

    ArrayListThreadSafe():size(0),arr(nullptr){}
    ~ArrayListThreadSafe();
    
    void add(T);
    void iterate_print();
    T accumult();
};

template<class T>
void ArrayListThreadSafe<T>::add(T e)
{
    unique_lock<mutex>ul(g_mutex1); // locks while contruction, unlocks while destructed RAII, + custom locking unlcking
    ++size;
    if(arr==nullptr)
        arr = (T*)malloc(sizeof(T));
    else{
        arr = (T*)realloc(arr, size * sizeof(T));
        
    }
    assert(arr!=nullptr);
    arr[size-1] = e;
    ul.unlock();
}

template<class T>
void ArrayListThreadSafe<T>::iterate_print()
{
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

template<class T>
T ArrayListThreadSafe<T>::accumult()
{
    T s = 0;
    for(int i=0;i<size;i++){s+=arr[i];}
    return s;
}

template<class T>
ArrayListThreadSafe<T>::~ArrayListThreadSafe()
{
    if(arr!=nullptr)
        free(arr);
}


#endif /* ArrayList_threadSafe_h */
