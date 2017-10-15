#include<stdio.h>
#include<stdlib.h>

 typedef struct node{
	 int vertexNumber;
	 struct node* next;
 }list;
 
 typedef struct graph{
	 int v;
	 int e;
	 list* array;
 }graph;
   typedef struct queue{
	int capacity;
	int front;
	int rear;
	int numberofelements;
	int *array;
	
}queue;
 int distance[8],weight[8][8];
 int inqueue[8];
 

 void printGraph(graph* g);
  graph* arrayList();


queue* createQueue(int capacity){queue* q=(queue*)malloc(sizeof(queue));
q->capacity=capacity;
q->front=0;
q->rear=0;
q->numberofelements=0;
q->array=(int*)malloc(sizeof(int)*capacity);
return q;}
int size(queue* q){return q->numberofelements;}
int isEmpty(queue* q){return (q->front==q->rear)&&(q->numberofelements!=q->capacity);}
int isFull(queue* q){return size(q)==q->capacity;}

enqueue(queue* q,int data){if(isFull(q)){printf("queue is full");
return ;}
q->array[q->rear]=data;
q->rear=(q->rear+1)%q->capacity;
//q->rear++;
q->numberofelements=q->numberofelements+1;
}
int dequeue(queue *q){
	if(isEmpty(q)){printf("queueu is empty...");
	return ;}
	int data=q->array[q->front];
	q->front=(q->front+1)%q->capacity;
	//q->front++;
	q->numberofelements--;
	return data;
}
//int size(queue* q){return ((q->capacity)-q->front+q->rear+1)%q->capacity;}
int peek(queue* q){
	if(isEmpty(q)) return;
	return q->array[q->front];
}
deleteQueue(queue* q){
	if(q){
		if(q->array) free(q->array);
		free(q->array);
	}
}

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
void bellmanFord(graph* g,int start){  
       int i,new_dis;
	   queue* q=createQueue(200);
	   int v; list* temp;
	   for(i=0;i<g->v;i++){
		   distance[i]=9999;
		   inqueue[i]=0;
	   }
	   enqueue(q,start); inqueue[start]=1;
	   distance[start]=0;
	   while(!isEmpty(q)){
		   v=dequeue(q); inqueue[v]=0;
		   temp= g->array[v].next;
		   while(temp){
			   new_dis=distance[v]+weight[v][temp->vertexNumber];
			   if(distance[temp->vertexNumber]> new_dis){
				   distance[temp->vertexNumber]=new_dis;
				   if(inqueue[temp->vertexNumber]==0){
					   enqueue(q,temp->vertexNumber); inqueue[temp->vertexNumber]=1;
				   }
			   } temp=temp->next;
		   }
	   }

		deleteQueue(q);
	}
int main(){ int i,j;
	graph* g=arrayList();
	//queue* q=createQueue(50);
	//scanf("%d",&n);
	for(i=0;i<g->v;i++){
		for(j=0;j<g->v;j++){scanf("%d",&weight[i][j]);}
	}
	
	printGraph(g);list* temp;
	/*for(i=0;i<g->v;i++) {temp=g->array[i].next;
		while(temp){
			enqueue(q,temp->vertexNumber); temp=temp->next;
			}
			}
 while(!isEmpty(q)){ printf("\n%d",dequeue(q));}*/
	bellmanFord(g,0);
	for(i=0;i<g->v;i++){printf("\n%d is  distance %d ",i,distance[i]);}
	//deleteQueue(q);
	}
	