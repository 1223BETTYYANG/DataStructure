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
        
        resultQueue.push(currentNode->data); // 将节点元素存入队列
        levelArray.push_back(level); // 将层级存入数组
        
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
    // 读入表达式
    string expression;
    cout << "请输入表达式~" << endl;
    cin >> expression;
    
    // 构造二叉树
    int index = 0;
    TreeNode* root = constructTree(expression, index);
    
    // 遍历二叉树并存储到队列和数组中
    queue<char> resultQueue;
    vector<int> levelArray;
    levelOrderTraversal(root, resultQueue, levelArray);
    
    // 打印队列元素
    cout << "队列元素为：";
    while (!resultQueue.empty()) {
        cout << resultQueue.front() << " ";
        resultQueue.pop();
    }
    cout << endl;
    
    // 打印层级数组
    cout << "层级数组为：";
    for (int i = 0; i < levelArray.size(); i++) {
        cout << levelArray[i] << " ";
    }
    cout << endl;
    
    return 0;
}


