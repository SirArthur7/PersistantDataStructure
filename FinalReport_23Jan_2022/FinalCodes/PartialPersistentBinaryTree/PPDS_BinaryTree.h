//
//  PPDS_BinaryTree.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 27/12/21.
//
// Tree
/*
 This is the position sequence:
                                   1
                                 /   \
                                /     \
                               /       \
                              2         3
                            /  \      /   \
                           4    5    6     7
                         / \   / \  /     / \
                        8  9  10 11 12   14 15
 
 Query String:
 
 "S" ->1
 "SRLL" -> 12
 "SL"   -> 2
 "SRR" -> 7
 */

#ifndef PPDS_BinaryTree_h
#define PPDS_BinaryTree_h
#include "headers_preprocessors.h"
#include "util.h"
#define LEFT 2
#define RIGHT 3
#define START LEFT // by default

/////////// these classes will be used in this ADT
template <class T_f1>
class NODE;

template <class T_f1>
class MOD;

template <class NODE_T>
class START_MODULE;
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                                                                       PPDS_BIN_TREE CLASS                                                                                 //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class PPDS_BIN_TREE
{
private:
    int GLOBAL_TIME;
    
    // binarytree specific
    static const int inDegree = 1;   // abrv. as p
    const int outDegree = 2;  // abrv. as d
    const int maxModCount = 2;
    
    START_MODULE<NODE<T>> *sm; // Start Module to store the roots at different versions

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED INTERNALLY WITHIN THE ADT CLASS
    ///  GLOBALTIME is NOT INCREMENTED
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    // to create node        INTERNAL
    NODE<T>* createNode(int realtivePosition_wrt_ancsestor);
    
    // creating copy of argument node        INTERNAL
    NODE<T>* createCopy(NODE<T> *nd, int version, int realtivePosition_wrt_ancsestor);
    
    
    // to update F1        INTERNAL
    void update_internal(int f_index,NODE<T> *nd, T newVal);
    // to update nonF1 (fwd pointers)        INTERNAL
    void update_internal(int f_index,NODE<T> *nd, NODE<T> *newNode);
    // insert at middle or at end        INTERNAL
    NODE<T>* addNode_internal(NODE<T> *ancesstorNode,int direction,T value);
    // insert at Begining        INTERNAL
    NODE<T>* addNode_internal(T value);
    // removing node_index th node        INTERNAL
    void removeLeafNode_internal(string node_index_encoded);
    
    ///////// retrieval of node at node_index th position at qr_ver version
    NODE<T>* NodeAtIndex(string ancesstor_node_index_encoded,int qr_ver);
public:
    
    PPDS_BIN_TREE():GLOBAL_TIME(0){sm = new START_MODULE<NODE<T>>();}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED BY USER
    /// GLOBALTIME is INCREMENTED by 1 at each call
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    ///////////////////////////////
    ///Functions for Updation of fields
    /////////////////////////////
    
    // to update F1  (given NODE_INDEX parameter as arg)   USER
    void updateF1(string node_index_encoded, T newVal);
    //
    //!!!!!!!!!!!!!!!!!!!!! USERS ARE NOT ALLOWED to update nonF1 (fwd pointers)
    //

    
    ///////////////////////////////
    ///Overloaded Functions for Insertion of nodes
    /////////////////////////////
    
    // insert at middle (after ancesstor_node)or at end  ( given NODE_INDEX parameter as arg)      USER
    bool addNode(string ancesstor_node_index_encoded,int direction, T value);
    
    // insert at Begining    USER
    bool addNode(T value);
    
    ////////// REMOVAL OF NODES
    void removeLeafNode(string node_index_enocoded);
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// THESE FUNCTION ARE CALLED BY USER AND ADT Class
    /// GLOBALTIME is NOT INCREMENTED
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    //////// iterating and priting the node Details at qr_ver version
    void iterate_and_printDetails_inBFS_at_ver(int qr_ver);
    
    //////// iterating and priting the Latest F1s at qr_ver version
    void iterate_and_print_F1_inBFS_at_ver(int qr_ver);
    
    //////// iterating to measure performance
    void iterate_performance_check(int qr_ver);

    int getCurTime(){return GLOBAL_TIME;}
};

