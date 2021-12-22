/*
* Created on 18/12/2021 by SOUMYAJIT RUDRA SARMA
*/

#include "linked_list_fully_persistent.h"

#define NEWL printf("\n")

int main()
{

    int choice,pos,version,c_ver;
    float data;
    linked_list_p *l;
    l=init_linked_list_p();
    if(l==NULL)
        return 1;
    else
        printf("Persistent linked list successfully initialized ...\n\n");

    printf("Within linked lists, position starts from 1 ...\n\n");

    while(1)
    {

        printf("Press 1 to print current linked list all versions\n");
        printf("Press 2 to insert at front into current linked list\n");
        printf("Press 3 to insert after position into current linked list\n");
        printf("Press 4 to delete front from current linked list\n");
        printf("Press 5 to delete at position from current linked list\n");
        printf("Press 6 to exit\n");
        printf("Enter your choice: ");

        scanf("%d",&choice);

        switch(choice)
        {

        case 1:
            NEWL;
            print_list_all_versions(l);
            NEWL;
            break;
        case 2:
            NEWL;
            printf("Enter version you want to operate on: ");
            scanf("%d",&version);
            printf("Enter data you want to insert at front: ");
            scanf("%f",&data);
            if((c_ver=insert_front(l,version,data))==-1)
                printf("Error ...\n");
            else
                printf("Successful, new version = %d created ...\n",c_ver);
            NEWL;
            break;
        case 3:
            NEWL;
            printf("Enter version you want to operate on: ");
            scanf("%d",&version);
            printf("Enter data you want to insert and after which position: ");
            scanf("%f %d",&data,&pos);
            if((c_ver=insert_after_pos(l,version,pos-1,data))==-1)
                printf("Error ...\n");
            else
                printf("Successful, new version = %d created ...\n",c_ver);
            NEWL;
            break;
        case 4:
            NEWL;
            printf("Enter version you want to operate on: ");
            scanf("%d",&version);
            printf("Deleting head ...\n");
            if((c_ver=delete_front(l,version))==-1)
                printf("Error ...\n");
            else
                printf("Successful, new version = %d created ...\n",c_ver);
            NEWL;
            break;
        case 5:
            NEWL;
            printf("Enter version you want to operate on: ");
            scanf("%d",&version);
            printf("Enter pos you want to delete: ");
            scanf("%d",&pos);
            if((c_ver=delete_at_pos(l,version,pos-1))==-1)
                printf("Error ...\n");
            else
                printf("Successful, new version = %d created ...\n",c_ver);
            NEWL;
            break;
        case 6:
            NEWL;
            // delete the structure
            printf("Program ended ...\n");
            return 0;
            NEWL;
            break;
        default:
            NEWL;
            printf("Invalid choice, please try again ...\n");
            NEWL;

        }

    }

}
