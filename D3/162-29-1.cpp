#include <iostream>
using namespace std;

template<class T>
class LowerTriangularMatrix 
{
public:
    LowerTriangularMatrix(int size = 10)
	{
	 	n = size; 
		t = new T [n*(n+1)/2];
	}
    ~LowerTriangularMatrix() {delete [] t;}
    LowerTriangularMatrix<T>& Store(const T& x, int i, int j);
    LowerTriangularMatrix<T>& Trans();
    T Retrieve(int i, int j) const;
public:
	int n; //  matrix dimension
    T *t;  // 1D array for lower triangle
};
template<class T>
LowerTriangularMatrix<T>& LowerTriangularMatrix<T>::Store(const T& x, int i, int j)
{	
   if (i >= j)
   {
   		t[i*(i-1)/2+j-1] = x;
   } 
   else if (x != 0) 
	{
		cout<<"unexpected input"<<endl;
	}
   return *this;
}

template<class T>
LowerTriangularMatrix<T>& LowerTriangularMatrix<T>::Trans()
{
	LowerTriangularMatrix<T> AT(n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			AT.t[i-j+(2*n+2-j)*(j-1)/2]=t[i*(i-1)/2+j-1];
			//test
			cout<<AT.t[i-j+(2*n+2-j)*(j-1)/2]<<" "<<t[i*(i-1)/2+j-1]<<"*"<<endl;
			cout<<i-j+(2*n+2-j)*(j-1)/2<<" "<<i*(i-1)/2+j-1<<"**"<<endl;
		}
	}
	for(int i=0;i<n*(n+1)/2;i++)
	{
		cout<<AT.t[i]<<" "; 
	}
	cout<<endl;
	return AT;
}

template <class T>
T LowerTriangularMatrix<T>::Retrieve(int i, int j) const
{// Retrieve L(i,j).
   if ( i < 1 || j < 1 || i > n || j > n)
   {
		cout<<"out of bounds"<<endl;
		return;
   }   
   // (i,j) in lower triangle if i >= j
   if (i >= j) 
   {
   		return t[i*(i-1)/2+j-1];
   }
   else 
   {
		return 0;
   }
}

int main()
{
	
	LowerTriangularMatrix<int> A(4);
	LowerTriangularMatrix<int> AT(4);
	int n=1;
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=i;j++)
		{
			A.Store(n,i,j);
			n++;
		}
	}
	
	AT=A.Trans();
	for(int i=0;i<10;i++)
	{
		cout<<A.t[i]<<" "; 
	}
	cout<<endl;
	
	return 0;
}
