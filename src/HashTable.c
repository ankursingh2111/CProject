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
void push(stackArray *sl1,int num)
{
  sl1->array[++(sl1->top)]=num;
}
int pop(stackArray *sl1)
{
   int num=sl1->array[sl1->top];
   sl1->top--;
   return num;
}
