#pragma once
// BTree
#include <vector>
#include "Borrow.h"
using namespace std;
#define OK 1
#define ERROR 0
#define Status int
#define M 3

typedef int KeyType;

typedef struct Book{
	KeyType no;
	CString name;
	CString author;
	int current_num;
	int total_num;
	vector<Borrow> borrow;
}DataType;

typedef struct BTNode{
	int keynum;
	struct BTNode *parent;
	DataType key[M+1];
	struct BTNode *ptr[M+1];
}BTNode,*pBTNode;

typedef struct{
	BTNode *pt;
 	int i;
	int tag;
}result;

class BTree:public CObject
{
public:
	DECLARE_SERIAL(BTree)
	BTree();
	virtual ~BTree();
	result SearchBTree(KeyType K);//查找
	Status InsertBTree(DataType K);//将结点插入到B树中
	pBTNode GetRoot();//获取根结点
	Status DeleteBTree(KeyType k);//删除结点,通过关键字k删除
	virtual void Serialize(CArchive& ar);//序列化
private:
	pBTNode root;//B树的根节点
	void copyData(DataType &to,DataType from);//复制关键字的信息
	int Search(pBTNode p,KeyType K);//查找在某个结点中的位置	
	void Insert(pBTNode &q,int i,DataType x,pBTNode ap);//插入
	void split(pBTNode &q,int s,pBTNode &ap);//分裂结点
	void newRoot(pBTNode &T,pBTNode p,DataType x,pBTNode ap);//生成一个新的结点
	int position(pBTNode T);//一个结点在双亲中的位置,返回其位置 i
	Status fix(pBTNode &T,pBTNode p);//调整树的结构
	Status combine(pBTNode &T,pBTNode &p);//合并结点
	void exchange(pBTNode &T,int i);//与右最左结点交换
	void Traverse(pBTNode T,void (BTree::*visit)(DataType e));//遍历
	void addToArr(pBTNode T,CArray<DataType> &arr);//加入结点到数组arr中
	void destroyBTree(pBTNode &T);//销毁B树
};
