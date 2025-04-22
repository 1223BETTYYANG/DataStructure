#include <iostream>
#include<cmath>
#include <fstream>
#include <iomanip>
#include<stdio.h>
#include <stack>
#include<queue>
using namespace std;

int PRI[128];//��ʾ���ȼ�

int height[100];//�������߶�

int MAX = -1;//���ڵ���Ŀ

string transform(string zhongzhui) {//��׺ת��׺

char c;

string tmp, houzhui;

stack<char>st;

int len = zhongzhui.length();

for (int i = 0; i < len; i++) {

c = zhongzhui[i];

if (c == '(')

st.push(c);

else if (c == ')') {

while (st.top() != '(') {

tmp = st.top();

houzhui.append(tmp);

st.pop();

}

st.pop();

}

else if (st.empty() && PRI[c] >= 1)

st.push(c);

else if (PRI[c] >= 1) {

while (!st.empty() && PRI[st.top()] >= PRI[c]) {

tmp = st.top();

houzhui.append(tmp);

st.pop();

}

st.push(c);

}

else {

tmp = c;

houzhui.append(tmp);

}

}

while (!st.empty()) {

tmp = st.top();

houzhui.append(tmp);

st.pop();

}

return houzhui;

}

struct Node {

char data;

Node* lchild, * rchild;

Node() {

data = 0;

lchild = NULL;

rchild = NULL;

}

};

Node* build_Tree(string s) 

{

char c;

int len = s.length();

Node* p=NULL;

if (len == 0) 

{

cout << "��" << endl;

return p;

}

stack<Node*>st;

for (int i = 0; i < len; i++) {

c = s[i];

if (PRI[c] >= 1) {

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

if (BT == NULL)

return 0;

int count = 0;

count = 1 + count_BT(BT->lchild) + count_BT(BT->rchild);

return count;

}

//�ݹ鷽����Ҷ�ӽڵ���Ŀ ��������ڵ�proot����������ΪNULL������Ҷ�ӽڵ㣬��Ҷ�ӽڵ���Ϊ1������1��

//��������ڵ�proot������������ΪNULL������Ҷ�ӽڵ㣬��prootΪ���ڵ������Ҷ�ӽڵ���=proot������Ҷ�ӽڵ���+proot������Ҷ�ӽڵ�����

int get_leaf_number(Node* BT)

{

if (BT == NULL)

return 0;

if (BT->lchild == NULL && BT->rchild == NULL)

return 1;

return (get_leaf_number(BT->lchild) + get_leaf_number(BT->rchild));

}

//�ݹ�

void exchange(Node* rt) {

Node* temp = NULL;

if (rt->lchild == NULL && rt->rchild == NULL)

return;

else {

temp = rt->lchild;

rt->lchild = rt->rchild;

rt->rchild = temp;

}

if (rt->lchild)

exchange(rt->lchild);

if (rt->rchild)

exchange(rt->rchild);


}

//��α���,���ö���ʵ�� 

/* �����ڵ�Ϊ�գ�ֱ�ӷ��أ�

�����ڵ�ǿգ��򽫸��ڵ���ӣ�Ȼ���ж��������ӽڵ��Ƿ�Ϊ�գ�����Ϊ�գ���ѹ����С���ʱ��������ӡ������������������С�����ѭ��ִ�У�ֱ������Ϊ�ա�*/

void levels_showBT(Node* BT) {

if (BT == NULL)

return;


queue<Node*> que;//����һ�������ָ��Ķ���

que.push(BT);


while (!que.empty()) {

Node* q = que.front();

cout << q->data << " ";

que.pop();


if (q->lchild != NULL)//que.front()�õ���ǰ��� 

{

que.push(q->lchild);

}



if (q->rchild != NULL) {

que.push(q->rchild);

}

}

cout << endl;

}

void FindWidth(Node*BT, int k)

{

if (BT == NULL)  return;

height[k]++;

if (MAX < height[k]) MAX = height[k];

FindWidth(BT->lchild, k + 1);

FindWidth(BT->rchild, k + 1);

}


//MAX��Ϊ������

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

memset(PRI, 0, sizeof(PRI[]));

PRI['+'] = PRI['-'] = 1;

PRI['*'] = PRI['/'] = 2;

string s1, s2;

cout << "������׺���ʽ" << endl;

cin >> s1;

s2 = transform(s1);

cout << s2 << endl;

Node* root = build_Tree(s2);

show(root, 1);

int tree_leaf_number = get_leaf_number(root);//�ݹ�

cout << "��������Ҷ�ڵ���Ŀ��" << tree_leaf_number << "��" << endl;

cout << "����������нڵ��������������" << endl;

exchange(root);

show(root, 1);

cout << "�����α������" << endl;

levels_showBT(root);

int k = log(count_BT(root)) / log(2);

cout << "������������" << endl;

FindWidth(root, k);

cout << MAX << endl;

return 0;

} 
