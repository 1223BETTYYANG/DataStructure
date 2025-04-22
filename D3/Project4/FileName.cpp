#include<iostream>
#include<istream>
#include<ostream>
using namespace std;

template <class T>
class Term
{
public:
    int row, col;
    T value;
};


template<class T>
class SparseMatrix
{
    friend ostream& operator<<(ostream& , const SparseMatrix<T>& );
    friend istream& operator>>(istream& , SparseMatrix<T>& );
public:
    SparseMatrix(int maxTerms = 10);
    ~SparseMatrix() { delete[] a; }
    void Transpose(SparseMatrix<T>& b) const;
    void Mul(const SparseMatrix<T>& b) const;
    int rows, cols;  // matrix dimensions
    int terms;  // current number of nonzero terms
    Term<T>* a;   // term array
    int MaxTerms; // size of array a;
};
template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{// Sparse matrix constructor.
    MaxTerms = maxTerms;
    a = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}
template <class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{// Put *this in output stream.
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms << endl;

    for (int i = 0; i < x.terms; i++)
        out << "a(" << x.a[i].row << ',' << x.a[i].col << ") = " << x.a[i].value << endl;
    return out;
}
template<class T>
istream& operator>>(istream& in, SparseMatrix<T>& x)
{// Input a sparse matrix.
    cout << "Enter number of rows, columns, and terms" << endl;
    in >> x.rows >> x.cols >> x.terms;
    for (int i = 0; i < x.terms; i++) {
        cout << "Enter row, column, and value of term " << (i + 1) << endl;
        in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
    }
    return in;
}


int main()
{
    SparseMatrix<int> s(5);
    cin >> s;
    return 0;
}
