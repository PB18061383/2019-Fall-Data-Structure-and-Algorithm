#ifndef __PRIM_H
#define __PRIM_H
//这是基于无向完全带权图的Prim最小生成树算法。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191116于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"GRAPHMATRIX.h"
//最小生成树存储结构 
struct ClosEdge{
	int id1;
	int id2;
	int used;
	int data;
};
//函数内容 
void InitCls(Graph *&g,ClosEdge cls[]){
	//初始化cls数组 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		cls[flag].id1=0;
		cls[flag].id2=0;
		cls[flag].data=INT_MAX;
		if(g->vex[flag].used==0){
			cls[flag].used=0;
		}
		else{
			cls[flag].used=1;
		}
	}
	return;
}
int ChsMin(Graph *&g,ClosEdge cls[]){
	//找最小元素坐标，没有返回-1 
	int flag,j,l;
	j=INT_MAX;
	for(flag=0;flag<g->vexsize;flag++){
		if(cls[flag].used!=0&&cls[flag].data<j&&cls[flag].data>0){
			j=cls[flag].data;
			l=flag;
		}
	}
	if(j==INT_MAX){
		return(-1);
	}
	return(l);
}
int Prim(Graph *&g,VexType v,ClosEdge cls[]){
	//求无向完全带权图g以v为根节点的最小生成树，成功返回0，图不合法返回1，v不合法返回2 
	int l,flag1,flag2;
	if(g->kind==1){
		return(1); 
	} 
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<flag1+1;flag2++){
			if((g->arc[flag1][flag2].used==0&&g->arc[flag2][flag1].used!=0||g->arc[flag1][flag2].used!=0&&g->arc[flag2][flag1].used==0)||g->arc[flag1][flag2].data!=g->arc[flag2][flag1].data){
				return(1);
			}
		}
	}
	l=LocateVex(g,v,0)-1;
	if(l<0){
		return(2);
	}
	InitCls(g,cls);
	for(flag1=0;flag1<g->vexsize;flag1++){
		if(l!=flag1&&cls[flag1].used!=0){
			cls[flag1].id1=l;
			cls[flag1].id2=flag1;
			if(g->arc[l][flag1].used!=0){
				cls[flag1].data=g->arc[l][flag1].data;
			}
			else{
				cls[flag1].data=INT_MAX;
			}
		}
		else{
			cls[flag1].data=0;
		}
	}
	for(flag1=0;flag1<g->vexsize;flag1++){
		l=ChsMin(g,cls);
		cls[l].data=0;
		if(cls[flag1].used==0){
			continue;
		}
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(cls[flag2].used!=0&&g->arc[cls[l].id2][flag2].used!=0&&g->arc[cls[l].id2][flag2].data<cls[flag2].data){
				cls[flag2].id1=cls[l].id2;
				cls[flag2].data=g->arc[cls[l].id2][flag2].data;
			}
		}
	}
	return(0); 
}
void TraverseCls(Graph *&g,ClosEdge cls[]){
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		if(cls[flag].used!=0&&cls[flag].id1!=cls[flag].id2){
			printf("<%d,%d>:%d\n",g->vex[cls[flag].id1].id,g->vex[cls[flag].id2].id,g->arc[cls[flag].id1][cls[flag].id2].data);
		}
	}
}
#endif
