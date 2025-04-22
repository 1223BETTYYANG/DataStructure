#include<iostream>

using namespace std;

class HashTable {
   public:
      HashTable(int divisor = 11); 
      ~HashTable() {delete [] ht;  delete [] neverUsed;}
      bool Search(const int& k, int& e) const;
      HashTable& Insert(const int& e);
      HashTable& Insert_re(const int& e);
      void reorganize();// output the hash table
      int hSearch(const int& k) const;
      int hSearch_re(const int& k) const;
      int m; // hash function divisor
      int *ht; // hash table array
      int *newht;
      bool *neverUsed; // 1D array
      bool *newneverUsed; 
};

HashTable::HashTable(int

 divisor)
{// Constructor.
   m = divisor;

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
   int i = k % m; // home bucket
   int j = i;     // start at home bucket
   do {
      if (neverUsed[j] || ht[j] == k) return j;
      j = (j + 1) % m;  // next bucket
      } while (j != i); // returned to home?

   return j;  // table full
}
int HashTable::hSearch_re(const int& k) const
{
   int i = ((k+3)*2) % m; 
   int j = i;     
   do {
      if (newneverUsed[j] || newht[j] == k) return j;
      j = (j + 1) % m;  // next bucket
      } while (j != i); // returned to home?

   return j;  // table full
}

bool HashTable::Search(const int& k, int& e) const
{// Put element that matches k in e.
 // Return false if no match.
   int b = hSearch(k);
   if (neverUsed[b] || ht[b] != k) return false;
   e = ht[b];
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

HashTable& HashTable::Insert_re(const int& e)
{// Hash table insert.
   int k = e; // extract key
   int b = hSearch_re(k);

   // check if insert is to be done
   if (newneverUsed[b]) 
	{
   		newneverUsed[b] = false;
        newht[b] = e;
	}
  
   return *this;  
}
void HashTable::reorganize()
{
	int whold = 0.6 * m;
	int count = 0;
	for (int i = 0; i < m; i++)
	 {
            if (neverUsed[i]!=0) 
			{
                count++;
            }
     }
     if(count>=whold)
     {
     	cout<<"*********"<<endl;
     	newht= new int [m];
     	newneverUsed= new bool [m];
     	for (int i = 0; i < m; i++)
      	{
      		newneverUsed[i] = true;
      	}
      	int i=0;
      	for (int k = 0; k < m; k++)
      	{
      		if(neverUsed[k]==0)
      		{
      		int e=ht[k];
      		Insert_re(e); 
      		}
      	}
      	ht=newht;
      	neverUsed=newneverUsed;
     }
}

int main()
{
	HashTable table(10);
    table.Insert(2);
    table.Insert(5);
    //table.Insert(35);
    table.Insert(15);
    int e=15;
    cout << table.Search(15,e) << endl; 
    for (int i = 0; i < 10; i++)
    {
        cout<<table.neverUsed[i]<<" "; 
    }
    cout<<endl;
    table.reorganize();
    for (int i = 0; i < 10; i++)
    {
        cout<<table.neverUsed[i]<<" "; 
    }
    return 0;
}
