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
		{	p = new Node;
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

	cout << s2 << endl;

	Node* root = build_Tree(s2);
	cout << "------------" << endl;
	show(root, 1);
	cout << "------------" << endl;
	return 0;

}
