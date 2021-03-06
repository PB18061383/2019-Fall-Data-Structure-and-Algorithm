//HuffmanTree测试文件，使用时注释掉相应内容，注意文件为ANSI编码 
#include<stdio.h>
#include<stdlib.h>
#include"STRINGHEAP.h"
#include"HUFFMANTREE.h"
main(){
	FILE *fpin,*fpout,*fq;
	String *s0,*b0,*s1,*b1;
	Hft a[511];
	float rate,org,zip;
	//压缩 
	/*fpin=fopen("InText.txt","r");
	fq=fopen("Code.cod","wb");
	InitString(s0);
	InitString(b0);
	InitHft(a);
	FileScanString(s0,fpin);
	CalWeight(s0,a);
	CreTree(a);
	FileCode(fq,s0,b0,a);
	DestroyString(s0);
	DestroyString(b0);
	fseek(fq,0,2);
	fseek(fpin,0,2);
	zip=ftell(fq);
	org=ftell(fpin);
	rate=zip/org;
	printf("\n\n");
	printf("压缩比: %2f\n",rate);
	fclose(fpin);
	fclose(fq);*/ 
	//解压缩
	/*fpout=fopen("OutText.txt","w");
	fq=fopen("Code.cod","rb");
	InitString(s1);
	InitString(b1);
	FileDecode(fq,s1,b1,a);
	FilePrintString(s1,fpout);
	DestroyString(s1);
	DestroyString(b1);
	fclose(fpout);
	fclose(fq);*/ 
	//debug
	fpin=fopen("InText.txt","r");
	fpout=fopen("OutText.txt","w");
	fq=fopen("Code.cod","wb+");
	InitString(s0);
	InitString(b0);
	InitString(s1);
	InitString(b1);
	InitHft(a);
	FileScanString(s0,fpin);
	CalWeight(s0,a);
	CreTree(a);
	FileCode(fq,s0,b0,a);
	printf("\n\n");
	PrintString(s0),
	printf("\n\n");
	PrintString(b0),
	printf("\n\n");
	//TrvTree(a);
	rewind(fq);
	FileDecode(fq,s1,b1,a);
	FilePrintString(s1,fpout);
	printf("\n\n");
	PrintString(s1),
	printf("\n\n");
	PrintString(b1),
	printf("\n\n");
	//TrvTree(a);
	DestroyString(s0);
	DestroyString(b0);
	DestroyString(s1);
	DestroyString(b1);
	fseek(fq,0,2);
	fseek(fpin,0,2);
	zip=ftell(fq);
	org=ftell(fpin);
	rate=zip/org;
	printf("\n\n");
	printf("压缩比: %2f\n",rate);
	fclose(fpin);
	fclose(fpout);
	fclose(fq);
}
