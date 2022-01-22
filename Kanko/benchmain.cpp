//
//  main.cpp
//
//
//  Created by DEBASMIT ROY on 29/12/21.
//

#include "array.h" // tor header file ta
#include <benchmark/benchmark.h>
#include <stack>
#include <iostream>
using namespace std;

//////////////////////////////////////////////  target function gulo likhlam
// only push
void consecutiveStore(Array *PersArr, int no_of_input){
    for(int i = 1; i <= no_of_input; i++)
        modify(PersArr, rand()%(*PersArr).latestVersion+1, rand()%100, rand());
}

//only pop
void consecutiveRetrieve(Array *PersArr, int no_of_input)
{
    for(int i=1;i<=no_of_input;i++)
        retrieve(*PersArr, (rand()%(*PersArr).latestVersion)+1, rand()%100);
}


// both push & pop random
/*void consecutivePushPop(stack_pp * s, int no_of_op)
{
    push(s,0); push(s,1); push(s,2); push(s,3);
    for(int i=0;i<no_of_op;i++)
    {
        if(rand()%2)
            pop(s);
        else
            push(s,10);
    }
}*/
//////////////////////////////////////


static void BM_STACK_Wraper(benchmark::State& state) {
// same thing
  for(auto _:state) {
      // this is time profiled
    state.PauseTiming();
      
      int * arr;
      Array PersArr;
      int size = 100;
      arr = (int *)malloc((size+1)*sizeof(int));
	  init(&PersArr, arr, size);
      consecutiveStore (&PersArr, state.range(0)); // 758.24 N
      // tor initialization gulo ekhane lekh
      //stack_pp *st=init_stack_pp();
      //consecutivePush(st,state.range(0)); // 48.51 N
      
    state.ResumeTiming();
      // timing resumes
      
      // ekhane tui jeglo ke profile korte chas seglo lekh
      consecutiveRetrieve (PersArr, state.range(0)); // 420.27 N
      //consecutivePushPop(st,state.range(0)); // 351.12 N
      
      // timing ends
      
      
  }
    
    state.SetItemsProcessed(state.iterations() * state.range(0)); //
    state.SetComplexityN(state.range(0));
    state.SetLabel(to_string(state.range(0)));
}



BENCHMARK(BM_STACK_Wraper)
    ->RangeMultiplier(2)
    ->Range(1<<0, 1<<5) // !!!!!!!!!!!!!!! Range selector 2^0 -> 2^5 a6e
    ->Complexity( benchmark::oN );
    // benchmark::oN , benchmark::oNSquared , ...

BENCHMARK_MAIN();

/*
 Compile:
 g++ tor_file_er_nam.cpp -std=c++11 -isystem benchmark/include \-Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
 
 Run:
 ./mybenchmark --benchmark_out="csv_er_nam.csv" --benchmark_out_format=csv
 */



