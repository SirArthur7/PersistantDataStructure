//
//  LinkedList.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#ifndef PPDS_LinkedList_h
#define PPDS_LinkedList_h
#include "headers_preprocessors.h"
#include "util.h"

/////////// these classes will be used in this ADT
template <class T_f1>
class NODE;

template <class T_f1>
class MOD;

template <class NODE_T>
class START_MODULE;
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                                                                                            PPDS_LINKED_LIST CLASS                                                                                                //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class PPDS_LINKED_LIST
{
private:
    int GLOBAL_TIME;
    
    // linkedList specific
    static const int inDegree = 1;   // abrv. as p
    const int outDegree = 1;  // abrv. as d
    const int maxModCount ;
    
    int current_no_of_nodes;
    int no_of_total_update_request;
    
    START_MODULE< NODE<T> > *sm; // Start Module to store the roots at different versions

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED INTERNALLY WITHIN THE ADT CLASS
    ///  GLOBALTIME is NOT INCREMENTED
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    NODE<T>* createNode();                                           // to create node        INTERNAL
    void update_internal(int f_index,NODE<T> *nd, T newVal);         // to update F1        INTERNAL
    void update_internal(int f_index,NODE<T> *nd, NODE<T> *newNode); // to update nonF1 (fwd pointers)        INTERNAL
    NODE<T>* addNode_internal(NODE<T> *ancesstorNode,T value);       // insert at middle or at end        INTERNAL
    NODE<T>* addNode_internal(T value);                              // insert at Begining        INTERNAL
    void removeNode_internal(int node_index);                        // removing node_index th node        INTERNAL
    NODE<T>* createCopy(NODE<T> *nd, int version);  // creating copy of argument node        INTERNAL
    
    ///////// retrieval of node at node_index th position at qr_ver version
    NODE<T>* NodeAtIndex(int node_index,int qr_ver);
public:
    
    PPDS_LINKED_LIST(int m):GLOBAL_TIME(0),current_no_of_nodes(0),no_of_total_update_request(0),maxModCount(m){sm = new START_MODULE< NODE<T> >();}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED BY USER
    /// GLOBALTIME is INCREMENTED by 1 at each call
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    ///////////////////////////////
    ///Overloaded Functions for Updation of fields
    /////////////////////////////
    
    // to update F1  (given NODE_INDEX parameter as arg)   USER
    void updateF1(int node_index, T newVal);
    //
    //!!!!!!!!!!!!!!!!!!!!! USERS ARE NOT ALLOWED to update nonF1 (fwd pointers)
    //
    
    ///////////////////////////////
    ///Overloaded Functions for Insertion of nodes
    /////////////////////////////
    
    // insert at middle (after ancesstor_node)or at end  ( given NODE_INDEX parameter as arg)      USER
    bool addNode(int ancesstor_node_index,T value);
    
    // insert at Begining    USER
    bool addNode(T value);
    
    ////////// REMOVAL OF NODES
    void removeNode(int node_index);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED BY USER AND ADT Class
    /// GLOBALTIME is NOT INCREMENTED
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    //////// iterating and priting the node Details at qr_ver version
    void iterate_and_printDetails_at_ver(int qr_ver);
    
    //////// iterating and priting the Latest F1s at qr_ver version
    void iterate_and_print_F1_at_ver(int qr_ver);
    
    //////// iterating to get  the Latest F1s at qr_ver version as vector
    vector<T> iterate_and_print_F1_at_ver_Vect(int qr_ver);

    //////// iterating to measure performance
    int iterate_performance_check(int qr_ver);
    
    //////// iterating to get length of the LL in any version
    int get_length_at_ver(int qr_ver);
    
    int getCurTime(){return GLOBAL_TIME;}
    int getCurrentNoOfNodesUsed(){return current_no_of_nodes;}
    int get_total_update_requests(){return no_of_total_update_request;}
    int getCurMemoryUsage();
};

/////////////\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////// user function defintition starts of PPDS_LINKED_LIST CLASS /////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///

template <class T>
void PPDS_LINKED_LIST<T>::updateF1(int node_index, T newVal)
{
    no_of_total_update_request++;
    int f_index = 1;
    GLOBAL_TIME ++;
    NODE<T>* nd = NodeAtIndex(node_index, GLOBAL_TIME);
    update_internal(f_index, nd, newVal);
}

template <class T>
bool PPDS_LINKED_LIST<T>::addNode(int ancesstor_node_index,T value)
{
    no_of_total_update_request++;
    GLOBAL_TIME++;
    if(ancesstor_node_index==0)
        return addNode_internal(value)!=nullptr;
    else{
    NODE<T>* ancs_nd = NodeAtIndex(ancesstor_node_index, GLOBAL_TIME);
        return (addNode_internal(ancs_nd,value)!=nullptr);}
}

template <class T>
bool PPDS_LINKED_LIST<T>::addNode(T value)
{
    no_of_total_update_request++;
    GLOBAL_TIME++;
    return (addNode_internal(value)!=nullptr);
}


