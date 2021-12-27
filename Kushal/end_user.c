#include <stdio.h>
#include <stdbool.h>
// #include "header.h"
#include "details.h"

int main()
{
  int x, y, z;

  Stack_fp *stack = init_stack();
  printf("Enter 5 numbers to push to stack\n");
  for (int i = 0; i < 5; i++)
  {
    scanf("%d", &x);
    if (!push(stack, x, stack->live_version))
      printf("Error\n");
  }
  printf("version now %d\n", stack->live_version);
  printf("\nEnter 3 (value,version) to push to stack\n");
  for (int i = 0; i < 3; i++)
  {
    scanf("%d,%d", &x, &y);
    if (!push(stack, x, y))
      printf("Error\n");
  }

  printf("\nEnter 3 (version) to pop from stack\n");
  for (int i = 0; i < 3; i++)
  {
    scanf("%d", &x);
    if (!pop(stack, x))
      printf("Error\n");
  }

  printf("\n");
  for (int i = 0; i < MAX_OP; i++)
  {
    print(stack, i);
  }
  return 0;
}
