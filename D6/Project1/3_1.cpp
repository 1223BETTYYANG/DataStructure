#include <iostream>
#include<cmath>
#include <fstream>
#include <iomanip>
#include<stdio.h>
#include <stack>
#include<queue>
using namespace std;

int PRI[100];

int height[100];

int MAX = -1;//最多节点数目

string transform(string zhong)
{
	char c;
	string tmp, hou;
	stack<char>st;
	int len = zhong.length();
	for (int i = 0; i < len; i++)
	{
		c = zhong[i];
		if (c == '(')
			st.push(c);
		else if (c == ')')
		{
			while (st.top() != '(')
			{
				tmp = st.top();
				hou.append(tmp);
				st.pop();
			}
			st.pop();
		}
		else if (st.empty() && PRI[c] >= 1)
		{
			st.push(c);
		}
		else if (PRI[c] >= 1)
		{
			while (!st.empty() && PRI[st.top()] >= PRI[c])
			{
				tmp = st.top();
				hou.append(tmp);
				st.pop();
			}
			st.push(c);
		}
		else
		{
			tmp = c;
			hou.append(tmp);
		}

	}
	while (!st.empty())
	{
		tmp = st.top();
		hou.append(tmp);
		st.pop();
	}
	return hou;
}

struct Node
{
	char data;
	Node* lchild, * rchild;
	Node()
	{
		data = 0;
		lchild = NULL;
		rchild = NULL;
	}
};

Node* build_Tree(string s)

{
	char c;
	int len = s.length();
	Node* p = NULL;
	if (len == 0)
	{
		cout << "empty" << endl;
		return p;
	}
	stack<Node*>st;
	for (int i = 0; i < len; i++)
	{
		c = s[i];
		if (PRI[c] >= 1)
		{
			p = new Node;
			Node* tmp = st.top();
			p->rchild = tmp;
			st.pop();
			tmp = st.top();
			p->lchild = tmp;
			st.pop();
			p->data = c;
			st.push(p);
		}
		else {
			p = new Node;
			p->data = c;
			st.push(p);
		}
	}
	return p;
}
int count_BT(Node* BT)

{
	if (BT == NULL)return 0;
	int count = 0;
	count = 1 + count_BT(BT->lchild) + count_BT(BT->rchild);
	return count;
}
int get_leaf_number(Node* BT)
{
	if (BT == NULL)return 0;
	if (BT->lchild == NULL && BT->rchild == NULL)
	return 1;
	return (get_leaf_number(BT->lchild) + get_leaf_number(BT->rchild));
}

void exchange(Node* rt) 
{
	Node* temp = NULL;
	if (rt->lchild == NULL && rt->rchild == NULL)
		return;
	else 
	{
		temp = rt->lchild;
		rt->lchild = rt->rchild;
		rt->rchild = temp;
	}
	if (rt->lchild)
		exchange(rt->lchild);
	if (rt->rchild)
		exchange(rt->rchild);
}
void levels_showBT(Node* BT) 
{
	if (BT == NULL)	return;
	queue<Node*> que;//构造一个树结点指针的队列
	que.push(BT);
	while (!que.empty()) {
		Node* q = que.front();
		cout << q->data << " ";
		que.pop();
		if (q->lchild != NULL)//que.front()拿到最前结点 
		{
			que.push(q->lchild);
		}

		if (q->rchild != NULL) 
		{
			que.push(q->rchild);
		}
	}
	cout << endl;
}
void FWidth(Node* BT, int k)
{
	if (BT == NULL)  return;
	height[k]++;
	if (MAX < height[k]) MAX = height[k];
	FWidth(BT->lchild, k + 1);
	FWidth(BT->rchild, k + 1);

}


void show(Node* x, int d) {

	if (x != NULL) {

		show(x->rchild, d + 1);

		cout.setf(ios::right);

		cout << setw(3 * d) << " ";

		cout << x->data << endl;

		show(x->lchild, d + 1);

	}

}

int main()
{
	memset(PRI, 0, sizeof(PRI));
	PRI['+'] = PRI['-'] = 1;
	PRI['*'] = PRI['/'] = 2;
	string s1, s2;
	cout << "输入表达式~" << endl;
	cin >> s1;
	s2 = transform(s1);
	Node* root = build_Tree(s2);
	cout << "------this tree------" << endl;
	show(root, 1);
	cout << "------this tree------" << endl;
	int tree_leaf_number = get_leaf_number(root);
	cout << "------number of leaves------" << endl;
	cout << tree_leaf_number << endl;
	cout << "------number of leaves------" << endl;
	cout << "------exchange~------" << endl;
	exchange(root);
	show(root, 1);
	cout << "------exchange~------" << endl;
	cout << "------遍历on Array级------" << endl;
	levels_showBT(root);
	int k = log(count_BT(root)) / log(2);
	cout << "------遍历on Array级------" << endl;
	cout << "------width~------" << endl;
	FWidth(root, k);
	cout << MAX << endl;
	cout << "------width~------" << endl;
	return 0;

}