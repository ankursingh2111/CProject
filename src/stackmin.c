#include<stdio.h>
#include<stdlib.h>

typedef struct stackArray
{
  int top;
  int capacity;
  int *array;
}stackArray;
typedef struct stackLists
{
  stackArray *s1;
  stackArray *s2;
}stackLists;

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
int push(stackLists *sl1,int num)
{
  sl1->s1->array[++(sl1->s1->top)]=num;
  if(sl1->s2->top==-1)
  {
    sl1->s2->array[++(sl1->s2->top)]=num; 
    return 0;
  }
  if(num <(sl1->s2->array[sl1->s2->top]))
    sl1->s2->array[++(sl1->s2->top)]=num;
}
void pop(stackLists *sl1)
{
   // sl1->s1.array[sl1->s1.top--];
   // sl1->s2.array[sl1->s2.top--];
   int num=sl1->s1->array[sl1->s1->top];
   sl1->s1->top--;
   if(num==sl1->s2->array[sl1->s2->top])
     sl1->s2->top--;
}
void display(stackLists *sl1)
{
  int num=sl1->s1->top;
  while(num>=0)
  {
    printf(" %d\n",sl1->s1->array[num]);
    num--;
    
  }
  num=sl1->s2->top;
  while(num>=0)
  {
    printf("%d\n",sl1->s2->array[num]);
    num--;

  }
}
int main()
{
  stackLists *sl1;
  sl1=(stackLists *)malloc(sizeof(stackLists));
  sl1->s1=createStack();
  sl1->s2=createStack();

  printf("Enter the elments\n");
  push(sl1,8);
  push(sl1,9);
  push(sl1,4);
  push(sl1,6);
  push(sl1,3);
  push(sl1,7);
  push(sl1,2);

  display(sl1);
  printf("\n");

  pop(sl1);
  display(sl1);
  printf("\n");
  pop(sl1);
  display(sl1);
  
}
