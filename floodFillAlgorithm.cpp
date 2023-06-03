#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> floodFill(vector<vector<int>> board, int pos[2], int replaceValue){
    if (board.at(pos[0]).at(pos[1]) == replaceValue){
        board.at(pos[0]).at(pos[1]) = 2;

        if (pos[0] + 1 < board.size()){
            int pos1[] = {pos[0] + 1, pos[1]};
            board = floodFill(board, pos1, replaceValue);
        }
        if (pos[0] - 1 >= 0){
            int pos2[] = {pos[0] - 1, pos[1]};
            board = floodFill(board, pos2, replaceValue);
        }
        if (pos[1] + 1 < board.at(0).size()){
            int pos3[] = {pos[0], pos[1] + 1};
            board = floodFill(board, pos3, replaceValue);
        }
        if (pos[1] - 1 >= 0){
            int pos4[] = {pos[0], pos[1] - 1};
            board = floodFill(board, pos4, replaceValue);
        }
    }
    return board;
}
vector<vector<int>> floodFill(vector<vector<int>> board, int i, int j, int replaceValue) {
    if (board.at(i).at(j) == replaceValue) {
        board.at(i).at(j) = 2;

        if (i + 1 < board.size()) {
            int pos1[] = { i + 1, j };
            board = floodFill(board, pos1, replaceValue);
        }
        if (i - 1 >= 0) {
            int pos2[] = { i - 1, j };
            board = floodFill(board, pos2, replaceValue);
        }
        if (j + 1 < board.at(0).size()) {
            int pos3[] = { i, j + 1 };
            board = floodFill(board, pos3, replaceValue);
        }
        if (j - 1 >= 0) {
            int pos4[] = { j, j - 1 };
            board = floodFill(board, pos4, replaceValue);
        }
    }
    return board;
}

int main(){
    vector<vector<int>> board = {
        {1,1,0,1,1,1,1,1,1,1},
        {1,1,0,1,0,0,0,0,0,1},
        {1,0,0,0,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,1,1,1},
        {1,1,1,0,1,1,0,0,1,1},
        {1,1,0,0,0,0,1,0,1,1},
        {1,1,0,1,1,1,1,0,0,0},
        {1,1,0,1,1,1,1,1,1,1},
        {1,1,0,1,1,1,1,1,1,1},
    };
    int pos[2] = {2,0};
    board = floodFill(board,pos,0);
    for (vector<int> v1:board){
        cout << "{";
        for (int n:v1){
            cout << n << ",";
        }
        cout << "}" << endl;
    }
}