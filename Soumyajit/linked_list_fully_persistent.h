/*
* Created on 18/12/2021 by SOUMYAJIT RUDRA SARMA
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VER 100
#define NULL_HISTORY -1
//#define MAX_UPDATES 100

typedef struct __node_p
{

    float data;
    struct __node_p *next[MAX_VER];
    //int prev_ver;

}node_p;

typedef struct __linked_list_p
{

    node_p *head[MAX_VER];
    int cur_ver;
    int version_history[MAX_VER];

}linked_list_p;

node_p *create_node_p(float d)
{
    node_p *temp=(node_p *)malloc(sizeof(node_p));
    if(temp==NULL)
    {
        perror("Node memory allocation failed ...\n");
        return temp;
    }
    temp->data=d;
    for(int i=0;i<MAX_VER;temp->next[i++]=NULL);
    return temp;
}

linked_list_p *init_linked_list_p()
{
    // creates an empty linked list and gives it version 0
    // versions range from 0 to MAX_VER-1
    linked_list_p *temp;
    temp=(linked_list_p *)malloc(sizeof(linked_list_p));
    if(temp==NULL)
    {
        perror("Linked List memory allocation failed ...\n");
        return temp;
    }
    for(int i=0;i<MAX_VER;temp->head[i]=NULL,temp->version_history[i++]=NULL_HISTORY);
    temp->cur_ver=0;
    return temp;
}

int max_version_reached_l(linked_list_p *l)
{
    if(l->cur_ver==MAX_VER-1)
        return 1;
    else
        return 0;
}

int empty_l(linked_list_p *l,int version)
{
    // returns -1 for invalid version, 1 for empty and 0 for non_empty
    if(l->cur_ver<version||version<0)
        return -1;

    if(l->head[version]==NULL)
        return 1;
    else
        return 0;
}

int length_l(linked_list_p *l,int version)
{
    // returns -1 for invalid version, else length
    if(l->cur_ver<version||version<0)
        return -1;

    int cnt=0;
    node_p *cur=l->head[version];
    while(cur!=NULL)
    {
        cnt++;
        cur=cur->next[version];
    }

    return cnt;
}

int insert_front(linked_list_p *l,int version,float data)
{
    // returns cur_ver if successful else -1 if max_version reached or unsuccessful or invalid version
    if(max_version_reached_l(l))
    {
        printf("Max version reached\n");
        return -1;
    }

    if(l->cur_ver<version||version<0)
    {
        printf("Version out of bounds\n");
        return -1;
    }

    node_p *temp,*cur;
    if((temp=create_node_p(data))==NULL)
        return -1;

    l->cur_ver=l->cur_ver+1;
    l->version_history[l->cur_ver]=version;

    l->head[l->cur_ver]=l->head[version];
    cur=l->head[version];
    while(cur!=NULL)
    {
        cur->next[l->cur_ver]=cur->next[version]; // first copying links into new version
        cur=cur->next[version];
    }

    temp->next[l->cur_ver]=l->head[l->cur_ver];
    l->head[l->cur_ver]=temp;

    return l->cur_ver;
}

int delete_front(linked_list_p *l,int version)
{
    // returns cur_ver if successful else -1 if max_version reached or list is already empty or invalid version
    if(max_version_reached_l(l))
    {
        printf("Max version reached\n");
        return -1;
    }

    if(l->cur_ver<version||version<0)
    {
        printf("Version out of bounds\n");
        return -1;
    }

    if(empty_l(l,version))
    {
        printf("List is empty , cannot delete front\n");
        return -1;
    }

    l->cur_ver=l->cur_ver+1;
    l->version_history[l->cur_ver]=version;

    node_p *cur;
    l->head[l->cur_ver]=l->head[version];
    cur=l->head[version];
    while(cur!=NULL)
    {
        cur->next[l->cur_ver]=cur->next[version]; // first copying links into new version
        cur=cur->next[version];
    }

    l->head[l->cur_ver]=l->head[l->cur_ver]->next[l->cur_ver];

    return l->cur_ver;
}

int insert_after_pos(linked_list_p *l,int version,int pos,float data)
{
    // returns cur_ver if successful else -1 if max_version reached or unsuccessful or invalid version
    // pos starts from 0 , pos can vary from 0 (after head insertion) to list_length-1(tail insertion)
    if(max_version_reached_l(l))
    {
        printf("Max version reached\n");
        return -1;
    }

    if(l->cur_ver<version||version<0)
    {
        printf("Version out of bounds\n");
        return -1;
    }

    if(pos<0||pos>=length_l(l,version))
    {
        printf("Pos out of bounds\n");
        return -1;
    }

    node_p *temp,*cur;
    if((temp=create_node_p(data))==NULL)
        return -1;

    l->cur_ver=l->cur_ver+1;
    l->version_history[l->cur_ver]=version;

    l->head[l->cur_ver]=l->head[version];
    cur=l->head[version];
    while(cur!=NULL)
    {
        cur->next[l->cur_ver]=cur->next[version]; // first copying links into new version
        cur=cur->next[version];
    }

    cur=l->head[l->cur_ver];
    for(int i=0;i<pos;i++)
    {
        cur=cur->next[l->cur_ver]; // we have already checked within bounds at beginning
    }

    temp->next[l->cur_ver]=cur->next[l->cur_ver];
    cur->next[l->cur_ver]=temp;

    return l->cur_ver;
}

int delete_at_pos(linked_list_p *l,int version,int pos)
{
    // returns cur_ver if successful else -1 if max_version reached or list empty at that pos or invalid version
    // pos starts from 0 , pos can vary from 0 (head deletion) to list_length-1(tail deletion)
    if(max_version_reached_l(l))
    {
        printf("Max version reached\n");
        return -1;
    }

    if(l->cur_ver<version||version<0)
    {
        printf("Version out of bounds\n");
        return -1;
    }

    if(pos<0||pos>=length_l(l,version))
    {
        printf("Position out of bounds\n");
        return -1;
    }

    if(pos==0)
        return delete_front(l,version); // base case ...

    l->cur_ver=l->cur_ver+1;
    l->version_history[l->cur_ver]=version;

    node_p *cur;
    l->head[l->cur_ver]=l->head[version];
    cur=l->head[version];
    while(cur!=NULL)
    {
        cur->next[l->cur_ver]=cur->next[version]; // first copying links into new version
        cur=cur->next[version];
    }

    cur=l->head[l->cur_ver];
    for(int i=0;i<pos-1;i++)
    {
        cur=cur->next[l->cur_ver]; // we have already checked within bounds at beginning
    }

    cur->next[l->cur_ver]=cur->next[l->cur_ver]->next[l->cur_ver]; // here cur cannot be last node becayse of position checking at start and cur is at pos-1

    return l->cur_ver;
}


void print_list_p(linked_list_p *l,int version)
{
    if(l->cur_ver<version||version<0)
    {
        printf("Invalid Version requested, cannot print ...\n");
        return;
    }

    //int cnt=0;

    node_p *cur=l->head[version];
    printf("[ ");
    while(cur!=NULL)
    {
        //cnt++;
        printf("%g %s",cur->data,((cur->next[version]==NULL)?(""):(", ")));
        cur=cur->next[version];
    }

    printf("]\n");
    //printf("Number of elements = %d\n",cnt);

}

void print_list_all_versions(linked_list_p *l)
{
    int h;
    for(int i=0;i<=l->cur_ver;i++)
    {
        printf("VERSION #%d -->\n",i);
        print_list_p(l,i);
        printf("# elements in version %d = %d\n",i,length_l(l,i));
        if((h=l->version_history[i])!=NULL_HISTORY)
            printf("This is generated from version %d\n\n",h);
        else
            printf("First Version ...\n\n");
    }
    printf("\nTotal no of versions = %d\n",l->cur_ver+1);
    printf("Max no of versions allowed = %d\n",MAX_VER);
    printf("__________________________________________________________________\n\n");
}
