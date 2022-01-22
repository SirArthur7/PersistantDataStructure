//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "FP_QUEUE.h"
#include <benchmark/benchmark.h>
#include <queue>

// enqueue & dequeue
void consecutiveEnqDeq(FP_QUEUE& q, int no_of_op)
{
    q.enqueue(10,0); q.enqueue(10,1); q.enqueue(10,2); q.enqueue(10,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            q.dequeue(q.getCurTime());
        else
            q.enqueue(10,q.getCurTime());
    }
}

void consecutiveEnqDeq(queue<int>& q, int no_of_op)
{
    q.push(10); q.push(10); q.push(10); q.push(10);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2){
            if(q.size())
                q.pop();
        }
        else
            q.push(10);
    }
}

void randomizedEnqDeq(FP_QUEUE& q, int no_of_op)
{
    q.enqueue(10,0); q.enqueue(10,1); q.enqueue(10,2); q.enqueue(10,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            q.enqueue(10, rand()%(q.getCurTime())+1);
        else
            q.dequeue(rand()%(q.getCurTime())+1);
    }
}


//////////////////////////////////////

static void BM_QUEUE_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    FP_QUEUE q_p;
    //queue<int>q_e;
    state.ResumeTiming();
      // timing resumes
      // turning off the compiler optimization
      
      
      //consecutiveEnqDeq(q_e,state.range(0)); // 44.99 N
      
      //consecutiveEnqDeq(q_p,state.range(0)); // 64.28 N
      randomizedEnqDeq(q_p,state.range(0)); // 11.54 NlgN
      
      
      //forces the compiler to perform all pending writes to global memory
    benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_QUEUE_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 0, 1 << 15)
    ->Complexity();
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */



