// BTree.cpp : 实现文件
#include "StdAfx.h"
#include "BTree.h"

IMPLEMENT_SERIAL(BTree,CObject,VERSIONABLE_SCHEMA|2)

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

pBTNode BTree::GetRoot()//获取根结点
{
	return root;
}

Status BTree::DeleteBTree(KeyType k)//删除结点,通过关键字k删除
{
	pBTNode p;
	int i;
	result res;
	if(root==NULL)
	{
		return ERROR;
	}
	else
	{
		res=SearchBTree(k);
		if(res.tag==FALSE)
		{
			return ERROR;
		}
		else
		{
			p=res.pt;
			i=res.i;
			exchange(p,i);
			if(p->keynum>=(M+1)/2-1)
			{
				return OK;
			}
			if(p==root)//只有一个根节点 
			{
				delete root;
				root=NULL;
				return OK;
			}
			else
			{
				while(p)
				{
					if(p==root||p->keynum>=(M+1)/2-1||p->parent==NULL)
					{
						return OK;
					}
					else
					{
						if(fix(p->parent,p)==OK)
						{
							return OK;
						}
					}
					combine(p->parent,p);
					p=p->parent;
					if((p==root||p->parent==NULL)&&p->keynum==0)
					{
						root=p->ptr[0];
						delete p;
						p=root;
						root->parent=NULL;
						return OK;
					}
				}
				return OK;
			}
		}
	}
}

void BTree::Serialize(CArchive& ar)//序列化
{
	int size,i,j,k;
	Borrow borrow;
	CObject::Serialize(ar);
	if(ar.IsStoring())//序列化
	{
		CArray<DataType> arr;
		addToArr(root,arr);
		size=arr.GetSize();
		ar<<size;
		for(i=0;i<size;i++)
		{
			DataType data;
			data=arr.GetAt(i);
			j=data.borrow.size();
			ar<<data.no<<data.name<<data.author<<data.current_num<<data.total_num<<j;
			for(k=0;k<j;k++)
			{
				ar<<data.borrow[k].no<<data.borrow[k].start_time<<data.borrow[k].end_time;
			}
		}
	}
	else//反序列化
	{
		ar>>size;
		for(i=0;i<size;i++)
		{
			DataType data;
			ar>>data.no>>data.name>>data.author>>data.current_num>>data.total_num>>j;
			for(k=0;k<j;k++)
			{
				ar>>borrow.no>>borrow.start_time>>borrow.end_time;
				data.borrow.push_back(borrow);
			}
			InsertBTree(data);
		}
	}
}

