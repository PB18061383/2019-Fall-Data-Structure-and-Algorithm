//AOVTopology测试文件，注意顶点id为其坐标 
#include<stdio.h>
#include<stdlib.h>
#include"GRAPHMATRIX.h" 
#include"AOVTOPOLOGY.h"
main(){
	int flag,topo[VEXSIZE];
	Stack *s;
	Graph *g;
	InitStack(s);
	InitGraph(g);
	g->kind=1;
	g->vexnum=6;
	g->vex[0].id=1;
	g->vex[0].used=1;
	g->vex[1].id=2;
	g->vex[1].used=1;
	g->vex[2].id=3;
	g->vex[2].used=1;
	g->vex[3].id=4;
	g->vex[3].used=1;
	g->vex[4].id=5;
	g->vex[4].used=1;
	g->vex[5].id=6;
	g->vex[5].used=1;
	g->arcnum=9;
	g->arc[0][1].used=1;
	g->arc[0][2].used=1;
	g->arc[0][3].used=1;
	g->arc[2][1].used=1;
	g->arc[2][4].used=1;
	g->arc[3][4].used=1;
	g->arc[5][3].used=1;
	g->arc[5][6].used=1;
	Topology(g,topo);
	TraverseTopo(g,topo);
}
