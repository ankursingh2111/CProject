#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void push(char c1, char *c2, int *top)
{
  c2[++(*top)]=c1;
}
char pop(char *c2,int *top)
{
  char c1=c2[(*top)--];
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
int checkSymbol(char *c1,char *c2,int *top)
{
  int return1=0;
  int priority=0;
  int priority1=0;
  char c3;
  while(*c1!='0')
  {
    priority=checkSymbolPriority(*c1);
    if(priority==1)
    {
       if(*c1==')')
       {
          while(c3=pop(c2,top))
          {
             if(c3!='(')
               printf("%c",c3);
             else
               break;
          }
       }
       else
          printf("%c",*c1);
    }
    else
    {
       while(c3=pop(c2,top))
       {
          if(c3!='(')
          {
            priority1=checkSymbolPriority(c3);
            if(priority1>=priority)
              printf("%c",c3);
            else
            {
              push(c3,c2,top);
              break;
            }
          }
          else
          {
             push(c3,c2,top);
             break ;
          }
       }
       push(*c1,c2,top);
    }
    
    c1++;

  }
  while(c3=pop(c2,top))
   printf("%c",c3);
}
int main()
{
  char *c1;
  char c5[33];
  int top;
  top=-1;
  char *c2;
  c1=(char*)malloc(18*sizeof(char));
  c2=(char*)malloc(18*sizeof(char));
  printf("%lu\n",sizeof(c5));
  printf("%lu\n",sizeof(char));
  printf("%lu\n",sizeof(char *));
  memset(c1,'0',sizeof(c1));
  memset(c2,'0',18);

  printf("Please enter the string\n");
  scanf("%s",c1);
  printf("\n");
  printf("Entered string\n");
  puts(c1);

  checkSymbol(c1,c2,&top);
}

