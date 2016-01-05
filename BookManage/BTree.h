#pragma once
// BTree
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define Status int
#define M 3

typedef int KeyType;

typedef struct Book{
	KeyType no;
	CString name;
	CString author;
	int current_num;
	int total_num;
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

class BTree
{
public:
	BTree();
	virtual ~BTree();
	result SearchBTree(KeyType K);//查找
	Status InsertBTree(DataType K);//将结点插入到B树中
	void Traverse(void (CBookManageDlg::*visit)(DataType e));//遍历
	//Status DeleteBTree(KeyType k);//删除结点,通过关键字 k 删除
private:
	pBTNode root;//B树的根节点
	void copyData(DataType &to,DataType from);//复制关键字的信息
	int Search(pBTNode p,KeyType K);//查找在某个结点中的位置	
	void Insert(pBTNode &q,int i,DataType x,pBTNode ap);//插入
	void split(pBTNode &q,int s,pBTNode &ap);//分裂结点
	void newRoot(pBTNode &T,pBTNode p,DataType x,pBTNode ap);//生成一个新的结点
	void Traverse(pBTNode T,void (CBookManageDlg::*visit)(DataType e));//遍历
	/*int position(BTree T);//一个结点在双亲中的位置,返回其位置 i
	Status fix(BTree &root,BTree p);//调整树的结构
	Status combine(BTree &root,BTree &p);//合并结点
	void exchange(BTree &T,int i);//与右最左结点交换*/
	void destroyBTree(pBTNode &T);//销毁B树
};
