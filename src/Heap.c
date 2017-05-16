#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Heap
{
  int *array;
  int count;
  int capacity;
  int heaptype;
}Heap;

Heap * createHeap(int cap,int heaptype)
{
  Heap *heap=(Heap*)malloc(sizeof(Heap));

  if(heap==NULL)
  {
     printf("No memory allocated");
     exit(1);
  }
  heap->array=(int*)malloc(sizeof(int) * cap);
  if(heap->array==NULL)
  {
    printf("No memory allocated");
     exit(1);
  }
  heap->capacity=cap;
  heap->count=0;
  heap->heaptype=1;
  return heap;
}
Heap * reHeap(Heap *heap)
{
  int *oldarr=heap->array;
  int count=heap->capacity;
  free(heap->array);
  heap->array=(int*)malloc(sizeof(int) * 2 * count);
  for(int i=0;i<count;i++)
  {
    heap->array[i]=oldarr[i];
  }
  heap->capacity=heap->capacity*2;
  return heap;
}
Heap * insertHeap(Heap *heap, int data)
{
  if(heap->count==heap->capacity)
    heap=reHeap(heap);

  heap->count=heap->count+1;
  int i=heap->count-1;
  while(i>=0 && data>heap->array[(i-1)/2])
  {
    heap->array[i]=heap->array[(i-1)/2];
    i=(i-1)/2;
  }
  heap->array[i]=data;
  return heap;
}


int Parent(Heap *heap, int i)
{
  if(i<=0 || i>heap->count)
    return -1;

  return(i-1)/2;
}

int leftChild(Heap *heap, int i)
{
  int left=2*i+1;
  if(left>=heap->count)
    return -1;
  else
    return left;
}

int rightChild(Heap *heap, int i)
{
  int right=2*i+2;
  if(right>=heap->count)
    return -1;
  else
    return right;
}
void print(int *arr, int n)
{
  for(int i=0;i<n;i++)
    printf("%d ",arr[i]);
  printf("\n");
}
Heap * perlocateHeap(Heap *heap, int i)
{
  int left=leftChild(heap,i);
  int right=rightChild(heap, i);
  int max=i;
  int data=heap->array[i];
  if(left!=-1 && heap->array[left]>data)
    max=left;

  if(right!=-1 && heap->array[right]>heap->array[max])
    max=right;
  
  if(i!=max)
  {
    heap->array[i]=heap->array[max];
    heap->array[max]=data;
    print(heap->array,7);

    heap=perlocateHeap(heap,max);
  }

  return heap;
}

Heap * deleteHeap(Heap *heap)
{
  if(heap->count==0)
    return NULL;

  heap->array[0]=heap->array[heap->count-1];
  heap->count=heap->count-1;
  perlocateHeap(heap,0);
  return heap;
}

Heap * buildHeap(int *arr, int n)
{
  Heap *heap=createHeap(10,0);
  heap->count=n;
  int i;
  for(i=0;i<n;i++)
    heap->array[i]=arr[i];
  print(heap->array,n);
  for(i=(heap->count-1)/2;i>=0;i--)
    heap=perlocateHeap(heap,i);

  return heap;
}

Heap * heapSort(Heap *heap, int n)
{
   int data;
   for(int i=heap->count-1;i>=0;i--)
   {
      data=heap->array[i];
      heap->array[i]=heap->array[0];
      heap->array[0]=data;
      heap->count=heap->count-1;
      heap=perlocateHeap(heap,0);
   }
   heap->count=n;
   return heap;
}

int searchHeap(Heap *heap,int i, int data)
{
  if(heap->count==0)
  {
     printf("No elements in heap");
     return 0;
  }
  if(data==heap->array[i])
    return data;
  int left=leftChild(heap,i);
  if(left==-1)
      return 0;
  int right=rightChild(heap,i);
  if(right==-1)
      return 0;
  int var=searchHeap(heap,left,data);
  if(!var)
    return searchHeap(heap,right,data);
  return var;
}
Heap * deleteElem(Heap *heap, int i)
{
  int key=heap->array[i];

  heap->array[i]=heap->array[heap->count-1];
  heap->array[heap->count-1]=key;
  heap->count--;
  perlocateHeap(heap,i);

}

int main()
{
  int arr[]={9,4,6,1,3,8,7};
  Heap *heap=buildHeap(arr,7);

  print(heap->array,7);

  //heap=heapSort(heap,7);

  printf("\n");

  print(heap->array,7);


  int data=searchHeap(heap,0,7);
  
  printf("\nElement Found %d\n",data);

  heap=insertHeap(heap,2);

  print(heap->array,8); 

//  heap=heapSort(heap,8);

  printf("\n");

  print(heap->array,8);

  heap=deleteElem(heap, 4);

  printf("\n");
  print(heap->array,7);

   heap=heapSort(heap,7);

  printf("\n");

  print(heap->array,7);

}


 
