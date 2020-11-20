//AOEPath�����ļ���ע�ⶥ��idΪ������ 
#include<stdio.h>
#include<stdlib.h>
#include"GRAPHMATRIX.h" 
#include"AOEPATH.h"
main(){
	int flag,topo[VEXSIZE];
	Stack *s;
	Graph *g;
	VexTime vt[VEXSIZE];
	ArcTime at[VEXSIZE][VEXSIZE];
	InitStack(s);
	InitGraph(g);
	g->kind=1;
	g->vexnum=9;
	g->vex[0].id=0;
	g->vex[0].used=1;
	g->vex[1].id=1;
	g->vex[1].used=1;
	g->vex[2].id=2;
	g->vex[2].used=1;
	g->vex[3].id=3;
	g->vex[3].used=1;
	g->vex[4].id=4;
	g->vex[4].used=1;
	g->vex[5].id=5;
	g->vex[5].used=1;
	g->vex[6].id=6;
	g->vex[6].used=1;
	g->vex[7].id=7;
	g->vex[7].used=1;
	g->vex[8].id=8;
	g->vex[8].used=1;
	g->arcnum=11;
	g->arc[0][1].data=6;
	g->arc[0][1].used=1;
	g->arc[0][2].data=4;
	g->arc[0][2].used=1;
	g->arc[0][3].data=5;
	g->arc[0][3].used=1;
	g->arc[1][4].data=1;
	g->arc[1][4].used=1;
	g->arc[2][4].data=1;
	g->arc[2][4].used=1;
	g->arc[3][5].data=2;
	g->arc[3][5].used=1;
	g->arc[4][6].data=9;
	g->arc[4][6].used=1;
	g->arc[4][7].data=7;
	g->arc[4][7].used=1;
	g->arc[5][7].data=4;
	g->arc[5][7].used=1;
	g->arc[6][8].data=2;
	g->arc[6][8].used=1;
	g->arc[7][8].data=4;
	g->arc[7][8].used=1;
	Path(g,topo,vt,at);
	TraverseVt(g,vt);
	TraverseAt(g,at);
}