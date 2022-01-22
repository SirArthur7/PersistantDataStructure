//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "stack_partially_persistent_pointer_model.h"
#include <benchmark/benchmark.h>
#include <stack>
#include <iostream>
using namespace std;

// push
void consecutivePush(stack_pp * s, int no_of_push)
{
    for(int i=1;i<=no_of_push;i++)
        push(s,i);
}

//pop
void consecutivePop(stack_pp * s, int no_of_pop)
{
    for(int i=1;i<=no_of_pop;i++)
        pop(s);
}


// push & pop
void consecutivePushPop(stack_pp * s, int no_of_op)
{
    push(s,0); push(s,1); push(s,2); push(s,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            pop(s);
        else
            push(s,10);
    }
}

//////////////////////////////////////

static void BM_STACK_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
      stack_pp *st=init_stack_pp();
      //consecutivePush(st,state.range(0)); // 48.51 N
    state.ResumeTiming();
      // timing resumes
      // turning off the compiler optimization
      
      //consecutivePush(st,state.range(0)); // 758.24 N
      //consecutivePop(st,state.range(0)); // 420.27 N
      consecutivePushPop(st,state.range(0)); // 351.12 N
      
      
      //forces the compiler to perform all pending writes to global memory
    benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_STACK_Wraper)
    ->RangeMultiplier(2)
    ->Range(1<<0, 1<<5)
    ->Complexity( benchmark::oN );
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */


