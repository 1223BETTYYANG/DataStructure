#include <iostream>
#include<cmath>
#include <fstream>
#include <iomanip>
#include<stdio.h>
#include <stack>
#include<queue>
using namespace std;

int PRI[128];//表示优先级

int height[100];//二叉树高度

int MAX = -1;//最多节点数目

string transform(string zhongzhui) {//中缀转后缀

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

cout << "空" << endl;

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

//递归方法求叶子节点数目 如果给定节点proot左右子树均为NULL，则是叶子节点，且叶子节点数为1，返回1；

//如果给定节点proot左右子树不都为NULL，则不是叶子节点，以proot为根节点的子树叶子节点数=proot左子树叶子节点数+proot右子树叶子节点数。

int get_leaf_number(Node* BT)

{

if (BT == NULL)

return 0;

if (BT->lchild == NULL && BT->rchild == NULL)

return 1;

return (get_leaf_number(BT->lchild) + get_leaf_number(BT->rchild));

}

//递归

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

//层次遍历,利用队列实现 

/* 若根节点为空，直接返回；

若根节点非空，则将根节点入队，然后判断其左右子节点是否为空，若不为空，则压入队列。此时将根结点打印输出，并将根结点出队列。依次循环执行，直到队列为空。*/

void levels_showBT(Node* BT) {

if (BT == NULL)

return;


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


//MAX即为所求宽度

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

cout << "输入中缀表达式" << endl;

cin >> s1;

s2 = transform(s1);

cout << s2 << endl;

Node* root = build_Tree(s2);

show(root, 1);

int tree_leaf_number = get_leaf_number(root);//递归

cout << "二叉树中叶节点数目有" << tree_leaf_number << "个" << endl;

cout << "输出交换所有节点左右子树后的树" << endl;

exchange(root);

show(root, 1);

cout << "输出层次遍历结果" << endl;

levels_showBT(root);

int k = log(count_BT(root)) / log(2);

cout << "输出二叉树宽度" << endl;

FindWidth(root, k);

cout << MAX << endl;

return 0;

} 
