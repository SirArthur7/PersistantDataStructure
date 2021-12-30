#ifndef TEMPLATE_TEST_WITH_VECTOR_AND_PDSLL_H
#define TEMPLATE_TEST_WITH_VECTOR_AND_PDSLL_H

#include<iostream>
#include<vector>
#include "src/lib/PPDS_LinkedList.h"
#include "src/lib/headers_preprocessors.h"
#include "src/lib/util.h"

using namespace std;


class VECT_AND_PDSLL
{
public:
    //vector<int>vect(MAX_TEST_SIZE);
    //PPDS_LINKED_LIST<int>list(MAX_MOD_COUNT);
    const int max_mod = 3;
    const int max_size = 2000;
    
    VECT_AND_PDSLL(int mm=3,int ms=2000):max_mod(mm),max_size(ms)
    {
        
    }
    
    void randomized_Insert(PPDS_LINKED_LIST<int> &list, vector<int>&vect) {
        // insert code here...
        
        for(int i = 1; i <= max_size/2; i++)
            {
                vect[i-1] = i;
                list.addNode(i-1, i);
            }
        
        for(int i = 1;i<=max_size/2;i++){
            int random_index = rand()%(max_size/2);
            list.addNode(random_index, i);
            vect.insert(vect.begin()+random_index,i);
        }
    }

    void randomized_Update(PPDS_LINKED_LIST<int> &list, vector<int>&vect)
    {
        for(int m = 1;m<=max_size;m++){
            int random_index = 1 + rand()%max_size;
            vect[random_index-1] = m;
            list.updateF1(random_index, m);
        }
    }

    vector<int> trimVect(vector<int> vect)
    {
        vector<int>ans;
        for(auto x:vect){
            if(x==SENTINEL)
                return ans;
            ans.push_back(x);
        }
        return ans;
    }
};


#endif
