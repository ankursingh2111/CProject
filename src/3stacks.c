#include<stdio.h>
#include<stdlib.h>

typedef struct stackArray
{
  int *toparray;
  int *startarray;
  int end;
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
  
  stack->array=(int*)malloc(20*sizeof(int));
  if(!stack->array)
  {
    printf("No memory allocated");
    exit(0);
  }
  stack->toparray=(int*)malloc(6*sizeof(int));
  stack->startarray=(int*)malloc(6*sizeof(int));
  int i=0;
  int j=0;
  while(i<=20)
  {
    stack->startarray[j]=i;
    stack->toparray[j]=i;
    i=i+4;
    j++;
  }
  return stack;
}
void push(stackArray *stack, int num,int stacknum)
{
  int *top;
  int *start;
  top=(int*)malloc(6*sizeof(int));
  start=(int*)malloc(6*sizeof(int));
  int i=0;
  int flag=0,stacknum1=0;
  int max=5;
  stacknum=stacknum-1;
  while(i<=max)
  {
    top[i]=stack->toparray[i];
    start[i]=stack->startarray[i];
    
    i++; 
  } 
  i=0;
  while(i<max)
  {
    if(top[i]==start[i+1])
      flag=0;
    else
    {
      flag=1;
      break;
    }
    i++;
  }
  if(!flag)
  {
    printf("Stack 1 and 2 and 3 are full\n");
    exit(0);
  } 
  if(top[stacknum]==start[stacknum+1])
  {
     stacknum1=stacknum+1;
     while(stacknum1<max)
     {
       if(top[stacknum1]==start[stacknum1])
         flag=0;
       else
       {
         flag=1;
         break;
       }
       stacknum1++;
     }
     if(flag)
     {
       while(max>stacknum1)
       {
         if(top[max-1]==top[max])
         {
            max--;
            continue;
         }
         while(top[max-1]>=start[max-1])
         {
           stack->array[top[max-1]+1]=stack->array[top[max-1]];
           top[max-1]--;
         }
         stack->startarray[max-1]++;
         stack->toparray[max-1]++;
         max--;
       } 
     }
     else
     {
       stacknum1=0;
       while(stacknum1<stacknum)
       {
         if(top[stacknum1]==top[stacknum1+1])
         {  
            stacknum1++;
            continue;
         }
         while(start[stacknum1+1]>=top[stacknum1+1])
         { 
           stack->array[start[stacknum1+1]-1]=stack->array[start[stacknum1+1]];
           start[stacknum1+1]++;
         }
         stack->startarray[stacknum1+1]--;
         stack->toparray[stacknum1+1]--;
       } 
       stacknum1++; 
     }
  }
  stack->array[stack->toparray[stacknum]++]=num;

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
void display(stackArray *stack)
{
  int *top;
  int *start;
  top=(int*)malloc(6*sizeof(int));
  start=(int*)malloc(6*sizeof(int));
  int i=0;
  int max=5;
  while(i<max)
  {
    top[i]=stack->toparray[i];
    start[i]=stack->startarray[i];

    i++;
  }
  i=0;
  while(i<max)
  {
    while((stack->array[start[i]]) && (start[i]<top[i]))
    {
      printf("%d ", stack->array[start[i]]);
      start[i]++;
    }
    printf("\n");
    i++;
  }
}
int main()
{
  stackArray *stack;
  stack=createStack(); 
  push(stack,1,1);
  push(stack,2,1);
  push(stack,3,1);
  push(stack,4,1);
  push(stack,5,2);
  push(stack,6,2);
  push(stack,11,3);
  push(stack,12,3);
  push(stack,8,2);
  push(stack,9,2);
  push(stack,7,2);
  push(stack,13,3);
  push(stack,14,4);
  push(stack,15,4);
  push(stack,16,5);
  push(stack,17,5);
  push(stack,10,1);

 display(stack);
  printf("\n");
//  display(stack,2);
  printf("\n");
//  display(stack,3);
}
