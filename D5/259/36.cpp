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

    // ɾ������
    void remove(int val) {
        Node* curr = head;
        Node* prev = nullptr;

        while (curr) {
            // �ҵ�Ҫɾ���Ľڵ�
            if (curr->value == val) {
                // ���Ҫɾ���Ľڵ���ͷ�ڵ�
                if (curr == head) {
                    head = curr->next;
                    // �������ֻ��һ���ڵ㣬����β�ڵ�
                    if (curr == tail) {
                        tail = head;
                    }
                }
                // ���Ҫɾ���Ľڵ���β�ڵ�
                else if (curr == tail) {
                    tail = prev;
                    tail->next = nullptr;
                }
   
                else {
                    prev->next = curr->next;
                }

                delete curr;  // �ͷ��ڴ�
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
};