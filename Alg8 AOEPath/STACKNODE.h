#ifndef __STACKNODE_H
#define __STACKNODE_H
//这是用于单链栈的基本操作，使用时请手动改StackElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190926于中国科学技术大学）  
#include<stdio.h> 
#include<stdlib.h> 
//单链栈数据类型，缺省int  
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
//函数内容 
int InitStack(Stack *&s){
	//初始化单链表栈s并创造一个空结点。成功返回0，l空返回1，结点空返回2  
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
	//销毁单链表栈s  
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
	//将单链表栈置空  
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
	//判断单链表栈s是否为空，是返回1，不是返回0 
	if(s->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int StackLength(Stack *&s){
	//返回单链表栈s长度 
	return(s->length);
} 
int GetTop(Stack *&s,StackElemType &e){
	//获取栈顶元素并存到e中，成功返回0，失败返回1 
	if(s->length==0){
		return(1);
	} 
	e=s->top->data;
	return(0);
} 
int Push(Stack *&s,StackElemType e){
	//把e压入s。成功返回0，失败返回1  
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
	//弹出s栈顶元素并赋值给e。成功返回0，失败返回1  
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
	//遍历s的所有内容执行自定义操作 
	StackNode *flag;
	for(flag=s->base;flag!=s->top->next;flag=flag->next){
		//自定义操作，缺省打印
		printf("%d\n",flag->data+1); 
	}
	return;
}
#endif 
