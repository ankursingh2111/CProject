#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void push(char c1, int *c2, int *top)
{
  c2[++(*top)]=c1;
}
int pop(int *c2,int *top)
{
  return c2[(*top)--];
}
int checkSymbolPriority(char c1)
{
  if(c1 =='(' || c1=='[' )
    return 17;
  else if(c1=='*' || c1=='/')
    return 13;
  else if(c1=='+' || c1=='-')
    return 12;
  else
    return 1;
}
int evaluatePostFix(char *c1,int *c2, int *top)
{
  int c3;
  int c4;
  int c5;
  int priority=0;
  while(*c1-'0')
  {
    if(*c1=='0')
      break;
    priority=checkSymbolPriority(*c1);
    if(priority==1)
    {
       push(*c1-'0',c2,top);
    }
    else
    {
       c3=(pop(c2,top));
       c4=(pop(c2,top));
       if(*c1=='*')
         c5=c3 * c4;
       else if(*c1=='+')
         c5=c3 + c4;
       else if(*c1=='-')
         c5=c3 - c4;
        
       push(c5,c2,top);
    }
    c1++;
   }
   printf("\n%c", c2[*top]);
}
int main()
{
  char c1[] = "231*+9-";
  char c5[33];
  int top;
  top=-1;
  int *c2;
  c2=(int*)malloc(9*sizeof(int));
  memset(c2,'0',9);

  printf("Entered string\n");
  puts(c1);
  printf("\n");

  evaluatePostFix(c1,c2,&top);
}
