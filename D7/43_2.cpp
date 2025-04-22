#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;
};

Node* createNode(char data, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->data = data;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

void encode(Node* root, string str, vector<pair<char, string> >& huffmanCode) {
    if (root == NULL)
        return;

    if (!root->left && !root->right) {
        huffmanCode.push_back(make_pair(root->data, str));
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(string text) {
    if (text.length() == 0)
        return;

    vector<pair<char, int> > freq;
    for (char c : text) {
        bool found = false;
        for (pair<char, int>& p : freq) {
            if (p.first == c) {
                p.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            freq.push_back(make_pair(c, 1));
        }
    }

    priority_queue<Node*, vector<Node*>, compare> pq;
    for (pair<char, int> p : freq) {
        pq.push(createNode(p.first, p.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(createNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    vector<pair<char, string>> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are:\n";
    for (pair<char, string> p : huffmanCode) {
        cout << p.first << " : " << p.second << "\n";
    }
}

int main() {
    string text = "Huffman compression and decompression example";
    buildHuffmanTree(text);

    return 0;
}
