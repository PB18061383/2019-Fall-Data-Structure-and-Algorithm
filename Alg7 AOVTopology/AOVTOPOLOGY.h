#ifndef __AOVTOPOLOGY_H
#define __AOVTOPOLOGY_H
//这是基于图的AOV排序。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191116于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include"GRAPHMATRIX.h"
#include"STACKNODE.h"
void FindInDegree(Graph *&g,int indegree[]){
	//求入度存到indegree中 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		indegree[flag]=VexInDegree(g,g->vex[flag],0);
	}
	return;
}
int Topology(Graph *&g,int topo[]){
	//求g的拓扑排序存到topo中，成功返回0，失败返回1 
	int indegree[g->vexsize],err,flag,m,j,l;
	FindInDegree(g,indegree);
	Stack *s;
	VexType v;
	InitStack(s);
	if(err!=0){
		return(1);
	}
	m=0;
	for(flag=0;flag<g->vexsize;flag++){
		if(indegree[flag]==0){
			Push(s,g->vex[flag].id);
		}
	}
	while(s->length!=0){
		Pop(s,j);
		topo[m]=j;
		m++;
		for(flag=0;flag<g->vexsize;flag++){
			v.id=j;
			l=LocateVex(g,v,0);
			if(l<1){
				return(1);
			}
			if(g->arc[l-1][flag].used!=0){
				indegree[flag]--;
				if(indegree[flag]==0){
					Push(s,g->vex[flag].id);
				}
			}
		}
	}
	if(m<g->vexnum){
		return(1);
	}
	else{
		return(0);
	}
	DestroyStack(s);
}
void TraverseTopo(Graph *&g,int topo[]){
	//打印与g对应的topo数组 
	int flag;
	for(flag=0;flag<g->vexnum;flag++){
		printf("%d\n",topo[flag]);
	}
}
#endif
