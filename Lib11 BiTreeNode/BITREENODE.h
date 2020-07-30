#ifndef __BITREENODE_H
#define __BITREENODE_H
//这是用于链表二叉树的基本操作，使用时请手动改BiTreeElemType定义，并按需修改NodePreTraverse、NodePostTraverse、NodeInTraverse、NodeLevelTraverse函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191025于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h> 
#include<math.h> 
//链表二叉树元素数据类型，缺省int 
typedef int BiTreeElemType;
struct BiTreeNode{
	BiTreeElemType data;
	BiTreeNode *left;
	BiTreeNode *right;
};
struct BiTree{
	int length;
	int depth;
	BiTreeNode *p; 
};
//队列元素数据类型，BiTreeNode *  
typedef BiTreeNode* BiTreeQueueElemType;
struct BiTreeQueueNode{
	BiTreeQueueElemType data;
	BiTreeQueueNode *next;
};
struct BiTreeQueue{
	BiTreeQueueNode *rear;
	BiTreeQueueNode *front;
	int length;
	BiTreeQueueNode *p; 
};
//函数内容 
int InitBiTree(BiTree *&t){
	//初始化二叉树t并创造一个非空结点根。成功返回0，t空返回1，结点空返回2  	
	t=(BiTree *)malloc(sizeof(BiTree));
	if(t==NULL){
		return(1);
	}
	t->p=(BiTreeNode *)malloc(sizeof(BiTreeNode));
	if(t->p==NULL){
		return(2);
	}
	t->p->left=NULL;
	t->p->right=NULL;
	t->length=1;
	t->depth=1;
	return(0);
}
void NodeFree(BiTreeNode *&p){
	//释放掉二叉树枝p结点 
	if(p!=NULL){
		NodeFree(p->left);
		NodeFree(p->right);
		free(p);
		p=NULL;
		return;
	}
	return;
} 
void DestroyBiTree(BiTree *&t){
	//销毁二叉树t 
	NodeFree(t->p);
	free(t->p);
	free(t);
	t=NULL;
	return;
}
void ClearBiTree(BiTree *&t){
	//将二叉树t置空  
	t->length=1;
	t->depth=1;
	NodeFree(t->p->left);
	NodeFree(t->p->right);
	return;
}
int BiTreeEmpty(BiTree *&t){
	//判断二叉树t是否为空，是返回1，不是返回0 
	if(t->length==0){
		return(1);
	}
	return(0);
}
int BiTreeFull(BiTree *&t){
	//判断二叉树t是否为满，是返回1，不是返回0 
	if(t->length==pow(2,t->depth)-1){
		return(1);
	}
	return(0);
}
int NodeLength(BiTreeNode *&p,int zero){
	//求二叉树枝的长度，zero为静态归零标志   
	static int flag;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		flag++;
		NodeLength(p->left,1);
		NodeLength(p->right,1);
		return(flag);
	}
	else{
		return(flag);
	}
}
int BiTreeLength(BiTree *&t){
	//返回二叉树t长度	
	return(t->length);
}
int NodeDepth(BiTreeNode *&p,int zero){
	//求二叉树枝的深度，zero为静态归零标志 
	static int flag;
	int x,y;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		x=NodeDepth(p->left,1);
		y=NodeDepth(p->right,1);
		if(x<y){
			flag=y+1;
		}
		else{
			flag=x+1;
		}
		return(flag);
	}
	else{
		return(0);
	}
}
int BiTreeDepth(BiTree *&t){
	//返回二叉树t深度 
	return(t->depth);
}
int NodeWidth(BiTreeNode *p,int i){
	//求二叉树枝第i层的宽度 
	int flag;
	if(p==NULL){
		return 0;
	}
	else{
		if(i==1){
			return 1;
		}
		flag=NodeWidth(p->left,i-1)+NodeWidth(p->right,i-1);
	}
	return(flag);
}
int BiTreeWidth(BiTree *&t,int i){
	//返回二叉树第i层的宽度 
	return(NodeWidth(t->p,i));
}
BiTreeNode *Root(BiTree *&t){
	//返回二叉树t根结点 
	return(t->p);
}
int Value(BiTree *&t,BiTreeNode *&p,BiTreeElemType &e){
	//返回二叉树t的指针p的元素,成功将值赋值给e所在地址并返回0，失败返回1 
	if(p==NULL){
		return(1);
	}
	e=p->data;
	return(0);
} 
int Assign(BiTree *&t,BiTreeNode *&p,BiTreeElemType e){
	//给二叉树t的指针p的元素赋值为e,成功返回0，失败返回1 
	if(p==NULL){
		return(1);
	}
	p->data=e;
	return(0);
}
BiTreeNode *NodeParent(BiTreeNode *&j,BiTreeNode *&p,int zero){
	//返回二叉树枝j的指针p的元素的父结点，zero为静态归零标志，成功返回相应指针，失败返回NULL 
	static BiTreeNode *flag;
	if(zero==0){
		flag=NULL;
		return(flag);
	} 
	if(j==NULL){
		return(j);
	}
	if(flag==NULL){
		flag=NodeParent(j->left,p,1);
	}
	if(flag==NULL){
		flag=NodeParent(j->right,p,1);
	}
	if(flag!=NULL){
		return(flag);
	} 
	if(flag==NULL){
		if(j->left==p||j->right==p){
			flag=j;
			return(flag);
		}
		return(flag);
	}
}
BiTreeNode *Parent(BiTree *&t,BiTreeNode *&p){
	//返回二叉树t的指针p的元素的父结点，成功返回相应指针，失败返回NULL  
	NodeParent(t->p,p,0);
	return(NodeParent(t->p,p,1));
}
BiTreeNode *LeftChild(BiTree *&t,BiTreeNode *&p){
	//返回二叉树t的指针p的元素的左子结点，成功返回相应指针，失败返回NULL  
	return(p->left);
}
BiTreeNode *RightChild(BiTree *&t,BiTreeNode *&p){
	//返回二叉树t的指针p的元素的右子结点，成功返回相应指针，失败返回NULL  
	return(p->left);
}
BiTreeNode *LeftSibling(BiTree *&t,BiTreeNode *&p){
	//返回二叉树t的指针p的元素的左兄弟结点，成功返回相应指针，失败返回NULL 
	BiTreeNode *q;
	NodeParent(t->p,p,0);
	q=NodeParent(t->p,p,1);
	if(p==q->left){
		return(NULL);
	}
	return(q->left);
}
BiTreeNode *RightSibling(BiTree *&t,BiTreeNode *&p){
	//返回二叉树t的指针p的元素的右兄弟结点，成功返回相应指针，失败返回NULL 
	BiTreeNode *q;
	NodeParent(t->p,p,0);
	q=NodeParent(t->p,p,1);
	if(p==q->right){
		return(NULL);
	}
	return(q->right);
}
int InsertChild(BiTree *&t,BiTreeNode *&p,int i,BiTreeNode *v){
	//给二叉树t的指针p的元素添加子系，i01分别代表左和右。成功返回0，i不合法返回1，操作不合法返回2 
	if(i==0){
		if(p->left!=NULL){
			return(2);
		}
		p->left=v;
		NodeLength(v,0);
		t->length=t->length+NodeLength(v,1);
		NodeDepth(v,0);
		t->depth=t->depth+NodeDepth(v,1);
		return(0);
	}
	if(i==1){
		if(p->right!=NULL){
			return(2);
		}
		p->right=v;
		NodeLength(v,0);
		t->length=t->length+NodeLength(v,1);
		NodeDepth(v,0);
		t->depth=t->depth+NodeDepth(v,1);
		return(0);
	}
	return(1);
}
int DeleteChild(BiTree *&t,BiTreeNode *&p,int i,BiTreeNode *&v){
	//给二叉树t的指针p的元素删除子系，i01分别代表左和右。并赋值给v，成功返回0，i不合法返回1，操作不合法返回2 
	if(i==0){
		if(p->left==NULL){
			return(2);
		}
		NodeLength(p->left,0);
		t->length=t->length-NodeLength(p->left,1);
		NodeDepth(p->left,0);
		t->depth=t->depth-NodeDepth(p->left,1);
		v=p->left;
		p->left=NULL;
		return(0);
	}
	if(i==1){
		if(p->right==NULL){
			return(2);
		}
		NodeLength(p->right,0);
		t->length=t->length-NodeLength(p->right,1);
		NodeDepth(p->right,0);
		t->depth=t->depth-NodeDepth(p->right,1);
		v=p->right;
		p->right=NULL;
		return(0);
	}
	return(1);
}
int NodeCopy(BiTreeNode *&p,BiTreeNode *&q,int zero){
	//复制二叉树枝p到q，成功返回0，失败返回1，zero为静态归零标志  
	static int err;
	if(zero==0){
		err=0;
		return(0);
	} 
	if(p!=NULL){
		q->data=p->data;
		q->left=(BiTreeNode *)malloc(sizeof(BiTreeNode));
		q->right=(BiTreeNode *)malloc(sizeof(BiTreeNode));
		if(q->left==NULL||q->right==NULL){
			err=1;
			return(1);
		}
		NodeCopy(p->left,q->left,1);
		NodeCopy(p->right,q->right,1);
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
int BiTreeCopy(BiTree *&t,BiTree *&u){
	//复制二叉树t到p，成功返回0，失败返回1
	int err;
	ClearBiTree(u);
	NodeCopy(t->p,u->p,0);
	err=NodeCopy(t->p,u->p,1);
	return(err);
}
void NodePreTraverse(BiTreeNode *&p){
	//先序遍历二叉树枝p的所有内容执行自定义操作 
	if(p!=NULL){
		//自定义操作，缺省打印
		printf("%d\n",p->data); 
		NodePreTraverse(p->left);
		NodePreTraverse(p->right);
		return;
	}
	return;
}
void PreTraverseBiTree(BiTree *&t){
	//先序遍历t的所有内容执行自定义操作 
	NodePreTraverse(t->p);
	return;
}
void NodePostTraverse(BiTreeNode *&p){
	//后序遍历二叉树枝p的所有内容执行自定义操作 
	if(p!=NULL){
		NodePostTraverse(p->left);
		NodePostTraverse(p->right);
		//自定义操作，缺省打印
		printf("%d\n",p->data);  
		return;
	}
	return;
}
void PostTraverseBiTree(BiTree *&t){
	//后序遍历t的所有内容执行自定义操作 
	NodePostTraverse(t->p);
	return;
}
void NodeInTraverse(BiTreeNode *&p){
	//中序遍历二叉树枝p的所有内容执行自定义操作 
	if(p!=NULL){
		NodeInTraverse(p->left);
		//自定义操作，缺省打印
		printf("%d\n",p->data);  
		NodeInTraverse(p->right);
		return;
	}
	return;
}
void InTraverseBiTree(BiTree *&t){
	//中序遍历t的所有内容执行自定义操作 
	NodeInTraverse(t->p);
	return;
}
int InitBiTreeQueue(BiTreeQueue *&q){
	//初始化单链表队列q并创造一个空结点。成功返回0，l空返回1，结点空返回2  
	q=(BiTreeQueue *)malloc(sizeof(BiTreeQueue));
	if(q==NULL){
		return(1);
	}
	q->p=(BiTreeQueueNode *)malloc(sizeof(BiTreeQueueNode)); 
	if(q->p==NULL){
		return(2);
	}
	q->p->next=NULL; 
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	return(0); 
}
void DestroyBiTreeQueue(BiTreeQueue *&q){
	//销毁单链表队列q  
	BiTreeQueueNode *flag,*res;
	flag=q->p;
	while(flag!=NULL){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(q);
	return;
}
int Enter(BiTreeQueue *&q,BiTreeQueueElemType e){
	//把e插入q。成功返回0，失败返回1  
	BiTreeQueueNode *j,*a;
	j=(BiTreeQueueNode *)malloc(sizeof(BiTreeQueueNode));
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
void Depart(BiTreeQueue *&q,BiTreeQueueElemType &e){
	//删除q队首元素并赋值给e。成功返回0，失败返回1  
	BiTreeQueueNode *j,*a;
	j=q->front;
	a=j->next;
	q->p->next=a;
	q->front=a;
	free(j);
	q->length--;
	return;
}
int LevelTraverseBiTree(BiTree *&t){
	//层序遍历t的所有内容执行自定义操作，成功返回0，初始化队列失败返回1，进入队列失败返回2 
	int err;
	BiTreeQueue *q;
	BiTreeQueueElemType e;
	e=t->p;
	err=InitBiTreeQueue(q);
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
		if(q->front->data->left!=NULL){
			err=Enter(q,q->front->data->left);
			if(err!=0){
				return(2); 
			}
		}
		if(q->front->data->right!=NULL){
			err=Enter(q,q->front->data->right);
			if(err!=0){
				return(2); 
			}
		}
		Depart(q,e);
	}
	DestroyBiTreeQueue(q);
	return(0);
}
#endif
