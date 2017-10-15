#include<stdio.h>
#include<stdlib.h>
typedef struct node1{
	int vertex;
	int data;
}node;
typedef struct heap{
	node* array;
	int count;
	int capacity;
	
}heap;
 typedef struct node{
	 int vertexNumber;
	 struct node* next;
 }list;
 
 typedef struct graph{
	 int v;
	 int e;
	 list* array;
 }graph;
 int distance[8],weight[8][8];
int insert(heap* h,int vertex,int data);
heap* createHeap(int capacity);
void proclateUp(heap* h,int i);
int leftChild(heap* h,int i);
int rightChild(heap* h,int i);
int parent(heap* h,int i);
int deleMin(heap* h);
void upDateHeap(heap* h,int vertex,int data);
int isEmpty(heap *h);
void proclateUpward(heap* h,int i);
 void printGraph(graph* g);
  graph* arrayList();

heap* createHeap(int capacity){
	heap* h=(heap*)malloc(sizeof(heap));
	h->count=0;
	h->capacity=capacity;
	h->array=(node*)malloc(sizeof(node)*h->capacity);
	return h;
}
int insert(heap* h,int vertex,int data){
	int i;h->count++;
	i=h->count-1;
	while(i>0&&data< h->array[(i-1)/2].data){
		h->array[i]=h->array[(i-1)/2];
		i=(i-1)/2;
	}
	h->array[i].data=data;
	h->array[i].vertex=vertex;
	proclateUpward(h,i);
}
void proclateUp(heap* h,int i){
	int l,r,min;
	node temp;
	l=leftChild(h,i);
	r=rightChild(h,i);
	if(l!= -1&& h->array[l].data< h->array[i].data)
		min = l;
	else min= i;
	if(r!= -1 && h->array[r].data < h->array[min].data)
		min = r;
	 if(min ==i) return;
	 if(min!= i){
		 temp=h->array[i];
		 h->array[i]=h->array[min];
		 h->array[min]=temp;
		 
	 }
	 proclateUp(h,min);// check here 
	 
}
int leftChild(heap* h,int i){
	int left=2*i+1;
	if(left>= h->count) return -1;
	return left;
}
int rightChild(heap* h,int i){
	int right= 2*i+2;
	if(right >=h->count) return -1;
	return right;
}
int parent(heap* h,int i){
	if(i<=0|| i>= h->count) return -1;
	return (i-1)/2;
	
}
void upDateHeap(heap* h,int vertex,int data){
	int i=0;
	while(i< h->count){
	if(h->array[i].vertex== vertex) {
		h->array[i].vertex= vertex;
		h->array[i].data= data; //proclateUp(h,i);
		proclateUpward(h,i);
		proclateUp(h,i);
		}
	i++;}
	
}
int deleMin(heap* h){
	int vertex;
	if(h->count== 0) return -1;
	
	//int dara=h->array[0].data;
	vertex=h->array[0].vertex;
	h->array[0]=h->array[h->count-1];
	h->count--;
	proclateUp(h,0);
	return vertex;
	
}
int isEmpty(heap *h){
	if(h->count==0) return 1;
	else return 0;
}
 void destroyHeap(heap* h){
	 if(h==NULL)
		 return;
	 free(h->array);
	 free(h);
	 h=NULL;
 }
 void proclateUpward(heap* h,int i){
	 int p=parent(h,i); node temp;
	 if(p== -1) return ;
	 if(p!= -1 && (h->array[p].data>h->array[i].data)){
		 temp=h->array[i];
		 h->array[i]=h->array[p];
		 h->array[p]=temp;
		 proclateUpward(h,p);
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
void dijkristraAlgo(graph* g,heap* h,int s){
	//heap* h=createHeap(100);
	int v,w,i;list* temp; int newdistance;
	insert(h,s,0);
	for(i=0;i<g->v;i++) distance[i]=-1;
	distance[s]=0;
	while(!isEmpty(h)){
		v=deleMin(h);
		temp=g->array[v].next;
		while(temp){
			newdistance=distance[v]+weight[v][temp->vertexNumber];
			if(distance[temp->vertexNumber]== -1){
				distance[temp->vertexNumber]=newdistance;
				//upDateHeap(h,temp->vertexNumber,newdistance);
				insert(h,temp->vertexNumber,newdistance);
			}
			if(distance[temp->vertexNumber]> newdistance){
				distance[temp->vertexNumber]= newdistance;
				//upDateHeap(h,temp->vertexNumber,newdistance);
				insert(h,temp->vertexNumber,newdistance);
			}
			temp=temp->next;
		}
	}
	
}
int main (){int i=0,j=0;list* temp;
	heap * h=createHeap(150);
	/*insert(h,0,5);
	insert(h,1,8);
	insert(h,2,14);
	insert(h,3,21);
	insert(h,4,27);
	insert(h,5,29);
	insert(h,6,12);               
	insert(h,7,7);
	insert(h,8,13);
	insert(h,9,11);
	insert(h,10,49);
	
	upDateHeap(h,10,2);
	upDateHeap(h,9,1);
	upDateHeap(h,10,0);*/
	graph *g=arrayList();
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){scanf("%d",&weight[i][j]);}
	}
	/*for(i=0;i<g->v;i++){temp=g->array[i].next;
	while(temp){
		insert(h,temp->vertexNumber,weight[i][temp->vertexNumber]);
		temp=temp->next;
	}}*/
	printGraph(g);dijkristraAlgo(g,h,0);
	/*while(!isEmpty(h)){
		printf("%d\n",deleMin(h));
	}*/
	for(i=0;i<g->v;i++) printf("\n%d  %d",i,distance[i]);
	destroyHeap(h);
	
	
}
















