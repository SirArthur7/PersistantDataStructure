//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "headers_preprocessors.h"
#include "PPDS_LinkedList.h"
//#include <bits/benchmark.h>

#define MAX_TEST 10000

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    FILE *fp = NULL;
    fp = fopen("/Users/debasmitroy/Desktop/mod_N10000.csv", "w");

    int m = 0;
    while(m++<=30)
    {
    const int length_of_LL = MAX_TEST, no_of_random_F1updates = MAX_TEST,no_of_random_insertion = MAX_TEST ;
    PPDS_LINKED_LIST<int>list(m);
    for(int i = 1; i <= length_of_LL; i++)
        list.addNode(i-1, i);
    
    for(int m = 1;m<=no_of_random_F1updates;m++){
        int random_index = 1 + rand()%length_of_LL;
        list.updateF1(random_index, m);
    }

    for(int m = 1;m<=no_of_random_insertion;m++){
        int random_index = rand()%length_of_LL;
        list.addNode(random_index, m);
    }
    
    //list.iterate_and_print_F1_at_ver(list.getCurTime());
    cout<<"Current number Of Nodes Are Used: "<<list.getCurrentNoOfNodesUsed()<<endl;
    cout<<"Current Length of LL: "<<list.get_length_at_ver(list.getCurTime())<<endl;
    cout<<"Total Update Request: "<<list.get_total_update_requests()<<endl;
    cout<<"Current Memory Usage For Allocation Of Nodes: "<<list.getCurMemoryUsage()<<" Byte"<<endl;
        DIVIDER;
    
        fprintf(fp, "%d, %d\n",m,list.getCurMemoryUsage());
    }
    
    fclose(fp);
    return 0;
}
