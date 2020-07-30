#ifndef __KRUSKAL_H 
#define __KRUSKAL_H
//这是基于无向完全带权图的Kruskal最小生成树算法。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191130于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include"GRAPHMATRIX.h"
//边的存储集合 
struct ClosEdge{
	int used;
	int data;
};
//点的所属同化集合 
struct VexSet{
	int set;
	int used;
}; 
//函数内容 
void InitCls(Graph *&g,ClosEdge cls[][VEXSIZE]){
	//初始化cls数组 
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			cls[flag1][flag2].data=g->arc[flag1][flag2].data;
			if(g->arc[flag1][flag2].used==0){
				cls[flag1][flag2].used=0;
			}
			else{
				cls[flag1][flag2].used=1;
			}
		}	
	}
	return;
}
void InitVxs(Graph *&g,VexSet vxs[]){
	//初始化vxs数组 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		vxs[flag].set=flag;
		if(g->vex[flag].used==0){
			vxs[flag].used=0;
		}
		else{
			vxs[flag].used=1;
		}
	}
	return;
}
int ChsMin(Graph *&g,ClosEdge cls[][VEXSIZE]){
	//找最小元素坐标，没有返回-1 
	int flag1,flag2,j,l;
	j=INT_MAX;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<flag1+1;flag2++){
			if(cls[flag1][flag2].used!=0&&cls[flag1][flag2].data<j&&cls[flag1][flag2].data>0){
				j=cls[flag1][flag2].data;
				l=flag1*VEXSIZE+flag2;
			}
		}
	}
	if(j==INT_MAX){
		return(-1);
	}
	return(l);
}
int Kruskal(Graph *&g,ClosEdge cls[][VEXSIZE]){
	//求无向完全带权图g的最小生成树，成功返回0，失败返回1 
	int l,l1,l2,flag1,flag2;
	VexSet vxs[g->vexsize];
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
	InitCls(g,cls);
	InitVxs(g,vxs);
	flag1=0;
	while(flag1!=5){
		l=ChsMin(g,cls);
		l1=l/VEXSIZE;
		l2=l%VEXSIZE;
		if(vxs[l1].used!=0&&vxs[l2].used!=0&&vxs[l1].set!=vxs[l2].set){	
			cls[l1][l2].data=0;
			flag1++;
			for(flag2=0;flag2<g->vexsize;flag2++){
				if(vxs[flag2].set==vxs[l2].set){
					vxs[flag2].set=vxs[l1].set;
				}
			}
		}
	}
	return(0); 
}
void TraverseCls(Graph *&g,ClosEdge cls[][VEXSIZE]){
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<flag1+1;flag2++){
			if(cls[flag1][flag2].used!=0&&cls[flag1][flag2].data==0){
				printf("<%d,%d>:%d\n",g->vex[flag1].id,g->vex[flag2].id,g->arc[flag1][flag2].data);
			}
		}
	}
}
#endif
