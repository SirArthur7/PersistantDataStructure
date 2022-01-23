/*
* Created by SOUMYAJIT RUDRA SARMA on 24/12/2021
*/

#include "linked_list_partially_persistent_pointer_model.h"

//typedef linked_list_pp queue_pp;

typedef struct __queue_pp
{
    linked_list_pp *l;
    node_pp *tail;
}queue_pp;

queue_pp *init_queue_pp()
{
    queue_pp *temp=(queue_pp *)malloc(sizeof(queue_pp));
    temp->l=init_linked_list_pp();
    temp->tail=NULL;
    return temp;
}

void iterate_over_queue_and_print(queue_pp *q,int version)
{
    iterate_over_ll_and_print(q->l,version);
}

int isempty(queue_pp *qq,int version)
{
    linked_list_pp *q=qq->l;
    if(version<0||version>q->cur_ver)
    {
        //printf("Invalid version selected , max cur version = %d\n",q->cur_ver);
        return 1;
    }

    node_pp *cur;
    cur=q->start_module[0].head;

    // selecting proper starting node ...
    int i;
    for(i=1;i<MAX_HEADS;i++)
    {
        if(q->start_module[i].version_no==INVALID_VERSION)
            break;

        if(q->start_module[i].version_no<=version)
            cur=q->start_module[i].head;
        else
            break;
    }

    if(cur==NULL)
        return 1;
    else
        return 0;
}

void enqueue(queue_pp *q,float data)
{
    if(isempty(q,q->l->cur_ver))
    {
        insert_head(q->l,data);
        // selecting proper starting node ...
        int i;
        for(i=1;i<MAX_HEADS;i++)
        {
            if(q->l->start_module[i].version_no==INVALID_VERSION)
                break;
        }
        q->tail=q->l->start_module[i-1].head;
    }
    else
    {
        node_pp *temp=make_node_pp();
        temp->data=data;

        q->l->cur_ver++;

        add_node_after(q->l,q->tail,temp);
        q->tail=temp;

        //printf("Node enqueued successfully ...\n");
        //printf("Version %d created ...\n",q->l->cur_ver);
    }
}

void dequeue(queue_pp *q)
{
    delete_node_at_pos(q->l,0);
}

float front_q(queue_pp *qq,int version)
{
    linked_list_pp *q=qq->l;
    if(version<0||version>q->cur_ver)
    {
        //printf("Invalid version selected , max cur version = %d\n",q->cur_ver);
        return 0;
    }

    node_pp *cur;
    cur=q->start_module[0].head;

    // selecting proper starting node ...
    int i;
    for(i=1;i<MAX_HEADS;i++)
    {
        if(q->start_module[i].version_no==INVALID_VERSION)
            break;

        if(q->start_module[i].version_no<=version)
            cur=q->start_module[i].head;
        else
            break;
    }

    if(cur==NULL)
    {
        //printf("Stack Underflow\n");
        return 0;
    }

    if(cur->mod_type==DATA_MOD&&cur->mod_version<=version&&cur->mod_version!=INVALID_VERSION)
    {
        return cur->mod_val.mod_data;
    }
    else
    {
        return cur->data;
    }
}

void print_queue_pp_all_versions(queue_pp *q)
{
    print_list_pp_all_versions(q->l);
}
