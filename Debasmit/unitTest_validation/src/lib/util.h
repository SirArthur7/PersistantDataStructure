//
//  util.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#ifndef util_h
#define util_h
#include "headers_preprocessors.h"

template <class T_f1>
class NODE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                                             MOD CLASS                                                                  //////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T_f1>
class MOD
{
private:
    int version;
    int field_index;
    char mode;
    
    T_f1 newValue;
    NODE<T_f1> *newNodeValue;
    
public:
    
    //////////////////////////////////////////////////////////////////
    /////// Overloaded constructors
    //////////////////////////////////////////////////////////////////
    
    // to generate mods to keep F1 mods
    MOD(int v,int f_i, T_f1 n_V):   version(v),field_index(f_i),newValue(n_V)
    {mode='v';//stoing value
        newNodeValue = nullptr;
    }
    
    // to generate mods to keep fwd_ptr mods
    MOD(int v,int f_i, NODE<T_f1>* n_V):   version(v),field_index(f_i),newNodeValue(n_V)
    {mode='p';//pointer
        newValue = SENTINEL;
    }
    
    // to initiate mods to keep null mods
    MOD(int v,int f_i,T_f1 n_Vv, NODE<T_f1>* n_Vp):   version(v),field_index(f_i),newValue(n_Vv),newNodeValue(n_Vp)
    {mode='x';//pointer
    }
    
