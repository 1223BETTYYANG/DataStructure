#include <iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;

#define LL long long

const int MAXN = 1e9;

template<class T>

class MaxHeap {

public:

MaxHeap(int MaxHeapSize = MAXN);

//~MaxHeap(){delete [] heap;heap=NULL;}

int Size()const { return CurrentSize; }

T Max() {

if (CurrentSize == 0)cout << "空" << endl;

return heap[1];

}

MaxHeap<T>& Push(const T& x);

MaxHeap<T>& Pop(T& x);

void Initialize(T a[], int size, int ArraySize);

void show();

private:

int CurrentSize, MaxSize;

T* heap;

};

template<class T>

MaxHeap<T>::MaxHeap(int MaxHeapSize) {//初始化

MaxSize = MaxHeapSize;

heap = new T[MaxSize + 1];//有一个“哨兵”,检查是否越界

CurrentSize = 0;

}

template<class T>

MaxHeap<T>& MaxHeap<T>::Push(const T& x) 
{//加元素(没写增加数组长度)
if (CurrentSize == MaxSize)
{
cout << "error" << endl;

}
int i = ++CurrentSize;
while (i != 1 && x > heap[i / 2])
{
	heap[i] = heap[i / 2];//元素向下移动
	i /= 2;//i移向双亲
}
heap[i] = x;//到合适位置 插入
return *this;
}

template<class T>

MaxHeap<T>& MaxHeap<T>::Pop(T& x) {//删除元素

if (CurrentSize == 0) 
{
	cout << "空" << endl;
	return *this;
}
x = heap[1];//删除最大元素
T y = heap[CurrentSize--];//删除最后一个元素 重建堆
int i = 1, ci = 2;//ci是i的孩子节点
while (ci <= CurrentSize) 
{
if (ci < CurrentSize && heap[ci] < heap[ci + 1])
{
	ci++;//heap[ci]是i的更大的孩子
}
if (y >= heap[ci])
{
	break;//判断是否可以把删除的元素放在当前位置
}
heap[i] = heap[ci];//孩子向上移动
i = ci;//向下一层寻找位置
ci *= 2;
}
heap[i] = y;
return *this;
}

template<class T>

void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) {//初始化

delete[] heap;

heap = a;//堆元素

CurrentSize = size;

MaxSize = ArraySize;

for (int i = CurrentSize / 2; i >= 1; i--) {

T y = heap[i];

int c = 2 * i;

while (c <= CurrentSize) {

if (c < CurrentSize && heap[c] < heap[c + 1])c++;

if (y >= heap[c])break;

heap[c / 2] = heap[c];

c *= 2;

}

heap[c / 2] = y;

}

}

template<class T>

void MaxHeap<T>::show() {

if (CurrentSize == 0) {

cout << "空" << endl;

return;

}

for (int i = 1; i < CurrentSize; i++)cout << heap[i] << " ";

cout << heap[CurrentSize] << endl;

}

template<class T>

void HeapSort(T a[], int n) {

MaxHeap<T> H(1);

H.Initialize(a, n, n);

T x;

for (int i = n - 1; i >= 1; i--) {

H.Pop(x);

a[i + 1] = x;

}

}


const int INF = 0x3f3f3f3f;//无穷大

template<class T>

class MaxHeap_ {

public:

MaxHeap_(int n = MAXN, int maxx = 0, int minn = 0);

//~MaxHeap(){delete [] heap;heap=NULL;}

int Size()const { return CurrentSize; }

T Max() {

if (CurrentSize == 0)cout << "空" << endl;

return heap[1];

}

MaxHeap_<T>& Push(const T& x);

MaxHeap_<T>& Pop(T& x);

void show();

private:

int CurrentSize, MaxSize;

T maxElem, minElem;

T* heap;

};

template<class T>

MaxHeap_<T>::MaxHeap_(int n, int maxx, int minn) {

MaxSize = 2 * n + 1;

heap = new T[MaxSize + 1];

CurrentSize = 0;

maxElem = maxx;

minElem = minn;

heap[0] = maxElem;//heap[0]是极大值，heap[n+1:2n+1]是极小值

for (int i = n + 1; i <= 2 * n + 1; i++)heap[i] = minElem;

}

template<class T>

MaxHeap_<T>& MaxHeap_<T>::Push(const T& x) {

if (CurrentSize == MaxSize)cout << "满" << endl;

int i = ++CurrentSize;

while (x > heap[i / 2]) {//最后x都小于heap[1/2]=heap[0]，跳出循环，push到根节点

heap[i] = heap[i / 2];

i /= 2;

}

heap[i] = x;

return *this;

}

template<class T>

MaxHeap_<T>& MaxHeap_<T>::Pop(T& x) {

if (CurrentSize == 0) {

cout << "空" << endl;

return *this;

}

x = heap[1];

T y = heap[CurrentSize];

heap[CurrentSize--] = -INF;

int i = 1, ci = 2;

while (heap[ci] > y) {

if (heap[ci] < heap[ci + 1])ci++;

heap[i] = heap[ci];

i = ci;

ci *= 2;

}

heap[i] = y;

return *this;

}

template<class T>

void MaxHeap_<T>::show() {

if (CurrentSize == 0) {

cout << "空" << endl;

return;

}

for (int i = 1; i < CurrentSize; i++)cout << heap[i] << " ";

cout << heap[CurrentSize] << endl;

}

template<class T>

void show(T a[], int n) {

for (int i = 1; i < n; i++)cout << a[i] << " ";

cout << a[n] << endl;

return;

}


int main() {

clock_t t1, t2;

int n;

cout << "请输入数字个数n：";

cin >> n;

int* a = new int[n];

int* b=new int [n];

srand(time(NULL));

for (int i = 1; i <= n; i++) {

a[i] = rand() % INF;

b[i] = a[i];

}

MaxHeap<int> A(n);

MaxHeap_<int> B(n, INF, -INF);

//show(a,n);


cout << endl << "-----测试Push方法-----" << endl << endl;

t1 = clock();

for (int i = 1; i <= n; i++)A.Push(a[i]);

//A.show();

t2 = clock();

cout << "方法一用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


t1 = clock();

for (int i = 1; i <= n; i++)B.Push(a[i]);

//B.show();

t2 = clock();

cout << "方法二用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


cout << endl << "-----测试Pop方法-----" << endl << endl;

t1 = clock();

for (int i = 1; i <= n; i++)A.Pop(a[i]);

//A.show();

t2 = clock();

cout << "方法一用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


t1 = clock();

for (int i = 1; i <= n; i++) {

B.Pop(a[i]);

//B.show();

}

t2 = clock();

cout << "方法二用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


return 0;

delete[]a;

delete[]b;

} 
