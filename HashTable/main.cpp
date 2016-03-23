//
//  main.cpp
//  HashTable
//
//  a hash table is essentially a dictionary, i.e., a container for (key, value) pairs
//  keys are mapped to indices (buckets) by a hash function
//  every bucket is a linked list
//

#include <iostream>

using namespace std;

typedef struct KeyValueNode {
    string key;
    string value;
    KeyValueNode * next = NULL;
    KeyValueNode(string theKey, string theValue) {
        key = theKey;
        value = theValue;
    }
} KeyValueNode;

class HashTable {
public:
    int nBuckets = 31;
    KeyValueNode ** buckets;
    
    HashTable() {
        buckets = (KeyValueNode **)malloc(nBuckets*sizeof(KeyValueNode *));
        for (int i = 0; i < nBuckets; i++) {
            buckets[i] = NULL;
        }
    }
    
    ~HashTable() {
        for (int i = 0; i < nBuckets; i++) {
            KeyValueNode * node = buckets[i];
            while (node != NULL) {
                KeyValueNode * tmpNode = node;
                node = node->next;
                delete tmpNode;
            }
        }
        free(buckets);
    }
    
    int hash(string s) {
        int h = 0;
        for (int i = 0; i < s.length(); i++) {
            h = (h*3 % nBuckets)+s.at(i);
        }
        return h % nBuckets;
    }
    
    void put(string key, string value) {
        int index = hash(key);
        KeyValueNode * bucket = buckets[index];
        if (bucket == NULL) {
            buckets[index] = new KeyValueNode(key, value);
        } else { // handle collision
            KeyValueNode * node = bucket;
            while (node->next != NULL) {
                node = node->next;
            }
            node->next = new KeyValueNode(key, value);
        }
    }
    
    string get(string key) {
        int index = hash(key);
        string value;
        KeyValueNode * node = buckets[index];
        while (node != NULL) {
            if (key.compare(node->key) == 0) {
                value = node->value;
                break;
            } else {
                node = node->next;
            }
        }
        return value;
    }
};

int main(int argc, const char * argv[]) {
    HashTable * ht = new HashTable();
    
    ht->put("one", "1");
    ht->put("two", "2");
    ht->put("three", "3");
    ht->put("four", "4");
    ht->put("five", "5");
    ht->put("six", "6");
    ht->put("seven", "7");
    
    string value = ht->get("three");
    if (!value.empty())
        cout << value << endl;
    value = ht->get("two");
    if (!value.empty())
        cout << value << endl;
    value = ht->get("one");
    if (!value.empty())
        cout << value << endl;
    value = ht->get("zero");
    if (!value.empty())
        cout << value << endl;
    value = ht->get("seven");
    if (!value.empty())
        cout << value << endl;
    
    delete ht;
    
    return 0;
}

