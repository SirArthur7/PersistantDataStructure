//
//  main.cpp
//  JAVA_CopyOnWriteArrayList_1
//
//  Created by DEBASMIT ROY on 30/12/21.
//

#include <iostream>
#include "ArrayListNaive.h"
#include "ArrayList_threadSafe.h"
#include "headers_precossesor.h"
#include "ArrayList_Persistent.h"
#define RANGE 500

void insert_N_ones_to_naive(ArrayListNaive<ll>&a, int n)
{
    for(int i = 1;i<=n;i++)
        a.add(1);
}

void insert_N_ones_to_threadSafe(ArrayListThreadSafe<ll>&a, int n)
{
    for(int i = 1;i<=n;i++)
        a.add(1);
}

void insert_N_ones_to_persistent(ArrayListPersistent<ll>&a, int n)
{
    for(int i = 1;i<=n;i++)
        a.add(1);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    {
        ArrayListNaive<ll>a1;
        vector<thread> threads(2);
        threads[0] = thread(insert_N_ones_to_naive,ref(a1),RANGE);
        //threads[1] = thread(insert_N_ones_to_naive,ref(a),RANGE); // race condtion
        threads[0].join();
        //threads[1].join();  // race condtion
        cout<<"Sum: "<<a1.accumult()<<endl;
    }

    {
        ArrayListThreadSafe<ll>a2;
        vector<thread> threads(2);
        threads[0] = thread(insert_N_ones_to_threadSafe,ref(a2),RANGE);
        threads[1] = thread(insert_N_ones_to_threadSafe,ref(a2),RANGE); // race condtion
        threads[0].join();
        threads[1].join();  // no race condtion
        cout<<"Sum: "<<a2.accumult()<<endl;
    }
    
    {
        ArrayListPersistent<ll>a3;
        vector<thread> threads(2);
        threads[0] = thread(insert_N_ones_to_persistent,ref(a3),RANGE);
        threads[1] = thread(insert_N_ones_to_persistent,ref(a3),RANGE); // race condtion
        threads[0].join();
        threads[1].join();  // no race condtion
        cout<<"Sum: "<<a3.accumult()<<endl;
    }
    

    return 0;
}
