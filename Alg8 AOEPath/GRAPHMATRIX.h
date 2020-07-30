#ifndef __GRAPHMATRIX_H
#define __GRAPHMATRIX_H
//这是用于邻接矩阵图的基本操作，使用时请手动改VexType、ArcType定义，并按需修改DFS、BFS函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191119于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
//图的种类，0无向，1有向，缺省1 
#define GRAPHKIND 1 
//顶点元素最大容量，缺省5 
#define VEXSIZE 9
//图元素数据类型，缺省struct 
struct VexType{
	int id; 
	int data;
	int used;
};
struct ArcType{
	int id;
	int data;
	int used;
};
struct Graph{
	VexType *vex;
	ArcType **arc;
	int vexnum;
	int vexsize;
	int arcnum;
	int kind;
};
//队列元素数据类型，VexType  
typedef VexType GraphQueueElemType;
struct GraphQueueNode{
	GraphQueueElemType data;
	GraphQueueNode *next;
};
struct GraphQueue{
	GraphQueueNode *rear;
	GraphQueueNode *front;
	int length;
	GraphQueueNode *p; 
};
//函数内容 
int InitGraph(Graph *&g){
	//初始化邻接矩阵图。成功返回0，g空返回1，vex空返回2，arc空返回3 
	int flag1,flag2;
	g=(Graph *)malloc(sizeof(Graph));
	if(g==NULL){
		return(1);
	}
	g->vex=(VexType *)malloc(VEXSIZE*sizeof(VexType));
	if(g->vex==NULL){
		return(2);
	}
	for(flag1=0;flag1<VEXSIZE;flag1++){
		g->vex[flag1].id=0;
		g->vex[flag1].data=0;
		g->vex[flag1].used=0;
	}
	g->arc=(ArcType **)malloc(VEXSIZE*sizeof(ArcType *));
	if(g->arc==NULL){
		return(3);
	}
	for(flag1=0;flag1<VEXSIZE;flag1++){
		g->arc[flag1]=(ArcType *)malloc(VEXSIZE*sizeof(ArcType));
		if(g->arc[flag1]==NULL){
			return(3);
		}
	}
	for(flag1=0;flag1<VEXSIZE;flag1++){
		for(flag2=0;flag2<VEXSIZE;flag2++){
			g->arc[flag1][flag2].id=0;
			g->arc[flag1][flag2].data=0;
			g->arc[flag1][flag2].used=0;
		}
	}
	g->vexnum=0;
	g->vexsize=VEXSIZE;
	g->arcnum=0;
	g->kind=GRAPHKIND;
	return(0);
}
void DestroyGraph(Graph *&g){
	//销毁邻接矩阵图g 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		free(g->arc[flag]);
	} 
	free(g->arc);
	free(g->vex);
	free(g);
	g=NULL;
	return;
}
int ClearGraph(Graph *&g){
	//将邻接矩阵图g置空，成功返回0，vex空返回1，arc空返回2 
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		g->vex[flag1].id=0;
		g->vex[flag1].data=0;
		g->vex[flag1].used=0;
	} 
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			g->arc[flag1][flag2].id=0;
			g->arc[flag1][flag2].data=0;
			g->arc[flag1][flag2].used=0;
		}
	}
	g->arcnum=0;
	g->vexnum=0;
	return(0);
}
int VexEmpty(Graph *&g){
	//判断邻接矩阵图g顶点是否为空，是返回1，不是返回0 
	if(g->vexnum==0){
		return(1);
	}
	return(0);
}
int VexFull(Graph *&g){
	//判断邻接矩阵图g顶点是否为满，是返回1，不是返回0 
	if(g->vexnum==g->vexsize){
		return(1);
	}
	return(0);
}
int ArcEmpty(Graph *&g){
	//判断邻接矩阵图g边是否为空，是返回1，不是返回0 
	if(g->arcnum==0){
		return(1);
	} 
	return(0);
}
int ArcFull(Graph *&g){
	//判断邻接矩阵图g边是否为满，是返回1，不是返回0 
	if(g->arcnum==pow(g->vexnum,2)){
		return(1);
	} 
	return(0);
}
int GraphEmpty(Graph *&g){
	//判断邻接矩阵图g是否为空，是返回1，不是返回0 
	if(g->arcnum==0){
		return(1);
	} 
	return(0);
}
int GraphFull(Graph *&g){
	//判断邻接矩阵图g是否为满，是返回1，不是返回0
	if(g->arcnum==pow(g->vexsize,2)){
		return(1);
	} 
	return(0);
}
int LocateVex(Graph *&g,VexType v,int i){
	//返回邻接矩阵图v的顶点位置，i为0是id，1是data，没有返回0，i不合法返回-1 
	int flag;
	if(i!=0&&i!=1){
		return(-1);
	}
	for(flag=0;flag<g->vexsize;flag++){
		if(i==0){
			if(g->vex[flag].id==v.id&&g->vex[flag].used!=0){
				return(flag+1);
			}
		}
		if(i==1){
			if(g->vex[flag].data==v.data&&g->vex[flag].used!=0){
				return(flag+1);
			}
		} 
	}
	return(0);
}
int LocateArc(Graph *&g,ArcType a,int i){
	//返回邻接矩阵图a的顶点位置，i为0是id，1是data，没有返回0，i不合法返回-1 
	int flag1,flag2;
	if(i!=0&&i!=1){
		return(-1);
	}
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(i==0){
				if(g->arc[flag1][flag2].id==a.id&&g->arc[flag1][flag2].used!=0){
					return(flag1*g->vexsize+flag2+1);
				}
			}
			if(i==1){
				if(g->arc[flag1][flag2].data==a.data&&g->arc[flag1][flag2].used!=0){
					return(flag1*g->vexsize+flag2+1);
				}
			} 
		}
	}
	return(0);
}
int VexInDegree(Graph *&g,VexType v,int i){
	//求顶点的入度，i为0是id，1是data，成功返回相应值，顶点不存在返回-1，i不合法返回-2，无向图返回-3 
	int flag1,flag2,l;
	if(i!=0&&i!=1){
		return(-2);
	}
	if(g->kind==0){
		return(-3);
	}
	flag2=0; 
	l=LocateVex(g,v,i);
	if(l==0){
		return(-1);
	} 
	for(flag1=0;flag1<g->vexsize;flag1++){
		if(g->arc[flag1][l-1].used!=0){
			flag2++;
		}
	}
	return(flag2);
}
int VexOutDegree(Graph *&g,VexType v,int i){
	//求顶点的出度，i为0是id，1是data，成功返回相应值，顶点不存在返回-1，i不合法返回-2，无向图返回-3   
	int flag1,flag2,l;
	if(i!=0&&i!=1){
		return(-2);
	}
	if(g->kind==0){
		return(-3);
	}
	flag2=0;
	l=LocateVex(g,v,i);
	if(l==0){
		return(-1);
	} 
	for(flag1=0;flag1<g->vexsize;flag1++){
		if(g->arc[l-1][flag1].used!=0){
			flag2++;
		}
	}
	return(flag2);
}
int VexDegree(Graph *&g,VexType v,int i){
	//求顶点的度，i为0是id，1是data，成功返回相应值，顶点不存在返回-1，i不合法返回-2 
	int flag1,flag2,l;
	if(i!=0&&i!=1){
		return(-2);
	}
	if(LocateVex(g,v,i)<1){
		return(-1);
	}
	flag2=0;
	if(g->kind==0){
		l=LocateVex(g,v,i);
		for(flag1=0;flag1<g->vexsize;flag1++){
			if(g->arc[flag1][l-1].used!=0){
				flag2++;
			}
		}
		return(flag2);
	} 
	if(g->kind==1){
		return(VexInDegree(g,v,i)+VexOutDegree(g,v,i));
	}
}
int InsertVex(Graph *&g,VexType v){
	//对图g加入v顶点，成功返回0,v存在返回1并重新赋值，vex满返回2 
	int flag1,flag2,l;
	l=LocateVex(g,v,0);
	if(l>0){
		g->vex[l-1]=v;
		g->vex[l-1].used=1;
		return(1);
	}
	if(g->vexnum==g->vexsize){
		return(2);
	}
	for(flag1=0;flag1<g->vexsize;flag1++){
		if(g->vex[flag1].used==0){
			break;
		}
	}
	g->vex[flag1]=v;
	g->vex[flag1].used=1;
	g->vexnum++;
	return(0);
}
int DeleteVex(Graph *&g,VexType v){
	//对图g删除v顶点，成功返回0,v不存在返回1 
	int flag1,flag2,l,d;
	l=LocateVex(g,v,0);
	if(l<1){
		return(1);
	}
	d=VexDegree(g,v,0);
	g->vex[l-1].used=0;
	g->vexnum--;
	for(flag1=0;flag1<g->vexsize;flag1++){
		g->arc[flag1][l-1].id=0;
		g->arc[flag1][l-1].data=0;
		g->arc[flag1][l-1].used=0;
		g->arc[l-1][flag1].id=0;
		g->arc[l-1][flag1].data=0;
		g->arc[l-1][flag1].used=0;
	}
	g->arcnum=g->arcnum-d;
	return(0);
}
int InsertArc(Graph *&g,VexType v,VexType w,ArcType a){
	//添加从v指向w的边a，成功返回0，a存在返回1并重新赋值，v或w不存在返回2 
	int l1,l2;
	l1=LocateVex(g,v,0);
	if(l1<1){
		return(2);
	}
	l2=LocateVex(g,w,0);
	if(l2<1){
		return(2);
	}
	if(g->arc[l1-1][l2-1].used!=0){
		g->arc[l1-1][l2-1]=a;
		return(1);
	}
	g->arc[l1-1][l2-1]=a;
	g->arc[l1-1][l2-1].used=1;
	g->arcnum++;
	return(0);
}
int DeleteArc(Graph *&g,VexType v,VexType w,ArcType a){
	//删除从v指向w的边a，成功返回0，a不存在返回1，v或w不存在返回2 
	int l1,l2;
	l1=LocateVex(g,v,0);
	if(l1<1){
		return(2);
	}
	l2=LocateVex(g,w,0);
	if(l2<1){
		return(2);
	}
	if(g->arc[l1-1][l2-1].used==0){
		return(1);
	}
	g->arc[l1-1][l2-1].used=0;
	g->arcnum--;
	return(0);
}
void GraphTraverse(Graph *&g){
	//展示图g的结点和邻接矩阵  
	int flag1,flag2;
	printf("Vex:\n\n");
	for(flag1=0;flag1<g->vexsize;flag1++){
		printf("id:%-5d data:%-5d used:%-5d\n",g->vex[flag1].id,g->vex[flag1].data,g->vex[flag1].used);
	}
	printf("\n\nArc:\n\n");
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			printf("id:%-5d",g->arc[flag1][flag2].id);
		}
		printf("\n");
		for(flag2=0;flag2<g->vexsize;flag2++){
			printf("data:%-5d",g->arc[flag1][flag2].data);
		}
		printf("\n");
		for(flag2=0;flag2<g->vexsize;flag2++){
			printf("used:%-5d",g->arc[flag1][flag2].used);
		}
		printf("\n\n");
	}
	return;
} 
void DFS(Graph *&g,VexType v,int visited[]){
	//深度遍历连通顶点 
	int flag;
	//自定义操作，缺省打印 
	printf("id:%-5d data:%-5d used:%-5d\n",v.id,v.data,v.used);
	visited[LocateVex(g,v,0)-1]=1;
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used!=0&&g->arc[LocateVex(g,v,0)-1][flag].used!=0&&visited[flag]==0){
			DFS(g,g->vex[flag],visited);
		}
	}
}
void VexDFS(Graph *&g,VexType v,int visited[]){
	//深度遍历一般顶点 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used!=0&&visited[flag]==0){
			DFS(g,v,visited);
		}
	} 
}
int DFSTraverse(Graph *&g,VexType v){
	//深度遍历g的所有内容执行自定义操作，成功返回0，失败返回1 
	int visited[g->vexsize],flag;
	if(LocateVex(g,v,0)<1){
		return(1);
	}
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used==0){
			visited[flag]=1;
		}
		else{
			visited[flag]=0;
		}
	}
	VexDFS(g,v,visited);
	return(0);
}
int InitGraphQueue(GraphQueue *&q){
	//初始化单链表队列q并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	q=(GraphQueue *)malloc(sizeof(GraphQueue));
	if(q==NULL){
		return(1);
	}
	q->p=(GraphQueueNode *)malloc(sizeof(GraphQueueNode)); 
	if(q->p==NULL){
		return(2);
	}
	q->p->next=NULL; 
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	return(0); 
}
void DestroyGraphQueue(GraphQueue *&q){
	//销毁单链表队列q  
	GraphQueueNode *flag,*res;
	flag=q->p;
	while(flag!=NULL){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(q);
	q=NULL;
	return;
}
int Enter(GraphQueue *&q,GraphQueueElemType e){
	//把e插入q。成功返回0，失败返回1  
	GraphQueueNode *j,*a;
	j=(GraphQueueNode *)malloc(sizeof(GraphQueueNode));
	if(j==NULL){
		return(1);
	}
	j->data=e;
	j->next=NULL;
	a=q->rear;
	a->next=j;
	q->rear=j;
	if(q->length==0){
		q->front=q->p->next;
	}
	q->length++;
	return(0);
}
int Depart(GraphQueue *&q,GraphQueueElemType &e){
	//删除q队首元素并赋值给e。成功返回0，失败返回1  
	GraphQueueNode *j,*a;
	int flag;
	if(q->length==0){
		return(1);
	}
	j=q->front;
	a=j->next;
	q->p->next=a;
	q->front=a;
	free(j);
	q->length--;
	return(0);
}
int BFS(Graph *&g,VexType v,int visited[]){
	//广度遍历连通顶点 
	int flag,err;
	GraphQueue *q;
	GraphQueueElemType e;
	err=InitGraphQueue(q);
	if(err!=0){
		return(1); 
	}
	err=Enter(q,v);
	if(err!=0){
		return(1); 
	}
	while(q->length!=0){
		//自定义操作，缺省打印 
		printf("id:%-5d data:%-5d used:%-5d\n",v.id,v.data,v.used);
		visited[LocateVex(g,v,0)-1]=1;
		for(flag=0;flag<g->vexsize;flag++){
			if(g->vex[flag].used!=0&&g->arc[LocateVex(g,v,0)-1][flag].used!=0&&visited[flag]==0){
				Enter(q,g->vex[flag]);
			}
		}
		Depart(q,e);
	}
	DestroyGraphQueue(q);
	return(0);
}
int VexBFS(Graph *&g,VexType v,int visited[]){
	//深度遍历一般顶点 
	int flag,err;
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used!=0&&g->arc[LocateVex(g,v,0)-1][flag].used!=0&&visited[flag]==0){
			err=BFS(g,g->vex[flag],visited);
			if(err!=0){
				return(1);
			}
		}
	}
}
int BFSTraverse(Graph *&g,VexType v){
	//广度遍历t的所有内容执行自定义操作，成功返回0，子函数出错返回1，v不合法返回2 
	int err,flag,visited[g->vexsize];
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used==0){
			visited[flag]=1;
		}
		else{
			visited[flag]=0;
		}
	}
	if(LocateVex(g,v,0)<1){
		return(3);
	}
	err=VexBFS(g,v,visited);
	if(err!=0){
		return(1);
	}
	return(0);
}
#endif 
