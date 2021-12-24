/*
* Created by SOUMYAJIT RUDRA SARMA on 24/12/2021
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEADS 1000

#define NO_MOD -1
#define DATA_MOD 0
#define PTR_MOD 1

#define INVALID_VERSION -1

typedef union __mod_value
{

    float mod_data;
    struct __node_pp *mod_next;

}mod_value;

typedef struct __node_pp
{

    // default fields
    float data;
    struct __node_pp *next;

    // back pointer
    struct __node_pp *bptr;

    // modification logs , in our version, we can store max 1 mod
    int mod_type;
    int mod_version;
    mod_value mod_val;
    struct __node_pp *copy_ptr;

    // version info
    int version_no;

}node_pp;

typedef struct __start_node
{

    int version_no;
    node_pp *head;

}start_node;

typedef struct __linked_list_pp
{

    start_node start_module[MAX_HEADS];
    int cur_ver;

}linked_list_pp;

node_pp *make_node_pp()
{
    // returns a node with no connections and invalid version

    node_pp *temp=(node_pp *)malloc(sizeof(node_pp));
    if(temp==NULL)
    {
        printf("Node memory allocation failure ...\n");
        exit(0);
    }
    temp->next=NULL;
    temp->bptr=NULL;
    temp->mod_type=NO_MOD;
    temp->mod_version=INVALID_VERSION;
    temp->copy_ptr=NULL;
    temp->version_no=INVALID_VERSION;

}

linked_list_pp *init_linked_list_pp()
{
    // creates an empty linked list and gives it version 0

    linked_list_pp *temp=(linked_list_pp *)malloc(sizeof(linked_list_pp));
    if(temp==NULL)
    {
        printf("Linked list structure memory allocation failure ...\n");
        exit(0);
    }
    for(int i=0;i<MAX_HEADS;i++)
    {
        temp->start_module[i].version_no=INVALID_VERSION;
        temp->start_module[i].head=NULL;
    }
    temp->cur_ver=0;
    temp->start_module[0].version_no=0;
    temp->start_module[0].head=NULL;

}

void iterate_over_ll_and_print(linked_list_pp *l,int version)
{
    if(version<0||version>l->cur_ver)
    {
        printf("Invalid version selected , max cur version = %d\n",l->cur_ver);
        return;
    }

    int cnt=0;

    node_pp *cur;
    cur=l->start_module[0].head;

    // selecting proper starting node ...
    int i;
    for(i=1;i<MAX_HEADS;i++)
    {
        if(l->start_module[i].version_no==INVALID_VERSION)
            break;

        if(l->start_module[i].version_no<=version)
            cur=l->start_module[i].head;
        else
            break;
    }

    printf("[  ");

    while(1)
    {
        if(cur==NULL)
            break;

        if(cur->version_no>version)
            break;

        // checking for data
        while(cur->copy_ptr!=NULL)
        {
            if(cur->copy_ptr->version_no<=version)
                cur=cur->copy_ptr;
            else
                break;
        }

        if(cur->mod_type==DATA_MOD&&cur->mod_version<=version&&cur->mod_version!=INVALID_VERSION)
        {
            printf("%g  ",cur->mod_val.mod_data);
        }
        else
        {
            printf("%g  ",cur->data);
        }
        cnt++;

        //checking for next
        if(cur->mod_type==PTR_MOD&&cur->mod_version<=version&&cur->mod_version!=INVALID_VERSION)
        {
            cur=cur->mod_val.mod_next;
        }
        else
        {
            cur=cur->next;
        }

    }

    printf("]\n");
    printf("# nodes = %d\n",cnt);

}

void update(linked_list_pp *l,node_pp *cur,int field,mod_value val)
{
    // it always updates in the current version, doesnot automatically increment version
    // it assumes cur is in l

    if(cur->next==NULL&&field==PTR_MOD)
    {
        cur->next=val.mod_next;
        return;
    }

    if(cur->mod_type==NO_MOD)
    {
        cur->mod_version=l->cur_ver;
        cur->mod_type=field;
        cur->mod_val=val;
    }
    else
    {
        // we need to create a copy now
        node_pp *temp=make_node_pp();
        temp->version_no=l->cur_ver;
        temp->bptr=cur->bptr;

        if(cur->mod_type==DATA_MOD)
            temp->data=cur->mod_val.mod_data;
        else
            temp->data=cur->data;

        if(cur->mod_type==PTR_MOD)
            temp->next=cur->mod_val.mod_next;
        else
            temp->next=cur->next;

        if(field==DATA_MOD)
            temp->data=val.mod_data;
        else
            temp->next=val.mod_next;

        cur->copy_ptr=temp;


        cur=temp->next;
        if(cur!=NULL)
            cur->bptr=temp; // it automatically changes next backpointers too

        if(temp->bptr==NULL)
        {
            // means its first node
            for(int i=1;i<MAX_HEADS;i++)
                if(l->start_module[i].version_no==INVALID_VERSION)
                {
                    l->start_module[i].version_no=l->cur_ver;
                    l->start_module[i].head=temp;
                    return;
                }
            printf("Max head reached, cannot update head, error ...\n");
            exit(0);
        }
        else
        {
            mod_value mv;
            mv.mod_next=temp;
            update(l,temp->bptr,PTR_MOD,mv);
        }
    }

}

void add_head(linked_list_pp *l,node_pp *head)
{
    // it always updates in the current version, doesnot automatically increment version

    int i;
    for(i=1;i<MAX_HEADS;i++)
        if(l->start_module[i].version_no==INVALID_VERSION)
        {
            l->start_module[i].version_no=l->cur_ver;
            l->start_module[i].head=head;
            break;
        }

    if(i==MAX_HEADS)
    {
        printf("Max head reached, cannot update head, error ...\n");
        exit(0);
    }

    head->version_no=l->cur_ver;
    head->next=l->start_module[i-1].head;
    if(head->next!=NULL)
        head->next->bptr=head;

}

void add_node_after(linked_list_pp *l,node_pp *prev,node_pp *cur)
{
    // it always updates in the current version, doesnot automatically increment version
    // we know prev is its latest version
    // it assumes prev is in l

    cur->version_no=l->cur_ver;
    if(prev->mod_type==PTR_MOD)
    {
        cur->next=prev->mod_val.mod_next;
        if(prev->mod_val.mod_next!=NULL)
            prev->mod_val.mod_next->bptr=cur;
    }
    else
    {
        cur->next=prev->next;
        if(prev->next!=NULL)
            prev->next->bptr=cur;
    }

    mod_value mv;
    mv.mod_next=cur;
    update(l,prev,PTR_MOD,mv);

    if(prev->copy_ptr==NULL)
        cur->bptr=prev;
    else
        cur->bptr=prev->copy_ptr;

}

void remove_node(linked_list_pp *l,node_pp *cur)
{
    // it always updates in the current version, doesnot automatically increment version
    // we know prev is its latest version
    // it assumes cur is in l

    if(cur->bptr==NULL)
    {
        // means its head node
        int i;
        for(i=1;i<MAX_HEADS;i++)
            if(l->start_module[i].version_no==INVALID_VERSION)
            {
                l->start_module[i].version_no=l->cur_ver;
                if(cur->mod_type==PTR_MOD)
                    l->start_module[i].head=cur->mod_val.mod_next;
                else
                    l->start_module[i].head=cur->next;

                if(l->start_module[i].head!=NULL)
                    l->start_module[i].head->bptr=NULL;
                break;
            }

        if(i==MAX_HEADS)
        {
            printf("Max head reached, cannot update head, error ...\n");
            exit(0);
        }
    }
    else
    {
        node_pp *nxt;
        if(cur->mod_type==PTR_MOD)
            nxt=cur->mod_val.mod_next;
        else
            nxt=cur->next;

        mod_value mv;
        mv.mod_next=nxt;
        update(l,cur->bptr,PTR_MOD,mv);

        cur=cur->bptr;
        if(cur->copy_ptr!=NULL)
            cur=cur->copy_ptr;

        if(nxt!=NULL)
            nxt->bptr=cur;

    }

}



// NOW SOME FUNCTIONS THAT USER CAN CALL SAFELY
// linked_list_pp *init_linked_list_pp() , void iterate_over_ll_and_print(linked_list_pp *l,int version) can also be called by user safely



void insert_head(linked_list_pp *l,float data)
{
    l->cur_ver++;

    node_pp *temp=make_node_pp();
    temp->data=data;

    add_head(l,temp);

    printf("Head inserted successfully ...\n");
    printf("Version %d created ...\n",l->cur_ver);
}

void insert_after_position(linked_list_pp *l,float data,int pos)
{
    // pos starts from 0;
    if(pos<0)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    node_pp *temp,*prev;
    prev=l->start_module[0].head;

    // selecting proper starting node ...
    for(int i=1;i<MAX_HEADS;i++)
    {
        if(l->start_module[i].version_no==INVALID_VERSION)
            break;

        prev=l->start_module[i].head;
    }

    for(int i=0;i<pos;i++)
    {
        if(prev==NULL)
        {
            printf("Position is out of bounds ...\n");
            return;
        }
        while(prev->copy_ptr!=NULL)
            prev=prev->copy_ptr;

        if(prev->mod_type==PTR_MOD)
            prev=prev->mod_val.mod_next;
        else
            prev=prev->next;
    }

    if(prev==NULL)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    // now here we know prev is found and position is valid , so we proceed ...

    temp=make_node_pp();
    temp->data=data;

    l->cur_ver++;

    add_node_after(l,prev,temp);

    printf("Node inserted successfully after position %d ...\n",pos);
    printf("Version %d created ...\n",l->cur_ver);
}

void delete_node_at_pos(linked_list_pp *l,int pos)
{
    // pos starts from 0;
    if(pos<0)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    node_pp *cur;
    cur=l->start_module[0].head;

    // selecting proper starting node ...
    for(int i=1;i<MAX_HEADS;i++)
    {
        if(l->start_module[i].version_no==INVALID_VERSION)
            break;

        cur=l->start_module[i].head;
    }

    for(int i=0;i<pos;i++)
    {
        if(cur==NULL)
        {
            printf("Position is out of bounds ...\n");
            return;
        }
        while(cur->copy_ptr!=NULL)
            cur=cur->copy_ptr;

        if(cur->mod_type==PTR_MOD)
            cur=cur->mod_val.mod_next;
        else
            cur=cur->next;
    }

    if(cur==NULL)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    // now here we know cur is found and position is valid , so we proceed ...

    l->cur_ver++;

    remove_node(l,cur);

    printf("Node deleted successfully at position %d with data = %g...\n",pos,((cur->mod_type==DATA_MOD)?(cur->mod_val.mod_data):(cur->data)));
    printf("Version %d created ...\n",l->cur_ver);
}

void edit_node_data_at_pos(linked_list_pp *l,int pos,float data)
{
    // pos starts from 0;
    if(pos<0)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    node_pp *cur;
    cur=l->start_module[0].head;

    // selecting proper starting node ...
    for(int i=1;i<MAX_HEADS;i++)
    {
        if(l->start_module[i].version_no==INVALID_VERSION)
            break;

        cur=l->start_module[i].head;
    }

    for(int i=0;i<pos;i++)
    {
        if(cur==NULL)
        {
            printf("Position is out of bounds ...\n");
            return;
        }
        while(cur->copy_ptr!=NULL)
            cur=cur->copy_ptr;

        if(cur->mod_type==PTR_MOD)
            cur=cur->mod_val.mod_next;
        else
            cur=cur->next;
    }

    if(cur==NULL)
    {
        printf("Position is out of bounds ...\n");
        return;
    }

    // now here we know cur is found and position is valid , so we proceed ...

    l->cur_ver++;

    mod_value mv;
    mv.mod_data=data;

    update(l,cur,DATA_MOD,mv);

    printf("Node data edited successfully at position %d ...\n",pos);
    printf("Version %d created ...\n",l->cur_ver);
}

void print_list_pp_all_versions(linked_list_pp *l)
{
    for(int i=0;i<=l->cur_ver;i++)
    {
        printf("VERSION #%d -->\n",i);
        iterate_over_ll_and_print(l,i);
        printf("\n");
    }
    printf("\nTotal no of versions = %d\n",l->cur_ver+1);
    printf("__________________________________________________________________\n\n");
}
