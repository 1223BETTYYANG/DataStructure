/*

设计一个c++类dRedBlackTree，它派生于抽象类dBStree（见15章 练习4）
函数find，insert，delete的时间复杂度必须是O(log n)
函数ascend的时间复杂度必须是O(n)
ps.
1）证明以上函数的时间复杂度
2）编写所有函数的代码并检验其正确性

*/

#include <iostream>
#include <iomanip>
using namespace std;
#define RED 1
#define BLACK -1
#define TT template<class T> 
TT
struct node
{
	T data;
	node* lc, * rc, * fa;
	int color;
	node(T value, int _color, node* _fa, node* _lc, node* _rc)
	{
		data = value;
		color = _color;
		fa = _fa;
		lc = _lc;
		rc = _rc;
	}
};
TT
class BSTree
{
public:
	node<T>* root;
	BSTree() { root = NULL; }
	virtual void ascend() = 0;
	virtual node<T>* find(T value) = 0;
	virtual void del(T value) = 0;
	virtual void insert(T value) = 0;
};
TT
class dredBlackTree :public BSTree<T> {
private:
	node<T>* root;
	node<T>* successor(node<T>* x);
	bool is_empty();
	void ascend(node<T>* t);
	void insert_fix_up(node<T>* x);
	void del_fix_up(node<T>* x);
	void del(node<T>* x);
	int get_color(node<T>* p)
	{
		return p == NULL ? BLACK : p->color;
	}
public:
	dredBlackTree() { root = NULL; }
	void ascend();
	void LL(node<T>* x);
	void RR(node<T>* y);
	node<T>* find(T value);
	T get_min();
	T get_max();
	void del(T value);
	void insert(T value);
};
TT
void dredBlackTree<T>::ascend(node<T>* t)
{
	if (t != NULL)
	{
		ascend(t->lc);
		cout << t->data << " ";
		ascend(t->rc);
	}
}
TT
void dredBlackTree<T>::ascend()
{
	ascend(root);
}
TT
T dredBlackTree<T>::get_min()
{
	if (is_empty())return 0;
	node<T>* p = root;
	while (p->lc != NULL)
		p = p->lc;
	cout << "min:" << p->data << endl;
	return p->data;
}
TT
T dredBlackTree<T>::get_max()
{
	if (is_empty())return 0;
	node<T>* p = root;
	while (p->rc != NULL)
		p = p->rc;
	cout << "max:" << p->data << endl;
	return p->data;
}
TT
void dredBlackTree<T>::LL(node<T>* x)
{
	if (x == NULL)return;
	node<T>* y = x->rc;
	x->rc = y->lc;
	if (y->lc != NULL)
		y->lc->fa = x;
	y->fa = x->fa;
	if (x->fa == NULL)
		root = y;
	else {
		if (x->fa->lc == x)
			x->fa->lc = y;
		else
			x->fa->rc = y;
	}
	y->lc = x;
	x->fa = y;
}
TT
void dredBlackTree<T>::RR(node<T>* y)
{
	if (y == NULL)return;
	node<T>* x = y->lc;
	y->lc = x->rc;
	if (x->rc != NULL)
		x->rc->fa = y;
	x->fa = y->fa;
	if (y->fa == NULL)
		root = x;
	else {
		if (y->fa->rc == y)
			y->fa->rc = x;
		else
			y->fa->lc = x;
	}
	x->rc = y;
	y->fa = x;
}
TT
void dredBlackTree<T>::insert(T value)
{
	if (root == NULL)
	{
		root = new node<T>(value, BLACK, NULL, NULL, NULL);
		return;
	}
	node<T>* pa = NULL;
	node<T>* x = root;
	while (x != NULL)
	{
		pa = x;
		if (value < x->data)
			x = x->lc;
		else x = x->rc;
	}
	node<T>* z = new node<T>(value, BLACK, NULL, NULL, NULL);
	z->fa = pa;
	if (value < pa->data)
		pa->lc = z;
	else
		pa->rc = z;
	insert_fix_up(z);
}
TT
void dredBlackTree<T>::insert_fix_up(node<T>* x)
{
	x->color = RED;
	while (x != NULL && x != root && get_color(x->fa) == RED)
	{
		if (x->fa == x->fa->fa->lc)
		{
			//父亲是祖父的右儿子，叔叔是左儿子
			node<T>* uncle = x->fa->fa->rc;
			if (get_color(uncle) == RED)
			{
				//1）叔叔是红色
				x->fa->color = BLACK;
				uncle->color = BLACK;
				x->fa->fa->color = RED;
				x = x->fa->fa;
			}
			else {
				//2）叔叔是黑色，x是父亲右儿子
				if (x == x->fa->rc)
				{
					x = x->fa;
					LL(x);
				}
				//3）叔叔是黑色，x是父亲左儿子
				x->fa->color = BLACK;
				x->fa->fa->color = RED;
				RR(x->fa->fa);
			}
		}
		else {
			//父亲是祖父的右儿子，叔叔是左儿子
			node<T>* uncle = x->fa->fa->lc;
			if (get_color(uncle) == RED)
			{
				//4）叔叔是红色
				x->fa->color = BLACK;
				uncle->color = BLACK;
				x->fa->fa->color = RED;
				x = x->fa->fa;
			}
			else {
				//5）叔叔是黑色，父亲是祖父左儿子
				if (x == x->fa->lc)
				{
					x = x->fa;
					RR(x);
				}
				//6）叔叔是黑色，父亲是祖父右儿子
				x->fa->color = BLACK;
				x->fa->fa->color = RED;
				LL(x->fa->fa);
			}
		}
	}
	root->color = BLACK;
}
TT
node<T>* dredBlackTree<T>::successor(node<T>* x)
{
	if (x == NULL)return NULL;
	if (x->rc != NULL)
	{
		node<T>* p = x->rc;
		while (p->lc != NULL)
			p = p->lc;
		return p;
	}
	else {
		node<T>* pa = x->fa;
		node<T>* ch = x;
		while (pa != NULL && ch == pa->rc)
		{
			ch = pa;
			pa = pa->fa;
		}
		return pa;
	}
}
TT
node<T>* dredBlackTree<T>::find(T value)
{
	node<T>* p = root;
	while (p != NULL)
	{
		if (value < p->data)
			p = p->lc;
		else if (value > p->data)
			p = p->rc;
		else return p;
	}
	return NULL;
}
TT
void dredBlackTree<T>::del(T value)
{
	node<T>* p = find(value);
	while (p != NULL)
	{
		del(p);
		p = find(value);
	}
}
TT
void dredBlackTree<T>::del(node<T>* x)
{
	if (x->lc != NULL && x->rc != NULL)
	{
		node<T>* s = successor(x);
		x->data = s->data;
		x = s;
	}
	node<T>* tmp = (x->lc != NULL ? x->lc : x->rc);
	if (tmp != NULL)
	{
		tmp->fa = x->fa;
		if (x->fa == NULL)
			root = tmp;
		else if (x == x->fa->lc)
			x->fa->lc = tmp;
		else
			x->fa->rc = tmp;
		x->lc = x->rc = x->fa = NULL;
		if (get_color(x) == BLACK)del_fix_up(tmp);
	}
	else if (x->fa == NULL)
	{
		root = NULL;
	}
	else {
		if (get_color(x) == BLACK)del_fix_up(x);
		if (x->fa != NULL)
		{
			if (x == x->fa->lc)
				x->fa->lc = NULL;
			else if (x == x->fa->rc)
				x->fa->rc = NULL;
			x->fa = NULL;
		}
	}
}
TT
void dredBlackTree<T>::del_fix_up(node<T>* x)
{
	while (x != root && get_color(x) == BLACK)
	{
		if (x == x->fa->lc)
		{
			node<T>* bro = x->fa->rc;
			if (get_color(bro) == RED)
			{
				bro->color = BLACK;
				x->fa->color = RED;
				LL(x->fa);
				bro = x->fa->rc;
			}
			if (get_color(bro->lc) == BLACK && get_color(bro->rc) == BLACK)
			{
				bro->color = RED;
				x = x->fa;
			}
			else {
				if (get_color(bro->rc) == BLACK)
				{
					bro->lc->color = BLACK;
					bro->color = RED;
					RR(bro);
					bro = x->fa->rc;
				}
				bro->color = get_color(x->fa);
				x->fa->color = BLACK;
				bro->rc->color = BLACK;
				LL(x->fa);
				x = root;
			}
		}
		else {
			node<T>* bro = x->fa->lc;
			if (get_color(bro) == RED)
			{
				bro->color = BLACK;
				x->fa->color = RED;
				RR(x->fa);
				bro = x->fa->lc;
			}
			if (get_color(bro->rc) == BLACK && get_color(bro->lc) == BLACK)
			{
				bro->color = RED;
				x = x->fa;
			}
			else {
				if (get_color(bro->lc) == BLACK)
				{
					bro->rc->color = BLACK;
					bro->color = RED;
					LL(bro);
					bro = x->fa->lc;
				}
				bro->color = get_color(x->fa);
				x->fa->color = BLACK;
				bro->lc->color = BLACK;
				RR(x->fa);
				x = root;
			}
		}
		x->color = BLACK;
	}
}
int main()
{
	BSTree<int>* p;
	dredBlackTree<int> A;
	p = &A;
	int tmp;
	cout << "请依序输入非0整数(输入0即停止)" << endl << endl;
	while (cin >> tmp)
	{
		if (tmp == 0)break;
		A.insert(tmp);
	}
	cout << "\n>>>得到自小至大的序列\n\n";
	A.ascend();
	cout << "\n\n";
	cout << "\n>>>输入删除目标\n\n";
	int a;
	cin >> a;
	A.del(a);
	cout << "\n>>>得到自小至大的序列\n\n";
	A.ascend();
	cout << "\n\n";
	cout << "\n>>>输入添加目标\n\n";
	cin >> a;
	A.insert(a);
	cout << "\n>>>得到自小至大的序列\n\n";
	A.ascend();
	cout << "\n\n";
	//system("pause");
	return 0;
}
