//
//  main.cpp
//  P_PDS_LL
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#include "headers_preprocessors.h"
#include "PPDS_LinkedList.h"



int main(int argc, const char * argv[]) {
    // insert code here...
    
    PPDS_LINKED_LIST<int>list;
    
    list.addNode(1);     // 1
    list.addNode(1,2);   // 1 -> 2
    list.addNode(2,3);   // 1 -> 2 -> 3
    list.addNode(3,4);   // 1 -> 2 -> 3 -> 4
    list.addNode(1,200); // 1 ->200 -> 2 -> 3 -> 4
    list.addNode(1,300); // 1 -> 300 -> 200 -> 2 -> 3 -> 4
    list.addNode(1,400); // 1 -> 400 -> 300 -> 200 -> 2 -> 3 -> 4

    list.iterate_and_print_F1_at_ver(list.getCurTime());

    list.updateF1( 3, 799); // 1 -> 400 -> 799 -> 200 -> 2 -> 3 -> 4
    list.updateF1( 4, 899); // 1 -> 400 -> 300 -> 899 -> 2 -> 3 -> 4
    list.updateF1( 7, 7999);// 1 -> 400 -> 300 -> 899 -> 2 -> 3 -> 7999
    list.updateF1( 3, 8999);// 1 -> 400 -> 8999 -> 899 -> 2 ->3 -> 7999
    
    list.iterate_and_print_F1_at_ver(list.getCurTime());

    list.removeNode(7);    // 1 -> 400 -> 8999 -> 899 -> 2 ->3
    list.removeNode(6);    // 1 -> 400 -> 8999 -> 899 -> 2
    list.removeNode(5);    // 1 -> 400 -> 8999 -> 899
    list.removeNode(4);    // 1 -> 400 -> 8999
    list.iterate_and_print_F1_at_ver(list.getCurTime());
    list.removeNode(3);    // 1 -> 400
    list.removeNode(2);    // 1
    list.removeNode(1);    // nullptr
    //list.removeNode(1);    // assertion error
    list.iterate_and_print_F1_at_ver(list.getCurTime());
    
    list.addNode(1);     // 1
    list.addNode(1,2);   // 1 -> 2
    list.addNode(2,3);   // 1 -> 2 -> 3
    list.iterate_and_print_F1_at_ver(list.getCurTime());

    return 0;
}

