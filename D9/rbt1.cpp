#include <iostream>
using namespace std;

// ����ڵ���ɫ
enum Color {
    RED,
    BLACK
};

// ���������ڵ���
template<typename T>
class RBTreeNode {
public:
    T data;
    Color color;
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;

    // ���캯��
    RBTreeNode(const T& val, Color c = RED, 
               RBTreeNode* l = nullptr, RBTreeNode* r = nullptr, RBTreeNode* p = nullptr)
        : data(val), color(c), left(l), right(r), parent(p) {}
};

// ����������
template<typename T>
class RBTree {
private:
    RBTreeNode<T>* root;  // ��������ڵ�

public:
    // ���캯��
    RBTree() : root(nullptr) {}

    // �ں�����в���ָ��ֵ�Ľڵ�
    RBTreeNode<T>* find(const T& val) {
        RBTreeNode<T>* curr = root;
        while (curr != nullptr && curr->data != val) {
            if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr;
    }

    // �������в���һ���ڵ�
    void insert(const T& val) {
        RBTreeNode<T>* node = new RBTreeNode<T>(val);
        RBTreeNode<T>* parent = nullptr;
        RBTreeNode<T>* curr = root;

        while (curr != nullptr) {
            parent = curr;
            if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        node->parent = parent;

        if (parent == nullptr)
            root = node;
        else if (val < parent->data)
            parent->left = node;
        else
            parent->right = node;

        insertFixup(node);
    }

    // �Ӻ������ɾ��һ���ڵ�
    void remove(const T& val) {
        RBTreeNode<T>* node = find(val);
        if (node == nullptr)
            return;

        RBTreeNode<T>* child;
        if (node->left == nullptr || node->right == nullptr)
            child = node;
        else
            child = successor(node);

        RBTreeNode<T>* sibling;
        if (child->left != nullptr)
            sibling = child->left;
        else
            sibling = child->right;

        if (sibling != nullptr)
            sibling->parent = child->parent;

        if (child->parent == nullptr)
            root = sibling;
        else if (child == child->parent->left)
            child->parent->left = sibling;
        else
            child->parent->right = sibling;

        if (child != node)
            node->data = child->data;

        if (child->color == BLACK)
            deleteFixup(sibling);

        delete child;
    }

    // �Ժ�������������������ӡ
    void ascend() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

private:
    // ��ȡ�ڵ�ĺ�̽ڵ�
    RBTreeNode<T>* successor(RBTreeNode<T>* node) {
        if (node->right != nullptr) {
            RBTreeNode<T>* curr = node->right;
            while (curr->left != nullptr)
                curr = curr->left;
            return curr;
        }

        RBTreeNode<T>* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    // ��������
    void leftRotate(RBTreeNode<T>* node) {
        RBTreeNode<T>* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    // ��������
    void rightRotate(RBTreeNode<T>* node) {
        RBTreeNode<T>* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    // �����޸�����
    void insertFixup(RBTreeNode<T>* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                RBTreeNode<T>* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                RBTreeNode<T>* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // ɾ���޸�����
    void deleteFixup(RBTreeNode<T>* node) {
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                RBTreeNode<T>* sibling = node->parent->right;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;

                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    leftRotate(node->parent);
                    break;
                }
            } else {
                RBTreeNode<T>* sibling = node->parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;

                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rightRotate(node->parent);
                    break;
                }
            }
        }
        node->color = BLACK;
    }

    // �����������ӡ�ڵ�����
    void inOrderTraversal(RBTreeNode<T>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
};

