#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Trie {
private:
//    vector<Trie*> children;
//    bool isEnd;
//    Trie *searchPrefix(string prefix) {
//        Trie* node = this;
//        for (char ch: prefix) {
//            ch -= 'a';
//            if (node->children[ch] == nullptr) {
//                return nullptr;
//            }
//            node = node->children[ch];
//        }
//        return node;
//    }

public:
    vector<Trie*> children;
    bool isEnd;
    Trie *searchPrefix(string prefix) {
        Trie* node = this;
        for (char ch: prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }

    Trie():children(26),isEnd(false) {}

    void insert(string word) {
        Trie* node = this;
        for (char ch :word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd= true;
    }

    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};

void printArr(Trie& trie) {
    for (int i=0; i<trie.children.size(); i++) {
        if (trie.children[i] != nullptr && trie.children[i]->isEnd) {
            cout << char(i+'a') << endl;

        }
        if (trie.children[i] != nullptr && !trie.children[i]->isEnd) {
            cout << char(i+'a') << endl;
            printArr(*trie.children[i]);
        }
    }
}

int main() {
    bool ret;
    Trie trie;
    cout << boolalpha;

    trie.insert("apple");
    printArr(trie);
    cout << endl;

    ret = trie.search("apple");
    cout <<ret<<endl; // true
    ret = trie.search("app");
    cout <<ret<<endl; // false
    ret = trie.startsWith("app");
    cout <<ret<<endl; // false
}