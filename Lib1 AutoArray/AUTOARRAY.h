#ifndef __AUTOARRAY_H
#define __AUTOARRAY_H
//这是用于动态数组线性表的基本操作，使用时请手动改LISTSIZE、LISTADDON、ListElemType定义，并按需修改TraverseList函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20190917于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h>
//动态数组最小长度，缺省50 
#define LISTSIZE 50
//动态数组每次申请新元素增量，缺省10 
#define LISTADDON 10 
//动态数组线性表数据类型，缺省int 
typedef int ListElemType; 
struct List{
	ListElemType *data;
	int length;
	int size;
};
//函数内容 
int InitList(List *&l){
	//初始化动态数组l，l的默认长度是LISTSIZE，可以增删。成功返回0，l空返回1，data空返回2 
	l=(List *)malloc(sizeof(List));
	if(l==NULL){
		return(1);
	}
	l->data=(ListElemType *)calloc(LISTSIZE,sizeof(ListElemType));
	if(l->data==NULL){
		return(2);
	}
	l->length=0;
	l->size=LISTSIZE;
	return(0);
}
void DestroyList(List *&l){
	//销毁动态数组l 
	free(l->data); 
	free(l);
	l=NULL;
	return;
}
int ClearList(List *&l){
	//将动态数组l置空，成功返回0，data空返回1 
	l->length=0;
	if(l->size>LISTSIZE){
		l->data=(ListElemType *)realloc(l->data,LISTSIZE*sizeof(ListElemType));
		if(l->data==NULL){
		    return(1);
	    }
		l->size=LISTSIZE;
	}
	return(0); 
}
int ListEmpty(List *&l){
	//判断动态数组l是否为空，是返回1，不是返回0 
	if(l->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int ListFull(List *&l){
	//判断动态数组l是否为满，是返回1，不是返回0 
	if(l->length==l->size){
		return(1);
	}
	else{
		return(0);
	}
}
int ListLength(List *&l){
	//返回动态数组l长度 
	return(l->length);
}
int GetElem(List *&l,int i,ListElemType &e){
	//返回动态数组l第i个元素,成功将值赋值给e所在地址并返回0，失败返回1 
	if(i<1||i>l->length){
		return(1); 
	}
	e=l->data[i-1];
	return(0);
}
int LocateItem(List *&l,ListElemType e){
	//返回动态数组第一个值为e的元素位置，没有返回0 
	int flag;
	for(flag=0;flag<l->length;flag++){
		if(l->data[flag]==e){
			return(flag+1);
		}
	} 
	return(0);
}
int PriorElem(List *&l,ListElemType e,ListElemType &pe){
	//返回动态数组第一个值为e的元素前驱，成功将赋值给pe所在地址并返回0，没有返回1 
	int flag;
	flag=LocateItem(l,e)-1;
	if(flag<1){
		return(1);
	}
	pe=l->data[flag-1];
	return(0);
}
int NextElem(List *&l,ListElemType e,ListElemType &ne){
	//返回动态数组第一个值为e的元素后继，成功将赋值给ne所在地址并返回0，没有返回1 
	int flag;
	flag=LocateItem(l,e)-1;
	if(flag==l->length-1){
		return(1);
	}
	ne=l->data[flag+1];
	return(0);
}
int ListInsert(List *&l,int i,ListElemType e){
	//在l的i位置前插入e，若i为0，则在后方插入。成功返回0，i不合法返回1，内存不足返回2 
	int flag;
	if(i<0||i>l->length){
		return(1);
	} 
	if(l->length==l->size){
		l->data=(ListElemType *)realloc(l->data,(l->size+LISTADDON)*sizeof(ListElemType));
		if(l->data==NULL){
			return(2);
		}
		l->size=l->size+LISTADDON;
	}
	if(i==0){
		l->data[l->length]=e;
		l->length++;
		return(0);
	}
	for(flag=l->length-1;flag>=i-1;flag--){
		l->data[flag+1]=l->data[flag];
	}
	l->data[i-1]=e;
	l->length++;
	return(0);
}
int ListDelete(List *&l,int i,ListElemType &e){
	//删除l的i位置的元素并赋值给e。成功返回0，i不合法返回1，内存不足返回2 
	int flag;
	if(i<1||i>l->length){
		return(1);
	}
	e=l->data[i-1];
	for(flag=i;flag<l->length;flag++){
		l->data[flag-1]=l->data[flag];
	}
	l->length--;
	if(l->size-l->length>LISTADDON&&l->size>LISTSIZE){
		l->data=(ListElemType *)realloc(l->data,(l->size-LISTADDON)*sizeof(ListElemType));
		if(l->data==NULL){
			return(2);
		}
		l->size=l->size-LISTADDON;
	}
	return(0);
}
void TraverseList(List *&l){
	//遍历l的所有内容执行自定义操作 
	int flag;
	for(flag=0;flag<l->length;flag++){
		//自定义操作，缺省打印 
		printf("%d\n",l->data[flag]); 
	}
	return;
}
#endif
