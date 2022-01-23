//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "src/lib/FP_STACK.h"
#include <benchmark/benchmark.h>
#include <stack>

// push
void consecutivePush(stack<int>& s, int no_of_push)
{
    for(int i=0;i<no_of_push;i++)
        s.push(10);
}


void consecutivePush(FP_STACK& s, int no_of_push)
{
    for(int i=0;i<no_of_push;i++)
        s.push(10, i);
}

void randomizedPush(FP_STACK& s, int no_of_push)
{
    s.push(10,0);
    for(int i=1;i<no_of_push;i++)
        s.push(10, rand()%(s.getCurTime())+1);
}

//pop
void consecutivePop(stack<int>& s, int no_of_pop)
{
    for(int i=0;i<no_of_pop;i++)
        s.pop();
}

void consecutivePop(FP_STACK& s, int no_of_pop)
{
    for(int i=0;i<no_of_pop;i++)
        s.pop(s.getCurTime());
}

void randomizedPop(FP_STACK& s, int no_of_pop)
{
    for(int i=1;i<no_of_pop;i++)
        s.pop(rand()%(s.getCurTime())+1);
}


//////////////////////////////////////

static void BM_STACK_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    FP_STACK s_p;
    //stack<int>s_e;
    state.ResumeTiming();
    consecutivePush(s_p,state.range(0));
      // timing resumes
      // turning off the compiler optimization
    randomizedPop(s_p,state.range(0));
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

