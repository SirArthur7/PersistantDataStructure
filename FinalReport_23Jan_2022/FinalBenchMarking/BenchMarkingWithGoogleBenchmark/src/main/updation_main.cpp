//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "src/lib/headers_preprocessors.h"
#include "src/lib/PPDS_LinkedList.h"
#include <benchmark/benchmark.h>

const int max_mod = 3;
const int max_size = 1200;

void initLL_randomized(PPDS_LINKED_LIST<int> &list) {
    // insert code here...
    
    for(int i = 1; i <= max_size/2; i++)
        list.addNode(i-1, i);
    
    for(int m = 1;m<=max_size/2;m++){
        int random_index = rand()%(max_size/2);
        list.addNode(random_index, m);
    }
}

void random_m_updates(PPDS_LINKED_LIST<int> &list, int max_m)
{
    for(int m = 1;m<=max_m;m++){
        int random_index = 1 + rand()%(max_m/2);
        list.updateF1(random_index, m);
    }
}


static void BM_Updation_OverLL_Wraper(benchmark::State& state) {
   unordered_map<int, int> ump;
   PPDS_LINKED_LIST<int>list(max_mod);
   initLL_randomized(list);
// same thing
    
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    // may re init here
    state.ResumeTiming();
      
      // timing resumes
      // turning off the compiler optimization
      //benchmark::DoNotOptimize(random_m_updates(list,state.range(0)));
      
      auto max_m = state.range(0);
      for(int m = 1;m<=max_m;m++){
          int random_index = 1 + rand()%(max_m);
          list.updateF1(random_index, m);
      }
      
      //forces the compiler to perform all pending writes to global memory
      //benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    // we are excluding the time to reach node before performing updation
    // so, our time complexity would be independent of the length(constant)
    state.SetComplexityN(state.range(0) * max_size);
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_Updation_OverLL_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 1, 1 << 10)
    ->Complexity(benchmark::oN);

BENCHMARK_MAIN();

/*
 enum BigO { oNone, o1, oN, oNSquared, oNCubed, oLogN, oNLogN, oAuto, oLambda };

 g++ updation_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
 */
