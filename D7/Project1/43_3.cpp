#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <vector>
#include <queue>

using namespace std;

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
HuffmanNode* buildHuffmanTree(map<char, int>& freqMap)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;//借用自带小根堆

    for (auto& entry : freqMap)
    {
        HuffmanNode* node = new HuffmanNode();
        node->data = entry.first;
        node->freq = entry.second;
        node->left = nullptr;
        node->right = nullptr;
        pq.push(node);
    }
    while (pq.size() > 1)
    {
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

void buildHuffmanCodes(HuffmanNode* root, map<char, string>& codes, string currentCode)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        codes[root->data] = currentCode;
        cout << root->data << " is now coded as " << currentCode << "~" << endl;
    }
    buildHuffmanCodes(root->left, codes, currentCode + "0");
    buildHuffmanCodes(root->right, codes, currentCode + "1");
}
string encodeText(string text, map<char, string>& codes)
{
    string encodedText = "";
    for (char c : text)
    {
        encodedText += codes[c];
    }
    return encodedText;
}
string decodeText(string encodedText, HuffmanNode* root) {
    string decodedText = "";
    HuffmanNode* current = root;
    for (char c : encodedText)
    {
        if (c == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

void saveFreqMapToFile(map<char, int>& freqMap, string filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (auto& entry : freqMap)
        {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
    }
}
int main() 
{
    string inputFilename = "input.txt";
    string freqMapFilename = "freqMap.txt";
   // string CodedMapFilename = "CodedMap.txt";
    string encodedFilename = "encoded.txt";
    string decodedFilename = "decoded.txt";
    string text;
    cout << "-----PLZ input your text-----" << endl;
    getline(cin, text);
    map<char, int> freqMap;
    for (char c : text)
    {
        freqMap[c]++;
    }
    saveFreqMapToFile(freqMap, freqMapFilename);
    HuffmanNode* root = buildHuffmanTree(freqMap);
    map<char, string> codes;
    buildHuffmanCodes(root, codes, "");
    string encodedText = encodeText(text, codes);
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
                }
                else {
                    break;
                }
            }
            encodedFile.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        }
        encodedFile.close();
    }
    string decodedText = decodeText(encodedText, root);
    ofstream decodedFile(decodedFilename);
    if (decodedFile.is_open()) 
    {
        decodedFile << decodedText;
        decodedFile.close();
    }

    cout << "请看霍夫曼编码后的文本：" << endl;
    cout << encodedText << endl;

    cout << "解压缩后的内容：" << endl;
    cout << decodedText << endl;

    return 0;
}