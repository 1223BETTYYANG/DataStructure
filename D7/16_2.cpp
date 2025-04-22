#include <iostream>
using namespace std;
const int MAXN = 1e9;

class maxHeap
{
private:
    int size; 
    int maxElement; // ���Ԫ��
    int minElement; // ��СԪ��

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
        delete[] heap; // �ͷŶ������ڴ�ռ�
    }

    void push(int element)
	 {
        if (element > maxElement||element < minElement) 
		{
            cout << "_____Error_____" << endl;
            return;
        }
        heap[++size] = element; // ��Ԫ����ӵ�����
        int i = size;
        while (heap[i] > heap[i/2]) 
		{ // �ϸ�������������MAX��Ҫ���ж�Ϊ�׸������~ 
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
        heap[1] = heap[size]; // �����һ��Ԫ�ظ��ǶѶ�Ԫ��
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
                break; // ��������������
            }

            swap(heap[i], heap[maxIndex]);
            i = maxIndex;
        }
        heap[size+1] = minElement; // ����minElement
    }
};

int main()
{
	cout<<"������Ķ����������ֵ����Сֵ��"<<endl;
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
