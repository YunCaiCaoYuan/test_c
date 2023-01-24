#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

// 回溯 + Trie

struct TrieNode {
    string word;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        this->word = "";
    }
};

void insertTrie(TrieNode * root, const string & word) {
    TrieNode * node = root;
    for (auto c : word) {
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->word = word;
}

class Solution {
public :
    int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    bool dfs(vector<vector<char>>& board, int x, int y, TrieNode* root, set<string>& res) {
        char ch = board[x][y];
        if (!root->children.count(ch)) {
            return false;
        }
        root = root->children[ch];
        if (root->word.size() > 0) {
            res.insert(root->word);
        }

        board[x][y] = '#';
        for (int i=0; i<4; ++i) {
            int nx = x+dirs[i][0];
            int ny = y+dirs[i][1];
            if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
                if (board[nx][ny] != '#') {
                    dfs(board, nx, ny, root, res);
                }
            }
        }
        board[x][y] = ch;

        return true;
    }

    vector<string> findWords(vector<vector<char>> & board, vector<string> & words) {
        TrieNode * root = new TrieNode();
        set<string> res;
        vector<string> ans;

        for (auto & word: words) {
            insertTrie(root, word);
        }
        for (int i=0; i<board.size(); ++i) {
            for (int j=0; j<board[0].size(); ++j) {
                dfs(board, i, j, root, res);
            }
        }
        for (auto &word: res) {
            ans.emplace_back(word);
        }
        return ans;
    }

};

// 输出：["eat","oath"]
int main() {
    Solution solution;
    vector<vector<char>> board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
    };
    vector<string> words = {"oath","pea","eat","rain"};
    vector<string> res = solution.findWords(board, words);
    for (int i=0; i<res.size();i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}