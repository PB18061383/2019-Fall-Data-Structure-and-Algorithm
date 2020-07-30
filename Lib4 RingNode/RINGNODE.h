#ifndef __RINGNODE_H
#define __RINGNODE_H
//这是用于单链环表的基本操作，使用时请手动改ListElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190925于中国科学技术大学）  
#include<stdio.h> 
#include<stdlib.h> 
//单链环表数据类型，缺省int  
typedef int ListElemType;
struct ListNode{
	ListElemType data;
	ListNode *next;
};
struct List{
	int length;
	ListNode *p; 
};
//函数内容 
int InitList(List *&l){
	//初始化单链环表l并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	l=(List *)malloc(sizeof(List));
	if(l==NULL){
		return(1);
	}
	l->p=(ListNode *)malloc(sizeof(ListNode)); 
	if(l->p==NULL){
		return(2);
	}
	l->p->next=l->p; 
	l->length=0;
	return(0); 
}
void DestroyList(List *&l){
	//先销毁结点，然后销毁l，实现销毁链表 
	ListNode *flag,*res;
	flag=l->p->next;
	while(flag!=l->p){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(flag);
	free(l);
	l=NULL;
	return;
}
void ClearList(List *&l){
	//将单链环表置空  
	ListNode *flag,*res;
	flag=l->p->next;
	while(flag!=l->p){
		res=flag;
		flag=flag->next;
		free(res);
	}
	l->p->next=NULL;
	return;
}
int ListEmpty(List *&l){
	//判断单链环表l是否为空，是返回1，不是返回0 
	if(l->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int ListLength(List *&l){
	//返回单链环表l长度 
	return(l->length);
} 
int GetElem(List *&l,int i,ListElemType &e){
	//返回单链环表l第i个元素,成功将值赋值给e所在地址并返回0，失败返回1 
	int flag1;
	ListNode *flag2;
	if(i<1||i>l->length){
		return(1); 
	}
	for(flag1=0,flag2=l->p->next;flag1<i-1;flag1++,flag2=flag2->next){
	}
	e=flag2->data;
	return(0);
} 
int LocateItem(List *&l,ListElemType e){
	//返回单链环表第一个值为e的元素位置，没有返回0 
	int flag1;
	ListNode *flag2;
	for(flag1=0,flag2=l->p->next;flag1<l->length;flag1++,flag2=flag2->next){
		if(flag2->data==e){
			return(flag1+1);
		}
	}
	return(0);
}
int PriorElem(List *&l,ListElemType e,ListElemType &pe){
	//返回单链环表第一个值为e的元素前驱，成功将赋值给pe所在地址并返回0，没有返回1 
	ListNode *flag;
	for(flag=l->p->next;flag->next!=l->p;flag=flag->next){
		if(flag->next->data==e){
			pe=flag->data;
			return(0);
		}
	}
	return(1);
}
int NextElem(List *&l,ListElemType e,ListElemType &ne){
	//返回单链环表第一个值为e的元素后继，成功将赋值给ne所在地址并返回0，没有返回1 
	ListNode *flag;
	for(flag=l->p->next;flag->next->next!=l->p&&flag->next!=l->p;flag=flag->next){
		if(flag->data==e){
			ne=flag->next->data;
			return(0);
		}
	}
	return(1);
}
int ListInsert(List *&l,int i,ListElemType e){
	//在l的i位置前插入e，若i为0，则在后方插入。成功返回0,i不合法返回1，j空返回2 
	int flag1;
	ListNode *flag2,*j,*a,*b;
	if(i<0||i>l->length){
		return(1);
	} 
	j=(ListNode *)malloc(sizeof(ListNode));
	if(j==NULL){
		return(2);
	}
	j->data=e;
	j->next=NULL;
	if(i==0){
		for(flag2=l->p;flag2->next!=l->p;flag2=flag2->next){
		}
		flag2->next=j;
		j->next=l->p;
		l->length++;
		return(0);
	}
	for(flag1=0,flag2=l->p;flag1<i-1;flag1++,flag2=flag2->next){
	}
	a=flag2;
	b=flag2->next;
	a->next=j;
	j->next=b;
	l->length++;
	return(0);
}
int ListDelete(List *&l,int i,ListElemType &e){
	//删除l的i位置的元素并赋值给e，成功返回0，失败返回1 
	int flag1;
	ListNode *flag2,*j,*a,*b;
	if(i<1||i>l->length){
		return(1);
	}
	for(flag1=0,flag2=l->p;flag1<i-1;flag1++,flag2=flag2->next){
	}
	a=flag2;
	j=flag2->next;
	b=flag2->next->next;
	a->next=b;
	e=j->data;
	free(j);
	l->length--; 
	return(0);
}
void TraverseList(List *&l){
	//遍历l的所有内容执行自定义操作 
	ListNode *flag;
	for(flag=l->p->next;flag!=l->p;flag=flag->next){
		//自定义操作，缺省打印
		printf("%d\n",flag->data); 
	}
	return;
}
#endif 
