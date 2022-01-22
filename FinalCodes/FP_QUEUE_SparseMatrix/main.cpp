//
//  main.cpp
//  FPDS_Queue
//
//  Created by DEBASMIT ROY on 18/01/22.
//

#include <iostream>
#include "FP_QUEUE.h"
#include<queue>
int main(int argc, const char * argv[]) {
    // insert code here...
    
    FP_QUEUE q;
    
    q.enqueue(10, 0); // 1
    q.enqueue(20, 1); // 2
    q.enqueue(30, 2); // 3
    q.dequeue(3); // 4
    q.dequeue(3); // 5
    q.enqueue(40, 5); // 6
    q.dequeue(4); // 7
    q.enqueue(50, 5); // 8
    q.dequeue(7); // 9
    q.dequeue(4); // 10
    q.enqueue(90, 9); // 11
    q.enqueue(100, 11); // 12

    q.allVerDisplay();
    
    cout<<q.rear(1)<<endl;
    cout<<q.front(12)<<endl;
    
    return 0;
}
