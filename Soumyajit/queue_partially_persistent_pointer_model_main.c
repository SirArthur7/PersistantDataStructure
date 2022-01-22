#include "queue_partially_persistent_pointer_model.h"

int main()
{
    queue_pp *st=init_queue_pp();

    iterate_over_queue_and_print(st,0);

    printf("\n%d\n\n",isempty(st,0));

    enqueue(st,1);
    enqueue(st,2);
    enqueue(st,3);
    enqueue(st,4);
    enqueue(st,5);

    iterate_over_queue_and_print(st,5);
    printf("\n%d %g\n\n",isempty(st,5),front_q(st,5));

    dequeue(st);

    iterate_over_queue_and_print(st,6);
    printf("\n%d %g\n\n",isempty(st,6),front_q(st,6));

    print_queue_pp_all_versions(st);

    return 0;
}
