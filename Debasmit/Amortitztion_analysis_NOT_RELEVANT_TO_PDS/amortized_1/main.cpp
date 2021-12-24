//
//  main.cpp
//  amortized_1
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#include <iostream>
#include "gnu_plot.h.h"
int *stack;
int cur_capacity, top;
int time_elp = 0;

void init()
{
    cur_capacity = 1;
    stack = (int*)malloc(cur_capacity * sizeof(int));
    top = 0;
}


void push(int val)
{
    if(top == cur_capacity)
        {
            cur_capacity*=2;
            stack = (int*)realloc(stack, cur_capacity);     time_elp+=(cur_capacity/2);
        }
    
    stack[top++] = val; time_elp+=1;
}

void printStack()
{
    for(int i = 0 ; i<top;i++)
        printf("%d  ",stack[i]);
    
    printf("            |Capacity: %d / Time Elapsed: %d\n",cur_capacity,time_elp);
}

#define MAX_ELEMENT 1000
int n[MAX_ELEMENT+1], real_Time[MAX_ELEMENT+1], amortizedTime[MAX_ELEMENT+1], normal_Calculation[MAX_ELEMENT+1];
float t_day_average[MAX_ELEMENT+1], beta = 0.99;

void storePerformance()
{
    n[top-1] = top;
    real_Time[top-1] = time_elp;
    amortizedTime[top-1] = 3*top;         // O(3n)
    normal_Calculation[top-1] = top*top;  // O(n^2)
    
    for(int i=1; i<MAX_ELEMENT;i++)
    {
        t_day_average[i] = beta * t_day_average[i-1] + (1-beta) * real_Time[i]; // 1/(1-beta) day avg
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    init();
    
    for(int v = 1;v<MAX_ELEMENT;v++)
    {
        push(v);
        printStack();
        storePerformance();
    }
    
    //plotData_real_amt_norm(n, real_Time,amortizedTime,normal_Calculation, MAX_ELEMENT-1);
    //plotData_real_amt(n, real_Time,amortizedTime, MAX_ELEMENT-1);
    plotData_real_amt_tDayAvg(n, real_Time,amortizedTime,t_day_average, MAX_ELEMENT-1);
    
    free(stack);
    return 0;
}
