#ifndef __DOUBLENODE_H
#define __DOUBLENODE_H
//这是用于双链线性表的基本操作，使用时请手动改ListElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190925于中国科学技术大学）  
#include<stdio.h> 
#include<stdlib.h> 
//双链线性表数据类型，缺省int  
typedef int ListElemType;
struct ListNode{
	ListElemType data;
	ListNode *prior;
	ListNode *next;
};
struct List{
	int length;
	ListNode *p1; 
	ListNode *p2;
};
//函数内容 
int InitList(List *&l){
	//初始化双链表l并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	l=(List *)malloc(sizeof(List));
	if(l==NULL){
		return(1);
	}
	l->p1=(ListNode *)malloc(sizeof(ListNode));
	if(l->p1==NULL){
		return(2);
	}
	l->p2=(ListNode *)malloc(sizeof(ListNode));
	if(l->p2==NULL){
		return(2);
	}
	l->p1->next=l->p2;
	l->p2->prior=l->p1;
	l->length=0;
	return(0); 
}
int DestroyList(List *&l,int j){
	//先销毁结点，然后销毁l，实现销毁链表，j为0从左，为1从右，成功返回0，j不合法返回1 
	ListNode *flag,*res;
	if(j==0){
		flag=l->p1;
		while(flag->next!=l->p2){
			res=flag;
			flag=flag->next;
			free(res);
		}
		free(l->p2);
		free(l);
		l=NULL;
		return(0);
	}
	else if(j==1){
		flag=l->p2;
		while(flag->prior!=l->p1){
			res=flag;
			flag=flag->prior;
			free(res);
		}
		free(l->p1);
		free(l);
		l=NULL;
		return(0);
	}
	else{
		return(1);
	}
}
int ClearList(List *&l,int j){
	//将双链表置空，j为0从左，为1从右，成功返回0，j不合法返回1  
	ListNode *flag,*res;
	if(j==0){
		flag=l->p1->next;
		while(flag->next!=l->p2){
			res=flag;
			flag=flag->next;
			free(res);
		}
		l->p1->next=l->p2;
		l->p2->prior=l->p1;
		l->length=0;
		return(0);
	}
	else if(j==1){
		flag=l->p2->prior;
		while(flag->prior!=l->p1){
			res=flag;
			flag=flag->prior;
			free(res);
		}
		l->p1->next=l->p2;
		l->p2->prior=l->p1;
		l->length=0;
		return(0);
	}
	else{
		return(1);
	}
}
int ListEmpty(List *&l){
	//判断双链表l是否为空，是返回1，不是返回0 
	if(l->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int ListLength(List *&l){
	//返回双链表l长度 
	return(l->length);
} 
int GetElem(List *&l,int i,ListElemType &e,int j){
	//返回双链表l第i个元素，j为0从左，为1从右，成功将值赋值给e所在地址并返回0，无元素返回1，l不合法返回2 
	int flag1;
	ListNode *flag2;
	if(i<1||i>l->length){
		return(1); 
	}
	if(j==0){
		for(flag1=0,flag2=l->p1->next;flag1<i-1;flag1++,flag2=flag2->next){
		}
		e=flag2->data;
	} 
	else if(j==1){
		for(flag1=0,flag2=l->p2->prior;flag1<i-1;flag1++,flag2=flag2->prior){
		}
		e=flag2->data;
	} 
	else{
		return(2);
	}
	return(0);
} 
int LocateItem(List *&l,ListElemType e,int j){
	//返回双链表第一个值为e的元素位置，j为0从左，为1从右，没有返回0，l不合法返回-1 
	int flag1;
	ListNode *flag2;
	if(j==0){
		for(flag1=0,flag2=l->p1->next;flag1<l->length;flag1++,flag2=flag2->next){
			if(flag2->data==e){
				return(flag1+1);
			}
		}
	}
	else if(j==1){
		for(flag1=0,flag2=l->p2->prior;flag1<l->length;flag1++,flag2=flag2->prior){
			if(flag2->data==e){
				return(flag1+1);
			}
		}
	}
	else{
		return(-1);
	}
	return(0);
}
int PriorElem(List *&l,ListElemType e,ListElemType &pe,int j){
	//返回双链表第一个值为e的元素前驱，j为0从左，为1从右，成功将赋值给pe所在地址并返回0，没有返回1，j不合法返回2 
	ListNode *flag;
	if(j==0){
		for(flag=l->p1->next;flag->next!=l->p2;flag=flag->next){
			if(flag->data==e&&flag->prior!=l->p1){
				pe=flag->prior->data;
				return(0);
			}
		}
	}
	else if(j==1){
		for(flag=l->p2->prior;flag->prior!=l->p1;flag=flag->prior){
			if(flag->data==e){
				pe=flag->prior->data;
				return(0);
			}
		}
	}
	else{
		return(2);
	} 
	return(1);
}
int NextElem(List *&l,ListElemType e,ListElemType &ne,int j){
	//返回双链表第一个值为e的元素后继，j为0从左，为1从右，成功将赋值给pe所在地址并返回0，没有返回1，j不合法返回2 
	ListNode *flag;
	if(j==0){	
		for(flag=l->p1->next;flag->next!=l->p2;flag=flag->next){
			if(flag->data==e){
				ne=flag->next->data;
				return(0);
			}
		}
	}
	else if(j==1){
		for(flag=l->p2->prior;flag->prior!=l->p1;flag=flag->prior){
			if(flag->data==e&&flag->next!=l->p2){
				ne=flag->next->data;
				return(0);
			}
		}
	}
	return(1);
}
int ListInsert(List *&l,int i,ListElemType e,int j){
	//在l的i位置先者插入e，若i为0，则在远端插入。j为0从左，为1从右，成功返回0,i不合法返回1，m空返回2，j不合法返回3 
	int flag1;
	ListNode *flag2,*m,*a,*b;
	if(i<0||i>l->length){
		return(1);
	} 
	m=(ListNode *)malloc(sizeof(ListNode));
	if(m==NULL){
		return(2);
	}
	m->data=e;
	m->next=NULL;
	m->prior=NULL;
	if(j==0){
		if(i==0){
			a=l->p2->prior;
			b=l->p2;
			a->next=m;
			m->prior=a;
			m->next=b;
			b->prior=m;
			l->length++;
			return(0);
		}
		for(flag1=0,flag2=l->p1;flag1<i-1;flag1++,flag2=flag2->next){
		}
		a=flag2;
		b=flag2->next;
		a->next=m;
		m->next=b;
		m->prior=a;
		b->prior=m;
		l->length++;
		return(0);
	} 
	else if(j==1){
		if(i==0){
			a=l->p1;
			b=l->p1->next;
			a->next=m;
			m->prior=a;
			m->next=b;
			b->prior=m;
			l->length++;
			return(0);
		}
		for(flag1=0,flag2=l->p2;flag1<i-1;flag1++,flag2=flag2->prior){
		}
		a=flag2->prior;
		b=flag2;
		a->next=m;
		m->next=b;
		m->prior=a;
		b->prior=m;
		l->length++;
		return(0);
	} 
	else{
		return(3);
	}
}
int ListDelete(List *&l,int i,ListElemType &e,int j){
	//删除l的i位置的元素并赋值给e，j为0从左，为1从右，成功返回0，无元素返回1，j不合法返回2  
	int flag1;
	ListNode *flag2,*m,*a,*b;
	if(j==0){
		if(i<1||i>l->length){
			return(1);
		}
		for(flag1=0,flag2=l->p1;flag1<i-1;flag1++,flag2=flag2->next){
		}
		a=flag2;
		m=flag2->next;
		b=flag2->next->next;
		a->next=b;
		b->prior=a;
		e=m->data;
		free(m);
		l->length--; 
		return(0);
	}
	else if(j==1){
		if(i<1||i>l->length){
			return(1);
		}
		for(flag1=0,flag2=l->p2;flag1<i-1;flag1++,flag2=flag2->prior){
		}
		a=flag2->prior->prior;
		m=flag2->prior;
		b=flag2;
		a->next=b;
		b->prior=a;
		e=m->data;
		free(m);
		l->length--; 
		return(0);
	}
	else{
		return(2);
	}
}
int TraverseList(List *&l,int j){
	//遍历l的所有内容执行自定义操作，j为0从左，为1从右，成功返回0，j不合法返回1 
	ListNode *flag;
	if(j==0){
		for(flag=l->p1->next;flag!=l->p2;flag=flag->next){
			//自定义操作，缺省打印 
			printf("%d\n",flag->data); 
		}
		return(0);
	} 
	else if(j==1){
		for(flag=l->p2->prior;flag!=l->p1;flag=flag->prior){
			//自定义操作，缺省打印 
			printf("%d\n",flag->data); 
		}
		return(0);
	} 
	else{
		return(1);
	}
}
#endif
