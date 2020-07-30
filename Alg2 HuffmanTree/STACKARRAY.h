#ifndef __STACKARRAY_H
#define __STACKARRAY_H
//这是用于动态数组栈的基本操作，使用时请手动改STACKSIZE、STACKADDON、StackElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190925于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h>
//动态数组栈最小长度 
#define STACKSIZE 50
//动态数组栈每次申请新元素增量
#define STACKADDON 10 
//动态数组栈数据类型 
typedef unsigned char StackElemType;
struct Stack{
	StackElemType *data;
	int base;
	int top;
	int length;
	int size;
};
//函数内容 
int InitStack(Stack *&s){
	//初始化动态数组栈s，s的默认长度是STACKSIZE，可以增删。成功返回0，s空返回1，data空返回2 
	s=(Stack *)malloc(sizeof(Stack));
	if(s==NULL){
		return(1);
	}
	s->data=(StackElemType *)calloc(STACKSIZE,sizeof(StackElemType));
	if(s->data==NULL){
		return(2);
	}
	s->top=-1;
	s->base=0;
	s->length=0;
	s->size=STACKSIZE;
	return(0);
}
void DestroyStack(Stack *&s){
	//销毁动态数组栈s 
	free(s->data); 
	free(s);
	return;
}
int ClearStack(Stack *&s){
	//将动态数组栈s置空，成功返回0，data空返回1 
	s->top=-1;
	s->base=0;
	s->length=0;
	if(s->size>STACKSIZE){
		s->data=(StackElemType *)realloc(s->data,STACKSIZE*sizeof(StackElemType));
		if(s->data==NULL){
		    return(1);
	    }
		s->size=STACKSIZE;
	}
	return(0); 
}
int StackEmpty(Stack *&s){
	//判断动态数组栈s是否为空，是返回1，不是返回0 
	if(s->length=0){
		return(1);
	}
	else{
		return(0);
	}
}
int StackFull(Stack *&s){
	//判断动态数组栈s是否为满，是返回1，不是返回0 
	if(s->length==s->size){
		return(1);
	}
	else{
		return(0);
	}
}
int StackLength(Stack *&s){
	//返回动态数组栈s长度 
	return(s->length);
}
void GetTop(Stack *&s,StackElemType &e){
	//获取栈顶元素并存到e中 
	e=s->data[s->top];
	return;
}
int Push(Stack *&s,StackElemType e){
	//把e压入s。成功返回0，失败返回1 
	if(s->length==s->size){
		s->data=(StackElemType *)realloc(s->data,(s->size+STACKADDON)*sizeof(StackElemType));
		if(s->data==NULL){
			return(1);
		}
		s->size=s->size+STACKADDON;
	}
	s->data[s->top+1]=e;
	s->top++;
	s->length++;
	return(0);
}
int Pop(Stack *&s,StackElemType &e){
	//弹出s栈顶元素并赋值给e。成功返回0，i不合法返回1，内存不足返回2 
	e=s->data[s->top];
	s->top--;
	if(s->size-s->top>STACKADDON+1&&s->size>STACKSIZE){
		s->data=(StackElemType *)realloc(s->data,(s->size-STACKADDON)*sizeof(StackElemType));
		if(s->data==NULL){
			return(2);
		}
		s->size=s->size-STACKADDON;
	}
	s->length--;
	return(0);
}
void TraverseStack(Stack *&s){
	//遍历s的所有内容执行自定义操作 
	int flag;
	for(flag=s->base;flag<s->top+1;flag++){
		//自定义操作
	}
	return;
}
#endif 
