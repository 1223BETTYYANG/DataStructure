#include<iostream>
#include<ostream>
using namespace std;

template <typename T>
class Node 
{
	public:
	Node(T da) : data(da), pre(NULL), next(NULL) {}
	T data;
	Node<T> *pre;
	Node<T> *next;
};

template <typename T>
class extendedChain 
{
public:
    Node<T>* head;
    Node<T>* tail;
    int listSize;

    extendedChain() : head(NULL),tail(NULL), listSize(1) {}
    
  void insert(const T& item) 
    {
        Node<T>* newNode = new Node<T>{item};
        if (!head) 
        {
            head = tail = newNode;
            tail->next=head;
            head->pre=tail;
            return;
        }
        newNode->pre =tail;
        tail->next=newNode;
        tail=newNode;
        tail->next = head;
        head->pre=tail;
        listSize++;
    }
   int size()const
    {
        return listSize;
    }
    Node<T>* getFirstNode()const
    {
        return head;
    }
    Node<T>* getLastNode()const
    {
        return tail;
    }
    Node<T>* get(int k)
    {
    	Node<T>* n=head;
    	for(int i=0;i<k;i++)
    	{
    		n=n->next;
    	}
    	return n;
    }
  //  void Output(ostream& out) const;
    extendedChain<T>& split()
    {
    	bool flag[listSize];
    	for(int i=0;i<listSize;i++)
    	{
    		if(get(i)->data%2==0)
    		{
    			flag[i]=1; 
    		}
    		else
    		{
    			flag[i]=0;
    		}
    	}
    	//test
    	for(int i=0;i<listSize;i++)
    	{
    		cout<<flag[i]<<" ";
    		cout<<endl;
    	}
    	
    	Node<T>* t_1=head;
    	Node<T>* t_2=tail;
    	Node<T>* a=head;
   		Node<T>* a1=head;
    	Node<T>* b=tail;
    	Node<T>* b1=tail;
    	int judge1=0,judge2=0;
		for(int j=0;j<listSize;j++)
		{
	
			if(flag[j]==1)
			{
			if(a==head&&judge1==0)
			{
				a=t_1;
				a1=t_1;
				judge1=1;
				//test
				cout<<a1->data<<"**"<<endl;
			}
			else if(a!=head||(a==head&&judge1!=0))
			{
				a->next=t_1;
				a=a->next; 
				//test
				cout<<a1->data<<"***"<<endl;
			}
			}
			
			if(flag[listSize-1-j]==0)
			{
				
				//test
				cout<<listSize-1-j<<endl;
			if(b==tail&&judge2==0)
			{
				b=t_2;
				b1=t_2;
				judge2=1;
				//test
				cout<<b1->data<<endl;
			}
			else if(b!=tail||(b==tail&&judge2!=0))
			{
				b->pre=t_2;
				b=b->pre;
				//test
				cout<<b1->data<<endl;
			}
			}
			
			/*	else
				{
					if(flag[listSize-1]==1)
					{
						a->next=t_1;
						a=a->next; 
						a->next=NULL;
					}
					else
					{
						a->next=NULL; 
					}
					if(flag[listSize-1-j]==0)
					{
						b->pre=t_2;
						b=b->pre;
						b->pre=NULL;
					}
					else
					{
						b->pre=NULL;
					}
				}*/
				if(j==listSize-1)
				{
					break;
				} 
				t_1=t_1->next;
				t_2=t_2->pre;
			}
	
			a->next=NULL; 
			b->pre=NULL;

			tail=b1;
			head=a1;
			head->pre=b1;
		
			return *this;
    	}
    	/*Node<T>* aNode = a.getFirstNode();
    	Node<T>* bNode = b.getFirstNode();
		Node<T>* cNode=head;
    while(cNode!=NULL)
	{
		if(cNode->data%2==0)
		{
			a.insert(cNode->data);
		}
		else
		{
			b.insert(cNode->data);
		}
		cNode=cNode->next;
	} 
	return *this;*/
};
/*template<class T>
void extendedChain<T>::Output(ostream& out) const
{
   Node<T> *current;
   for (current = head; current!=tail; current = current->next)
      out << current->data << "  ";
}

template <class T>
ostream& operator<<(ostream& out, const extendedChain<T>& x)
{
     x.Output(out);    
	 return out;
}
*/

int main()
{
	//extendedChain<int> a,b;
	extendedChain<int> c;

	for(int i=1;i<=9;i++)
	{
		c.insert(i); 
	}
	c=c.split();
	/*)int aNode = a.size();
    int bNode = b.size();
    int cNode = c.size();*/
	Node<int>* temp = c.getFirstNode();
	//int i=0;
	cout <<temp->data<<" ";
    while (temp->next!=NULL) 
    {
        temp = temp->next;
        cout <<temp->data<<" ";
        //i++;
    }
    cout<<endl;
    temp = c.getLastNode();
    //i=0;
    cout <<temp->data<< " ";
    while (temp->pre!=NULL) 
    {
        temp = temp->pre;
        cout <<temp->data<< " ";
       // i++;
    }
    cout<<endl;
    /*temp = c.getFirstNode();
    i=0;
    while (i<= cNode) 
    {
        cout <<temp->data<< " ";
        temp = temp->next;
        i++;
    }
    cout << endl;*/
    
   	return 0;
}

