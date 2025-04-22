#include <iostream>
using namespace std;

class Node 
{
public:
    int row;
    int col;
    int value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(NULL) {}
};

class linkedMatrix 
{
public:
    int numRows;
    int numCols;
    Node** rows;

    linkedMatrix(int rows, int cols) : numRows(rows), numCols(cols) 
    {
        this->rows = new Node * [rows];
        for (int i = 0; i < rows; ++i) 
        {
            this->rows[i] = NULL;
        }
    }

    // �洢һ��Ԫ��/////////////////////////
    void setElement(int row, int col, int value) 
    {
        //�ж��Ƿ���Ч
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) 
        {
            cout << "Invalid row or column index." << endl;
            return;
        }

        Node* newNode = new Node(row, col, value);
        newNode->next = rows[row];
        rows[row] = newNode;
    }

    // ȡ��һ��Ԫ��//////////////////////////
    int getElement(int row, int col) const 
    {
        //�ж��Ƿ���Ч
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) 
        {
            cout << "Invalid row or column index." << endl;
            return 0; // ����Ĭ��ֵ
        }

        Node* current = rows[row];
        while (current != NULL) 
        {
            if (current->col == col) 
            {
                return current->value;
            }
            current = current->next;
        }
        return 0; // ���Ԫ�ز����ڣ�����Ĭ��ֵ
    }

    // ����ϡ��������
    linkedMatrix operator+(const linkedMatrix& other) const 
    {
        if (numRows != other.numRows || numCols != other.numCols) 
        {
            cout << "����!" << endl;
            return *this;
        }

        linkedMatrix result(numRows, numCols);

        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                int sum = getElement(i, j) + other.getElement(i, j);
                result.setElement(i, j, sum);
            }
        }

        return result;
    }

    // ����ϡ��������
    linkedMatrix operator-(const linkedMatrix& other) const 
    {
        if (numRows != other.numRows || numCols != other.numCols) 
        {
            cout << "����" << endl;
            return *this;
        }

        linkedMatrix result(numRows, numCols);

        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                int sub = getElement(i, j) - other.getElement(i, j);
                result.setElement(i, j, sub);
            }
        }

        return result;
    }

    // ����ϡ��������
    linkedMatrix operator*(const linkedMatrix& other) const 
    {
        if (numCols != other.numRows) 
        {
            cout << "����" << endl;
            return *this;
        }

        linkedMatrix result(numRows, other.numCols);

        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < other.numCols; ++j) 
            {
                int mul = 0;
                for (int k = 0; k < numCols; ++k)
                {
                    mul += getElement(i, k) * other.getElement(k, j);
                }
                result.setElement(i, j, mul);
            }
        }

        return result;
    }

    // �������������
    friend istream& operator>>(istream& cin, linkedMatrix& matrix) 
    {
        int row, col, value;
       for (int i = 0; i < matrix.numRows; i++)
       {
            for (int j = 0; j < matrix.numCols; j++)
            {
                cin >> value;
                matrix.setElement(i, j, value);
            }
       }
        return cin;
    }

    // �������������
    friend ostream& operator<<(ostream& out, const linkedMatrix& matrix) 
    {
        for (int i = 0; i < matrix.numRows; ++i) 
        {
            for (int j = 0; j < matrix.numCols; ++j) 
            {
                out << matrix.getElement(i, j) << " ";
            }
            out << endl;
        }
        return out;
    }
};



int main() 
{
	int rows1, cols1;
	int rows2, cols2;
    cout << "����a�����У�" << endl;
    cin >> rows1 >> cols1;
    cout << "����b�����У�" << endl;
    cin >> rows2 >> cols2;
    linkedMatrix matrix1(rows1, cols1);
    linkedMatrix matrix2(rows2, cols2);
	cout << "�������1��" << endl;
    cin >> matrix1;
	cout << "�������2��" << endl;
    cin >> matrix2;
    cout << "getelement��"<<endl;
    cout << matrix1.getElement(1, 1)<<endl;
    cout << matrix2.getElement(1, 1)<<endl;
    linkedMatrix sum = matrix1 + matrix2;
    linkedMatrix subtraction = matrix1 - matrix2;
    linkedMatrix multiplication = matrix1 * matrix2;

    cout << "Matrix1 + Matrix2=" << endl;
    cout << sum << endl;

    cout << "Matrix1 - Matrix2=" << endl;
    cout << subtraction << endl;

    cout << "Matrix1 * Matrix2=" << endl;
    cout << multiplication << endl;

    return 0;
}
