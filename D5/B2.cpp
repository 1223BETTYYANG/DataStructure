#include <iostream>
#include <cstdlib>
#include <ctime>



using namespace std;
#define INF 0x3f3f3f3f
const int Max = 11;
class Node 
{
public:
	int data;
	Node* next;
};

class hashChainsWithTail
{
public:
	Node* HT[Max];
	Node* tail;
	hashChainsWithTail()
	{
		tail = new Node;
		tail->next = NULL;
		tail->data = INF;
		for (int i = 0; i < Max; i++)
		{
			HT[i] = new Node;
			HT[i]->next = tail;//同一个尾节点
		}
	}
	~hashChainsWithTail() 
	{
		delete tail;
		for (int i = 0; i < Max; i++)
		{
			delete[] HT[i];
		}
	}

	int hash(int v);

	bool vis(int v);

	void insert(int v);

	void show();

	bool search1(int v);

	};

int hashChainsWithTail::hash(int v) 

{

	int tmp = 0;

	tmp = v * 33 % Max;

	return tmp;

}

bool hashChainsWithTail::vis(int v) 
{

	Node* p;

	int index = hash(v);

	p = HT[index];

	for (p = p->next; p->data <= v; p = p->next);

	if (p->data == v)return true;

	return false;

}

void hashChainsWithTail::insert(int v) 
{

	Node* p, * tmp;

	int index = hash(v);//应该插在哪个位置  

	if (vis(v))return;//本身有这个元素 不用插入

	p = HT[index];

	if (p->next == tail) //这个位置没元素

	{

		tmp = new Node;

		tmp->data = v;

		tmp->next = tail;

		p->next = tmp;

	}

	else //这个位置本来有元素
	{
		for (p = HT[index]; p->next->data < v; p = p->next);//p->next->data < v 顺序插入才能用这个遍历条件

		tmp = new Node;

		tmp->data = v;

		tmp->next = p->next;//把tmp插到p后面

		p->next = tmp;

	}

}

bool hashChainsWithTail::search1(int v) 

{

	int index = hash(v);

	Node* p;

	p = HT[index];

	for (p = p->next; p->data < v; p = p->next);

	if (p->data != INF) 
	{

		cout<<v<<"此处对应的数据："<<p->data<<endl;

		return true;

	}

cout<<"找不到捏~"<<endl;

return false;

}

void hashChainsWithTail::show() 

{

	Node* p;

	for (int i = 0; i < Max; i++) 

	{

		if (HT[i] != NULL)

		{
			p = HT[i];

			for (p = p->next; p->data < INF; p = p->next)

			cout << p->data << " ";

			cout << endl;
		}

	}


}

class HashTable {
   public:
      HashTable(); 
      ~HashTable() {delete [] ht;  delete [] neverUsed;}
      bool Search(const int& k, int& e) const;
      HashTable& Insert(const int& e);
      int hSearch(const int& k) const;
      int m; // hash function divisor
      int *ht; // hash table array
      int *newht;
      bool *neverUsed; // 1D array
      bool *newneverUsed; 
};

HashTable::HashTable()
{// Constructor.
   m = Max;

   // allocate hash table arrays
   ht = new int [m];
   neverUsed = new bool [m];

   // set all buckets to empty
   for (int i = 0; i < m; i++)
      neverUsed[i] = true;
}

int HashTable::hSearch(const int& k) const
{// Search an open addressed table.
 // Return location of k if present.
 // Otherwise return insert point if there is space.
   int i = k*33 % m; // home bucket
   int j = i;     // start at home bucket
   do {
      if (neverUsed[j] || ht[j] == k) return j;
      j = (j + 1) % m;  // next bucket
      } while (j != i); // returned to home?

   return j;  // table full
}


bool HashTable::Search(const int& k, int& e) const
{// Put element that matches k in e.
 // Return false if no match.
   int b = hSearch(k);
   if (neverUsed[b] || ht[b] != k) 
   {
   		cout<<"找不到捏~"<<endl;
		return false; 
   }
   e = ht[b];
   cout<<b<<"此处对应的数据："<<e<<endl;
   return true;
}

HashTable& HashTable::Insert(const int& e)
{// Hash table insert.
   int k = e; // extract key
   int b = hSearch(k);

   // check if insert is to be done
   if (neverUsed[b]) {neverUsed[b] = false;
                  ht[b] = e;
                  return *this;}
  
   // no insert, check if duplicate or full
   if (ht[b] == k) 
   {
   		cout<<"duplicate"<<endl;
   } 
   else
   {
    	cout<<"table full"<<endl;
   }
   return *this;  
}




int main() 

{

clock_t t1, t2;

hashChainsWithTail ht;
HashTable ta;

for (int i = 0; i < 5; i++)ht.insert(i + rand() % 5);
for (int i = 0; i < 10; i++)ta.Insert(i);

//ht.show();


cout << endl << "-----测试结果-----" << endl << endl;

t1 = clock();

for (int i = 0; i < 10; i++)ht.search1(i);

t2 = clock();

cout << "hashChainsWithTail用时： " << double(t2 - t1) << " CLOCKS_PER_SEC" <<endl;

t1 = clock();

for (int i = 0; i < 10; i++)
{
	ta.Search(i,i);
}
t2 = clock();

cout << "hashTable用时： " << double(t2 - t1) << " CLOCKS_PER_SEC" <<endl;

return 0;

} 