///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   USER ONLY FUNCTIONS DEFINITION
template <class T>
void PPDS_BIN_TREE<T>::updateF1(string node_index_encoded, T newVal)
{
    int f_index = 1;
    GLOBAL_TIME ++;
    NODE<T>* nd = NodeAtIndex(node_index_encoded, GLOBAL_TIME);
    update_internal(f_index, nd, newVal);
}

template <class T>
bool PPDS_BIN_TREE<T>::addNode(string ancesstor_node_index_encoded,int direction, T value)
{
    GLOBAL_TIME++;
    NODE<T>* ancs_nd = NodeAtIndex(ancesstor_node_index_encoded, GLOBAL_TIME);
    return (addNode_internal(ancs_nd,direction,value)!=nullptr);          /// !!!!!!!!!
}

template <class T>
bool PPDS_BIN_TREE<T>::addNode(T value)
{
    GLOBAL_TIME++;
    return (addNode_internal(value)!=nullptr);
}


template <class T>
void PPDS_BIN_TREE<T>::removeLeafNode(string node_index_encoded)
{
    GLOBAL_TIME++;
    removeLeafNode_internal(node_index_encoded);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   OTHER FUNCTIONS DEFINITION
template <class T>
NODE<T>* PPDS_BIN_TREE<T>::createNode(int realtivePosition_wrt_ancsestor)
{
        NODE<T>* nd = nullptr;
        nd = new NODE<T>(GLOBAL_TIME,inDegree,outDegree,maxModCount,realtivePosition_wrt_ancsestor);
        return nd;
}


template <class T>
NODE<T>* PPDS_BIN_TREE<T>::createCopy(NODE<T> *nd, int version,int realtivePosition_wrt_ancsestor)
{
    NODE<T>*nd_ = createNode(realtivePosition_wrt_ancsestor);
    
    // latest values of nd are set to default values in nd'
    nd_->addF1Mod(version, nd->latestF1_at(version));                      //
    nd_->add_nonF1_Mod(version, LEFT, nd->latestNonF1_Field_at(LEFT,version));    //
    nd_->add_nonF1_Mod(version, RIGHT, nd->latestNonF1_Field_at(RIGHT,version));    //
    nd_->set_default_BPs(1, nd->BP_Field_at(1));           // no version needed

    return nd_;
}


// to update F1
template <class T>
void PPDS_BIN_TREE<T>::update_internal(int f_index,NODE<T> *nd, T newVal)
{
    assert(f_index==1); // it must be 1 for F1 update
        
    bool isModFull = (nd->addF1Mod(GLOBAL_TIME, newVal)); // modLog of F1 is full
       
    
        if(isModFull)
        {
            int realtivePosition_wrt_ancsestor = nd->getRealtivePosition_wrt_ancsestor();
            // create_copy
            NODE<T>*nd_ = createCopy(nd,GLOBAL_TIME,realtivePosition_wrt_ancsestor);
            
            // according to user Querey set the F1
            nd_->addF1Mod(GLOBAL_TIME, newVal); // set

            //Rewrite THE BACK POINTERS OF THE SUCCESSOR NODE TO THE NEWLY CREATED NODE
            
            NODE<T>* left_of_nd_ = nd_->latestNonF1_Field_at(LEFT, GLOBAL_TIME);
            
            if(left_of_nd_!=nullptr)
                left_of_nd_->set_default_BPs(1,nd_);
            
            NODE<T>*right_of_nd_ = nd_->latestNonF1_Field_at(RIGHT, GLOBAL_TIME);
            
            if(right_of_nd_!=nullptr)
                right_of_nd_->set_default_BPs(1,nd_);
            
            //GO TO ANCESTOR NODES RECURSIVELY AND DO update(f2,ancester_node,NEW_NODE)
            NODE<T>* bp1_of_nd_ = nd->BP_Field_at(1);
            
            if(bp1_of_nd_!=nullptr)
                update_internal(realtivePosition_wrt_ancsestor, bp1_of_nd_, nd_);
            else
                sm->add_newNodeReff_to_start(nd_,GLOBAL_TIME);
        }
}

// to update_internal nonF1 (fwd pointers) // only to be called internally
template <class T>
void PPDS_BIN_TREE<T>::update_internal(int f_index,NODE<T> *nd, NODE<T> *newNode)
{
    assert(f_index>1); // it must be 1 for F1 update
        
    bool isModFull = (nd->add_nonF1_Mod(GLOBAL_TIME,f_index, newNode)); // modLog of F1 is full

        if(isModFull)
        {
            int realtivePosition_wrt_ancsestor = nd->getRealtivePosition_wrt_ancsestor();
            
            // create_copy
            NODE<T>*nd_ = createCopy(nd,GLOBAL_TIME,realtivePosition_wrt_ancsestor);
            
            // according to user Querey set the F1
            nd_->set_default_nonF1(f_index, newNode);
            
            //Rewrite THE BACK POINTERS OF THE SUCCESSOR NODE TO THE NEWLY CREATED NODE
            NODE<T>* left_of_nd_ = nd_->latestNonF1_Field_at(LEFT, GLOBAL_TIME);
            if(left_of_nd_!=nullptr)
                left_of_nd_->set_default_BPs(1,nd_);
            
            NODE<T>*right_of_nd_ = nd_->latestNonF1_Field_at(RIGHT, GLOBAL_TIME);
            if(right_of_nd_!=nullptr)
                right_of_nd_->set_default_BPs(1,nd_);
            
            //GO TO ANCESTOR NODES RECURSIVELY AND DO update(f2,ancester_node,NEW_NODE)
            NODE<T>* bp1_of_nd_ = nd->BP_Field_at(1);
            if(bp1_of_nd_!=nullptr)
                update_internal(realtivePosition_wrt_ancsestor, bp1_of_nd_, nd_);
            else
                sm->add_newNodeReff_to_start(nd_,GLOBAL_TIME);
        }
}


template <class T>
NODE<T>* PPDS_BIN_TREE<T>::addNode_internal(NODE<T> *ancesstorNode,int direction,T value)
{
    NODE<T>*X = createNode(direction);
    X->set_default_F1(value);
    
    /*
     case1:
     insert X, after B at LEFT
              A           A
           /    \      /     \
          B(v)        B(v+1)
         / \         /      \
        C  D        X(v+1)  D
                   /
                  C
     case2:
     insert X, after B at LEFT
            A             A
           / \         /     \
          B(v)        B(v+1)
         / \         /      \
        C   NULL    X(v+1)   NULL
                   /
                  C
     insert X
     insert X, after B at LEFT   (after Leaf)
            A            A
           / \         /    \
          B(v)        B(v+1)
         / \         /      \
     Null   Null    X(v+1)  NULL
                   /
                 Null
     
     
     ||||||||||| Acutally there is a pathcopying in b/w B(v) and B(v+1) |||||||||||
    */
    
    NODE<T>*B = ancesstorNode;      // ancestor node
    NODE<T>*C = ancesstorNode->latestNonF1_Field_at(direction, GLOBAL_TIME); // existing node on that direction

    
    update_internal(direction, B, X);
    update_internal(direction, X, C); // here C will be on that direction  of X now
    X->set_default_BPs(1, B);     // as X's BP is B
    

    if(C!=nullptr)
        C->set_default_BPs(1, X);

    return X;
}


template <class T>
NODE<T>* PPDS_BIN_TREE<T>::addNode_internal(T value)
{

    NODE<T>*X = createNode(START);
    X->set_default_F1(value);

    /*
     insert X at beginning (By Default B will be at left of newly added node X)
     
         START           START
          (v)         (v)    (v+1)
          |            |       |
          A             \     X(v+1)
         / \             \   /      \
        B  C              A(v)(v+1)  NULL
                         / \
                        B  C
     
     PathCopying is being done internally
     */

    if(sm->curVersionCountInStart()==0){
        // if it is the very first node in Tree
        sm->add_newNodeReff_to_start(X,GLOBAL_TIME);
    }
    else{
        NODE<T>* A = sm->getJustLatestNode();
        sm->add_newNodeReff_to_start(X,GLOBAL_TIME);
        update_internal(LEFT, X, A);      ///////////////////// By Default B will be at left of newly added node X
        
        if(A!=nullptr)
            A->set_default_BPs(1, X);
    }
    
    return X;
}


template <class T>
void PPDS_BIN_TREE<T>::removeLeafNode_internal(string node_index_encoded)
{
    // node_index starts from 1
    NODE<T>* X = NodeAtIndex(node_index_encoded, GLOBAL_TIME); // to be deleted
    
    
    /*
    Remove X
     
           A           A
          / \         / \
         B(v)        B(v+1)
        / \         / \
       X  D      NULL  D
                
    */
    
    
    NODE<T>* A = X->BP_Field_at(1);
    NODE<T>* LEFT_of_X = X->latestNonF1_Field_at(LEFT, GLOBAL_TIME);
    NODE<T>* RIGHT_of_X = X->latestNonF1_Field_at(RIGHT, GLOBAL_TIME);
    assert(LEFT_of_X==nullptr && RIGHT_of_X==nullptr ); // to ensure whehter X uis a leaf node

    int direction_X_wrt_A  =  X->getRealtivePosition_wrt_ancsestor();                       ///!!!!!!
    update_internal(direction_X_wrt_A, A, nullptr);      ///!!!!!!
}


template <class T>
NODE<T>* PPDS_BIN_TREE<T>::NodeAtIndex(string node_index_encoded, int qr_ver)
{
    // node_index starts from 1
    unsigned long code_length = node_index_encoded.length();
    assert(code_length>0);
    int it=0;
    
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    
    if(node_index_encoded=="S") // root node
        return ptr;
    
    it++;
    
    while(1) {
        if(ptr==nullptr)
            break;
        
        if(it==(code_length))
            return ptr;
        
        if(node_index_encoded[it] == 'L')
            ptr = ptr->latestNonF1_Field_at(LEFT, qr_ver);
        else if(node_index_encoded[it] == 'R')
            ptr = ptr->latestNonF1_Field_at(RIGHT, qr_ver);
        else
            assert(0);
        it++;
    }
    
    assert(0);
    return nullptr;
}


template <class T>
void PPDS_BIN_TREE<T>::iterate_and_printDetails_inBFS_at_ver(int qr_ver)
{
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    cout<<"BFS Iteration At Version _______________ "<<qr_ver<<endl;
    sm->printAllRoots();
    
    queue<NODE<T>*>q;
    q.push(ptr);

    
    do{
        NODE<T>* cur_node = q.front();
        q.pop();
        
        if(cur_node==nullptr)
        {
            cout<<"(nullptr)  ";
            continue;
        }
        
        if(cur_node->getDefaultVersion()>qr_ver)
            continue;
        
        cur_node->printDetails(qr_ver);
        
        q.push(cur_node->latestNonF1_Field_at(LEFT, qr_ver));
        q.push(cur_node->latestNonF1_Field_at(RIGHT, qr_ver));
    }while (!q.empty());
    
    
    cout<<"\n__________________ end Iter\n\n";
}


template <class T>
void PPDS_BIN_TREE<T>::iterate_and_print_F1_inBFS_at_ver(int qr_ver)
{
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    cout<<"BFS Iteration At Version _______________ "<<qr_ver<<endl;
        
    queue<NODE<T>*>q;
    q.push(ptr);

    
    do{
        NODE<T>* cur_node = q.front();
        q.pop();
        
        if(cur_node==nullptr)
        {
            cout<<"(nullptr)  ";
            continue;
        }
        
        if(cur_node->getDefaultVersion()>qr_ver)
            continue;
        
        cout<<cur_node->latestF1_at(qr_ver)<<"  ";
        
        q.push(cur_node->latestNonF1_Field_at(LEFT, qr_ver));
        q.push(cur_node->latestNonF1_Field_at(RIGHT, qr_ver));
    }while (!q.empty());
    
    
    cout<<"\n__________________ end Iter\n\n";
}


template <class T>
void PPDS_BIN_TREE<T>::iterate_performance_check(int qr_ver)
{
    NODE<T>* ptr = sm->findLatestRootNodeAtVersion(qr_ver);
    queue<NODE<T>*>q;
    q.push(ptr);
    
    do{
        NODE<T>* cur_node = q.front();
        q.pop();
        
        if(cur_node==nullptr)
            continue;
        
        if(cur_node->getDefaultVersion()>qr_ver)
            continue;
        
        q.push(cur_node->latestNonF1_Field_at(LEFT, qr_ver));
        q.push(cur_node->latestNonF1_Field_at(RIGHT, qr_ver));
    }while (!q.empty());
}


#endif /* PPDS_BinaryTree_h */