template <class T>
void PPDS_LINKED_LIST<T>::removeNode(int node_index)
{
    no_of_total_update_request++;
    GLOBAL_TIME++;
    removeNode_internal(node_index);
}



/////////////\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////// other function defintition starts of PPDS_LINKED_LIST CLASS /////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///

template <class T>
NODE<T>* PPDS_LINKED_LIST<T>::createNode()
{
    current_no_of_nodes++;
        NODE<T>* nd = nullptr;
        nd = new NODE<T>(GLOBAL_TIME,inDegree,outDegree,maxModCount);
        return nd;
}


template <class T>
NODE<T>* PPDS_LINKED_LIST<T>::createCopy(NODE<T> *nd, int version)
{
    NODE<T>*nd_ = createNode();
    
    // latest values of nd are set to default values in nd'
    nd_->addF1Mod(version, nd->latestF1_at(version));                      //
    nd_->add_nonF1_Mod(version, 2, nd->latestNonF1_Field_at(2,version));    //
    nd_->set_default_BPs(1, nd->BP_Field_at(1));           // no version needed

    return nd_;
}


// to update F1
template <class T>
void PPDS_LINKED_LIST<T>::update_internal(int f_index,NODE<T> *nd, T newVal)
{
    assert(f_index==1); // it must be 1 for F1 update
        
    bool isModFull = (nd->addF1Mod(GLOBAL_TIME, newVal)); // modLog of F1 is full
       
    
        if(isModFull)
        {
            // create_copy
            NODE<T>*nd_ = createCopy(nd,GLOBAL_TIME);
            
            // according to user Querey set the F1
            nd_->addF1Mod(GLOBAL_TIME, newVal); // set

            //Rewrite THE BACK POINTERS OF THE SUCCESSOR NODE TO THE NEWLY CREATED NODE
            
            NODE<T>* f2_of_nd_ = nd_->latestNonF1_Field_at(2, GLOBAL_TIME);
            
            if(f2_of_nd_!=nullptr)
                f2_of_nd_->set_default_BPs(1,nd_);
            
            //GO TO ANCESTOR NODES RECURSIVELY AND DO update(f2,ancester_node,NEW_NODE)
            NODE<T>* bp1_of_nd_ = nd->BP_Field_at(1);
            
            if(bp1_of_nd_!=nullptr)
                update_internal(2, bp1_of_nd_, nd_);
            else
                sm->add_newNodeReff_to_start(nd_,GLOBAL_TIME);
        }
}

// to update_internal nonF1 (fwd pointers) // only to be called internally
template <class T>
void PPDS_LINKED_LIST<T>::update_internal(int f_index,NODE<T> *nd, NODE<T> *newNode)
{
    assert(f_index>1); // it must be 1 for F1 update
        
    bool isModFull = (nd->add_nonF1_Mod(GLOBAL_TIME,f_index, newNode)); // modLog of F1 is full

        if(isModFull)
        {
            // create_copy
            NODE<T>*nd_ = createCopy(nd,GLOBAL_TIME);
            
            //set the nonF1
            nd_->set_default_nonF1(f_index, newNode);
            
            //Rewrite THE BACK POINTERS OF THE SUCCESSOR NODE TO THE NEWLY CREATED NODE
            NODE<T>* f2_of_nd_ = nd_->latestNonF1_Field_at(2, GLOBAL_TIME);
            
            if(f2_of_nd_!=nullptr)
                f2_of_nd_->set_default_BPs(1,nd_);
            
            //GO TO ANCESTOR NODES RECURSIVELY AND DO update(f2,ancester_node,NEW_NODE)
            NODE<T>* bp1_of_nd_ = nd->BP_Field_at(1);
            if(bp1_of_nd_!=nullptr)
                update_internal(2, bp1_of_nd_, nd_);
            else
                sm->add_newNodeReff_to_start(nd_,GLOBAL_TIME);
        }
}


template <class T>
NODE<T>* PPDS_LINKED_LIST<T>::addNode_internal(NODE<T> *ancesstorNode,T value)
{
    NODE<T>*X = createNode();
    X->set_default_F1(value);
    
    /*
     ... -> A -> B -> ...
     insert X
     ... -> A -> x -> B -> ...     (at mid)
     
     ... -> A -> B -> NULL
     insert X
     ... -> A -> x -> B -> NULL    (at end)
    */
    
    NODE<T>*A = ancesstorNode;
    NODE<T>*B = ancesstorNode->latestNonF1_Field_at(2, GLOBAL_TIME);
    
    
    if(B==nullptr)        // end postion
    {
        update_internal(2, A, X);
        update_internal(2, X, B);
        X->set_default_BPs(1, A);
    }
    
    else       // non end postion
    {
        update_internal(2, A, X);
        update_internal(2, X, B); // here B = nullptr
        X->set_default_BPs(1, A);
        B->set_default_BPs(1, X);
    }
    
    return X;
}


