#ifndef __AOEPATH_H
#define __AOEPATH_H
//这是基于图的AOE关键路径。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191203于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"GRAPHMATRIX.h"
#include"STACKNODE.h"
#include"AOVTOPOLOGY.h"
//记录最早开始、最迟开始、 
struct VexTime{
	int ve;
	int vl;
	int used;
};
struct ArcTime{
	int ae;
	int al;
	int used;
};
//函数内容 
void InitVt(Graph *&g,VexTime vt[]){
	//初始化vt数组 
	int flag;
	for(flag=0;flag<g->vexsize;flag++){
		if(g->vex[flag].used==0){
			vt[flag].used=0;
			continue;
		}
		else{
			vt[flag].used=1;
		}
		vt[flag].ve=0;
		vt[flag].vl=INT_MAX;
	}
	return;
}
void InitAt(Graph *&g,ArcTime at[][VEXSIZE]){
	//初始化at数组 
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->arc[flag1][flag2].used==0){
				at[flag1][flag2].used=0;
				continue;
			}
			else{
				at[flag1][flag2].used=1;
			}
		}
	}
	return;
}
int Path(Graph *&g,int topo[],VexTime vt[],ArcTime at[][VEXSIZE]){
	//求g的拓扑排序存到topo中，再求出点和边的最早最晚开始时间存到vt、at中，成功返回0，失败返回1 
	int err,flag1,flag2,vexflag;
	VexType v;
	err=Topology(g,topo); 
	if(err!=0){
		return(1);
	}
	InitVt(g,vt);
	InitAt(g,at);
	for(flag1=0;flag1<g->vexnum;flag1++){
		v.id=topo[flag1];
		v.used=1;
		vexflag=LocateVex(g,v,0)-1;
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->vex[flag2].used==0||g->arc[vexflag][flag2].used==0){
				continue;
			}
			if(g->arc[vexflag][flag2].data+vt[vexflag].ve>vt[flag2].ve){
				vt[flag2].ve=g->arc[vexflag][flag2].data+vt[vexflag].ve;
			}
		}
	}
	v.id=topo[g->vexnum-1];
	v.used=1;
	vexflag=LocateVex(g,v,0)-1;
	vt[vexflag].vl=vt[vexflag].ve;
	for(flag1=g->vexnum-2;flag1>=0;flag1--){
		v.id=topo[flag1];
		v.used=1;
		vexflag=LocateVex(g,v,0)-1;
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->vex[flag2].used==0||g->arc[vexflag][flag2].used==0){
				continue;
			}
			if(vt[flag2].vl-g->arc[vexflag][flag2].data<vt[vexflag].vl){
				vt[vexflag].vl=vt[flag2].vl-g->arc[vexflag][flag2].data;
			}
		}
	}
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->arc[flag1][flag2].used==0){
				continue;
			}
			at[flag1][flag2].ae=vt[flag1].ve;
			at[flag1][flag2].al=vt[flag2].vl-g->arc[flag1][flag2].data;
		}
	}
}
void TraverseVt(Graph *&g,VexTime vt[]){
	//打印与g对应的vt数组 
	int flag;
	for(flag=0;flag<g->vexnum;flag++){
		if(g->vex[flag].used==0){
			continue;
		}
		printf("id:%d,ve:%d,vl:%d\n",g->vex[flag].id,vt[flag].ve,vt[flag].vl);
	}
}
void TraverseAt(Graph *&g,ArcTime at[][VEXSIZE]){
	//打印与g对应的at数组 
	int flag1,flag2;
	for(flag1=0;flag1<g->vexsize;flag1++){
		for(flag2=0;flag2<g->vexsize;flag2++){
			if(g->arc[flag1][flag2].used==0){
				continue;
			}
			printf("<%d,%d>,ae:%d,al:%d\n",g->vex[flag1].id,g->vex[flag2].id,at[flag1][flag2].ae,at[flag1][flag2].al);
		}
	}
}
#endif
