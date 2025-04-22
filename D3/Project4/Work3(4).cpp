#include <bits/stdc++.h>
#include <random>
using namespace std;

namespace Question1
{
    template<typename T>
    class matrix
    {
    protected:
        int rows;
        int cols;
        vector<vector<T>> data;

    public:
        matrix(int r = 1, int c = 1) : rows(r), cols(c)
        {
            data.resize(rows, vector<T>(cols));
        }

    public:
        void set(int i, int j, T value)
        {
            if (i < 0 || j < 0 || i >= rows || j >= cols) return;
            data[i][j] = value;
        }
        T get(int i, int j) const
        {
            if (i < 0 || j < 0 || i >= rows || j >= cols) return T();
            return data[i][j];
        }
        void display() const
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                    cout << data[i][j] << " ";
                cout << '\n';
            }
        }
    };
    template<typename T>
    class upperTriangularMatrix;
    template<typename T>
    class lowerTriangularMatrix;

    template<typename T>
    class upperTriangularMatrix : public matrix<T>
    {
    public:
        upperTriangularMatrix(int size = 1) : matrix<T>(size, size) {}

    public:
        void set(int i, int j, T value)
        {
            if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) return;
            if (i <= j) this->data[i][j] = value;
        }
        lowerTriangularMatrix<T> transpose() const
        {
            lowerTriangularMatrix<T> result(this->rows);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    result.set(j, i, this->get(i, j));
            return result;
        }
    };

    template<typename T>
    class lowerTriangularMatrix : public matrix<T>
    {
    public:
        lowerTriangularMatrix(int size = 1) : matrix<T>(size, size) {}

    public:
        void set(int i, int j, T value)
        {
            if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) return;
            if (i >= j) this->data[i][j] = value;
        }
        upperTriangularMatrix<T> transpose()
        {
            upperTriangularMatrix<T> result(this->rows);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    result.set(j, i, this->get(i, j));
            return result;
        }
    };

    void test(int rows)
    {
        lowerTriangularMatrix<int> testMatrix(rows);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 999);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j <= i; j++)
                testMatrix.set(i, j, dis(gen));
        cout << "原下三角矩阵：\n";
        testMatrix.display();
        upperTriangularMatrix<int> transposeMatrix = testMatrix.transpose();
        cout << "\n转置后矩阵：\n";
        transposeMatrix.display();
    }
}

namespace Question2
{
    template<typename T>
    struct triplet
    {
        int row, col;
        T value;
        triplet(int r, int c, T v) : row(r), col(c), value(v) {}
    };

    template<typename T>
    class sparseMatrix
    {
    private:
        int rows, cols;
        vector<triplet<T>> data;

    public:
        sparseMatrix(int r, int c) : rows(r), cols(c) {}

    public:
        void addData(int row, int col, T value)
        {
            if (row >= 0 && col >= 0 && row < rows && col < cols && value != 0) data.push_back(triplet<T>(row, col, value));
        }
        sparseMatrix<T> multiply(const sparseMatrix<T>& other)
        {
            if (cols != other.rows) 
            {
                cout << "乘不了一点，下边是A\n";
                return *this;
            }
            sparseMatrix<T> ans(rows, other.cols);
            for (const auto& a : data)
            {
                for (const auto& b : other.data)
                {
                    if (a.col != b.row) continue;
                    bool found = 0;
                    for (auto& r : ans.data)
                    {
                        if (!(r.row == a.row && r.col == b.col)) continue;
                        r.value += a.value * b.value;
                        found = 1;
                        break;
                    }
                    if (!found) ans.addData(a.row, b.col, a.value * b.value);
                }
            }
            return ans;
        }
        void display()
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    bool printed = 0;
                    for (const auto& elem : data)
                    {
                        if (elem.row == i && elem.col == j)
                        {
                            cout << elem.value << " ";
                            printed = 1;
                            break;
                        }
                    }
                    if (!printed) cout << "0 ";
                }
                cout << '\n';
            }
        }
    };

    void test()
    {
        int r1 = 0, r2 = 0, l1 = 0, l2 = 0;
        cout << "请分别输入两个矩阵的行和列：\n矩阵A：";
        cin >> r1 >> l1;
        cout << "矩阵B：";
        cin >> r2 >> l2;
        sparseMatrix<int> testMatA(r1, l1), testMatB(r2, l2);
        int n = 0;
        int x = 0, y = 0, v = 0;
        cout << "矩阵A有的数据点数量：";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y >> v;
            testMatA.addData(x, y, v);
        }
        cout << "矩阵B有的数据点数量：";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y >> v;
            testMatB.addData(x, y, v);
        }
        cout << "\n\n输入的矩阵为：\nA：\n";
        testMatA.display();
        cout << "B：\n";
        testMatB.display();
        cout << "\n相乘结果为：\n";
        testMatA.multiply(testMatB).display();
    }
}

