/*** 23/12/2021
 * Persistent Stack implementation 
Created by Kushal Das */

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define GARBAGE -1
#define UNUSED -1

typedef struct Node Node;
typedef struct Mod Mod;
typedef struct Stack_fp Stack_fp;

struct Node // each node in the stack
{
    int data;
    int node_version;
    Mod *mod;
    Node *next;
    Node *prev;
};

struct Mod // modifications log
{
    int data;
    int version;
    Node *next;
    Node *prev;
};

struct Stack_fp // main stack
{
    Node *head[MAX_OP];
    int num_el;
    int live_version;
};

Stack_fp *init_stack(); // initializes the stack

/* OPERATIONS */

bool isEmpty(Stack_fp *stack, int version);        // check if stack is empty
bool push(Stack_fp *stack, int data, int version); // push the element in the stack
int pop(Stack_fp *stack, int version);             // pop and return the value
