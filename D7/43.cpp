#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// �����������
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
};

// compareʵ�֣�rely on�������أ� 
struct Compare {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b)
	{
        return a->freq > b->freq;
    }
};

// ���ɻ�������
HuffmanNode* buildHuffmanTree(map<char, int>& freqMap)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // �����������ڵ㲢�������ȶ���
    for (auto& entry : freqMap) {
        HuffmanNode* node = new HuffmanNode();
        node->data = entry.first;
        node->freq = entry.second;
        node->left = nullptr;
        node->right = nullptr;
        pq.push(node);
    }

    // ������������
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        
        HuffmanNode* right = pq.top();
        pq.pop();
        
        HuffmanNode* parent = new HuffmanNode();
        parent->data = '\0';
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }

    return pq.top();
}

// ���ɻ����������
void buildHuffmanCodes(HuffmanNode* root, map<char, string>& codes, string currentCode) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        codes[root->data] = currentCode;
    }

    buildHuffmanCodes(root->left, codes, currentCode + "0");
    buildHuffmanCodes(root->right, codes, currentCode + "1");
}

// ������ת��Ϊ�������ַ���
string encodeText(string text, map<char, string>& codes) {
    string encodedText = "";
    for (char c : text) {
        encodedText += codes[c];
    }
    return encodedText;
}

// ���������ַ���ת��Ϊ����
string decodeText(string encodedText, HuffmanNode* root) {
    string decodedText = "";
    HuffmanNode* current = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

// ��Ƶ��ͳ��ӳ�䱣�浽�ļ�
void saveFreqMapToFile(map<char, int>& freqMap, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto& entry : freqMap) {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
    }
}

// ���ļ��м���Ƶ��ͳ��ӳ��
map<char, int> loadFreqMapFromFile(string filename) {
    map<char, int> freqMap;
    ifstream file(filename);
    if (file.is_open()) {
        char c;
        int freq;
        while (file >> c >> freq) {
            freqMap[c] = freq;
        }
        file.close();
    }
    return freqMap;
}

int main() {
    string inputFilename = "input.txt";
    string freqMapFilename = "freqMap.txt";
    string encodedFilename = "encoded.txt";
    string decodedFilename = "decoded.txt";

    // ��ȡ�����ı���ͳ���ַ�Ƶ��
    string text;
    cout << "������Ҫѹ�����ı����ݣ�" << endl;
    getline(cin, text);

    map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    // ����Ƶ��ͳ��ӳ�䵽�ļ�
    saveFreqMapToFile(freqMap, freqMapFilename);

    // �����������������ɱ����
    HuffmanNode* root = buildHuffmanTree(freqMap);
    map<char, string> codes;
    buildHuffmanCodes(root, codes, "");

    // ���ı�����Ϊ�������ַ���
    string encodedText = encodeText(text, codes);

    // ���������ַ������浽�ļ�
    ofstream encodedFile(encodedFilename, ios::binary);
    if (encodedFile.is_open()) {
        for (int i = 0; i < encodedText.length(); i += 8) {
            unsigned char byte = 0;
            for (int j = 0; j < 8; j++) {
                if (i + j < encodedText.length()) {
                    byte <<= 1;
                    if (encodedText[i + j] == '1') {
                        byte |= 1;
                    }
                } else {
                    break;
                }
            }
            encodedFile.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        }
        encodedFile.close();
    }

    // ����Ƶ��ͳ��ӳ�䲢������������
    map<char, int> loadedFreqMap = loadFreqMapFromFile(freqMapFilename);
    HuffmanNode* loadedRoot = buildHuffmanTree(loadedFreqMap);

    // ���������ļ�����
    ifstream encodedFileToDecode(encodedFilename, ios::binary);
    string encodedTextToDecode;
    if (encodedFileToDecode.is_open()) {
        char byte;
        while (encodedFileToDecode.read(&byte, sizeof(byte))) {
            for (int i = 7; i >= 0; i--) {
                encodedTextToDecode += ((byte >> i) & 1) ? '1' : '0';
            }
        }
        encodedFileToDecode.close();
    }

    // �����ı�
    string decodedText = decodeText(encodedTextToDecode, loadedRoot);

    // ����������ı����ļ�
    ofstream decodedFile(decodedFilename);
    if (decodedFile.is_open()) {
        decodedFile << decodedText;
        decodedFile.close();
    }

    cout << "ѹ����ı��룺" << endl;
    cout << encodedText << endl;

    cout << "��ѹ��������ݣ�" << endl;
    cout << decodedText << endl;

    return 0;
}
