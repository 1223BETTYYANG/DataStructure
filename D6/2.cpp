#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct TreeNode 
{
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : data(val), left(NULL), right(NULL) {}
};

TreeNode* constructTree(string expression, int& index)
 {
    if (index >= expression.length())
	 {
        return NULL;
    }
    
    if (expression[index] == '#')
	 {
        index++;
        return NULL;
    }
    
    TreeNode* newNode = new TreeNode(expression[index++]);
    newNode->left = constructTree(expression, index);
    newNode->right = constructTree(expression, index);
    
    return newNode;
}

void levelOrderTraversal(TreeNode* root, queue<char>& resultQueue, vector<int>& levelArray) 
{
    if (root == NULL) {
        return;
    }
    
    queue<TreeNode*> nodeQueue;
    queue<int> levelQueue;
    int level = 0;
    nodeQueue.push(root);
    levelQueue.push(level);
    
    while (!nodeQueue.empty()) {
        TreeNode* currentNode = nodeQueue.front();
        nodeQueue.pop();
        level = levelQueue.front();
        levelQueue.pop();
        
        resultQueue.push(currentNode->data); // ���ڵ�Ԫ�ش������
        levelArray.push_back(level); // ���㼶��������
        
        if (currentNode->left != NULL) {
            nodeQueue.push(currentNode->left);
            levelQueue.push(level + 1);
        }
        
        if (currentNode->right != NULL) {
            nodeQueue.push(currentNode->right);
            levelQueue.push(level + 1);
        }
    }
}

int main() {
    // ������ʽ
    string expression;
    cout << "��������ʽ~" << endl;
    cin >> expression;
    
    // ���������
    int index = 0;
    TreeNode* root = constructTree(expression, index);
    
    // �������������洢�����к�������
    queue<char> resultQueue;
    vector<int> levelArray;
    levelOrderTraversal(root, resultQueue, levelArray);
    
    // ��ӡ����Ԫ��
    cout << "����Ԫ��Ϊ��";
    while (!resultQueue.empty()) {
        cout << resultQueue.front() << " ";
        resultQueue.pop();
    }
    cout << endl;
    
    // ��ӡ�㼶����
    cout << "�㼶����Ϊ��";
    for (int i = 0; i < levelArray.size(); i++) {
        cout << levelArray[i] << " ";
    }
    cout << endl;
    
    return 0;
}