    ///////////////////////////////////////////////////
    /////// Getter Functions to retrieve mods
    //////////////////////////////////////////////////
    int getVer(){return version;}
    int getField_index(){return field_index;}
    char getMode(){return mode;}
    T_f1 getNewVal(){return newValue;}
    NODE<T_f1>* getNewPointerVal(){return newNodeValue;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                                             NODE CLASS                                                                  //////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T_f1>
class NODE
{
private:
    
    const int inDegree ;   // abrv. as p
    const int outDegree ;  // abrv. as d
    const int maxModCount ;
    
    int cur_MOD_count; // sotres current no of used mods
    
    int defaultVersion; // it will store the node's default version

    // it will store the node's default value
    T_f1 F1;

    // maximum 2 for linked list   #(max 2 * p)
    vector<MOD<T_f1>*> modLogs;
    
    // it will store the default fwd pointer               (# outDegree)
    vector<NODE*> fwd_pointers;
    
    // it will store the backpointer to the previous node  (# inDegree)
    vector<NODE*> back_pointers;
    
    // it will alocate cur_MOD_count number of mods in modlog
    void initModLogWithNULL();
    
public:

    ///////////////////////////////
    ///Overloaded Constructors
    /////////////////////////////

    NODE(int _defaultVersion, int inDeg, int outDeg, int maxMod);
    NODE(int _defaultVersion, int _F1 , vector<NODE*>& _fwd_pointers, vector<NODE*>& _back_pointers, int inDeg, int outDeg, int maxMod);
      
    
    ///////////////////////////////
    ///Overloaded Functions for adding mods
    /////////////////////////////

    // for Value
    bool addF1Mod(int v, T_f1 n_Val);
    // for Fwd Pointer
    bool add_nonF1_Mod(int v,int f_i, NODE<T_f1>* n_FP);
    
    
    ///////////////////////////////
    ///Functions for setting default values
    /////////////////////////////
    void set_default_F1( T_f1 n_Val);
    void set_default_nonF1( int f_i, NODE<T_f1>* n_FP);
    void set_default_BPs(int bp_i, NODE<T_f1>* new_BP);
    
    ///////////////////////////////
    ///Functions for retrieving the fields
    /////////////////////////////
    T_f1 latestF1_at(int qr_ver);
    NODE<T_f1>* latestNonF1_Field_at(int index,int qr_ver);
    NODE<T_f1>* BP_Field_at(int index);
    int getDefaultVersion();
    
    void printDetails(int ver);
};


template <class T_f1>
void NODE<T_f1>::initModLogWithNULL()
{
    for(auto &x:modLogs)
        x = new MOD<T_f1>(SENTINEL, SENTINEL, SENTINEL, nullptr);
}

template <class T_f1>
NODE<T_f1>::NODE(int _defaultVersion, int inDeg, int outDeg, int maxMod):cur_MOD_count(0),inDegree(inDeg),outDegree(outDeg),maxModCount(maxMod)
{
    defaultVersion = _defaultVersion;
    
    F1 = SENTINEL;

    fwd_pointers  =   vector<NODE*> (outDegree,nullptr);
    back_pointers =   vector<NODE*> (inDegree,nullptr);
    modLogs       =   vector<MOD<T_f1>*> (maxModCount);
    initModLogWithNULL();
}


template <class T_f1>
NODE<T_f1>::NODE(int _defaultVersion, int _F1 , vector<NODE*>& _fwd_pointers, vector<NODE*>& _back_pointers, int inDeg, int outDeg, int maxMod):cur_MOD_count(0),inDegree(inDeg),outDegree(outDeg),maxModCount(maxMod)
{
    defaultVersion = _defaultVersion;
    F1 = _F1;
    
    fwd_pointers  =   vector<NODE*> (outDegree,nullptr);
    back_pointers =   vector<NODE*> (inDegree,nullptr);
    
    for(int i = 0; i<outDegree; i++)
        fwd_pointers[i] = _fwd_pointers[i];
    
    for(int i = 0; i<inDegree; i++)
        back_pointers[i] = _back_pointers[i];
    
    modLogs       =   vector<MOD<T_f1>*> (maxModCount);
    initModLogWithNULL();
}

template <class T_f1>
bool NODE<T_f1>:: addF1Mod(int v, T_f1 n_Val)
{
    if(cur_MOD_count == maxModCount)
        return true;
    
    else if(F1==SENTINEL && defaultVersion == v)
        F1 = n_Val;
    
    else{
        MOD<T_f1>*m = new MOD<T_f1>(v,1,n_Val);
        
        free(modLogs[cur_MOD_count]);
        modLogs[cur_MOD_count]=(m);
        cur_MOD_count++;
    }
    return false;
}

template <class T_f1>
bool NODE<T_f1>:: add_nonF1_Mod(int v,int f_i, NODE<T_f1>* n_FP)
{
    if(cur_MOD_count == maxModCount)
        return true;
    
    else if(fwd_pointers[f_i-2]==nullptr && defaultVersion == v)
        fwd_pointers[f_i-2] = n_FP;
    
    else{
        MOD<T_f1>*m = new MOD<T_f1>(v,f_i,n_FP);
        
        free(modLogs[cur_MOD_count]);
        modLogs[cur_MOD_count]=(m);
        cur_MOD_count++;
    }
    
    return false;
}


template <class T_f1>
void NODE<T_f1>:: set_default_F1( T_f1 n_Val){
    F1 = n_Val;
}

template <class T_f1>
void NODE<T_f1>:: set_default_nonF1( int f_i, NODE<T_f1>* n_FP){
    fwd_pointers[f_i-2] = n_FP;
}

template <class T_f1>
void NODE<T_f1>:: set_default_BPs(int bp_i, NODE<T_f1>* new_BP){
    // no versioning needed for partial mode
    // just rewrite on the previous value
    
    back_pointers[bp_i-1] = new_BP;
}



template <class T_f1>
T_f1 NODE<T_f1>:: latestF1_at(int qr_ver){
    // finding latest values wrt version order
    
    if(defaultVersion>qr_ver)
        return SENTINEL; // defaultVer is itself later than qr_ver
    
    int latest_ver  = defaultVersion;  T_f1 latest_ver_fld = F1;
    
    for(auto &x:modLogs){
        if(x->getMode()=='v')
            if((x->getVer() >= latest_ver) && (x->getVer()<=qr_ver)&& (x->getVer()!=SENTINEL)) // !!
            {
                latest_ver =     x->getVer();
                latest_ver_fld = x->getNewVal();
            }
    }
    return latest_ver_fld;
}

template <class T_f1>
NODE<T_f1>* NODE<T_f1>::latestNonF1_Field_at(int index,int qr_ver){
    // finding latest values wrt version order
    
    if(defaultVersion>qr_ver)
        return nullptr; // defaultVer is itself later than qr_ver
    
    int latest_ver  = defaultVersion;  NODE<T_f1>* latest_ver_fld = fwd_pointers[index-2]; // -2 due to user qry starts from 0
    
    for(auto &x:modLogs){
        if(x->getMode()=='p')
            if((x->getVer()>=latest_ver) && (x->getVer()<=qr_ver) && (x->getVer()!=SENTINEL)) // !!
            {
                latest_ver =     x->getVer();
                latest_ver_fld = x->getNewPointerVal();
            }
    }

    return latest_ver_fld;
}

template <class T_f1>
NODE<T_f1>* NODE<T_f1>::BP_Field_at(int index){
        return back_pointers[index-1]; // -1 due to user qry starts from 0
    }
 
template <class T_f1>
int NODE<T_f1>::getDefaultVersion()
 {
     return defaultVersion;
 }

template <class T_f1>
void NODE<T_f1>::printDetails(int ver)
{
    cout<<"-------------------------------------------------------------------------------- NODE INFO "<<this<<endl;;
    cout<<"Def Version: "<<getDefaultVersion()<<endl;
    cout<<"===================> Latest F1: "<<latestF1_at(ver)<<endl;
    cout<<"Latest Fwd Pointers: "<<endl;
    
    for(int f_i=0;f_i<outDegree;f_i++)
        cout<<"F"<<(f_i+2)<<": "<<latestNonF1_Field_at(f_i+2, ver)<<endl;
    
    
    cout<<"\nAll FIELDS ...\n";
    cout<<F1<<endl;
    for(auto x:fwd_pointers)
        cout<<x<<endl;
    
    cout<<"\nAll BPs ...\n";
    for(auto x:back_pointers)
        cout<<x<<endl;
    
    cout<<"\nAll Mods ... modCount="<<cur_MOD_count<<endl;
    for(auto x:modLogs)
        cout<<"Ver: "<<x->getVer()<<", F_i: "<<x->getField_index()<<", NewVal: "<<x->getNewVal()<<", NewValPtr: "<<x->getNewPointerVal()<<", Mode: "<<x->getMode()<<endl;
    
    cout<<"------------------------------------------------------------------------------   endOfDetails "<<endl;
}
    
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                                             START MODULE CLASS                                                      //////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class NODE_T>
class START_MODULE
{
private:
    int cur_root_versions_count;
    vector<pair<NODE_T*,int> > cur_root_versions; // may Use B_tree Here !!!!!!!!!
    
public:
    START_MODULE();
    
    void add_newNodeReff_to_start(NODE_T *t,int ver);
    
    NODE_T* findLatestRootNodeAtVersion(int qry_ver);
    
    NODE_T* getJustLatestNode();
    
    int curVersionCountInStart();
    
    void printAllRoots();
};


template <class NODE_T>
START_MODULE<NODE_T>:: START_MODULE()
{cur_root_versions_count = 0;}

template <class NODE_T>
void START_MODULE<NODE_T>::add_newNodeReff_to_start(NODE_T *t,int ver)
{
    cur_root_versions.push_back({ t,ver });
    cur_root_versions_count++;
}

template <class NODE_T>
NODE_T* START_MODULE<NODE_T>::findLatestRootNodeAtVersion(int qry_ver)
{
    NODE_T* latest_ver_Node = cur_root_versions[0].first;
    int latest_ver  = cur_root_versions[0].second;
    
    for(auto &x:cur_root_versions){
            if((x.second > latest_ver ) && (x.second <=qry_ver))
            {
                latest_ver_Node = x.first;
                latest_ver = x.second;
            }
    }
    return latest_ver_Node;
}

template <class NODE_T>
NODE_T* START_MODULE<NODE_T>::getJustLatestNode()
{
    return (cur_root_versions.end()-1)->first;
}

template <class NODE_T>
int START_MODULE<NODE_T>::curVersionCountInStart()
{
    return cur_root_versions_count;
}

template <class NODE_T>
void START_MODULE<NODE_T>::printAllRoots()
{
    TITLE("Start Module");
    for(auto &x:cur_root_versions)
        cout<<"{"<<x.first<<", "<<x.second<<"}   ";
    cout<<endl<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   END


#endif /* util_h */
