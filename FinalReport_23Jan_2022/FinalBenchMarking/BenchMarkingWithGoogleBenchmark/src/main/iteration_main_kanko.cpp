//
//  main.cpp
//  P_PDS_LL_BenchMark
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "src/lib/Array.h"
#include "src/lib/headers_preprocessors.h"
#include <benchmark/benchmark.h>
#define DEFAULT_N 260
#define DEFAULT_M 260

void initLL_and_autoUpdate(Array* A,int N=DEFAULT_N,int M = DEFAULT_M)
{
    init(A,N);
    for(int i = 0;i<N;i++)
    {
        int cur_ver = A->latestVersion , no_of_mods = M;
        for(int m=1;m<no_of_mods;m++)
            modify(A, cur_ver , i, 100);
    }
}



static void BM_IterationOverLL_Wraper(benchmark::State& state) {
   unordered_map<int, int> ump;
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
    Array A;
    initLL_and_autoUpdate(&A,DEFAULT_N,state.range(0)); // keep N constant
    //initLL_and_autoUpdate(&A,state.range(0),DEFAULT_M); // keep M constant

    state.ResumeTiming();
      
      // timing resumes
      // turning off the compiler optimization
      int selected_ver = rand()%A.latestVersion+1 ;
      benchmark::DoNotOptimize(dummyIter(A,selected_ver));
      //forces the compiler to perform all pending writes to global memory
      benchmark::ClobberMemory();
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetComplexityN(state.range(0)); // 2 * state.range(0) => current length of Linked List
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_IterationOverLL_Wraper)
    ->RangeMultiplier(2)
    ->Range(1 << 0, 1 << 8)
    ->Complexity(benchmark::oNSquared);
    // benchmark::oN , oNSquared // wrt N , wrt M2

BENCHMARK_MAIN();

/*
 g++ iteration_main.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

 */

