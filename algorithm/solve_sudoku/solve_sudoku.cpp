#include <vector>
#include <iostream>

using namespace std;

// 数独
// 回溯（二维递归）

class Solution {
private:
    bool backtracking(vector<vector<char>>& board) {
        for (int i=0; i<board.size(); i++)
            for (int j=0; j<board[0].size(); j++) {
                if (board[i][j] != '.')
                    continue;
                for (char k='1'; k<='9'; k++) {
                    if (isValid(i,j,k,board)) {
                        board[i][j] = k;
                        if (backtracking(board))
                            return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        return true;
    }

    bool isValid(int row, int col, char val, vector<vector<char>>& board) {
        for (int i=0; i<9; i++) {
            if (board[row][i] == val) {
                return false;
            }
        }
        for (int j=0; j<9; j++) {
            if (board[j][col] == val) {
                return false;
            }
        }

        int startRow = (row/3) * 3;
        int startCol = (col/3) * 3;
        for (int i=startRow; i<startRow+3; i++) {
            for (int j=startCol; j<startCol+3; j++) {
                if(board[i][j] == val) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};

int main() {
    vector<vector<char>> board={
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    Solution solution;
    solution.solveSudoku(board);

    for (int i=0; i<board.size();i++)
    {
        for (int j=0;j<board[i].size();j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}