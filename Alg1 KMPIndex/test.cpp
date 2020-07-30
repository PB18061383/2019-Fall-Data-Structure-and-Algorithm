//KMPIndex测试文件 
#include<stdio.h> 
#include"STRINGHEAP.h"
#include"KMPINDEX.h"
main(){
	String *s,*t;
	InitString(s);
	InitString(t);
	printf("标准串\n");
	ScanString(s);
	printf("模式串\n");
	ScanString(t);
	printf("%d\n",KMPIndex(s,t,1,1)); 
	DestroyString(s); 
	DestroyString(t); 
}
