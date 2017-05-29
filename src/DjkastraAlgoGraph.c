#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT_MAX 100
typedef struct adjacencyListNode
{
  int data;
  int weight;
  struct adjacencyListNode * next;
}adjacencyListNode;

typedef struct adjacencyList
{
  adjacencyListNode *head;
}adjacencyList;

typedef struct Graph
{
int V;
int E;
adjacencyList * array;
}Graph;

Graph * createGraph(int vertices, int edge)
{
  Graph *graph=(Graph*)malloc(sizeof(Graph));

  if(graph==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  graph->V=vertices;
  graph->E=edge;

  graph->array=(adjacencyList *)malloc(sizeof(adjacencyList) * graph->V);

  if(graph->array==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  for(int i=0;i<vertices;i++)
    graph->array[i].head=NULL;

  return graph;

}
adjacencyListNode * createNode(int data, int weight)
{
  adjacencyListNode *temp=(adjacencyListNode*)malloc(sizeof(adjacencyListNode));

  if(temp==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  temp->data=data;
  temp->weight=weight;
  temp->next=NULL;
  return temp;
}
typedef struct minHeapNode
{
  int v;
  int dist;
}minHeapNode;
minHeapNode * createHeapNode(int v, int dist)
{
  minHeapNode * temp=(minHeapNode*)malloc(sizeof(minHeapNode));
  temp->v=v;
  temp->dist=dist;
  return temp;
}
typedef struct Heap
{
  int capacity;
  int size;
  int *pos;
  minHeapNode ** array;
}Heap;

Heap * createHeap(int cap)
{
  Heap *heap=(Heap*)malloc(sizeof(Heap));

  if(heap==NULL)
  {
     printf("No memory allocated");
     exit(1);
  }
  heap->pos=(int*)malloc(sizeof(int)*cap);
  heap->array=(minHeapNode**)malloc(sizeof(minHeapNode*) * cap);
  if(heap->array==NULL)
  {
    printf("No memory allocated");
     exit(1);
  }
  heap->capacity=cap;
  heap->size=0;
  return heap;
}
Heap * reHeap(Heap *heap)
{
  minHeapNode **oldarr=heap->array;
  int size=heap->capacity;
  free(heap->array);
  heap->array=(minHeapNode**)malloc(sizeof(minHeapNode*) * 2 * size);
  for(int i=0;i<size;i++)
  {
    heap->array[i]=oldarr[i];
  }
  heap->capacity=heap->capacity*2;
  return heap;
}
int Parent(Heap *heap, int i)
{
  if(i<=0 || i>heap->size)
    return -1;

  return(i-1)/2;
}

int leftChild(Heap *heap, int i)
{
  int left=2*i+1;
  if(left>=heap->size)
    return -1;
  else
    return left;
}

int rightChild(Heap *heap, int i)
{
  int right=2*i+2;
  if(right>=heap->size)
    return -1;
  else
    return right;
}
Heap * perlocateHeap(Heap *heap, int i)
{
  int left=leftChild(heap,i);
  int right=rightChild(heap, i);
  int min=i;
  int data=heap->array[i]->dist;
  if(left!=-1 && heap->array[left]->dist<data)
    min=left;

  if(right!=-1 && heap->array[right]->dist<heap->array[min]->dist)
    min=right;

  if(i!=min)
  {
    minHeapNode *temp=heap->array[i];
    minHeapNode *temp1=heap->array[min];
    heap->pos[temp->v]=min;
    heap->pos[temp1->v]=i;
    heap->array[i]=heap->array[min];
    heap->array[min]=temp;

    heap=perlocateHeap(heap,min);
  }

  return heap;
}
// Standard function to extract minimum node from heap
minHeapNode* extractMin(Heap* minHeap)
{
    if (minHeap->size==0)
        return NULL;
 
    // Store the root node
    minHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    minHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    perlocateHeap(minHeap, 0);
 
    return root;
}
void swapMinHeapNode(minHeapNode** a, minHeapNode** b)
{
    minHeapNode* t = *a;
    *a = *b;
    *b = t;
} 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(Heap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
Heap * deleteHeap(Heap *heap)
{
  if(heap->size==0)
    return NULL;

  heap->array[0]=heap->array[heap->size-1];
  heap->size=heap->size-1;
  perlocateHeap(heap,0);
  return heap;
}

int isInMinHeap(Heap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra( Graph* graph, int src)
{
    int V = graph->V;// Get the number of vertices in graph
    int dist[V];      // dist values used to pick minimum weight edge in cut
 
    // minHeap represents set E
    Heap* minHeap = createHeap(V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = createHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = createHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (minHeap->size!=0)
    {
        // Extract the vertex with minimum distance value
        minHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        adjacencyListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->data;
 
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr(dist, V);
}
void  addEdge(Graph *graph, int src, int dest,int weight)
{
  adjacencyListNode *temp=createNode(dest,weight);

  temp->next=graph->array[src].head;
  graph->array[src].head=temp;
  temp=createNode(src,weight);
  temp->next=graph->array[dest].head;
  graph->array[dest].head=temp;
} 
 
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 9;
    Graph* graph = createGraph(V,1);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
 
    dijkstra(graph, 0);
 
    return 0;
}
