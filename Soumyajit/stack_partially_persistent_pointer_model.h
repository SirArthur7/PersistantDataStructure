/*
* Created by SOUMYAJIT RUDRA SARMA on 20/01/2022
*/

#include "linked_list_partially_persistent_pointer_model.h"

typedef linked_list_pp stack_pp;

stack_pp *init_stack_pp()
{
    return init_linked_list_pp();
}

void iterate_over_stack_and_print(stack_pp *st,int version)
{
    iterate_over_ll_and_print(st,version);
}

void push(stack_pp *st,float data)
{
    insert_head(st,data);
}

void pop(stack_pp *st)
{
    delete_node_at_pos(st,0);
}

int isempty(stack_pp *st,int version)
{
    if(version<0||version>st->cur_ver)
    {
        printf("Invalid version selected , max cur version = %d\n",st->cur_ver);
        return 1;
    }

    node_pp *cur;
    cur=st->start_module[0].head;

    // selecting proper starting node ...
    int i;
    for(i=1;i<MAX_HEADS;i++)
    {
        if(st->start_module[i].version_no==INVALID_VERSION)
            break;

        if(st->start_module[i].version_no<=version)
            cur=st->start_module[i].head;
        else
            break;
    }

    if(cur==NULL)
        return 1;
    else
        return 0;
}

float top(stack_pp *st,int version)
{
    if(version<0||version>st->cur_ver)
    {
        printf("Invalid version selected , max cur version = %d\n",st->cur_ver);
        return 0;
    }

    node_pp *cur;
    cur=st->start_module[0].head;

    // selecting proper starting node ...
    int i;
    for(i=1;i<MAX_HEADS;i++)
    {
        if(st->start_module[i].version_no==INVALID_VERSION)
            break;

        if(st->start_module[i].version_no<=version)
            cur=st->start_module[i].head;
        else
            break;
    }

    if(cur==NULL)
    {
        printf("Stack Underflow\n");
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

void print_stack_pp_all_versions(stack_pp *st)
{
    print_list_pp_all_versions(st);
}
