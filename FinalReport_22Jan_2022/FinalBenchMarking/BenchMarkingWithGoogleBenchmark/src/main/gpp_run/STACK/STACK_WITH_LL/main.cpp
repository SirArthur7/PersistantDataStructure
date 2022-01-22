#include "stack_partially_persistent_pointer_model.h"

int main()
{
    stack_pp *st=init_stack_pp();
    iterate_over_stack_and_print(st,0);

    printf("\n%d\n\n",isempty(st,0));

    push(st,1);
    push(st,2);
    iterate_over_stack_and_print(st,st->cur_ver);
    pop(st);
    iterate_over_stack_and_print(st,st->cur_ver);
    pop(st);
    iterate_over_stack_and_print(st,st->cur_ver);
    pop(st);
    iterate_over_stack_and_print(st,st->cur_ver);
    
    iterate_over_stack_and_print(st,5);
    printf("\n%d %g\n\n",isempty(st,5),top(st,5));

    //pop(st);

    iterate_over_stack_and_print(st,6);
    printf("\n%d %g\n\n",isempty(st,6),top(st,6));

    print_stack_pp_all_versions(st);

    return 0;
}
