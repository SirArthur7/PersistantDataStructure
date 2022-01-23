//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "FP_QUEUE.h"
#include <benchmark/benchmark.h>
#include <queue>
#include<iostream>
using namespace std;


void consecutiveEnq(Queue * q, int no_of_Enq)
{
    for(int i=0;i<no_of_Enq;i++)
        enqueue(q, i, 10);
}

void randomizedEnq(Queue * q, int no_of_Enq)
{
    enqueue(q,0,10);
    for(int i=1;i<no_of_Enq;i++)
        enqueue(q, rand()%(q->lat_ver)+1, 10);
}

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

static void BM_QUEUE_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
        state.PauseTiming();
        Queue *q_p;
        q_p=init_q();
        //queue<int>q_e;
        state.ResumeTiming();
      
      // timing resumes
      // turning off the compiler optimization

      consecutiveEnq(q_p,state.range(0));  // 8223.88 N, 155.84 N
      //randomizedEnq(q_p,state.range(0));   // 9870.90 N 378.79 N
      
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
    ->Range(1 << 0, 1 << 8)
    ->Complexity();
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ FP_QUEUE_MAIN_ENQ.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

./mybenchmark --benchmark_out="cons_enq_FP_256.csv" --benchmark_out_format=csv
 */