void BTree::copyData(DataType &to,DataType from)//复制关键字的信息
{
	to.no=from.no;
	to.name=from.name;
	to.author=from.author;
	to.current_num=from.current_num;
	to.total_num=from.total_num;
	to.borrow=from.borrow;
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

int BTree::position(pBTNode T)//一个结点在双亲中的位置,返回其位置 i
{
	int i=0;
	if(T==NULL)return 0;
	if(T->parent!=NULL)
	{
		while(i<=T->parent->keynum)
		{
			if(T==T->parent->ptr[i])return i;
			i++;
		}
	}
	return -1;
}

Status BTree::fix(pBTNode &T,pBTNode p)//调整树的结构
{
	int i=position(p);//取得p 在双亲中的位置
	int mid=(M+1)/2-1;//要交换的临界点
	pBTNode temp;
	int k;
	if(i>0&&T->ptr[i-1]->keynum>mid)//向左借 
	{
		temp=T->ptr[i-1];//比自己小的兄弟结点
		p->keynum++;
		for(k=p->keynum;k>1;k--)
		{
			copyData(p->key[k],p->key[k-1]);//将前面的结点后移一位
		}
		if(p->ptr[0]!=NULL)
		{
			for(k=p->keynum;k>=1;k--)
			{
				p->ptr[k]=p->ptr[k-1];//将要移动的结点的子结点向后移动
			}
		}
		copyData(p->key[1],T->key[i]);//将双亲的结点复制到根
		copyData(T->key[i],temp->key[temp->keynum]);//将小兄弟结点的最大的那个移动到双亲中
		if(temp->ptr[temp->keynum]!=NULL)//将兄弟结点的子结点也复制过来
		{
			p->ptr[0] = temp->ptr[temp->keynum];
			temp->ptr[temp->keynum]->parent=p; //修改指向双亲的结点
			temp->ptr[temp->keynum]=NULL;
		}
		temp->keynum--;
		return OK;
	}
	else if(i<T->keynum&&T->ptr[i+1]->keynum>mid)//向右借 
	{
		temp=T->ptr[i+1];
		p->keynum++;
		copyData(p->key[p->keynum],T->key[i+1]);
		copyData(T->key[i+1],temp->key[1]);
		for(k=1;k<temp->keynum;k++)
		{
			copyData(temp->key[k],temp->key[k+1]);
		}
		if(temp->ptr[0]!=NULL)
		{
			p->ptr[p->keynum]=temp->ptr[0];
			temp->ptr[0]->parent=p;
			for(k=0;k<temp->keynum;k++)
			{
				temp->ptr[k]=temp->ptr[k+1];
			}
			temp->ptr[k+1]=NULL;
		}
		temp->keynum--;
		return OK;
	}
	else
	{
		return ERROR;
	}
}

Status BTree::combine(pBTNode &T,pBTNode &p)//合并结点
{
	int k,i=position(p);//取得p 在双亲中的位置
	int mid=(M+1)/2-1;//交换的条件
	pBTNode p2;
	if(i==0)//如果是第一个位置
	{
		i=1;
		p2=T->ptr[i];
		p->keynum++;//增加一个结点
		copyData(p->key[p->keynum],root->key[i]);//将双亲的结点复制下来
		if(p2->ptr[0]!=NULL)
		{
			p->ptr[p->keynum]=p2->ptr[0]; //将兄弟的子结点也复制过来
			p2->ptr[0]->parent=p; //修改双亲
		}		
		for(k=i;k<root->keynum;k++)
		{//将双亲的结点向前移动一位
			copyData(T->key[k],T->key[k+1]);
		}
		p->keynum++;
		p->key[p->keynum]=p2->key[1];
		if(p2->ptr[1]!=NULL)
		{
			p->ptr[p->keynum]=p2->ptr[1];//将兄弟的子结点也复制过来
			p2->ptr[1]->parent=p;//修改指向双亲的结点
		}
		T->keynum--;
		delete p2;
		p2=NULL;
		for(k=1;k<=T->keynum;k++)
		{
			T->ptr[k]=T->ptr[k+1];//将双亲结点子结点向前移动
		}
		T->ptr[k+1]=NULL;
	}
	else if(i>0)
	{
		p2=T->ptr[i-1];
		p2->keynum++;
		copyData(p2->key[p2->keynum],T->key[i]);//复制根结点的值到子结点中
		if(p->ptr[0]!=NULL)
		{
			p2->ptr[p2->keynum]=p->ptr[0];
			p->ptr[0]->parent=p2;//修改指向双亲的结点
		}				
		for(k=i;k<T->keynum;k++)
		{
			copyData(T->key[k],T->key[k+1]);//将结点前移
			T->ptr[k]=T->ptr[k+1];//将子结点前移
		}
		T->ptr[k+1]=NULL;
		T->keynum--;
		delete p;
		p=p2;
	}
	return OK;
}

void BTree::exchange(pBTNode &T,int i)//与右最左结点交换
{
	pBTNode p=T;
	if(p->ptr[i]!=NULL)
	{
		p=p->ptr[i];
		while(p->ptr[0])
		{
			p=p->ptr[0];
		}
		copyData(T->key[i],p->key[1]);//交换数据
	}
	while(i<p->keynum)//将该结点后面的数据后移
	{
		copyData(p->key[i],p->key[i+1]);//将后一个数据复制到前一个数据
		i++;
	}
	p->keynum--;//删除结点
	T=p;
}

void BTree::Traverse(pBTNode T,void (BTree::*visit)(DataType e))//遍历
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)(this->*visit)(T->key[i]);
		for(i=0;i<=T->keynum;i++)Traverse(T->ptr[i],visit);
	}
}

void BTree::addToArr(pBTNode T,CArray<DataType> &arr)//加入结点到数组arr中
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)arr.Add(T->key[i]);
		for(i=0;i<=T->keynum;i++)addToArr(T->ptr[i],arr);
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
