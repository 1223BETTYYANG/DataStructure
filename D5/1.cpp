#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    int capacity; // 散列表的容量
    vector<int> keys; // 存储键的向量
     // 每个桶是否被使用过的标记

    int hash(int key) {
        return key % capacity; // 简单的哈希函数，这里直接使用取模
    }

public:
	vector<bool> neverUsed;
    HashTable(int capacity) {
        this->capacity = capacity;
        keys = vector<int>(capacity, -1); // 初始化所有键为-1
        neverUsed = vector<bool>(capacity, true); // 初始化所有桶的neverUsed为true
    }
void insert(int key) {
        int index = hash(key);
        while (keys[index] != -1) { // 线性探查寻找空桶
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        neverUsed[index] = false; // 插入后更新neverUsed
    }

    bool search(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // 在散列表中寻找键
            index = (index + 1) % capacity;
            counter++;
        }
        return keys[index] == key;
    }
     void remove(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // 寻找要删除的键
            index = (index + 1) % capacity;
            counter++;
        }
        if (keys[index] == key) {
            keys[index] = -1;
            neverUsed[index] = true; // 标记为neverUsed
        }
    }

    void reorganize() {
        int threshold = 0.6 * capacity; // 60%的空桶的neverUsed域的值为false时，重新组织散列表
        int count = 0;
        for (int i = 0; i < capacity; i++) {
            if (keys[i] == -1 && !neverUsed[i]) {
                count++;
            }
        }
        if (count >= threshold) {
            vector<int> newKeys(capacity, -1);
            vector<bool> newNeverUsed(capacity, true);
            for (int i = 0; i < capacity; i++) {
                if (keys[i] != -1) {
                    int newIndex = hash(keys[i]);
                    while (newKeys[newIndex] != -1) { // 线性探查寻找空桶
                        newIndex = (newIndex + 1) % capacity;
                    }
                    newKeys[newIndex] = keys[i];
                    newNeverUsed[newIndex] = false;
                }
            }
            keys = newKeys;
            neverUsed = newNeverUsed;
        }
    }
};

int main() {
    HashTable table(10);
    table.insert(5);
    table.insert(15);
    table.insert(25);
    table.insert(35);
    cout << table.search(15) << endl;
	for(int i = 0; i < 10; i++)
	{
		cout<<table.neverUsed[i]<<" ";
	} 
	cout<<endl;
    table.remove(15);
    cout << table.search(15) << endl; 

    table.reorganize();
    for (int i = 0; i < 10; i++)
    {
        cout<<table.neverUsed[i]<<" "; 
    }
    return 0;
}
