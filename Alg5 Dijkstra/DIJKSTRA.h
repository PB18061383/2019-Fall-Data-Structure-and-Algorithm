#ifndef __KRUSKAL_H 
#define __KRUSKAL_H
//这是基于有向带权图的Dijkstra最短路径算法。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191130于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"GRAPHMATRIX.h"
#include"STACKNODE.h"
//点的确定性、前驱、与源点的长度 
struct ShPath{
	int cer;
	int preid;
	int len;
	int used;
};
//函数内容
void InitShp(Graph *&g,VexType v,ShPath p[]){
	//初始化p数组 
	int flag,l;
	l=LocateVex(g,v,0)-1;
	for(flag=0;flag<g->vexsize;flag++){
		p[flag].cer=0;
		if(g->arc[l][flag].used!=0){
			p[flag].len=g->arc[l][flag].data;
		}
		else{
			p[flag].len=INT_MAX;
		}
		if(p[flag].len!=INT_MAX){
			p[flag].preid=g->vex[l].id;
		}
		else{
			p[flag].preid=-1;
		}
		if(g->vex[flag].used!=0){
			p[flag].used=1;
		}
		else{
			p[flag].used=0;
		}
	}
	p[l].cer=1;
	p[l].preid=-1;
	p[l].len=0;
	return;
}
int DijPoint(Graph *&g,VexType v,ShPath p[]){
	//求有向带权图g以v为根节点的最短路径，成功返回0，图不合法返回1，v不合法返回2
	int flag1,flag2,l,min;
	if(g->kind==0){
		return(1); 
	} 
	l=LocateVex(g,v,0)-1;
	if(l<0){
		return(2);
	} 
	InitShp(g,v,p);
	for(flag1=1;flag1<g->vexsize;flag1++){
		if(g->vex[flag1].used==0){
			continue;
		}
		min=INT_MAX;
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->vex[flag1].used==0){
				continue;
			}
			if(p[flag2].cer==0&&p[flag2].len<min&&p[flag2].len>0){
				l=flag2;
				min=p[flag2].len;
			}
		}
		p[l].cer=1;
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->vex[flag1].used==0){
					continue;
			}
			if(p[flag2].cer==0&&g->arc[l][flag2].used!=0&&p[l].len+g->arc[l][flag2].data<p[flag2].len){
				p[flag2].len=p[l].len+g->arc[l][flag2].data;
				p[flag2].preid=g->vex[l].id;
			}
		}
	}
} 
int Dijkstra(Graph *&g,ShPath p[][VEXSIZE]){
	//求有向带权图g的最短路径矩阵，成功返回0，图不合法返回1，子函数不合法返回2
	int flag1,flag2,err;
	if(g->kind==0){
		return(1); 
	} 
	for(flag1=0;flag1<g->vexsize;flag1++){
		err=DijPoint(g,g->vex[flag1],p[flag1]);
		if(err==2){
			for(flag2=0;flag2<g->vexsize;flag2++){
				p[flag1][flag2].used=0;
			}
		}
	}
}
int TraverseDij(Graph *&g,VexType v1,VexType v2,ShPath p[][VEXSIZE]){
	//打印生成矩阵的v1到v2的特定路径，成功返回0，v1不合法返回1，v2不合法返回2，无有效路径返回3，点重合返回4，栈初始化失败返回5 
	int flag,l1,l2,err;
	Stack *s;
	err=InitStack(s);
	if(err!=0){
		return(5);
	}
	l1=LocateVex(g,v1,0)-1;
	if(l1<0){
		return(1);
	} 
	l2=LocateVex(g,v2,0)-1;
	if(l2<0){
		return(2);
	}
	if(p[l1][l2].len==INT_MAX){
		printf("无有效路径\n");
		return(3);
	}
	if(p[l1][l2].len==0){
		printf("点重合\n");
		return(4);
	}
	for(flag=l2;p[l1][flag].preid!=-1;flag=p[l1][flag].preid){
		Push(s,flag);
	}
	printf("start -> %d -> ",l1);
	while(s->length!=0){
		printf("%d -> ",s->top->data);
		Pop(s,flag);
	}
	printf("end\n");
	DestroyStack(s);
	return(0);
}
#endif
