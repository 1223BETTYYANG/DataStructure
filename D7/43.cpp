#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// 定义霍夫曼树
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
};

// compare实现（rely on（）重载） 
struct Compare {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b)
	{
        return a->freq > b->freq;
    }
};

// 生成霍夫曼树
HuffmanNode* buildHuffmanTree(map<char, int>& freqMap)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // 构建霍夫曼节点并加入优先队列
    for (auto& entry : freqMap) {
        HuffmanNode* node = new HuffmanNode();
        node->data = entry.first;
        node->freq = entry.second;
        node->left = nullptr;
        node->right = nullptr;
        pq.push(node);
    }

    // 构建霍夫曼树
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

// 生成霍夫曼编码表
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

// 将编码转换为二进制字符串
string encodeText(string text, map<char, string>& codes) {
    string encodedText = "";
    for (char c : text) {
        encodedText += codes[c];
    }
    return encodedText;
}

// 将二进制字符串转换为编码
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

// 将频率统计映射保存到文件
void saveFreqMapToFile(map<char, int>& freqMap, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto& entry : freqMap) {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
    }
}

// 从文件中加载频率统计映射
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

    // 读取输入文本并统计字符频率
    string text;
    cout << "请输入要压缩的文本内容：" << endl;
    getline(cin, text);

    map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    // 保存频率统计映射到文件
    saveFreqMapToFile(freqMap, freqMapFilename);

    // 构建霍夫曼树并生成编码表
    HuffmanNode* root = buildHuffmanTree(freqMap);
    map<char, string> codes;
    buildHuffmanCodes(root, codes, "");

    // 将文本编码为二进制字符串
    string encodedText = encodeText(text, codes);

    // 将编码后的字符串保存到文件
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

    // 加载频率统计映射并构建霍夫曼树
    map<char, int> loadedFreqMap = loadFreqMapFromFile(freqMapFilename);
    HuffmanNode* loadedRoot = buildHuffmanTree(loadedFreqMap);

    // 将编码后的文件解码
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

    // 解码文本
    string decodedText = decodeText(encodedTextToDecode, loadedRoot);

    // 保存解码后的文本到文件
    ofstream decodedFile(decodedFilename);
    if (decodedFile.is_open()) {
        decodedFile << decodedText;
        decodedFile.close();
    }

    cout << "压缩后的编码：" << endl;
    cout << encodedText << endl;

    cout << "解压缩后的内容：" << endl;
    cout << decodedText << endl;

    return 0;
}
