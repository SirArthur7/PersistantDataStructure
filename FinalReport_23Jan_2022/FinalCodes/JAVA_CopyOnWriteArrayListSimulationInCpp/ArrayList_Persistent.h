//
//  ArrayList_Persistent.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 30/12/21.
//

#ifndef ArrayList_Persistent_h
#define ArrayList_Persistent_h
#include "headers_precossesor.h"
#define MAX_VER 1024

template <class T>
class ArrayListPersistent {
private:
    T* arr_s[MAX_VER];
    size_t cur_size;
    int cur_version;
    mutex g_mutex1,g_mutex2;  // shared var
    
    void copyContent(T* from, T* to,size_t src_size);
public:

    ArrayListPersistent();
    ~ArrayListPersistent();
    
    void add(T); // thread safe
    void iterate_print(); // not thread safe
    T accumult();// not thread safe
};


template<class T>
ArrayListPersistent<T>::ArrayListPersistent()
{
    cur_size = 0;
    cur_version = 0;
    for(int i = 0 ; i < MAX_VER; i++)
        arr_s[i] = nullptr;
}


template<class T>
void ArrayListPersistent<T>::add(T e)
{
    unique_lock<mutex>ul(g_mutex1); // locks while contruction, unlocks while destructed RAII, + custom locking unlcking
    T* prev_ver_reff = arr_s[cur_version];
    size_t prev_ver_size = cur_size;
    int cur_ver = ++cur_version;
    ++cur_size;
    arr_s[cur_ver] = (T*)malloc(sizeof(T)*(prev_ver_size+1));
    copyContent(prev_ver_reff,arr_s[cur_ver],prev_ver_size);
    ul.unlock();

    
    arr_s[cur_ver][prev_ver_size] = e;
    assert(arr_s[cur_ver]!=nullptr);
    //ul.unlock(); // unlocks
}

template<class T>
void ArrayListPersistent<T>::iterate_print()
{
    for(int i=0;i<cur_size;i++)
        cout<<arr_s[cur_version][i]<<" ";
    cout<<endl;
}

template<class T>
T ArrayListPersistent<T>::accumult()
{
    T s = 0;
    for(int i=0;i<cur_size;i++)
    {
        s+=arr_s[cur_version][i];
    }
    return s;
}


template<class T>
void ArrayListPersistent<T>::copyContent(T* from ,T* to, size_t prev_size)
{
    if(from==nullptr)
        return;
    for(int i=0;i<prev_size;i++)
        to[i] = from[i];
}


template<class T>
ArrayListPersistent<T>::~ArrayListPersistent()
{
    for(int i=0;i<cur_size;i++)
    { if(arr_s[i]!=nullptr)
        free(arr_s[i]);}
}


#endif /* ArrayList_Persistent_h */
