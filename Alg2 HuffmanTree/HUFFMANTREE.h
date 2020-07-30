#ifndef __HUFFMANTREE_H
#define __HUFFMANTREE_H
//这是用于压缩文件的哈夫曼树算法，需三个文件（输入，输出，编码）四个字符串（输入字符串、输出编码、输入编码、输出字符串），使用时需初始化哈
//夫曼树、，然后从输入文件扫描字符串至输入字符串，计算权重，建树，编码，重置文件指针，解码，释放字符串。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191112于中国科学技术大学）
#include<stdio.h>
#include<stdlib.h>
#include"STRINGHEAP.h" 
#include"STACKARRAY.h"
//哈夫曼树存储结构 
struct Hft{
	int weight;
	int parent;
	int left;
	int right;
};
//函数内容 
void InitHft(Hft a[]){
	int flag;
	for(flag=0;flag<511;flag++){
		if(flag<256){
			a[flag].weight=0;
		}
		else{
			a[flag].weight=-1;
		}
		a[flag].left=-1;
		a[flag].right=-1;
		a[flag].parent=-1; 
	}
}
void CalWeight(String *&s,Hft a[]){
	//计算每个字符的权重 
	int flag;
	for(flag=0;flag<s->length;flag++){
		a[s->str[flag]].weight++; 
	}
	return;
}
int ChsLittle(Hft a[]){
	//选最小的两个权重对应字符的位置 
	int flag,i;
	for(flag=0;flag<511;flag++){
		if(a[flag].parent==-1){
			i=flag;
			break;
		}
	}
	for(flag=0;flag<511;flag++){
		if(a[flag].parent==-1&&a[flag].weight>-1){
			if(a[flag].weight<=a[i].weight){
				i=flag;
			}
		}
	}
	a[i].parent=-2;
	return(i);
}
void CreTree(Hft a[]){
	//创建哈夫曼树 
	int l[2],flag;
	for(flag=256;flag<511;flag++){
		l[0]=ChsLittle(a);
		l[1]=ChsLittle(a);
		a[l[0]].parent=flag;
		a[l[1]].parent=flag;
		a[flag].left=l[0];
		a[flag].right=l[1];
		a[flag].weight=a[l[0]].weight+a[l[1]].weight;
	}
}
void TrvTree(Hft a[]){
	//遍历树的元素 
	int flag;
	for(flag=0;flag<511;flag++){
		printf("%4d:      weight:%4d      parent:%4d      left:%4d      right:%4d\n",flag,a[flag].weight,a[flag].parent,a[flag].left,a[flag].right);
	}
}
int Code(String *&s,String *&b,Hft a[]){
	//对s编码存到b中，成功返回0，失败返回1 
	int flag1,flag2,add;
	Stack *st;
	for(flag1=0;flag1<s->length;flag1++){
		InitStack(st);
		for(flag2=s->str[flag1];flag2>0;flag2=a[flag2].parent){
			if(a[a[flag2].parent].left==flag2){
				Push(st,'0');
			}
			else if(a[a[flag2].parent].right==flag2){
				Push(st,'1');
			}
		}
		for(;st->length!=0;){
			if(b->length+10>=b->size){
				add=10;
				b->str=(unsigned char *)realloc(b->str,(b->size+add*STRINGADDON)*sizeof(char));
				if(b->str==NULL){
					return(1);
				}
				b->size=b->size+add*STRINGADDON;
			}
			Pop(st,b->str[b->length]);
			b->length++;
		}
		DestroyStack(st);
	}
	return(0);
}
void Decode(String *&s,String *&b,Hft a[]){
	//对b解码存到s中 
	int flag1,flag2;
	String *t;
	InitString(t);
	t->length=1;
	for(flag1=0,flag2=510;flag1<b->length;flag1++){
		if(b->str[flag1]=='0'){
			if(a[a[flag2].left].left==-1&&a[a[flag2].left].right==-1){
				t->str[0]=a[flag2].left;
				StringInsert(s,t,0);
				flag2=510;
			}
			else{
				flag2=a[flag2].left;
			}
		}
		else if(b->str[flag1]=='1'){
			if(a[a[flag2].right].left==-1&&a[a[flag2].right].right==-1){
				t->str[0]=a[flag2].right;
				StringInsert(s,t,0);
				flag2=510;
			}
			else{
				flag2=a[flag2].right;
			}
		}
	}
}
int FileCode(FILE *fp,String *&s,String *&b,Hft a[]){
	//对s向文件编码b，编码规则是int的留出0空间，255个哈夫曼树，补0的编码，成功返回0，失败返回1 
	int flag,err,res;
	char j;
	String *t;
	res=0;
	j=0;
	InitString(t);
	t->str[0]='0';
	t->length=1;
	err=Code(s,b,a);
	if(err!=0){
		return(1);
	}
	while(b->length%8!=0){
		StringInsert(b,t,0);
		res++;
	} 
	fwrite(&res,sizeof(int),1,fp);
	for(flag=0;flag<256;flag++){
		fwrite(&a[flag].weight,sizeof(int),1,fp);
	}
	for(flag=0;flag<b->length;flag++){
		if(flag%8!=7){
			if(b->str[flag]=='0'){
				j=(j<<1)+0;
			}
			if(b->str[flag]=='1'){
				j=(j<<1)+1;
			}
		}
		else{
			if(b->str[flag]=='0'){
				j=(j<<1)+0;
			}
			if(b->str[flag]=='1'){
				j=(j<<1)+1;
			}
			fwrite(&j,sizeof(unsigned char),1,fp);
			j=0;
		}
	}
	DestroyString(t);
	return(0);
}
int FileDecode(FILE *fp,String *&s,String *&b,Hft a[]){
	//对b从文件解码s， 
	int res,flag;
	unsigned char i,j;
	String *t0,*t1;
	InitString(t0);
	InitString(t1);
	InitHft(a);
	t0->str[0]='0';
	t0->length=1;
	t1->str[0]='1';
	t1->length=1;
	fread(&res,sizeof(int),1,fp);
	for(flag=0;flag<256;flag++){
		fread(&a[flag].weight,sizeof(int),1,fp); 		
	}
	CreTree(a);
	fread(&j,sizeof(unsigned char),1,fp);
	while(feof(fp)==0){
		for(flag=0;flag<8*sizeof(char);flag++){
			if((j&0x80)==0x00){
				StringInsert(b,t0,0);
			}
			if((j&0x80)==0x80){
				StringInsert(b,t1,0);
			}
			j=j<<1;
		}
		fread(&j,sizeof(char),1,fp);
	}
	b->length=b->length-res;
	Decode(s,b,a);
	DestroyString(t0);
	DestroyString(t1);
}
#endif
