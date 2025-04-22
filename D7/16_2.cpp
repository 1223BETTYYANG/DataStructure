#include <iostream>
using namespace std;
const int MAXN = 1e9;

class maxHeap
{
private:
    int size; 
    int maxElement; // 最大元素
    int minElement; // 最小元素

public:
	int* heap;
    maxHeap(int max, int min,int csize=MAXN) 
	{
        maxElement = max;
        minElement = min;
        size = 0;
        heap = new int[2*csize + 2];
        heap[0] = maxElement;
        for(int i=csize+1;i<=2*csize+1;i++)
		{
			heap[i] = minElement;
		}
    }

    ~maxHeap() {
        delete[] heap; // 释放堆数组内存空间
    }

    void push(int element)
	 {
        if (element > maxElement||element < minElement) 
		{
            cout << "_____Error_____" << endl;
            return;
        }
        heap[++size] = element; // 将元素添加到堆中
        int i = size;
        while (heap[i] > heap[i/2]) 
		{ // 上浮操作由于有了MAX则不要再判断为首个与否了~ 
            swap(heap[i], heap[i/2]);
            i = i/2;
        }
    }

    void pop()
	{
        if (size <= 0) 
		{
            cout << "empty" << endl;
            return;
        }
        heap[1] = heap[size]; // 用最后一个元素覆盖堆顶元素
        size--;
        int i = 1;
        while (true) {
            int maxIndex = i;
            if (heap[2*i] > heap[maxIndex]) {
                maxIndex = 2*i;
            }
            if (heap[2*i+1] > heap[maxIndex]) {
                maxIndex = 2*i+1;
            }

            if (maxIndex == i) {
                break; // 已满足最大堆性质
            }

            swap(heap[i], heap[maxIndex]);
            i = maxIndex;
        }
        heap[size+1] = minElement; // 更新minElement
    }
};

int main()
{
	cout<<"输入你的堆容量、最大值与最小值："<<endl;
	int n,ma,mi;
	cin>>n>>ma>>mi;
	maxHeap mh(ma,mi,n);
	for(int i=0;i<n;i++)
	{
		cin>>mi;
		mh.push(mi);
	}
	for(int i=n;i>0;i--)
	{
		for(int j=1;j<=i;j++)
		{
			cout<<mh.heap[j]<<" ";
		}
		cout<<endl;
		cout<<"____pop~pop____"<<endl;
		mh.pop();
	}
	return 0;
}
