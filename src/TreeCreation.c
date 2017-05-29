#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct binaryTree
{
  int data;
  struct binaryTree *left;
  struct binaryTree *right;
}binaryTree;

typedef struct queueArray
{
  int front,rear;
  int capacity;
  binaryTree **btree;
}queueArray;
queueArray * createQueue()
{
  queueArray *queue=(queueArray*)malloc(sizeof(queueArray));
  if(queue==NULL)
  {
    printf("No memory allocated");
    exit(0);
  }
  queue->capacity=11;
  queue->front=queue->rear=-1;
  queue->btree=(binaryTree**)malloc(queue->capacity*sizeof(binaryTree));
  if(!queue->btree)
  {
    printf("No memory allocated");
    exit(0);
  }
  return queue;
}
binaryTree * createTree(int num)
{
  binaryTree *btemp=(binaryTree*)malloc(sizeof(binaryTree));
  if(btemp==NULL)
  {
     printf("No memory allocated");
     exit(1);
  }
  btemp->data=num;
  btemp->left=NULL;
  btemp->right=NULL;
  return btemp;
}
void resizeQueue(queueArray *queue)
{
  int size=queue->capacity;
  queue->capacity=queue->capacity*2;
  int i=0;
  queue->btree=realloc(queue->btree,queue->capacity);

  if(!queue->btree)
  {
    printf("No memory allocated");
    exit(0);
  }
  if(queue->front>queue->rear)
  {
    for(i=0;i<=queue->rear;i++)
    {
      queue->btree[i+size]=queue->btree[i];
    }
  queue->rear=queue->rear+size;
  }

}

