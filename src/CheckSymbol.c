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
int checkSymbolBalance(char c1, char c2)
{
  if(c1 =='{' && c2=='}')
    return 0;
  else if(c1=='(' && c2==')')
    return 0;
  else if(c1=='[' && c2==']')
    return 0;
  else
    return 1;
}
int checkSymbol(char *c1,char *c2,int *top)
{
  int return1=0;
  char c3;
  while(*c1!='0')
  {
    if(*c1=='{' || *c1=='(' || *c1=='[')
      push(*c1,c2,top);
    else if(*c1=='}' || *c1==')' || *c1==']')
    {
      c3=pop(c2,top);

      return1=checkSymbolBalance(c3,*c1);
      if(return1)
      {
        printf("Symbol not balanced");
        exit(0);
      } 
    }
    c1++;
     
  }
  printf("Symbol balanced");
}
int main()
{
  char *c1;
  int top;
  top=-1;
  char *c2;
  c1=(char*)malloc(12*sizeof(char));
  c2=(char*)malloc(12*sizeof(char));

  memset(c1,'0',sizeof(c1));
  memset(c2,'0',sizeof(c2));

  printf("Please enter the string\n");
  scanf("%s",c1);
  printf("\n");
  printf("Entered string\n");
  puts(c1);
 
  checkSymbol(c1,c2,&top);
}
