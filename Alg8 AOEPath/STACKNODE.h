#ifndef __STACKNODE_H
#define __STACKNODE_H
//�������ڵ���ջ�Ļ���������ʹ��ʱ���ֶ���StackElemType���壬�������޸�TraverseList������
//���ڸϹ���æ��������Щ��bug���Դ˱�����б�Ǹ�����н����Խ��飬��ͨ��QQ��1345578933��ϵ������껣�20190926���й���ѧ������ѧ��  
#include<stdio.h> 
#include<stdlib.h> 
//����ջ�������ͣ�ȱʡint  
typedef int StackElemType;
struct StackNode{
	StackElemType data;
	StackNode *next;
};
struct Stack{
	StackNode *base;
	StackNode *top;
	int length;
	StackNode *p; 
};
//�������� 
int InitStack(Stack *&s){
	//��ʼ��������ջs������һ���ս�㡣�ɹ�����0��l�շ���1�����շ���2  
	s=(Stack *)malloc(sizeof(Stack));
	if(s==NULL){
		return(1);
	}
	s->p=(StackNode *)malloc(sizeof(StackNode)); 
	if(s->p==NULL){
		return(2);
	}
	s->p->next=NULL; 
	s->top=s->p;
	s->base=s->p->next;
	s->length=0;
	return(0); 
}
void DestroyStack(Stack *&s){
	//���ٵ�����ջs  
	StackNode *flag,*res;
	flag=s->p;
	while(flag!=NULL){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(s);
	s=NULL;
	return;
}
void ClearStack(Stack *&s){
	//��������ջ�ÿ�  
	StackNode *flag1,*flag2;
	flag1=s->p->next;
	while(flag1!=NULL){
		flag2=flag1;
		flag1=flag1->next;
		free(flag2);
	}
	s->top=s->p;
	s->base=s->p->next;
	s->length=0;
	return;
}
int StackEmpty(Stack *&s){
	//�жϵ�����ջs�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0 
	if(s->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int StackLength(Stack *&s){
	//���ص�����ջs���� 
	return(s->length);
} 
int GetTop(Stack *&s,StackElemType &e){
	//��ȡջ��Ԫ�ز��浽e�У��ɹ�����0��ʧ�ܷ���1 
	if(s->length==0){
		return(1);
	} 
	e=s->top->data;
	return(0);
} 
int Push(Stack *&s,StackElemType e){
	//��eѹ��s���ɹ�����0��ʧ�ܷ���1  
	StackNode *j,*a;
	j=(StackNode *)malloc(sizeof(StackNode));
	if(j==NULL){
		return(1);
	}
	j->data=e;
	j->next=NULL;
	a=s->top;
	a->next=j;
	s->top=j;
	if(s->length==0){
		s->base=s->p->next;
	}
	s->length++;
	return(0);
}
int Pop(Stack *&s,StackElemType &e){
	//����sջ��Ԫ�ز���ֵ��e���ɹ�����0��ʧ�ܷ���1  
	StackNode *flag,*j,*a;
	if(s->length==0){
		return(1);
	}
	if(s->length==1){
		e=s->top->data;
		free(s->p->next);
		s->p->next=NULL;
		s->top=s->p;
		s->base=s->p->next;
		s->length=0;
		return(0);
	}
	for(flag=s->base;flag->next!=s->top;flag=flag->next){
	}
	e=s->top->data;
	a=flag;
	j=flag->next;
	a->next=NULL;
	s->top=a;
	free(j);
	s->length--;
	if(s->length==0){
		s->base=NULL;
	}
	return(0);
}
void TraverseStack(Stack *&s){
	//����s����������ִ���Զ������ 
	StackNode *flag;
	for(flag=s->base;flag!=s->top->next;flag=flag->next){
		//�Զ��������ȱʡ��ӡ
		printf("%d\n",flag->data+1); 
	}
	return;
}
#endif 
