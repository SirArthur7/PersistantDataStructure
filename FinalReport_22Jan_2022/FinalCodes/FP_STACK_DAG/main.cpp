//
//  main.cpp
//  FP_STACK
//
//  Created by DEBASMIT ROY on 19/01/22.
//

#include "FP_STACK.h"
#include <iostream>
#include <stack>
using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
       
    FP_STACK s;
    s.push(10, 0);
    s.push(20, 1);
    s.push(30, 2);
    s.push(40, 3);
    
    s.pop(3);
    s.iterateFromTop(1);
    
    return 0;
}
