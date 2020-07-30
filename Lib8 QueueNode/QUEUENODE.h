#ifndef __QUEUENODE_H
#define __QUEUENODE_H
//这是用于单链队列的基本操作，使用时请手动改QueueElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190926于中国科学技术大学）  
#include<stdio.h> 
#include<stdlib.h> 
//单链队列元素数据类型，缺省int  
typedef int QueueElemType;
struct QueueNode{
	QueueElemType data;
	QueueNode *next;
};
struct Queue{
	QueueNode *rear;
	QueueNode *front;
	int length;
	QueueNode *p; 
};
//函数内容 
int InitQueue(Queue *&q){
	//初始化单链表队列q并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	q=(Queue *)malloc(sizeof(Queue));
	if(q==NULL){
		return(1);
	}
	q->p=(QueueNode *)malloc(sizeof(QueueNode)); 
	if(q->p==NULL){
		return(2);
	}
	q->p->next=NULL; 
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	return(0); 
}
void DestroyQueue(Queue *&q){
	//销毁单链表队列q  
	QueueNode *flag,*res;
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
void ClearQueue(Queue *&q){
	//将单链表队列置空  
	QueueNode *flag1,*flag2;
	flag1=q->p->next;
	while(flag1!=NULL){
		flag2=flag1;
		flag1=flag1->next;
		free(flag2);
	}
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	q->p->next=NULL;
	return;
}
int QueueEmpty(Queue *&q){
	//判断单链表队列q是否为空，是返回1，不是返回0 
	if(q->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int QueueLength(Queue *&q){
	//返回单链表队列q长度 
	return(q->length);
} 
int GetFront(Queue *&q,QueueElemType &e){
	//获取队首元素并存到e中，成功返回0，失败返回1 
	if(q->length==0){
		return(1);
	}   
	e=q->front->data;
	return(0);
} 
int Enter(Queue *&q,QueueElemType e){
	//把e插入q。成功返回0，失败返回1  
	QueueNode *j,*a;
	j=(QueueNode *)malloc(sizeof(QueueNode));
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
int Depart(Queue *&q,QueueElemType &e){
	//删除q队首元素并赋值给e。成功返回0，失败返回1  
	QueueNode *j,*a;
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
void TraverseQueue(Queue *&q){
	//遍历l的所有内容执行自定义操作 
	QueueNode *flag;
	for(flag=q->front;flag!=NULL;flag=flag->next){
		//自定义操作，缺省打印
		printf("%d\n",flag->data);
	}
	return;
}
#endif 
