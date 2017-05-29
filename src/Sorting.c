#include<stdio.h>

void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
void merge(int arr[], int tmp[], int left, int mid, int right)
{
  int low=left;
  int left_end=mid-1;
  int pos=left;
  int size=right-left+1;
  while((left<=left_end) && (mid<=right))
  {
     if(arr[left]<arr[mid])
     {
        tmp[pos++]=arr[left];
        left++;
     }
     else
     {
        tmp[pos++]=arr[mid];
        mid++;
     }
  }

  while(left<=left_end)
  {
      tmp[pos++]=arr[left];
      left++;
  }
  while(mid<=right)
  {
      tmp[pos++]=arr[mid];
      mid++;
  }
  for(int i=0;i<size;i++)
  {
     arr[right]=tmp[right];
     right=right-1;
  }
 // #printArray(tmp,pos-1);
}
void swap( int *array, int left, int right)
{
   int temp=array[left];
   array[left]=array[right];
   array[right]=temp;
}
void mergeSort(int arr[],int tmp[], int left, int right)
{
  int mid;
  if(right>left)
  {
     mid=(right+left)/2;
     mergeSort(arr,tmp,left,mid);    
     mergeSort(arr,tmp,mid+1,right);
     merge(arr,tmp,left,mid+1,right);
  }
}
int Partition(int array[], int left, int right)
{
  int pivot=array[left];
  int low=left+1;
  while(low<=right)
  {
    while(array[low]<=pivot)
     low++;
    while(array[right]>pivot)
     right--;

    if(low<right)
     swap(array,low,right);
  }
  array[left]=array[right];
  array[right]=pivot;
  return right;
}
void quickSort(int array[], int low, int high)
{
  int pivot;
  if(low<high)
  {
    pivot=Partition(array,low,high);
    quickSort(array,low,pivot-1);
    quickSort(array,pivot+1,high);
  }
} 
/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int tmp[6];
    int arr_size = sizeof(arr)/sizeof(arr[0]);
 
    printf("Given array is \n");
    printArray(arr, arr_size);
 
  //  mergeSort(arr,tmp, 0, arr_size-1 );
    quickSort(arr,0,arr_size-1);
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
