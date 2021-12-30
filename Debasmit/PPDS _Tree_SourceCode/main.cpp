//
//  main.cpp
//  P_PDS_TREE
//
//  Created by DEBASMIT ROY on 27/12/21.
//

#include <iostream>
#include "PPDS_BinaryTree.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    
    PPDS_BIN_TREE<int>t1;
    
    t1.addNode(1);

    
    t1.addNode("S", LEFT, 2);

    
    t1.addNode("S", RIGHT, 3);

    
    t1.addNode("SL", LEFT, 4);
    
    
    t1.addNode("SL", RIGHT, 5);
    
    
    t1.addNode("SR", RIGHT, 6);
    
    
    t1.addNode("SLR", LEFT, 7);
    
    
    t1.updateF1("SRR", 60);
    
    
    t1.addNode(8);
    
    
    t1.addNode("SL", LEFT, 9);
    
    t1.addNode("S", RIGHT, 10);
    
    t1.removeLeafNode("SLLLL");
    
    t1.iterate_and_print_F1_inBFS_at_ver(t1.getCurTime());
    
    return 0;
}

