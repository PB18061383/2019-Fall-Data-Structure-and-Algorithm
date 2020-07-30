#ifndef __FLOYD_H 
#define __FLOYD_H
//这是基于有向带权图的Floyd最短路径算法。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191202于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"GRAPHMATRIX.h"
#include"STACKNODE.h"
//点的前驱、与源点的长度 
struct ShPath{
	int preid;
	int len;
	int used;
};
void InitShp(Graph *&g,ShPath p[][VEXSIZE]){
	//初始化p数组 
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->vex[flag1].used==0||g->vex[flag2].used==0){
				p[flag1][flag2].used=0;
				continue;
			}
			if(flag1==flag2){
				p[flag1][flag2].len=0;
				p[flag1][flag2].preid=-1;
				p[flag1][flag2].used=1;
				continue;
			}
			if(g->arc[flag1][flag2].used==0){
				p[flag1][flag2].len=INT_MAX;
				p[flag1][flag2].preid=-1;
				p[flag1][flag2].used=1;
			}
			else{
				p[flag1][flag2].len=g->arc[flag1][flag2].data;
				p[flag1][flag2].preid=flag1;
				p[flag1][flag2].used=1;
			}
		}
	}
}
int Floyd(Graph *&g,ShPath p[][VEXSIZE]){
	//求有向带权图g的最短路径矩阵，成功返回0，图不合法返回1，子函数不合法返回2
	int flag1,flag2,flag3;
	if(g->kind==0){
		return(1); 
	} 
	InitShp(g,p);
	for(flag3=0;flag3<g->vexsize;flag3++){
		for(flag1=0;flag1<g->vexsize;flag1++){
			for(flag2=0;flag2<g->vexsize;flag2++){
				if(g->vex[flag1].used==0||g->vex[flag2].used==0){
					continue;
				}
				if(p[flag1][flag3].len+p[flag3][flag2].len>0&&p[flag1][flag3].len+p[flag3][flag2].len<p[flag1][flag2].len){
					p[flag1][flag2].len=p[flag1][flag3].len+p[flag3][flag2].len;
					p[flag1][flag2].preid=p[flag3][flag2].preid;
				}
			}
		}
	}
}
int TraverseFloyd(Graph *&g,VexType v1,VexType v2,ShPath p[][VEXSIZE]){
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
	for(flag=l2;flag!=l1;flag=p[l1][flag].preid){
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
