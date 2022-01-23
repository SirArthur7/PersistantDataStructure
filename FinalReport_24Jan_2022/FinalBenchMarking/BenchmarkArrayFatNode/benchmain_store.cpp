//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "array.h"
#include <benchmark/benchmark.h>
#include <stack>
#include <iostream>
using namespace std;

//////////////////////////////////////////////  target function
//  randomStore/Value_Modifcation
void randomStore(Array *PersArr, int no_of_input){
    for(int i = 1; i <= no_of_input; i++)
        modify(PersArr, rand()%(*PersArr).latestVersion+1, rand()%MAXSIZE, rand());
}

// randomRetrieve
void randomRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++)
        retrieve(*PersArr, (rand()%(*PersArr).latestVersion)+1, rand()%MAXSIZE);
}
//////////////////////////////////////


static void BM_ARRAY_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
      
      int * arr;
      Array PersArr;
      int size = MAXSIZE;
      arr = (int *)malloc((size+1)*sizeof(int));
	  init(&PersArr, arr, size);
      state.ResumeTiming();
      // timing resumes
      
      randomStore (&PersArr, state.range(0)); //100.59 N

      // timing ends
      free(arr);
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0)); //
    state.SetComplexityN(state.range(0));
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_ARRAY_Wraper)
    ->RangeMultiplier(2)
    ->Range(1<<0, 1<<14)
    ->Complexity();

BENCHMARK_MAIN();

/*
 Compile:
 g++ benchmain_store.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
 
 Run:
 ./mybenchmark --benchmark_out="random_store_FP_array.csv" --benchmark_out_format=csv
 */



