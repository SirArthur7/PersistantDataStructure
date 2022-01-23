#include<stdio.h>
#include<stdlib.h>

#define MAX_VER 100

typedef struct Node
{
    int data;
    int branch_or_ancestors;
    struct Node *nxt;
    struct Ancestry *thread;
}Node;

typedef struct Ancestry
{
    Node *branch_pt;
    Node *ancestor;
}Ancestry;

typedef struct Queue
{
    int lat_ver;
    Node *ver[2][MAX_VER];
}Queue;


Node* create_node(int data)
{
    Node *temp=(Node*)malloc(sizeof(Node));
    if(temp==NULL)
    {
        perror("Node memory allocation failed\n");
        return temp;
    }
    temp->data=data;
    temp->nxt=NULL;
    temp->branch_or_ancestors=INT_MIN;
    temp->thread=NULL;
    return temp;
}

Ancestry* create_thread(int n, Node *branch, Node *new)
{
    Ancestry *tmp;
    int i;
    tmp=(Ancestry *)malloc((n+1)*sizeof(Ancestry));
    for(i=0; i<n; i++)
    {
        tmp[i].branch_pt=new->thread[i].branch_pt;
        tmp[i].ancestor=new->thread[i].ancestor;
    }
    tmp[n].branch_pt=branch;
    tmp[n].ancestor=new;
    return tmp;
}

Node* advance_ptr(Node* cur, Node* end)
{
    if(cur->branch_or_ancestors<0)
        return cur->nxt;
    else
    {
        int i,n;
        n = abs(end->branch_or_ancestors);
        for(i=0; i<n; i++)
        {
            if(end->thread[i].branch_pt==cur)
            {
                return end->thread[i].ancestor;
            }
        }
    }
}

int is_empty(Queue q, int ver)
{
    if(q.ver[0][ver]==NULL)
        return 1;
    else
        return 0;
}

Queue* init_q()
{
    Queue *tmp;
    tmp=(Queue *)malloc(sizeof(Queue));
    if(tmp==NULL)
    {
        perror("Memory allocation failed\n");
        return tmp;
    }
    for(int i=0;i<MAX_VER;i++)
    {
        for(int j=0; j<2; j++)
            tmp->ver[j][i]=NULL;
    }
    tmp->lat_ver=0;
    return tmp;
}

void print_q_all(Queue *q)
{
    Node *tmp1=NULL,*tmp2=NULL;
    for(int i=0;i<q->lat_ver; i++)
    {
        tmp1=q->ver[0][i];

        printf("Version %d:\n",i);
        if(is_empty(*q,i))
            printf("Empty list");
        else
        {
            while(tmp2!=q->ver[1][i])
            {   
                printf("%d ",tmp1->data);
                tmp2=tmp1;
                tmp1=advance_ptr(tmp1,q->ver[1][i]);
            }
        }        
        printf("\n");
    }
}

int enqueue(Queue *q, int ver, int data)
{
    if(ver>q->lat_ver || ver<0)
    {
        perror("Version doesn't exist!\n");
        return -1;
    }

    Node *new_node;
    if((new_node=create_node(data))==NULL)
        return -1;
    
    if(is_empty(*q,ver))
    {
        q->ver[0][q->lat_ver]=new_node;
        q->ver[1][q->lat_ver]=new_node;
    }

    else
    {
        q->ver[0][q->lat_ver]=q->ver[0][ver];
        if(q->ver[1][ver]->branch_or_ancestors!=0 || q->ver[1][ver]->branch_or_ancestors!=INT_MIN)
        {
            new_node->thread=q->ver[1][ver]->thread;
        }
        
        if(q->ver[1][ver]->nxt==NULL && q->ver[1][ver]->branch_or_ancestors<0)
        {            
            new_node->branch_or_ancestors=q->ver[1][ver]->branch_or_ancestors;
            q->ver[1][ver]->nxt=new_node;
        }
        else 
        {
            if(q->ver[1][ver]->branch_or_ancestors<0)
            {
                if(q->ver[1][ver]->branch_or_ancestors==INT_MIN)
                    q->ver[1][ver]->branch_or_ancestors=0;
                else
                    q->ver[1][ver]->branch_or_ancestors=abs(q->ver[1][ver]->branch_or_ancestors);

                int n=q->ver[1][ver]->branch_or_ancestors;
                q->ver[1][ver]->nxt->branch_or_ancestors=-(n+1);
                
                q->ver[1][ver]->nxt->thread=create_thread(n,q->ver[1][ver],q->ver[1][ver]->nxt);

                Node *tmp=q->ver[1][ver]->nxt->nxt;
                while(tmp!=NULL)
                {
                    tmp->branch_or_ancestors=q->ver[1][ver]->nxt->branch_or_ancestors;
                    tmp->thread=q->ver[1][ver]->nxt->thread;
                    tmp=tmp->nxt;
                }
                q->ver[1][ver]->nxt=NULL;
            }
            int n=q->ver[1][ver]->branch_or_ancestors;
            new_node->branch_or_ancestors=-(n+1);
            
            new_node->thread=create_thread(n,q->ver[1][ver],new_node);
        }
        q->ver[1][q->lat_ver]=new_node;
    }
    q->lat_ver++;
    printf("Item added successfully! New version %d created\n",q->lat_ver);
}

int dequeue(Queue *q, int ver)
{
    if(ver>q->lat_ver || ver<0)
    {
        perror("Version doesn't exist!\n");
        return -1;
    }

    Node *tmp;
    if(is_empty(*q,ver))
    {
        perror("Empty list\n");
        return -1;
    }

    if(q->ver[0][ver]==q->ver[1][ver])
    {
        q->ver[0][q->lat_ver]=q->ver[1][q->lat_ver]=NULL;
    }    
    else
    {        
        q->ver[0][q->lat_ver]=advance_ptr(q->ver[0][ver],q->ver[1][ver]);
        q->ver[1][q->lat_ver]=q->ver[1][ver];
    }
    
    q->lat_ver++;
    printf("Front of queue deleted successfully! New version %d created\n",q->lat_ver);
}

void destroy_q(Queue *q)
{
    Node *tmp;
    int i;
    
    for(int i=q->lat_ver-1; i>=0; i--)
    {
        tmp=q->ver[1][i];
        if(tmp->thread!=NULL)
        {
            for(i=0; i<abs(tmp->branch_or_ancestors); i++)
            {
                free((tmp->thread)+i);
            }
        }
        free(tmp);        
    }
}