void enque(queueArray *queue, binaryTree* num)
{
  if((queue->rear==queue->capacity-1 && queue->front==0) || (queue->front==queue->rear+1))
  {
    printf("Queue is full");
    resizeQueue(queue);
  }
  if(queue->rear==queue->capacity-1 && queue->front!=0)
    queue->rear=-1;

  queue->btree[++queue->rear]=num;

  if(queue->front==-1)
    queue->front=0;
}
binaryTree* deque(queueArray *queue)
{
  if(queue->rear==-1 && queue->front==-1)
    printf("Queue is Empty");

  binaryTree *num=queue->btree[queue->front++];

  if(queue->front==queue->capacity)
    queue->front=0;
  if(queue->front-1==queue->rear)
    queue->front=queue->rear=-1;
  
  return num;
}
binaryTree * frontNode(queueArray *queue)
{
   return queue->btree[queue->front];
}           
binaryTree * addNode(binaryTree *root, int num,queueArray *queue)
{
   binaryTree *prev,*curr, *temp;

   temp=createTree(num);
   if(root==NULL)
     root=temp;
   else
   {
     curr=frontNode(queue);

     if(curr->left==NULL)
       curr->left=temp;
     else if(curr->right==NULL)
       curr->right=temp;
     else
     {
        deque(queue);
        
        curr=frontNode(queue);

        if(curr->left==NULL)
        curr->left=temp;
        else if(curr->right==NULL)
        curr->right=temp;
     }
   }
   enque(queue,temp);

   return root;
}
int isEmpty(queueArray *queue)
{
    return queue->front == -1;
}
void levelOrder(binaryTree* root)
{
    queueArray * queue = createQueue(10);
 
    enque(queue,root);
 
    while (!isEmpty(queue))
    {
        binaryTree* temp = deque(queue);
 
        printf("%d ", temp->data);
 
        if (temp->left)
            enque(queue,temp->left);
 
        if (temp->right)
            enque(queue,temp->right);
    }
}
void levelOrderleafs(binaryTree* root)
{
    queueArray * queue = createQueue(12);
    
    enque(queue,root);
    int count_leaf=0;
    int count_sng_leaf=0;
    int count_full=0;
    binaryTree* temp;
    while (!isEmpty(queue))
    {
         temp = deque(queue);
        if((temp->left) && (temp->right))
          count_full++;
        else if(!temp->left &&!temp->right)
          count_leaf++;
        else
          count_sng_leaf++;
        if (temp->left)
            enque(queue,temp->left);

        if (temp->right)
            enque(queue,temp->right);
    }
    printf("\nNumber of full nodes, %d\n",count_full);
    printf("\nNumber of leaf nodes, %d\n",count_leaf);
    printf("\nNumber of half nodes, %d\n",count_sng_leaf);
    printf("\nlast Node, %d\n",temp->data);
    
 
}
int levelOrderheight(binaryTree* root)
{
    queueArray * queue = createQueue(20);
    int level=0;
    enque(queue,root);
    enque(queue,NULL);

    while (!isEmpty(queue))
    {
        binaryTree* temp = deque(queue);
        if(temp==NULL)
        {
          if(!isEmpty(queue))
          enque(queue,NULL);
          level++;
        }
        else
        {
          if (temp->left)
            enque(queue,temp->left);

          if (temp->right)
            enque(queue,temp->right);
        }
    }
    return level;
}
int findMax(binaryTree *btree)
{
  int max1, max2;
  int max=0;
  int root_val;
  if(btree)
  {
    root_val=btree->data;
    max1=findMax(btree->left);
    max2=findMax(btree->right);
    if(max2>max1)
      max=max2;
    else
     max=max1;
    if(max<root_val)
      max=root_val;    
  }
  return max;
}
int findNode(binaryTree *btree, int max)
{
  int temp=0;
  if(btree)
  {
    if(max==btree->data)
      return 1;

    temp=findNode(btree->left,max);
    if(temp!=0)
      return temp;
    temp= findNode(btree->right,max);
    if(temp!=0)
      return temp;
   }
  return 0;
}
int findNumNode(binaryTree *btree)
{
  int temp=0;
  int temp1=0;
  if(btree==NULL)
    return 0;
  temp=findNumNode(btree->left);
  temp1=findNumNode(btree->right);
  return temp+1+temp1;
}
binaryTree * insertNode(binaryTree *btree, int num)
{
  queueArray *queue=createQueue();
  binaryTree *temp,*curr;
  curr=createTree(num);
  if(btree)
  {
    enque(queue,btree);

    while(!isEmpty(queue))
    {
      temp=deque(queue);
      if(temp->left)
        enque(queue,temp->left);
      else
      {
        temp->left=curr;
        return btree;
      }
      if(temp->right)
        enque(queue,temp->right);
      else
      {
        temp->right=curr;
        return btree;  
      }
    }
  }
}
int compareTree(binaryTree *btree1 ,binaryTree *btree2)
{
  int temp1=0;
  int temp2=0;
  if(btree1==NULL && btree2==NULL)
    return 1;

  if(btree1==NULL || btree2==NULL)
    return 0;
 
  temp1=compareTree(btree1->left,btree2->left); 
  temp2=compareTree(btree1->right,btree2->right); 

  if(btree1->data==btree2->data && temp1 &&temp2)
    return 1;
  else
    return 0;
}
int max(int a, int b)
{
  return (a >= b)? a: b;
}
/*The second parameter is to store the height of tree.
   Initially, we need to pass a pointer to a location with value
   as 0. So, function should be used as follows:
 
   int height = 0;
   struct node *root = SomeFunctionToMakeTree();
   int diameter = diameterOpt(root, &height); */
