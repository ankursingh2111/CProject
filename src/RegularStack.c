#include<stdio.h>
#include<stdlib.h>

typedef struct stackArray
{
  int top;
  int capacity;
  int *array;
}stackArray;
stackArray * createStack()
{
  stackArray *stack=(stackArray*)malloc(sizeof(stackArray));
  if(stack==NULL)
  {
    printf("No memory allocated");
    exit(0);
  }
  stack->capacity=10;
  stack->top=-1;
  stack->array=(int*)malloc(stack->capacity*sizeof(int));
  if(!stack->array)
  {
    printf("No memory allocated");
    exit(0);
  }
  return stack;
}
int full(int capacity, int top)
{
  if(capacity==top)
  {
    return 0;
  }
  else
    return 1;
}
int empty(int top)
{
  if(top==-1)
    return 1;
  else
    return 0;
}
void push(stackArray *stack, int data)
{
  if(full(stack->capacity,stack->top+1))
  {
    stack->array[++stack->top]=data;   
  }
  else
  {
    printf("Stack is full");
    exit(0);
  }
}
int pop(stackArray *stack)
{
   if(empty(stack->top))
   {
     printf("No elements in stack");
     exit(0);
   }
   return stack->array[stack->top--];
}
void traverse(stackArray *stack)
{
  if(empty(stack->top))
  {
    printf("No elements in stack");
    exit(0);
  }
  int count=0;
  while(count<stack->capacity)
    printf("%d ",stack->array[count++]);
    
}
int main()
{
  stackArray *stack;
  stack=createStack();
  push(stack,1);
  push(stack,2);
  push(stack,3);
  push(stack,4);
  push(stack,5);
  push(stack,6);
  push(stack,7);
  printf("\n");
  traverse(stack);
  int count;
  count=pop(stack);
  printf("\n");
  printf("Popped element %d",count);
  printf("\n");
  traverse(stack);
  push(stack,9);
  push(stack,8);
  printf("\n");
  traverse(stack);
  count=pop(stack);
  printf("\n");
  printf("Popped element %d",count);
  printf("\n");
  traverse(stack);

}