namespace Question3
{
    template<typename T>
    class rowList;

    template<typename T>
    class rowNode
    {
    public:
        int colIndex;
        T data;
        rowNode<T>* next;

    public:
        // 构造函数，初始化行节点
        rowNode(int c, T d) : colIndex(c), data(d), next(nullptr) {}
    };

    template<typename T>
    class headerNode
    {
    public:
        rowList<T>* row;
        headerNode<T>* next;

    public:
        // 构造函数，初始化头节点
        headerNode() : row(new rowList<T>()), next(nullptr) {}
    };

    template<typename T>
    class rowList
    {
    private:
        rowNode<T>* head;

    public:
        // 默认构造函数，初始化空的行列表
        rowList() : head(nullptr) {}
        // 拷贝构造函数，从源复制一个行列表
        rowList(const rowList<T>& source)
        {
            head = nullptr;
            rowNode<T>* currentSource = source.head;
            rowNode<T>* currentCopy = nullptr;
            while (currentSource) {
                rowNode<T>* newNode = new rowNode<T>(currentSource->colIndex, currentSource->data);
                if (!head) {
                    head = newNode;
                    currentCopy = head;
                }
                else {
                    currentCopy->next = newNode;
                    currentCopy = newNode;
                }
                currentSource = currentSource->next;
            }
        }
        // 析构函数，删除行列表及其所有元素
        ~rowList()
        {
            rowNode<T>* current = head;
            while (current)
            {
                rowNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }

    public:
        // 插入一个新元素到指定的列索引
        void insert(int colIndex, T data)
        {
            rowNode<T>* newNode = new rowNode<T>(colIndex, data);
            if (!head || colIndex < head->colIndex)
            {
                newNode->next = head;
                head = newNode;
                return;
            }
            rowNode<T>* current = head;
            while (current->next && current->next->colIndex < colIndex) current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
        // 从指定的列索引中删除元素
        void remove(int colIndex)
        {
            if (!head) return;
            if (head->colIndex == colIndex)
            {
                rowNode<T>* temp = head;
                head = head->next;
                delete temp;
                return;
            }
            rowNode<T>* current = head;
            while (current->next && current->next->colIndex != colIndex) current = current->next;
            if (current->next)
            {
                rowNode<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
        // 在指定的列索引中查找元素
        T find(int colIndex)
        {
            rowNode<T>* current = head;
            while (current && current->colIndex != colIndex) current = current->next;
            return (current ? current->data : T());
        }
        // 获取行列表的头节点
        rowNode<T>* getHead() const
        {
            return head;
        }
    };

    template<typename T>
    class headerList
    {
    private:
        headerNode<T>* head;
        int headerSize;

    public:
        // 默认构造函数，初始化空的头列表
        headerList() : headerSize(0), head(nullptr) {}
        // 拷贝构造函数，从源复制一个头列表
        headerList(const headerList<T>& source)
        {
            head = nullptr;
            headerNode<T>* currentSource = source.head;
            headerNode<T>* currentCopy = nullptr;
            while (currentSource) {
                headerNode<T>* newHeader = new headerNode<T>();
                newHeader->row = new rowList<T>(*currentSource->row);
                if (!head) {
                    head = newHeader;
                    currentCopy = head;
                }
                else {
                    currentCopy->next = newHeader;
                    currentCopy = newHeader;
                }
                currentSource = currentSource->next;
            }
            headerSize = source.headerSize;
        }
        // 析构函数，删除头列表及其所有元素
        ~headerList()
        {
            headerNode<T>* current = head;
            while (current)
            {
                headerNode<T>* temp = current;
                current = current->next;
                delete temp->row;
                delete temp;
            }
        }

    public:
        // 在尾部追加一个新的头节点
        void append()
        {
            if (!head)
            {
                head = new headerNode<T>();
                return;
            }
            headerNode<T>* current = head;
            while (current->next) current = current->next;
            current->next = new headerNode<T>();
        }
        // 删除最后一个头节点
        void removeLast()
        {
            if (!head) return;
            if (!head->next)
            {
                delete head;
                head = nullptr;
                return;
            }
            headerNode<T>* current = head;
            while (current->next->next)
            {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        // 获取指定行索引的头节点
        headerNode<T>* get(int rowIndex)
        {
            int index = 0;
            headerNode<T>* current = head;
            while (current && index < rowIndex)
            {
                current = current->next;
                index++;
            }
            return current;
        }
    };

    template<typename T>
    class linkedMatrix
    {
    private:
        headerList<T> headers;
        int rows;
        int cols;

    public:
        // 构造函数，初始化一个指定大小的矩阵
        linkedMatrix(int r = 5, int c = 5) : rows(r), cols(c) {}

    public:
        // 在指定的行和列索引插入数据
        void insert(int rowIndex, int colIndex, T data)
        {
            if (rowIndex < 0 || rowIndex >= rows || colIndex < 0 || colIndex >= cols) return;
            headerNode<T>* header = headers.get(rowIndex);
            while (!header)
            {
                headers.append();
                header = headers.get(rowIndex);
            }
            header->row->insert(colIndex, data);
        }
        // 从指定的行和列索引中删除数据
        void remove(int rowIndex, int colIndex)
        {
            if (rowIndex < 0 || rowIndex >= rows || colIndex < 0 || colIndex >= cols) return;
            headerNode<T>* header = headers.get(rowIndex);
            if (header) header->row->remove(colIndex);
        }
        // 在指定的行和列索引中查找数据
        T find(int rowIndex, int colIndex)
        {
            if (rowIndex < 0 || rowIndex >= rows || colIndex < 0 || colIndex >= cols) return T();
            headerNode<T>* header = headers.get(rowIndex);
            if (header) return header->row->find(colIndex);
            return T();
        }
        // 显示矩阵的所有元素
        void display()
        {
            for (int i = 0; i < rows; ++i)
            {
                headerNode<T>* header = headers.get(i);
                rowNode<T>* rnode = header ? header->row->getHead() : nullptr;
                for (int j = 0; j < cols; ++j)
                {
                    if (rnode && rnode->colIndex == j)
                    {
                        cout << rnode->data << " ";
                        rnode = rnode->next;
                    }
                    else
                    {
                        cout << "0 ";
                    }
                }
                cout << '\n';
            }
        }

    public:
        friend linkedMatrix<T> operator + (linkedMatrix<T>& leftMat, linkedMatrix<T>& rightMat)
        {
            if (leftMat.rows != rightMat.rows || leftMat.cols != rightMat.cols)
            {
                cout << "加不了一点\n";
                return leftMat;
            }
            linkedMatrix<T> ans(leftMat.rows, leftMat.cols);
            for (int i = 0; i < leftMat.rows; ++i)
            {
                for (int j = 0; j < leftMat.cols; ++j)
                {
                    T lhs_val = leftMat.find(i, j);
                    T rhs_val = rightMat.find(i, j);
                    if (lhs_val + rhs_val != 0) ans.insert(i, j, lhs_val + rhs_val);
                }
            }
            return ans;
        }

        friend linkedMatrix<T> operator - (linkedMatrix<T>& leftMat, linkedMatrix<T>& rightMat)
        {
            if (leftMat.rows != rightMat.rows || leftMat.cols != rightMat.cols)
            {
                cout << "减不了一点\n";
                return leftMat;
            }
            linkedMatrix<T> ans(leftMat.rows, leftMat.cols);
            for (int i = 0; i < leftMat.rows; ++i)
            {
                for (int j = 0; j < leftMat.cols; ++j)
                {
                    T lhs_val = leftMat.find(i, j);
                    T rhs_val = rightMat.find(i, j);
                    if (lhs_val - rhs_val != 0) ans.insert(i, j, lhs_val - rhs_val);
                }
            }
            return ans;
        }

        friend linkedMatrix<T> operator * (linkedMatrix<T>& leftMat, linkedMatrix<T>& rightMat)
        {
            if (leftMat.cols != rightMat.rows)
            {
                cout << "乘不了一点\n";
                return leftMat;
            }
            linkedMatrix<T> ans(leftMat.rows, rightMat.cols);
            for (int i = 0; i < leftMat.rows; ++i)
            {
                for (int j = 0; j < rightMat.cols; ++j)
                {
                    T sum = T();
                    for (int k = 0; k < leftMat.cols; ++k)
                    {
                        sum += leftMat.find(i, k) * rightMat.find(k, j);
                    }
                    if (sum != T())
                    {
                        ans.insert(i, j, sum);
                    }
                }
            }
            return ans;
        }

        friend istream& operator >> (istream& input, linkedMatrix<T>& matrix)
        {
            int totalNum = 0;
            input >> totalNum;
            for (int i = 0; i < totalNum; ++i)
            {
                int rowIndex, colIndex;
                T value = T();
                input >> rowIndex >> colIndex >> value;
                matrix.insert(rowIndex, colIndex, value);
            }
            return input;
        }
    };

    void test()
    {
        linkedMatrix<int> matrix(10, 10);
        cin >> matrix;
        matrix.display();
        cout << '\n';

        linkedMatrix<int> Matrix(10, 10);
        cin >> Matrix;
        Matrix.display();
        cout << '\n';

        (matrix + Matrix).display();
        cout << '\n';

        (matrix - Matrix).display();
        cout << '\n';

        (matrix * Matrix).display();
        cout << '\n';
    }
}

int main()
{
    Question1::test(5);
}