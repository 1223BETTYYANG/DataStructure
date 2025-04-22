#include<iostream>
#include<string.h>

using namespace std;

struct Node
{
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

class BuildAVLTree
{
public:
	//Node* root;
	BuildAVLTree()
	{
	//	root=NULL;
	}
	int getHeight(Node* node)
	{
    	if (node == NULL)
    	{
        	return 0;
		}
		return node->height;
	}
	void updateHeight(Node* node)
	{
    	int leftHeight = getHeight(node->left);
    	int rightHeight = getHeight(node->right);
    	node->height = max(leftHeight, rightHeight) + 1;
	}
	int getBalanceFactor(Node* node)
	{
    	if (node == NULL)
        {	
			return 0;
		}
    	return getHeight(node->left) - getHeight(node->right);
	}
	Node* rightRotate(Node* node)
	{
    	Node* leftChild = node->left;
    	Node* rightGrandChild = leftChild->right;
		leftChild->right = node;
    	node->left = rightGrandChild;
		// 更新高度
    	updateHeight(node);
    	updateHeight(leftChild);
    	return leftChild;
	}

	Node* leftRotate(Node* node) 
	{
    	Node* rightChild = node->right;
    	Node* leftGrandChild = rightChild->left;
    	rightChild->left = node;
    	node->right = leftGrandChild;
		updateHeight(node);
    	updateHeight(rightChild);
    	return rightChild;
	}
	Node* insert(Node* root, int value) 
	{
    	if (root == NULL)
        {
        	return new Node(value);
        }
    	if (value < root->data)
        {
        	root->left = insert(root->left, value);
    	}
		else
		{
        root->right = insert(root->right, value);
	    updateHeight(root);
		// 平衡操作
    	int balanceFactor = getBalanceFactor(root);
    	if (balanceFactor > 1 && value < root->left->data)
        	return rightRotate(root);
 	    if (balanceFactor < -1 && value > root->right->data)
        	return leftRotate(root);
    	if (balanceFactor > 1 && value > root->left->data)
		{
        	root->left = leftRotate(root->left);
        	return rightRotate(root);
    	}
		if (balanceFactor < -1 && value < root->right->data) 
		{
        	root->right = rightRotate(root->right);
        	return leftRotate(root);
    	}
		return root;
		}
	}
	int FindHeight(Node* root) 
	{
    	if (root == NULL)
    	{
        	return 0;
    	}
    	return root->height;
	}
	int findClosestLeaf(Node* root) 
	{
    	if (root == NULL)
        {
        	return -1;
		}
    	Node* current = root;
    	while (current->left != NULL || current->right != NULL) 
		{
        	if (current->left != NULL)
            	current = current->left;
        	else
            	current = current->right;
    	}
    	return current->data;
	}
};

int main()
{
	Node* root=NULL;
	BuildAVLTree BVL;
	int n;
	cin>>n;
	while(n!=0)
	{
		BVL.insert(root,n);
		cout<<"---the height of AVLTree at this moment---"<<BVL.FindHeight(root) << endl;
		cin>>n;
	}
	cout<<"---最终height---"<<BVL.FindHeight(root) << endl;
	cout << "---距离根节点最近的叶节点的值为---" <<BVL.findClosestLeaf(root) << endl;
	return 0;
}
