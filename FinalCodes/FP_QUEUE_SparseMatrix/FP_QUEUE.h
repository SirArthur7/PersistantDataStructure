//
//  FP_QUEUE.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 19/01/22.
//

#ifndef FP_QUEUE_h
#define FP_QUEUE_h
#include <iostream>
#define SENTINEL -999
#define MAX_NO_VER 65536
#define LOG_MAX_NO_VER 16
#define CHECK_VERSION(ver) if(ver>cur_time){cout<<".. can not perform opeation ahead of real time ...\n";return SENTINEL;}
#define CHECK_VERSION_(ver) if(ver>cur_time){cout<<".. can not perform opeation ahead of real time ...\n";return ;}
using namespace std;


class FP_QUEUE
{
private:
    // ver_child -> (2^i th)ver_grand_par mapping
    int table[MAX_NO_VER][LOG_MAX_NO_VER];
    // map(ver) = {data, front_ver,cur_length} of rear
    int map[MAX_NO_VER][3] ;
    // to hold what type of update happened in version v, 'E' for Enqueue & 'D' for Dequeue
    char type_of_update[MAX_NO_VER];
    // to hold the real times
    int cur_time;

    // to add version into sparse table
    void add_to_table(int src,int par=0);

    // to find version 'jump_req' amount height above given version node
    int lift_node(int node, int jmp_req);

    // to return 'E' type node which is atmost _upShift_ unit above than rear at par_ver and also furthest to rear at par_ver
    int getNewFront(int par_ver,int up_Shift,int &shrink);
public:
    //constructor
    FP_QUEUE();
    
    // to enqueue the Data at rear along par_ver
    void enqueue(int data, int par_ver);

    // to dequeue the Data at front along par_ver
    int dequeue(int par_ver);

    // to iterate over the whole queue at ver [from front to rear]
    void iterate_over_queue_at_ver(int ver);

    // to get status of all versions till now
    void allVerDisplay();
    
    // to return the Data at rear at version ver
    int rear(int ver);
    
    // to return the Data at front at version ver
    int front(int ver);

    // to retirieve the current real time
    int getCurTime();
};

FP_QUEUE::FP_QUEUE(){
        cur_time=0;
    
    map[0][0] = map[0][1] = map[0][2] = 0;
    table[0][0] = table[0][1] = table[0][2] = 0;

    
//        for(int i=0;i<MAX_NO_VER;i++){
//            map[i][0] = map[i][1] = map[i][2] = 0;
//            for(int j=0; j<=LOG_MAX_NO_VER;j++)
//                table[i][j] = -1;
//        }
    }

void FP_QUEUE:: add_to_table(int src,int par){
    table[src][0] = par;
    for(int  i=1;i<20;i++){
        if(table[src][i-1]==-1)
            break;
        table[src][i] = table[ table[src][i-1]][i-1];
    } // as par > child ( No need to do BFS)
}

int FP_QUEUE:: lift_node(int node, int jmp_req){
    for(int i = 19; i>= 0;i--){
       if (jmp_req == 0 || node == -1)
           break;
        
        if (jmp_req >= (1<<i)){
            jmp_req -= (i<<i);
            node = table[node][i];
        }
    }
    return node;
}

int FP_QUEUE:: getNewFront(int par_ver,int up_Shift, int &shrink){
    CHECK_VERSION(par_ver)
    int up_node = lift_node(par_ver,up_Shift);
    
    if(up_node==par_ver)
        return up_node;
    
    if(type_of_update[up_node]=='E')
        return up_node;
    else{
        shrink++;
        return getNewFront(par_ver, up_Shift-1,shrink);}
}

void FP_QUEUE::enqueue(int data, int par_ver){
    CHECK_VERSION_(par_ver)
    if(cur_time == MAX_NO_VER){
        cout<<"No Support to hold further versions in RAM ... You store them in Disk\n";
        return;
    }
    
    cur_time++;
    map[cur_time][0] = data;
    int cur_legth = map[cur_time][2] = map[par_ver][2]+1; // length ++
    map[cur_time][1] = (cur_legth!=1)?map[par_ver][1]:cur_time; // front = parent's front
    type_of_update[cur_time] = 'E';
    add_to_table(cur_time, par_ver);
}

int FP_QUEUE::dequeue(int par_ver){
    CHECK_VERSION(par_ver)
    
    if(cur_time == MAX_NO_VER){
        cout<<"No Support to hold further versions in RAM ... You store them in Disk\n";
        return SENTINEL;
    }
    int prev_length = map[par_ver][2];
    int prev_front = map[par_ver][1];
    
    if(type_of_update[map[par_ver][1]]=='D' || map[par_ver][1]==0){
        cout<<"Queue Underflowed!!\n";
        return SENTINEL;
    }
    
    int shrink = 0;
    int new_length = prev_length; // +1 -1
    int new_front = getNewFront(par_ver,prev_length-2,shrink); // upshift will deduct by 2
    
    // the follwing condition happens iff there is no element left
    // there is no need to do this ... just for sake of understanding
    if(new_front==par_ver && type_of_update[new_front]=='D'){
        new_front = cur_time+1;
        shrink++;
    }
    
    new_length-=shrink;
    
    cur_time++;
    
    map[cur_time][0] = map[par_ver][0]; // front data won't change
    map[cur_time][1] = new_front;
    map[cur_time][2] = new_length;
    type_of_update[cur_time] = 'D';
    add_to_table(cur_time, par_ver);
    return map[prev_front][0];
}

void FP_QUEUE::iterate_over_queue_at_ver(int ver){
    CHECK_VERSION_(ver)
    for(int l = map[ver][2];l>0;l--)
    {
        int pos = lift_node(ver, l-1);
        if(type_of_update[pos]=='E')
            cout<<map[pos][0]<<" ";
    }
    
    cout<<endl;
}

void FP_QUEUE::allVerDisplay(){
    for(int v = 0;v<=cur_time;v++)
        iterate_over_queue_at_ver(v);
}

int FP_QUEUE::rear(int ver){
    CHECK_VERSION(ver)
    if(ver<=cur_time)
        return map[ver][0];
    else
        return SENTINEL;
}

int FP_QUEUE::front(int ver){
    CHECK_VERSION(ver)
    if(ver<=cur_time)
    {
        if(type_of_update[map[ver][1]]=='E')
            return map[map[ver][1]][0];
        else
            return map[lift_node(ver, map[ver][2]-2)][0];
    }
    else
        return SENTINEL;
}

int FP_QUEUE::getCurTime(){
    return cur_time;
}

#endif /* FP_QUEUE_h */