int diameterOpt(binaryTree *root, int* height)
{
  /* lh --> Height of left subtree
     rh --> Height of right subtree */
  int lh = 0, rh = 0;
  
  /* ldiameter  --> diameter of left subtree
     rdiameter  --> Diameter of right subtree */
  int ldiameter = 0, rdiameter = 0;
  
  if(root == NULL)
  {
    *height = 0;
     return 0; /* diameter is also 0 */
  }
  
  /* Get the heights of left and right subtrees in lh and rh
    And store the returned values in ldiameter and ldiameter */
  ldiameter = diameterOpt(root->left, &lh);
  rdiameter = diameterOpt(root->right, &rh);
  
  /* Height of current node is max of heights of left and
     right subtrees plus 1*/
  *height = max(lh, rh) + 1;
  
  return max(lh + rh + 1, max(ldiameter, rdiameter));
}
void printArray(int arr[], int count)
{
 for(int i=0;i<count;i++)
   printf("%d ",arr[i]);
}
int printPath(binaryTree * btree, int arr[],int count)
{
  if(btree==NULL)
    return 0;
  arr[count++]=btree->data;
  if(btree->left==NULL && btree->right==NULL)
  {
     printArray(arr,count);
     printf("\n");
     return 0;
  }
  printPath(btree->left,arr,count);
  printPath(btree->right,arr,count);
  return 0;
}
int printAllLCA(binaryTree * btree, int arr[],int count,int num)
{
  if(btree==NULL)
    return 0;
  if(btree->left->data==num || btree->right->data==num|| printAllLCA(btree->left,arr,count,num) || printAllLCA(btree->right,arr,count,num))
  {
     printf("%d ",btree->data);
     return 1;
  }
  return 0;
}

int checkSum(binaryTree * btree,int arr[],int count,int sum)
{
  if(btree==NULL)
    return 0;

  sum=sum-btree->data;
  arr[count++]=btree->data;
  if(btree->left==NULL && btree->right==NULL)
  {
     if(sum==0)
     {
       printf("Sum found\n");
       printArray(arr,count);
     }

     return 0;
  }
  checkSum(btree->left,arr,count,sum);
  checkSum(btree->right,arr,count,sum);
}
binaryTree * LCA(binaryTree *root,binaryTree *var1,binaryTree *var2)
{
  if(root==NULL)
    return root;

  if(root==var1||root==var2)
    return root;

  binaryTree *left=LCA(root->left,var1,var2);
  binaryTree *right=LCA(root->right,var1,var2);

  if(left)
    return left;
  else
    return right;
}
/*binaryTree * constructTree()
{
  char arr1[]=("D","B","E","A","F","C");
  char arr2[]=("A","B","D","E","C","F");

  char ch=arr2[0];

  int temp=find(arr1,0,6,ch);

  while(temp>0)
  {
    ch=arr2[i];
    temp=find(arr1,0,6,ch);
  }
}*/
int main()
{
  binaryTree *btree=NULL;
  binaryTree *btree1=NULL;
  queueArray *queue=NULL;
  queueArray *queue1=NULL;

  queue=createQueue();
  queue1=createQueue();
  for(int i=0;i<10;i++)
    btree= addNode(btree,i,queue);

  for(int i=0;i<10;i++)
    btree1= addNode(btree1,i,queue1);
  levelOrder(btree);
  int max;
  max=findMax(btree);
  int height=0;
  printf("\nMax Value %d\n",max);
  printf("\n");
  if(findNode(btree,5))
    printf("\nNode found\n");
  else
    printf("Node not found\n");

  if(findNode(btree,11))
    printf("Node found\n");
  else
    printf("Node not found\n");
  btree=insertNode(btree,10);
  btree1=insertNode(btree1,10);
   levelOrder(btree);
   printf("\n%d\n",findNumNode(btree));
   printf("\n%d\n",levelOrderheight(btree)); 
   levelOrderleafs(btree);
   if(compareTree(btree,btree1))
     printf("Both the trees are equal");
   else
      printf("Both the trees are not equal");
   printf("\nDiameter of the given binary tree is %d\n", diameterOpt(btree,&height));
   int arr[12];
   int count=0;
   int count1=0;
   printPath(btree,arr,count);
   checkSum(btree,arr,count,20);
   binaryTree * temp=LCA(btree,btree->right->left,btree->left->left);
   printf("\n LCA is %d\n",temp->data);
   printAllLCA(btree,arr,count,8);
}
