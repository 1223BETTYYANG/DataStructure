#include<iostream>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) 
	{
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* node)
{
    if (node == NULL)
    {
        return 0;
	}
    return node->height;
}

// 更新节点的高度
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

// 计算平衡因子
int getBalanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋操作
Node* rightRotate(Node* node) {
    Node* leftChild = node->left;
    Node* rightGrandChild = leftChild->right;

    // 旋转
    leftChild->right = node;
    node->left = rightGrandChild;

    // 更新高度
    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

// 左旋操作
Node* leftRotate(Node* node) {
    Node* rightChild = node->right;
    Node* leftGrandChild = rightChild->left;

    // 旋转
    rightChild->left = node;
    node->right = leftGrandChild;

    // 更新高度
    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

// 插入节点
Node* insert(Node* root, int value) {
    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    // 更新高度
    updateHeight(root);

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && value < root->left->data)
        return rightRotate(root);

    if (balanceFactor < -1 && value > root->right->data)
        return leftRotate(root);

    if (balanceFactor > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int calculateHeight(Node* root) {
    if (root == NULL)
        return 0;
    return root->height;
}

// 找到距离根节点最近的叶节点的值
int findClosestLeaf(Node* root) {
    if (root == NULL)
        return -1;

    Node* current = root;
    while (current->left != NULL || current->right != NULL) {
        if (current->left != NULL)
            current = current->left;
        else
            current = current->right;
    }

    return current->data;
}

int main() {
	Node* root=NULL;
    root = insert(root, 2);
     cout<<"---the height of AVLTree at this moment---"<<calculateHeight(root) << endl;
    root = insert(root, 4);
     cout<<"---the height of AVLTree at this moment---"<<calculateHeight(root) << endl;
    root = insert(root, 1);
     cout<<"---the height of AVLTree at this moment---"<<calculateHeight(root) << endl;
    root = insert(root, 6);
     cout<<"---the height of AVLTree at this moment---"<<calculateHeight(root) << endl;
    root = insert(root, 3);
	 cout<<"---the height of AVLTree at this moment---"<<calculateHeight(root) << endl;

    // 计算树的高度
    cout<<"---最终height---"<<calculateHeight(root) << endl;

    // 找到距离根节点最近的叶节点的值
    cout << "距离根节点最近的叶节点的值为：" << findClosestLeaf(root) << endl;

    return 0;
}

