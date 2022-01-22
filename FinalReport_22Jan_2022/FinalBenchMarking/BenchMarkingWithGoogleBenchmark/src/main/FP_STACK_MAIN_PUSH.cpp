//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "src/lib/FP_STACK.h"
#include <benchmark/benchmark.h>
#include <stack>

void consecutivePush_E(stack<int>& s, int no_of_push)
{
    for(int i=0;i<no_of_push;i++)
        s.push(10);
}


void consecutivePush_P(FP_STACK& s, int no_of_push)
{
    for(int i=0;i<no_of_push;i++)
        s.push(10, i);
}

void randomizedPush_P(FP_STACK& s, int no_of_push)
{
    s.push(10,0);
    for(int i=1;i<no_of_push;i++)
        s.push(10, rand()%(s.getCurTime())+1);
}


static void BM_STACK_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
        state.PauseTiming();
        FP_STACK s_p;
        stack<int>s_e;
        state.ResumeTiming();
      
      // timing resumes
      // turning off the compiler optimization
        consecutivePush_E(s_e,state.range(0));
      //forces the compiler to perform all pending writes to global memory
        benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_STACK_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 0, 1 << 15)
    ->Complexity();
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */

