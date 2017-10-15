#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int visited[20];
typedef struct queue1{int capacity;
int front;
int rear;
int numberofelement;
int *array;}queue;
queue* createqueue(int capacity){queue* q=(queue*)malloc(sizeof(queue)*capacity);
q->capacity=capacity;
q->front=0;
q->rear=0;
q->numberofelement=0;
q->array=(int*)malloc(sizeof(int)*capacity);
return q;
}
int size(queue* q){return q->numberofelement;}
int isEmpty(queue* q){return q->front==q->rear;}
int isFull(queue* q){return size(q)==q->capacity;}
void enque(queue* q,int ele){if(isFull(q)){
                                            printf("queue is full\n");
                                           return;	} 
										   q->array[q->rear++]=ele;
										   
										   q->numberofelement=q->numberofelement+1;
										   }
int dequeue(queue* q){if(isEmpty(q)){
                     printf("queue is empty\n");
                     return;
					 }
					 int element=q->array[q->front];
					 q->front=q->front+1;
					 q->numberofelement=q->numberofelement-1;
					 return element;
					 }
int peekfront(queue* q){if(isEmpty(q)){
    printf("queue is empty\n");
    return;	}		
	return q->array[q->front];}

void printqueue(queue* q){if(isEmpty(q)) printf("\n empty hai queue..");
	while(!isEmpty(q)){printf("%d",dequeue(q));printf("\n");}}
 typedef struct node{
	 int vertexNumber;
	 struct node* next;
 }list;
 
 typedef struct graph{
	 int v;
	 int e;
	 list* array;
 }graph;
 
 graph* arrayList(){
	 int i,x,y;
	 list* temp;
	 graph* g=(graph*)malloc(sizeof(graph));
	 if(!g){
		 printf("memory error...");
		 return;
	 }
	 scanf("%d %d",&g->v,&g->e);
	 (g->array)=(list*)malloc(sizeof(list)*g->v);
	 for(i=0;i<g->v;i++){
		// g->array[i]=(list*)malloc(sizeof(list));
		 g->array[i].vertexNumber=i;
		 g->array[i].next=NULL;
	 }
	 for(i=0;i<g->e;i++){
		 scanf("%d %d",&x,&y);
		 temp=(list*)malloc(sizeof(list));
		 temp->vertexNumber=y;
		 temp->next=g->array[x].next;
		 g->array[x].next=temp;
		 temp=(list*)malloc(sizeof(list));
		 temp->vertexNumber=x;
		 temp->next=g->array[y].next;
		 g->array[y].next=temp;
	 }
	 return g;
 }
  void printGraph(graph* g)
{
    int i;
    for (i = 0; i < g->v; i++)
    {
        list *temp= g->array[i].next;// i may remain it as *temp=g->array[i]; see what happen than...
        printf("\n Adjacency list of vertex %d\n head ", i);
        while (temp)
        {
            printf("-> %d", temp->vertexNumber);
            temp = temp->next;
        }
        printf("\n");
    }
}
void bfs(graph* g,int u){ int count=0;
	int v;
	list* temp;
	queue* q=createqueue(100);
	enque(q,u);
	while(!isEmpty(q)){
		u=dequeue(q);
		temp=g->array[u].next;
		if(visited[u]==0) printf("\n%d",u);
		visited[u]=1;
		while(temp){
			if(visited[temp->vertexNumber]==0){enque(q,temp->vertexNumber);count++; temp=temp->next;}
			else temp=temp->next;
		}
	}
	//printqueue(q);
	printf("\nnumber of enqueue operations are %d",count);
}
void bfsTraversal(graph* g){
	int i;
	for(i=0;i<g->v;i++){visited[i]=0;}
	bfs(g,0);
	for(i=0;i<g->v;i++){
		if(!visited[i]) bfs(g,i);
	}
}
int main(){
graph* g=arrayList();
printGraph(g);
printf("\n");
bfsTraversal(g);

	}	
	
	
	
	
	
	
	
	
	
	
	
	
















