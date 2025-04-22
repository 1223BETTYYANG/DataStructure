#include <iostream>
#include <cstring> 

using namespace std;

class Bqueue
{
	public:
		int*arr;
		int size;
		int front;
		int rear;
		Bqueue(int MaxSize=10)
		{
			size=MaxSize+1;
			arr=new int[size];
			front=rear=0;
		}
		~Bqueue()
		{
			delete []arr;
		}
		bool IsEmpty()
		{
			return front==rear;
		}
		bool IsFull()
		{
			return front==(rear+1)%size;
		}
		int Left()
		{
			if(IsEmpty())
			{
				cout<<"Empty"<<endl;
				return -1;
			}
			return arr[front];
		}
		int Right()
		{
			if(IsEmpty())
			{
				cout<<"Empty"<<endl;
				return -1;
			}
			return arr[(rear-1+size)%size];
		}
		void AddLeft(int data)
		{
			if(IsFull())
			{
				cout<<"Full"<<endl;
				return;
			}
			front=(front-1+size)%size;
			arr[front]=data;
		}
		void AddRight(int data)
		{
			if(IsFull())
			{
				cout<<"Full"<<endl;
				return;
			}
			arr[rear]=data;
			rear=(rear+1)%size; 
		}
		void DeleteLeft()
		{
			if(IsEmpty())
			{
				cout<<"Empty"<<endl;
				return;
			}
			front=(front+1+size)%size;
		}
		void DeleteRight()
		{
			if(IsEmpty())
			{
				cout<<"Empty"<<endl;
				return;
			}
			rear=(rear-1+size)%size;
		}
		void Print()
		{
			if(IsEmpty())
			{
				cout<<""<<endl;
			}
			else
			{
				int n=front;
				while(n!=rear)
				{
					cout<<arr[n]<<" ";
					n=(n+1)%size;
				}
				cout<<endl;
			}
		}
		
};

int main()
{
	Bqueue q;
	string s;
	int n;
	cin>>s;
	while(1)
	{
		if (s == "End")
		{
			break;
		}
		else if (s == "DeleteRight")
		{
			q.DeleteRight();
			q.Print();
		}
		else if (s== "DeleteLeft" )
		{
			q.DeleteLeft();
			q.Print();
		}
		else if(s=="IsFull")
		{
			if(q.IsFull())cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
		else if(s=="IsEmpty")
		{
			if(q.IsEmpty())cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
		else
		{
			cin >> n;
			if(s=="AddLeft")
			{
				q.AddLeft(n);
				q.Print();
			}
			else if(s=="AddRight")
			{
				q.AddRight(n);
				q.Print();
			}
			else
			{
				cout<<"Wrong"<<endl;
			} 
		}
		cin>>s;
	}
	cout<<"-------------finished-------------"<<endl;
	return 0;
}

