#ifndef __QUEUEARRAY_H
#define __QUEUEARRAY_H
//这是用于动态数组队列的基本操作，使用时请手动改QUEUESIZE、QUEUEADDON、QueueElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191004于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h>
//动态数组队列最小长度，缺省50 
#define QUEUESIZE 50
//动态数组队列每次申请新元素增量，缺省10 
#define QUEUEADDON 10 
//动态数组队列数据类型，缺省int 
typedef int QueueElemType;
struct Queue{
	QueueElemType *data;
	int rear;
	int front;
	int length;
	int size;
};
//函数内容 
int InitQueue(Queue *&q){
	//初始化动态数组队列q，q的默认长度是QUEUESIZE，可以增删。成功返回0，q空返回1，data空返回2 
	q=(Queue *)malloc(sizeof(Queue));
	if(q==NULL){
		return(1);
	}
	q->data=(QueueElemType *)calloc(QUEUESIZE,sizeof(QueueElemType));
	if(q->data==NULL){
		return(2);
	}
	q->front=0;
	q->rear=0;
	q->length=0;
	q->size=QUEUESIZE;
	return(0);
}
void DestroyQueue(Queue *&q){
	//销毁动态数组队列q 
	free(q->data); 
	free(q);
	q=NULL;
	return;
}
int ClearQueue(Queue *&q){
	//将动态数组队列q置空，成功返回0，data空返回1 
	q->front=-1;
	q->rear=0;
	q->length=0;
	if(q->size>QUEUESIZE){
		q->data=(QueueElemType *)realloc(q->data,QUEUESIZE*sizeof(QueueElemType));
		if(q->data==NULL){
		    return(1);
	    }
		q->size=QUEUESIZE;
	}
	return(0); 
}
int QueueEmpty(Queue *&q){
	//判断动态数组队列q是否为空，是返回1，不是返回0 
	if(q->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int QueueFull(Queue *&q){
	//判断动态数组队列q是否为满，是返回1，不是返回0 
	if(q->length==q->size){
		return(1);
	}
	else{
		return(0);
	}
}
int QueueLength(Queue *&q){
	//返回动态数组队列q长度 
	return(q->length);
}
int GetFront(Queue *&q,QueueElemType &e){
	//获取队首元素并存到e中，成功返回0，失败返回1 
	if(q->length==0){
		return(1);
	}  
	e=q->data[q->front];
	return(0);
}
int Enter(Queue *&q,QueueElemType e){
	//把e插入q。成功返回0，失败返回1  
	int flag;
	if(q->length==q->size){
		q->data=(QueueElemType *)realloc(q->data,(q->size+QUEUEADDON)*sizeof(QueueElemType));
		if(q->data==NULL){
			return(1);
		}
		q->size=q->size+QUEUEADDON;
		if(q->rear==0&&q->front==0){
			q->rear=q->front+q->length;
		}
		else{
			for(flag=q->size-QUEUEADDON-1;flag>=q->front;flag--){
				q->data[flag+QUEUEADDON]=q->data[flag];
			}
			q->front=q->front+QUEUEADDON;
		}
	}
	if(q->rear+1==q->size){
		q->data[q->rear]=e;
		q->rear=0;
		q->length++;
		return(0);
	}
	q->data[q->rear]=e;
	q->rear++;
	q->length++;
	return(0);
}
int Depart(Queue *&q,QueueElemType &e){
	//删除q队首元素并赋值给e。成功返回0，操作不合法返回1，内存不足返回2  
	int flag;
	if(q->length==0){
		return(1);
	}
	if(q->size-q->length>QUEUEADDON&&q->size>QUEUESIZE){
		if(q->front<q->rear){
			for(flag=q->front;flag<q->rear;flag++){
				q->data[flag-q->front]=q->data[flag];
			}
			q->front=0;
			q->rear=q->length;
		}
		else if(q->front>q->rear){
			for(flag=q->front;flag<q->size;flag++){
				q->data[flag-QUEUEADDON]=q->data[flag];
			}
			q->front=q->front-QUEUEADDON;
		}
		q->data=(QueueElemType *)realloc(q->data,(q->size-QUEUEADDON)*sizeof(QueueElemType));
		if(q->data==NULL){
			return(2);
		}
		q->size=q->size-QUEUEADDON;
	}
	if(q->front==q->size-1){
		e=q->data[q->front];
		q->front=0;
		q->length--;
		return(0);
	}
	e=q->data[q->front];
	q->front++;
	q->length--;
	return(0);
}
void TraverseQueue(Queue *&q){
	//遍历q的所有内容执行自定义操作 
	int flag;
	if(q->front<q->rear){
		for(flag=q->front;flag<q->rear;flag++){
			//自定义操作，缺省打印
			printf("%d\n",q->data[flag]);
		}
	}
	else{
		for(flag=q->front;flag<q->size;flag++){
			//自定义操作，缺省打印
			printf("%d\n",q->data[flag]);
		}
		for(flag=0;flag<q->rear;flag++){
			//自定义操作，缺省打印
			printf("%d\n",q->data[flag]);
		}
	}
	return;
}
#endif 
