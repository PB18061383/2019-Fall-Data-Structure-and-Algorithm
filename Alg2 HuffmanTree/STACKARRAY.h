#ifndef __STACKARRAY_H
#define __STACKARRAY_H
//�������ڶ�̬����ջ�Ļ���������ʹ��ʱ���ֶ���STACKSIZE��STACKADDON��StackElemType���壬�������޸�TraverseList������
//���ڸϹ���æ��������Щ��bug���Դ˱�����б�Ǹ�����н����Խ��飬��ͨ��QQ��1345578933��ϵ������껣�20190925���й���ѧ������ѧ�� 
#include<stdio.h>
#include<stdlib.h>
//��̬����ջ��С���� 
#define STACKSIZE 50
//��̬����ջÿ��������Ԫ������
#define STACKADDON 10 
//��̬����ջ�������� 
typedef unsigned char StackElemType;
struct Stack{
	StackElemType *data;
	int base;
	int top;
	int length;
	int size;
};
//�������� 
int InitStack(Stack *&s){
	//��ʼ����̬����ջs��s��Ĭ�ϳ�����STACKSIZE��������ɾ���ɹ�����0��s�շ���1��data�շ���2 
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
	//���ٶ�̬����ջs 
	free(s->data); 
	free(s);
	return;
}
int ClearStack(Stack *&s){
	//����̬����ջs�ÿգ��ɹ�����0��data�շ���1 
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
	//�ж϶�̬����ջs�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0 
	if(s->length=0){
		return(1);
	}
	else{
		return(0);
	}
}
int StackFull(Stack *&s){
	//�ж϶�̬����ջs�Ƿ�Ϊ�����Ƿ���1�����Ƿ���0 
	if(s->length==s->size){
		return(1);
	}
	else{
		return(0);
	}
}
int StackLength(Stack *&s){
	//���ض�̬����ջs���� 
	return(s->length);
}
void GetTop(Stack *&s,StackElemType &e){
	//��ȡջ��Ԫ�ز��浽e�� 
	e=s->data[s->top];
	return;
}
int Push(Stack *&s,StackElemType e){
	//��eѹ��s���ɹ�����0��ʧ�ܷ���1 
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
	//����sջ��Ԫ�ز���ֵ��e���ɹ�����0��i���Ϸ�����1���ڴ治�㷵��2 
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
	//����s����������ִ���Զ������ 
	int flag;
	for(flag=s->base;flag<s->top+1;flag++){
		//�Զ������
	}
	return;
}
#endif 
