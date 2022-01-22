//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "FP_QUEUE.h"
#include <benchmark/benchmark.h>
#include <queue>

void consecutiveEnq(queue<int>& q, int no_of_Enq)
{
    for(int i=0;i<no_of_Enq;i++)
        q.push(10);
}


void consecutiveEnq(FP_QUEUE& q, int no_of_Enq)
{
    for(int i=0;i<no_of_Enq;i++)
        q.enqueue(10, i);
}

void randomizedEnq(FP_QUEUE& q, int no_of_Enq)
{
    q.enqueue(10,0);
    for(int i=1;i<no_of_Enq;i++)
        q.enqueue(10, rand()%(q.getCurTime())+1);
}


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
      //consecutiveEnq(q_e,state.range(0));  // 47.88 N
      consecutiveEnq(q_p,state.range(0));  // 6.79 NlgN
      //randomizedEnq(q_p,state.range(0));   // 7.21 NlgN
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


