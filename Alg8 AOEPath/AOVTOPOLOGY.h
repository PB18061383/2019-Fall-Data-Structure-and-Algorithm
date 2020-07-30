#ifndef __AOVTOPOLOGY_H
#define __AOVTOPOLOGY_H
//���ǻ���ͼ��AOV���� 
//���ڸϹ���æ��������Щ��bug���Դ˱�����б�Ǹ�����н����Խ��飬��ͨ��QQ��1345578933��ϵ������껣�20191116���й���ѧ������ѧ��
#include<stdio.h>
#include<stdlib.h>
#include"GRAPHMATRIX.h"
#include"STACKNODE.h"
//�������� 
void FindInDegree(Graph *&g,int indegree[]){
	//����ȴ浽indegree�� 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		indegree[flag]=VexInDegree(g,g->vex[flag],0);
	}
	return;
}
int Topology(Graph *&g,int topo[]){
	//��g����������浽topo�У��ɹ�����0��ʧ�ܷ���1 
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
	//��ӡ��g��Ӧ��topo���� 
	int flag;
	for(flag=0;flag<g->vexnum;flag++){
		printf("%d\n",topo[flag]);
	}
}
#endif
