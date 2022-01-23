//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "FP_STACK.h"
#include <benchmark/benchmark.h>
#include <stack>

// push & pop
void consecutivePushPop(FP_STACK& s, int no_of_op)
{
    s.push(10,0); s.push(10,1); s.push(10,2); s.push(10,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            s.pop(s.getCurTime());
        else
            s.push(10,s.getCurTime());
    }
}

void consecutivePushPop(stack<int>& s, int no_of_op)
{
    s.push(10); s.push(10); s.push(10); s.push(10);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2){
            if(s.size())
                s.pop();
        }
        else
            s.push(10);
    }
}

void randomizedPushPop(FP_STACK& s, int no_of_op)
{
    s.push(10,0); s.push(10,1); s.push(10,2); s.push(10,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            s.push(10, rand()%(s.getCurTime())+1);
        else
            s.pop(rand()%(s.getCurTime())+1);
    }
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
      // timing resumes
      // turning off the compiler optimization
      
      
      //consecutivePushPop(s_e,state.range(0)); // 48.51 N
      
      //consecutivePushPop(s_p,state.range(0)); // 18.87 N
      randomizedPushPop(s_p,state.range(0)); // 33.33 N
      
      
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


