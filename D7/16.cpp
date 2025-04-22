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

if (CurrentSize == 0)cout << "��" << endl;

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

MaxHeap<T>::MaxHeap(int MaxHeapSize) {//��ʼ��

MaxSize = MaxHeapSize;

heap = new T[MaxSize + 1];//��һ�����ڱ���,����Ƿ�Խ��

CurrentSize = 0;

}

template<class T>

MaxHeap<T>& MaxHeap<T>::Push(const T& x) 
{//��Ԫ��(ûд�������鳤��)
if (CurrentSize == MaxSize)
{
cout << "error" << endl;

}
int i = ++CurrentSize;
while (i != 1 && x > heap[i / 2])
{
	heap[i] = heap[i / 2];//Ԫ�������ƶ�
	i /= 2;//i����˫��
}
heap[i] = x;//������λ�� ����
return *this;
}

template<class T>

MaxHeap<T>& MaxHeap<T>::Pop(T& x) {//ɾ��Ԫ��

if (CurrentSize == 0) 
{
	cout << "��" << endl;
	return *this;
}
x = heap[1];//ɾ�����Ԫ��
T y = heap[CurrentSize--];//ɾ�����һ��Ԫ�� �ؽ���
int i = 1, ci = 2;//ci��i�ĺ��ӽڵ�
while (ci <= CurrentSize) 
{
if (ci < CurrentSize && heap[ci] < heap[ci + 1])
{
	ci++;//heap[ci]��i�ĸ���ĺ���
}
if (y >= heap[ci])
{
	break;//�ж��Ƿ���԰�ɾ����Ԫ�ط��ڵ�ǰλ��
}
heap[i] = heap[ci];//���������ƶ�
i = ci;//����һ��Ѱ��λ��
ci *= 2;
}
heap[i] = y;
return *this;
}

template<class T>

void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) {//��ʼ��

delete[] heap;

heap = a;//��Ԫ��

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

cout << "��" << endl;

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


const int INF = 0x3f3f3f3f;//�����

template<class T>

class MaxHeap_ {

public:

MaxHeap_(int n = MAXN, int maxx = 0, int minn = 0);

//~MaxHeap(){delete [] heap;heap=NULL;}

int Size()const { return CurrentSize; }

T Max() {

if (CurrentSize == 0)cout << "��" << endl;

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

heap[0] = maxElem;//heap[0]�Ǽ���ֵ��heap[n+1:2n+1]�Ǽ�Сֵ

for (int i = n + 1; i <= 2 * n + 1; i++)heap[i] = minElem;

}

template<class T>

MaxHeap_<T>& MaxHeap_<T>::Push(const T& x) {

if (CurrentSize == MaxSize)cout << "��" << endl;

int i = ++CurrentSize;

while (x > heap[i / 2]) {//���x��С��heap[1/2]=heap[0]������ѭ����push�����ڵ�

heap[i] = heap[i / 2];

i /= 2;

}

heap[i] = x;

return *this;

}

template<class T>

MaxHeap_<T>& MaxHeap_<T>::Pop(T& x) {

if (CurrentSize == 0) {

cout << "��" << endl;

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

cout << "��" << endl;

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

cout << "���������ָ���n��";

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


cout << endl << "-----����Push����-----" << endl << endl;

t1 = clock();

for (int i = 1; i <= n; i++)A.Push(a[i]);

//A.show();

t2 = clock();

cout << "����һ��ʱ�� " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


t1 = clock();

for (int i = 1; i <= n; i++)B.Push(a[i]);

//B.show();

t2 = clock();

cout << "��������ʱ�� " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


cout << endl << "-----����Pop����-----" << endl << endl;

t1 = clock();

for (int i = 1; i <= n; i++)A.Pop(a[i]);

//A.show();

t2 = clock();

cout << "����һ��ʱ�� " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


t1 = clock();

for (int i = 1; i <= n; i++) {

B.Pop(a[i]);

//B.show();

}

t2 = clock();

cout << "��������ʱ�� " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


return 0;

delete[]a;

delete[]b;

} 
