//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "headers_preprocessors.h"
#include "PPDS_LinkedList.h"
#include <benchmark/benchmark.h>

const int max_mod = 3;


void initLL_randomized(PPDS_LINKED_LIST<int> &list, int MAX_TEST) {
    // insert code here...

    for(int i = 1; i <= MAX_TEST; i++)
        list.addNode(i-1, i);
    
    for(int m = 1;m<=MAX_TEST;m++){
        int random_index = 1 + rand()%MAX_TEST;
        list.updateF1(random_index, m);
    }

    for(int m = 1;m<=MAX_TEST;m++){
        int random_index = rand()%MAX_TEST;
        list.addNode(random_index, m);
    }
}



static void BM_IterationOverLL_Wraper(benchmark::State& state) {
   unordered_map<int, int> ump;
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    PPDS_LINKED_LIST<int>list(max_mod);
    initLL_randomized(list,state.range(0));
    state.ResumeTiming();
      
      // timing resumes
      // turning off the compiler optimization
      benchmark::DoNotOptimize(list.iterate_performance_check(list.getCurTime()));
      //forces the compiler to perform all pending writes to global memory
      benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(2 * state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_IterationOverLL_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 0, 1 << 8)
    ->Complexity();

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */
