#include <iostream>

class Node {
public:
    int value;
    Node* next;

    Node(int val) {
        value = val;
        next = nullptr;
    }
};

class hashChainsWithTail {
private:
    Node* head;
    Node* tail;

public:
    hashChainsWithTail() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else if (val <= head->value) {
            newNode->next = head;
            head = newNode;
        }
        else if (val >= tail->value) {
            tail->next = newNode;
            tail = newNode;
        }
        else {
            Node* curr = head;
            while (curr->next && curr->next->value < val) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }

    // 删除操作
    void remove(int val) {
        Node* curr = head;
        Node* prev = nullptr;

        while (curr) {
            // 找到要删除的节点
            if (curr->value == val) {
                // 如果要删除的节点是头节点
                if (curr == head) {
                    head = curr->next;
                    // 如果链表只有一个节点，更新尾节点
                    if (curr == tail) {
                        tail = head;
                    }
                }
                // 如果要删除的节点是尾节点
                else if (curr == tail) {
                    tail = prev;
                    tail->next = nullptr;
                }
   
                else {
                    prev->next = curr->next;
                }

                delete curr;  // 释放内存
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
};