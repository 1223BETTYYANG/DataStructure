#include<iostream>
#include<istream>
#include<ostream>
#include<string>
using namespace std;


class Term 
{
public:
      int row, col;
      int value;
};



class SparseMatrix
{

public:
      SparseMatrix(int maxTerms = 10);
      ~SparseMatrix() {delete [] a;}
      //void Transpose(SparseMatrix<T> &b) const;
      SparseMatrix Mul(const SparseMatrix &b);
      int rows, cols;  // matrix dimensions
      int terms;  // current number of nonzero terms
      Term *a;   // term array
      int MaxTerms; // size of array a;
};
SparseMatrix::SparseMatrix(int maxTerms)
{// Sparse matrix constructor.
   MaxTerms = maxTerms;
   a = new Term [MaxTerms];
   terms = rows = cols = 0;
}

ostream& operator<<(ostream& out,const SparseMatrix& x)
{// Put *this in output stream.
   out << "rows = " << x.rows << " columns = "
       << x.cols  << endl;
   out << "nonzero terms = " << x.terms << endl;

   for (int i = 0; i < x.terms; i++)
      out << "a(" << x.a[i].row << ',' << x.a[i].col<< ") = " << x.a[i].value << endl;
   return out;
}




istream& operator>>(istream& in, SparseMatrix& x)
{// Input a sparse matrix.
   cout << "Enter number of rows, columns, and terms"<< endl;
   in >> x.rows >> x.cols >> x.terms;
   for (int i = 0; i < x.terms; i++) {
      cout << "Enter row, column, and value of term " << (i + 1) << endl;
      in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
      }
   return in;
}

SparseMatrix SparseMatrix::Mul(const SparseMatrix &b)
	  {
	SparseMatrix result(10);//°´ÕÕ×î´ó
	result.rows = rows;
	result.cols = b.cols;
	result.terms=0;
	for(int i=0;i<rows;i++)
	{
		//int r_ij=0;
		for(int j=0;j<b.cols;j++)
		{
			int r_ij=0;
				for(int k=0;k<terms;k++)
				{
					if(a[k].row==i+1)
					{
						for(int k1=0;k1<b.terms;k1++)
						{
							if(b.a[k1].col==j+1&&a[k].col==b.a[k1].row)
							{
								cout<<a[j].value<<" "<<b.a[k].value<<endl;
								r_ij+= a[k].value*b.a[k1].value;
							}
						}

					}
				}
			if(r_ij!=0)
		{
			result.a[result.terms].row=i+1;
			result.a[result.terms].col=j+1;
			result.a[result.terms].value=r_ij;
			result.terms++;
		}	
		}
		
	}
		return result; 
	}

int main()
{
	SparseMatrix s(10),b(10);
	cin>>s;
	cout<<s;
	cin>>b;
	cout<<b;
	cout<<s.Mul(b);
	return 0;
}
//65		C:\Users\lenovo\Desktop\173-45.cpp	undefined reference to `operator>>(std::istream&, SparseMatrix<int>&)'
