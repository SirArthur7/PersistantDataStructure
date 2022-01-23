#include "FP_QUEUE.h"

int main()
{

    int ch,version,data;
    Queue *q;
    q=init_q();
    if(q==NULL)
        return -1;
    else
        printf("\nFully Persistent Queue Menu\n\n");

    while(1)
    {
        printf("\nPress 1 to print any version of the queue\n");
        printf("Press 2 to insert element into queue\n");
        printf("Press 3 to delete element from queue\n");
        printf("Press 4 to exit\n");
        printf("Enter your choice: ");

        scanf("%d",&ch);

        switch(ch)
        {

        case 1:            
            print_q_all(q);
             
            break;
        case 2:             
            printf("Enter version you want to use: ");
            scanf("%d",&version);
            printf("Enter data you want to enqueue: ");
            scanf("%d",&data);
            if((enqueue(q,version,data))==-1)
                printf("Error\n");             
            break;
        case 3:
            printf("Enter version you want to use: ");
            scanf("%d",&version);            
            if((dequeue(q,version))==-1)
                printf("Error\n");             
            break;
        case 4:
            destroy_q(q);
            return 0;
        default:
            printf("Invalid choice! Try again!\n");
        }
    }
}