template <class T>
NODE<T>* PPDS_LINKED_LIST<T>::addNode_internal(T value)
{
    NODE<T>*X = createNode();
    X->set_default_F1(value);

    /*
     START_MODULE -> A -> ...
     insert X
     START_MODULE -> X -> A -> ...     (at START)
    */

    if(sm->curVersionCountInStart()==0){
        // if it is the very first node in LL
        sm->add_newNodeReff_to_start(X,GLOBAL_TIME);
    }
    else{
        NODE<T>* A = sm->getJustLatestNode();
        sm->add_newNodeReff_to_start(X,GLOBAL_TIME);
        update_internal(2, X, A);
        if(A!=nullptr)
            A->set_default_BPs(1, X);
    }
    
    return X;
}


template <class T>
void PPDS_LINKED_LIST<T>::removeNode_internal(int node_index)
{
    // node_index starts from 1
    NODE<T>* X = NodeAtIndex(node_index, GLOBAL_TIME); // to be deleted
    /*
     case1:
     sm(v) -> X -> B -> ...             ...>     sm(v+1) -> B -> ...
                                                      (v)   -> X -> B -> ...

     case2:
     ... -> A(v) -> X -> NULL              ...>     ... -> A(v+1) -> NULL
                                                              (v) -> X -> NULL
     
     case3:
     ... -> A(v) -> X -> B -> ...          ...>     ... -> A(v+1) -> B -> ...
                                                              (v) -> X -> B -> ..
     */
    
    NODE<T>* A = X->BP_Field_at(1);
    NODE<T>* B = X->latestNonF1_Field_at(2, GLOBAL_TIME);
    
    if(A == nullptr)
    {
        sm->add_newNodeReff_to_start(B,GLOBAL_TIME);
        if(B!=nullptr)
            B->set_default_BPs(1, nullptr);
    }
    else if(B == nullptr)
    {
        update_internal(2, A, nullptr);
    }
    else
    {
        update_internal(2, A, B);
        if(B!=nullptr)
            B->set_default_BPs(1, A);
    }
}


template <class T>
NODE<T>* PPDS_LINKED_LIST<T>::NodeAtIndex(int node_index, int qr_ver)
{
    // node_index starts from 1
    assert(node_index>0);

    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    while(1) {
        if(ptr==nullptr)
            break;
        
        if((--node_index)==0)
            {
                return ptr;
            }
        
        ptr = ptr->latestNonF1_Field_at(2, qr_ver);

    }
    
    assert(0);
    return nullptr;
}


template <class T>
void PPDS_LINKED_LIST<T>::iterate_and_printDetails_at_ver(int qr_ver)
{
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);

    cout<<"Iteration At Version _______________ "<<qr_ver<<endl;
    sm->printAllRoots();

    while(1) {
        if(ptr==nullptr)
            break;
        
        if(ptr->getDefaultVersion()>qr_ver)
            break;
        
        ptr->printDetails(qr_ver);
        ptr = ptr->latestNonF1_Field_at(2, qr_ver);
    }
    cout<<"__________________ end Iter\n\n";
}

template <class T>
void PPDS_LINKED_LIST<T>::iterate_and_print_F1_at_ver(int qr_ver)
{
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    cout<<"Iteration At Version _______________ "<<qr_ver<<endl;
        
    while(1) {
        if(ptr==nullptr)
            break;
        
        if(ptr->getDefaultVersion()>qr_ver)
            break;
        
        cout<<ptr->latestF1_at(qr_ver)<<"  -> ";
        ptr = ptr->latestNonF1_Field_at(2, qr_ver);
    }
    cout<<"nullptr \n__________________ end Iter\n\n";
}


template <class T>
int PPDS_LINKED_LIST<T>::iterate_performance_check(int qr_ver)
{
    int len = 0;
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    while(1) {
        if(ptr==nullptr)
            return len;
        
        if(ptr->getDefaultVersion()>qr_ver)
            return len;
        
        len++;
        ptr = ptr->latestNonF1_Field_at(2, qr_ver);
    }
}

template <class T>
vector<T> PPDS_LINKED_LIST<T>::iterate_and_print_F1_at_ver_Vect(int qr_ver)
{
    vector<T>ans;
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    while(1) {
        if(ptr==nullptr)
            break;
        
        if(ptr->getDefaultVersion()>qr_ver)
            break;
        
        ans.push_back(ptr->latestF1_at(qr_ver));
        ptr = ptr->latestNonF1_Field_at(2, qr_ver);
    }
    return ans;
}

template <class T>
int PPDS_LINKED_LIST<T>::get_length_at_ver(int qr_ver)
{
    return iterate_performance_check(qr_ver);
}

template <class T>
int PPDS_LINKED_LIST<T>::getCurMemoryUsage()
{
    int size =  current_no_of_nodes * (inDegree*sizeof(NODE<T>*) + outDegree*sizeof(NODE<T>*) + maxModCount * sizeof(MOD<T>) + sizeof(NODE<T>));
    return size;
}


#endif /* LinkedList_h */
