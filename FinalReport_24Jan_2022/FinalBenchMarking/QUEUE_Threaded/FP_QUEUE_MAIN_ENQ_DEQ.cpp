//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "FP_QUEUE.h"
#include <benchmark/benchmark.h>
#include <queue>
#include<iostream>
using namespace std;
/*
   #include "1.h"

   int main()
   {
       Queue *q;
       q=init_q();
       enqueue(q, 0, 2);
       enqueue(q, 0, 5);
       enqueue(q, 1, 7);
       enqueue(q, 1, 9);
       dequeue(q, 1);
       destroy_q(q);
   }
*/
  

// enqueue & dequeue
void consecutiveEnqDeq(Queue * q, int no_of_op)
{
    enqueue(q,0,10); enqueue(q,1,10); enqueue(q,2,10); enqueue(q,3,10);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            dequeue(q,q->lat_ver);
        else
            enqueue(q,q->lat_ver,10);
    }
}

void randomizedEnqDeq(Queue * q, int no_of_op)
{
    enqueue(q,0,10); enqueue(q,1,10); enqueue(q,2,10); enqueue(q,3,10);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            enqueue(q,rand()%(q->lat_ver)+1,10);
        else
            dequeue(q,rand()%(q->lat_ver)+1);
    }
}


//////////////////////////////////////

static void BM_QUEUE_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    Queue *q_p;
    q_p=init_q();
    state.ResumeTiming();
      // timing resumes
      // turning off the compiler optimization
      
            
      consecutiveEnqDeq(q_p,state.range(0)); // 8174.92 N 229 N
      //randomizedEnqDeq(q_p,state.range(0)); // 210.01 N 8321.50 N
      
      
      //forces the compiler to perform all pending writes to global memory
      benchmark::ClobberMemory();
      state.PauseTiming();
      //destroy_q(q_p);
      state.ResumeTiming();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_QUEUE_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 0, 1 << 12)
    ->Complexity();
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ FP_QUEUE_MAIN_ENQ_DEQ.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
 
 ./mybenchmark --benchmark_out="cons_enq_deq_PP_4096.csv" --benchmark_out_format=csv
 */



