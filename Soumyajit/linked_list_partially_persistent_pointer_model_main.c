/*
* Created by SOUMYAJIT RUDRA SARMA on 24/12/2021
*/

#include "linked_list_partially_persistent_pointer_model.h"

#define NEWL printf("\n")

int main()
{

    int choice,pos;
    float data;
    linked_list_pp *l;
    l=init_linked_list_pp();

    printf("Within linked lists, position starts from 1 ...\n\n");

    while(1)
    {

        printf("Press 1 to print current linked list all versions\n");
        printf("Press 2 to insert at front into current linked list\n");
        printf("Press 3 to insert after position into current linked list\n");
        printf("Press 4 to delete at position from current linked list\n");
        printf("Press 5 to edit a node's data at a position\n");
        printf("Press 6 to exit\n");
        printf("Enter your choice: ");

        scanf("%d",&choice);

        switch(choice)
        {

        case 1:
            NEWL;
            print_list_pp_all_versions(l);
            NEWL;
            break;
        case 2:
            NEWL;
            printf("Enter data you want to insert at front: ");
            scanf("%f",&data);
            insert_head(l,data);
            NEWL;
            break;
        case 3:
            NEWL;
            printf("Enter data you want to insert and after which position: ");
            scanf("%f %d",&data,&pos);
            insert_after_position(l,data,pos-1);
            NEWL;
            break;
        case 4:
            NEWL;
            printf("Enter pos you want to delete: ");
            scanf("%d",&pos);
            delete_node_at_pos(l,pos-1);
            NEWL;
            break;
        case 5:
            NEWL;
            printf("Enter pos you want to edit and the new data: ");
            scanf("%d %f",&pos,&data);
            edit_node_data_at_pos(l,pos-1,data);
            NEWL;
            break;
        case 6:
            NEWL;
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
