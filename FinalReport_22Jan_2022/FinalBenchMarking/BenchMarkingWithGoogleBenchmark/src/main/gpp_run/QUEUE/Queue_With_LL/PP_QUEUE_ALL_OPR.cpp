//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "queue_partially_persistent_pointer_model.h"
#include <benchmark/benchmark.h>
#include <queue>
#include <iostream>
using namespace std;

// enqueue
void consecutiveenqueue(queue_pp * s, int no_of_enqueue)
{
    for(int i=1;i<=no_of_enqueue;i++)
        enqueue(s,i);
}

//dequeue
void consecutivedequeue(queue_pp * s, int no_of_dequeue)
{
    for(int i=1;i<=no_of_dequeue;i++)
        dequeue(s);
}


// enqueue & dequeue
void consecutiveenqueuedequeue(queue_pp * s, int no_of_op)
{
    enqueue(s,0); enqueue(s,1); enqueue(s,2); enqueue(s,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            dequeue(s);
        else
            enqueue(s,10);
    }
}

//////////////////////////////////////

static void BM_queue_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
      queue_pp *st=init_queue_pp();
      //consecutiveenqueue(st,state.range(0));
    state.ResumeTiming();
      // timing resumes
      // turning off the compiler optimization
      
      //consecutiveenqueue(st,state.range(0)); // 187.22 N
      //consecutivedequeue(st,state.range(0)); // 554.27 N
      consecutiveenqueuedequeue(st,state.range(0)); // 354.12 N
      
      
      //forces the compiler to perform all pending writes to global memory
    benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_queue_Wraper)
    ->RangeMultiplier(2)
    ->Range(1<<0, 1<<8)
    ->Complexity( benchmark::oN );
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */


