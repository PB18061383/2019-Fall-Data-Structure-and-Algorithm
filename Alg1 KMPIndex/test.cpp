//KMPIndex�����ļ� 
#include<stdio.h> 
#include"STRINGHEAP.h"
#include"KMPINDEX.h"
main(){
	String *s,*t;
	InitString(s);
	InitString(t);
	printf("��׼��\n");
	ScanString(s);
	printf("ģʽ��\n");
	ScanString(t);
	printf("%d\n",KMPIndex(s,t,1,1)); 
	DestroyString(s); 
	DestroyString(t); 
}
