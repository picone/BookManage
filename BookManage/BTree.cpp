// BTree.cpp : 实现文件
#include "StdAfx.h"
#include "BookManageDlg.cpp"
#include "BTree.h"

BTree::BTree()
{
	root=NULL;//初始化变量
}

BTree::~BTree()
{
	destroyBTree(root);//析构时释放内存
}

result BTree::SearchBTree(KeyType K)
{
	pBTNode p=root,q=NULL;
	int found=FALSE,i=0;
	result res;
	// 初始化，p指向待查结点，q指向p的双亲
	while(p!=NULL&&found==FALSE)
	{
 		i=Search(p,K);
		// 找到待查关键字
		if (i>0&&p->key[i].no==K)
		{
			found=TRUE;
		}
		else
		{
			q=p;
			p=p->ptr[i];
		}
	}
	res.pt=found?p:q;
	res.i=i;
	res.tag=found;
	return res;
}

Status BTree::InsertBTree(DataType data)
{
	//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B树。
	pBTNode q=NULL,ap=NULL;
	result res;
	int i,s;
	int finished=FALSE,needNewRoot=FALSE;
	DataType x;
	//如果 T 结点为空就生成一个新的结点
	if(root==NULL)
	{
		newRoot(root,NULL,data,NULL);
	}
	else
	{
		//查找元素 k 在树中的位置
		res=SearchBTree(data.no);//查找到包含元素 k 的结点
		if(res.tag==TRUE)
		{
			return FALSE;
		}
		else
		{
			q=res.pt;
			i=res.i;
			x=data;
			while(needNewRoot==FALSE&&finished==FALSE)
			{
				Insert(q,i,x,ap);
				if(q->keynum<M)
				{
					finished=TRUE; 
				}
				else
				{
					s=(M+1)/2;
					split(q,s,ap);
					x=q->key[s];
					if(q->parent)
					{
						q=q->parent;
						i=Search(q,x.no);//在双亲结点*q中查找x的插入位置
					}
					else
					{
						needNewRoot=TRUE;
					}
				}
			}
			if(needNewRoot==TRUE)newRoot(root,q,x,ap);//生成含信息(t,x,ap)的新结点root
		}
	}
	return OK;
}

void BTree::Traverse(void (CBookManageDlg::*visit)(DataType e))//遍历
{
	Traverse(root,visit);
}

void BTree::copyData(DataType &to,DataType from)//复制关键字的信息
{
	to.no=from.no;
	to.name=from.name;
	to.author=from.author;
	to.current_num=from.current_num;
	to.total_num=from.total_num;
}

int BTree::Search(pBTNode p,KeyType K)//查找在某个结点中的位置
{
	if(p==NULL)return -1;
	int i=0;
	for(i=0;i<p->keynum&&p->key[i+1].no<=K;i++);
	return i;
}

void BTree::Insert(pBTNode &q,int i,DataType x,pBTNode ap)//插入
{
	int n=q->keynum;
	for(int j=n;j>i;j--)//腾出空间
	{
		copyData(q->key[j + 1],q->key[j]);
		q->ptr[j+1]=q->ptr[j];
	}
	copyData(q->key[i+1],x);
	q->ptr[i+1]=ap;
	if(ap)ap->parent=q;
	q->keynum++;
}

void BTree::split(pBTNode &q,int s,pBTNode &ap)//分裂结点
{
	int i,j,n=q->keynum;
	ap=new BTNode;
	ap->ptr[0]=q->ptr[s];
	for (i = s + 1,j = 1; i <= n; i++,j++)
	{
		copyData(ap->key[j],q->key[i]);
		ap->ptr[j]=q->ptr[i];
	}
	ap->keynum=n-s;
	ap->parent=q->parent;
	for(i=0;i<=n-s;i++)
	{
		if(ap->ptr[i]!=NULL)ap->ptr[i]->parent=ap;
	}   
	q->keynum=s-1;
}

void BTree::newRoot(pBTNode &T,pBTNode p,DataType x,pBTNode ap)//生成一个新的结点
{
	T=new BTNode;
	T->keynum=1;
	T->ptr[0]=p;//设置左边结点的树根
	T->ptr[1]=ap;//设置右边的树根
	copyData(T->key[1],x);//将 x 元素的结点值复制到 T 的第一个元素中
	//当孩子不空的时候就设置当前结点为孩子的双亲
	if(p!=NULL)p->parent=T;
	if(ap!=NULL)ap->parent=T;
	T->parent=NULL;
}

void Traverse(pBTNode T,void (CBookManageDlg::*visit)(DataType e))//遍历
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)visit(T->key[i]);
		for(i=0;i<=T->keynum;i++)Traverse(T->ptr[i],visit);
	}
}

void BTree::destroyBTree(pBTNode &T)
{
	int i; 
	pBTNode p;
	if(T!=NULL)
	{
		p=T;
		for(i=0;i<=T->keynum;i++)destroyBTree(T->ptr[i]);
		delete p;
		T=NULL;
	}
}
