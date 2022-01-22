//
//  FP_STACK.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 19/01/22.
//

#ifndef FP_STACK_h
#define FP_STACK_h
#include <iostream>
#define SENTINEL -999
#define MAX_NO_VER 65536
#define LOG_MAX_NO_VER 16
#define CHECK_VERSION(ver) if(ver>cur_time){cout<<".. can not perform opeation ahead of real time ...\n";return SENTINEL;}
#define CHECK_VERSION_(ver) if(ver>cur_time){cout<<".. can not perform opeation ahead of real time ...\n";return ;}
using namespace std;


class FP_STACK
{
private:
    int MAP[MAX_NO_VER][2];
    int cur_time;

public:
    FP_STACK();
    // to push data at par_ver
    void push(int data, int par_ver);
    // to pop data at par_ver
    int pop(int par_ver);
    // to get TOP at par_ver
    int getTop(int ver);
    // to iterate from TOP to BOTTOM at par_ver
    void iterateFromTop(int ver);
    // to get current Real Time
    int getCurTime();
};

FP_STACK::FP_STACK():cur_time(0){
    MAP[cur_time][0] = SENTINEL;
    MAP[cur_time][1] = -1;
}

void FP_STACK::push(int data, int par_ver)
{
    CHECK_VERSION_(par_ver);
    if(cur_time == MAX_NO_VER){
        cout<<"No Support to hold further versions in RAM ... You store them in Disk\n";
        return;
    }
    cur_time++;
    MAP[cur_time][0] = data;     // TOP
    MAP[cur_time][1] = par_ver;  // BP
}

int FP_STACK::pop(int par_ver)
{
    CHECK_VERSION(par_ver);
    if(cur_time == MAX_NO_VER){
        cout<<"No Support to hold further versions in RAM ... You store them in Disk\n";
        return SENTINEL;
    }
    
    // previously no element present
    if(MAP[par_ver][1]==-1){
        cout<<"Stack UnderFlowed!!\n";
        return SENTINEL;
    }
    
    cur_time++;
    int grand_par_ver = MAP[par_ver][1];
    
    // previously only element was present
    if(grand_par_ver==0){
        MAP[cur_time][0] = SENTINEL; // TOP
        MAP[cur_time][1] = -1;       // BP
        return MAP[par_ver][0];
    }
    
    int great_grand_par_ver = MAP[grand_par_ver][1];
    
    MAP[cur_time][0] = MAP[grand_par_ver][0];//TOP
    MAP[cur_time][1] = great_grand_par_ver;// BP
    return MAP[par_ver][0];
}

int FP_STACK::getTop(int ver)
{
    CHECK_VERSION(ver);
    return MAP[ver][0];
}

void FP_STACK::iterateFromTop(int ver)
{
    CHECK_VERSION_(ver);
    int cur = ver;
    while (cur>0) {
        cout<<MAP[cur][0]<<" ";
        cur = MAP[cur][1];
    }
    cout<<endl;
}

int FP_STACK::getCurTime(){
    return cur_time;
}
#endif /* FP_STACK_h */
