#ifndef __TREENODE_H
#define __TREENODE_H
//这是用于链表树的基本操作，使用时请手动改TreeElemType定义，并按需修改NodePreTraverse、NodePostTraverse、NodeInTraverse、NodeLevelTraverse函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191025于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h> 
#include<math.h> 
//链表树元素数据类型，缺省int 
typedef int TreeElemType;
struct TreeNode{
	TreeElemType data;
	TreeNode *child;
	TreeNode *sibling;
};
struct Tree{
	int length;
	int depth;
	TreeNode *p; 
};
//队列元素数据类型，TreeNode *  
typedef TreeNode* TreeQueueElemType;
struct TreeQueueNode{
	TreeQueueElemType data;
	TreeQueueNode *next;
};
struct TreeQueue{
	TreeQueueNode *rear;
	TreeQueueNode *front;
	int length;
	TreeQueueNode *p; 
};
//函数内容 
int InitTree(Tree *&t){
	//初始化树t并创造一个非空结点根。成功返回0，t空返回1，结点空返回2  	
	t=(Tree *)malloc(sizeof(Tree));
	if(t==NULL){
		return(1);
	}
	t->p=(TreeNode *)malloc(sizeof(TreeNode));
	if(t->p==NULL){
		return(2);
	}
	t->p->child=NULL;
	t->p->sibling=NULL;
	t->length=1;
	t->depth=1;
	return(0);
}
void NodeFree(TreeNode *&p){
	//释放掉树枝p结点 
	TreeNode *j,*k;
	if(p!=NULL){
		for(j=p->child;j!=NULL;){
			k=j->sibling;
			NodeFree(j);
			j=k;
		}
		free(p);
		p=NULL;
		return;
	}
	return;
} 
void DestroyTree(Tree *&t){
	//销毁树t 
	NodeFree(t->p);
	free(t);
	t=NULL;
	return;
}
void ClearTree(Tree *&t){
	//将树t置空，保留根  
	TreeNode *j,*k;
	t->length=1;
	t->depth=1;
	for(j=t->p->child;j!=NULL;){
		k=j->sibling;
		NodeFree(j);
		j=k;
	}
	return; 
}
int TreeEmpty(Tree *&t){
	//判断树t是否为空，是返回1，不是返回0 
	if(t->length==0){
		return(1);
	}
	return(0);
}
int NodeLength(TreeNode *&p,int zero){
	//求树枝的长度，zero为静态归零标志   
	static int flag;
	TreeNode *j;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		flag++;
		for(j=p->child;j!=NULL;j=j->sibling){
			NodeLength(j,1);
		}
		return(flag);
	}
	else{
		return(flag);
	}
}
int TreeLength(Tree *&t){
	//返回树t长度 
	return(t->length);
}
int NodeDepth(TreeNode *&p,int zero){
	//求树枝的深度，zero为静态归零标志 
	static int flag;
	int n,i;
	TreeNode *j;
	i=0;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		flag++;
		for(j=p->child;j!=NULL;j=j->sibling){
			n=NodeDepth(j,1);
			if(i<n){
				i=n;
			}
		}
		flag=n+1;
		return(flag);
	}
	else{
		return(0);
	}
}
int TreeDepth(Tree *&t){
	//返回树t深度 
	return(t->depth);
}
int NodeWidth(TreeNode *p,int i){
	//求树枝第i层的宽度 
	int flag;
	TreeNode *j;
	flag=0;
	if(p==NULL){
		return(0);
	}
	else{
		if(i==1){
			return(1);
		}
		for(j=p->child;j!=NULL;j=j->sibling){
			flag=flag+NodeWidth(j,i-1);
		}
	}
	return(flag);
}
int TreeWidth(Tree *&t,int i){
	//返回树第i层的宽度 
	return(NodeWidth(t->p,i));
}
TreeNode *Root(Tree *&t){
	//返回树t根结点 
	return(t->p);
}
int Value(Tree *&t,TreeNode *&p,TreeElemType &e){
	//返回树t的指针p的元素,成功将值赋值给e所在地址并返回0，失败返回1 
	if(p==NULL){
		return(1);
	}
	e=p->data;
	return(0);
} 
int Assign(Tree *&t,TreeNode *&p,TreeElemType e){
	//给树t的指针p的元素赋值为e,成功返回0，失败返回1 
	if(p==NULL){
		return(1);
	}
	p->data=e;
	return(0);
}
TreeNode *NodeParent(TreeNode *&j,TreeNode *&p,int zero){
	//返回树枝j的指针p的元素的父结点，zero为静态归零标志，成功返回相应指针，失败返回NULL 
	static TreeNode *flag;
	TreeNode *l;
	if(zero==0){
		flag=NULL;
		return(flag);
	} 
	if(j==NULL){
		return(j);
	}
	if(flag==NULL){
		for(l=j->child;l!=NULL;l=l->sibling){
			flag=NodeParent(l,p,1);
			if(flag!=NULL){
				break;
			}
		}
		return(flag);
	}
	if(flag!=NULL){
		return(flag);
	} 
	if(flag==NULL){
		for(l=j->child;l!=NULL;l=l->sibling){
			if(l==p){
				flag=j;
				return(flag);
			}
		}
		return(flag);
	}
}
TreeNode *Parent(Tree *&t,TreeNode *&p){
	//返回树t的指针p的元素的父结点，成功返回相应指针，失败返回NULL  
	NodeParent(t->p,p,0);
	return(NodeParent(t->p,p,1));
}
TreeNode *Child(Tree *&t,TreeNode *&p,int i){
	//返回树t的指针p的元素的第i个子结点，成功返回相应指针，失败返回NULL  
	int width,flag1;
	TreeNode *flag2; 
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(NULL);
	}
	for(flag1=0,flag2=p->child;flag1<i-1;flag1++,flag2=flag2->sibling){
	}
	return(flag2);
}
TreeNode *LeftSibling(Tree *&t,TreeNode *&p){
	//返回树t的指针p的元素的左兄弟结点，成功返回相应指针，失败返回NULL 
	TreeNode *q,*j,*k;
	NodeParent(t->p,p,0);
	q=NodeParent(t->p,p,1);
	if(p==q->child){
		return(NULL);
	}
	for(j=q->child;j!=NULL;j=j->sibling){
		if(j->sibling==p){
			return(j);
		}
	}
	return(NULL);
}
TreeNode *RightSibling(Tree *&t,TreeNode *&p){
	//返回树t的指针p的元素的右兄弟结点，成功返回相应指针，失败返回NULL 
	return(p->sibling);
}
int InsertChild(Tree *&t,TreeNode *&p,int i,TreeNode *&v){
	//给树t的指针p的元素添加i位置前的子系v，若i为0，则在后方插入。成功返回0，失败返回1 
	int width,flag1;
	TreeNode *flag2;
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(1);
	}
	if(i==0){
		for(flag2=p->child;flag2->sibling!=NULL;flag2=flag2->sibling){
			flag2->sibling=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
		    return(0);
		}
	}
	else{
		if(i==1){
			v->sibling=p->child;
			p->child=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
			return(0);
		}
		else{
			for(flag1=0,flag2=p->child;flag1<i-2;flag1++,flag2=flag2->sibling){
			}
			v->sibling=flag2->sibling;
			flag2->sibling=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
			return(0);
		}
	}
}
int DeleteChild(Tree *&t,TreeNode *&p,int i,TreeNode *&v){
	//给树t的指针p的元素删除i位置子系，并赋值给v，成功返回0，失败返回1 
	int width,flag1;
	TreeNode *flag2;
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(1);
	}
	if(i==1){
		NodeLength(p->child,0);
		t->length=t->length-NodeLength(p->child,1);
		NodeDepth(p->child,0);
		t->depth=t->depth-NodeDepth(p->child,1);
		v=p->child;
		p->child=p->child->sibling;
		v->sibling=NULL;
		return(0);
	}
	else{
		for(flag1=0,flag2=p->child;flag1<i-2;flag1++,flag2=flag2->sibling){
		}
		NodeLength(flag2->sibling,0);
		t->length=t->length-NodeLength(flag2->sibling,1);
	    NodeDepth(flag2->sibling,0);
	    t->depth=t->depth-NodeDepth(flag2->sibling,1);
	    v=flag2->sibling;
	    flag2->sibling=flag2->sibling->sibling;
	    v->sibling=NULL;
		return(0);
	}
}
int NodeCopy(TreeNode *&p,TreeNode *&q,int zero){
	//复制树枝p到q，成功返回0，失败返回1，zero为静态归零标志  
	static int err;
	TreeNode *j;
	if(zero==0){
		err=0;
		return(0);
	} 
	if(p!=NULL){
		q->data=p->data;
		q->child=(TreeNode *)malloc(sizeof(TreeNode));
		q->sibling=(TreeNode *)malloc(sizeof(TreeNode));
		if(q->child==NULL||q->sibling==NULL){
			err=1;
			return(1);
		}
		for(j=p->child;;j=j->sibling){
			NodeCopy(j,q->sibling,1);
			if(j==NULL){
				break;
			}
		}
		return(0);
	}
	if(p==NULL){
		free(q);
		q=NULL;
	}
	if(err==1){
		return(1);
	}
	return(0);
}
int TreeCopy(Tree *&t,Tree *&u){
	//复制树t到p，成功返回0，失败返回1
	int err;
	ClearTree(u);
	NodeCopy(t->p,u->p,0);
	err=NodeCopy(t->p,u->p,1);
	return(err);
}
void NodePreTraverse(TreeNode *&p){
	//先序遍历树枝p的所有内容执行自定义操作 
	TreeNode *j;
	if(p!=NULL){
		//自定义操作，缺省打印
		printf("%d\n",p->data); 
		for(j=p->child;j!=NULL;j=j->sibling){
			NodePreTraverse(j);
		}
		return;
	}
	return;
}
void PreTraverseTree(Tree *&t){
	//先序遍历t的所有内容执行自定义操作 
	NodePreTraverse(t->p);
	return;
}
void NodePostTraverse(TreeNode *&p){
	//后序遍历树枝p的所有内容执行自定义操作 
	TreeNode *j;
	if(p!=NULL){
		for(j=p->child;j!=NULL;j=j->sibling){
			NodePostTraverse(j);
		}
		//自定义操作，缺省打印
		printf("%d\n",p->data);  
		return;
	}
	return;
}
void PostTraverseTree(Tree *&t){
	//后序遍历t的所有内容执行自定义操作 
	NodePostTraverse(t->p);
	return;
}
int InitTreeQueue(TreeQueue *&q){
	//初始化单链表队列q并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	q=(TreeQueue *)malloc(sizeof(TreeQueue));
	if(q==NULL){
		return(1);
	}
	q->p=(TreeQueueNode *)malloc(sizeof(TreeQueueNode)); 
	if(q->p==NULL){
		return(2);
	}
	q->p->next=NULL; 
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	return(0); 
}
void DestroyTreeQueue(TreeQueue *&q){
	//销毁单链表队列q  
	TreeQueueNode *flag,*res;
	flag=q->p;
	while(flag!=NULL){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(q);
	return;
}
int Enter(TreeQueue *&q,TreeQueueElemType e){
	//把e插入q。成功返回0，失败返回1  
	TreeQueueNode *j,*a;
	j=(TreeQueueNode *)malloc(sizeof(TreeQueueNode));
	if(j==NULL){
		return(1);
	}
	j->data=e;
	j->next=NULL;
	a=q->rear;
	a->next=j;
	q->rear=j;
	if(q->length==0){
		q->front=q->p->next;
	}
	q->length++;
	return(0);
}
void Depart(TreeQueue *&q,TreeQueueElemType &e){
	//删除q队首元素并赋值给e。成功返回0，失败返回1  
	TreeQueueNode *j,*a;
	j=q->front;
	a=j->next;
	q->p->next=a;
	q->front=a;
	free(j);
	q->length--;
	return;
}
int LevelTraverseTree(Tree *&t){
	//层序遍历t的所有内容执行自定义操作，成功返回0，初始化队列失败返回1，进入队列失败返回2 
	int err;
	TreeQueue *q;
	TreeQueueElemType e;
	TreeNode *j;
	e=t->p;
	err=InitTreeQueue(q);
	if(err!=0){
		return(1); 
	}
	err=Enter(q,e);
	if(err!=0){
		return(2); 
	}
	while(q->length!=0){
		//自定义操作，缺省打印 
		printf("%d\n",q->front->data);  
		for(j=q->front->data->child;j!=NULL;j=j->sibling){
		    err=Enter(q,j);
		    if(err!=0){
	    		return(2); 
	    	}
		}
		Depart(q,e);
	}
	DestroyTreeQueue(q);
	return(0);
}
#endif
