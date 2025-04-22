#include<iostream>
#include<istream>
#include<ostream>
#include<string>
using namespace std;
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
        rowNode(int c, T d) : colIndex(c), data(d), next(NULL) {}
    };

    template<typename T>
    class headerNode
    {
    public:
        rowList<T>* row;
        headerNode<T>* next;

    public:
        // 构造函数，初始化头节点
        headerNode() : row(new rowList<T>()), next(NULL) {}
    };

    template<typename T>
    class rowList
    {
    private:
        rowNode<T>* head;

    public:
        // 默认构造函数，初始化空的行列表
        rowList() : head(NULL) {}
        // 拷贝构造函数，从源复制一个行列表
        rowList(const rowList<T>& source)
        {
            head = NULL;
            rowNode<T>* currentSource = source.head;
            rowNode<T>* currentCopy = NULL;
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
        headerList() : headerSize(0), head(NULL) {}
        // 拷贝构造函数，从源复制一个头列表
        headerList(const headerList<T>& source)
        {
            head = NULL;
            headerNode<T>* currentSource = source.head;
            headerNode<T>* currentCopy = NULL;
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
                head = NULL;
                return;
            }
            headerNode<T>* current = head;
            while (current->next->next)
            {
                current = current->next;
            }
            delete current->next;
            current->next = NULL;
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
                rowNode<T>* rnode = header ? header->row->getHead() : NULL;
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
