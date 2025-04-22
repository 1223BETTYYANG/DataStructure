#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    int capacity; // ɢ�б������
    vector<int> keys; // �洢��������
     // ÿ��Ͱ�Ƿ�ʹ�ù��ı��

    int hash(int key) {
        return key % capacity; // �򵥵Ĺ�ϣ����������ֱ��ʹ��ȡģ
    }

public:
	vector<bool> neverUsed;
    HashTable(int capacity) {
        this->capacity = capacity;
        keys = vector<int>(capacity, -1); // ��ʼ�����м�Ϊ-1
        neverUsed = vector<bool>(capacity, true); // ��ʼ������Ͱ��neverUsedΪtrue
    }
void insert(int key) {
        int index = hash(key);
        while (keys[index] != -1) { // ����̽��Ѱ�ҿ�Ͱ
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        neverUsed[index] = false; // ��������neverUsed
    }

    bool search(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // ��ɢ�б���Ѱ�Ҽ�
            index = (index + 1) % capacity;
            counter++;
        }
        return keys[index] == key;
    }
     void remove(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // Ѱ��Ҫɾ���ļ�
            index = (index + 1) % capacity;
            counter++;
        }
        if (keys[index] == key) {
            keys[index] = -1;
            neverUsed[index] = true; // ���ΪneverUsed
        }
    }

    void reorganize() {
        int threshold = 0.6 * capacity; // 60%�Ŀ�Ͱ��neverUsed���ֵΪfalseʱ��������֯ɢ�б�
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
                    while (newKeys[newIndex] != -1) { // ����̽��Ѱ�ҿ�Ͱ
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
