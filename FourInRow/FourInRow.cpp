
#include <iostream>
#include<vector>
using namespace std;

const int rows = 6;
const int cols = 7;
class Board {
private:
    vector<vector<char>> brd;
public:
    Board()
    {
        brd = vector<vector<char>>(rows, vector<char>(cols, ' '));
    }
    void printBoard() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << brd[i][j] << "] ";
            }
            cout << endl;
        }
        
    }
    bool AddDisc(int col, char disc) {
        if (brd[0][col] != ' ')return false; // the board is full
        for (int i = rows - 1; i >= 0; i--) {
            if (brd[i][col] == ' ') {
                brd[i][col] = disc;
                return true;
            }
        }
        return false;
    }
    bool isRowWin(char disc) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 3; j++) {
                if (brd[i][j] == disc &&
                    brd[i][j + 1] == disc &&
                    brd[i][j + 2] == disc &&
                    brd[i][j + 3] == disc)
                    return true;
            }
        }
        return false;
    }
    bool isColWin(char disc) {
        for (int i = 0; i < rows-3; i++) {
            for (int j = 0; j < cols ; j++) {
                if (brd[i][j] == disc &&
                    brd[i+1][j] == disc &&
                    brd[i+2][j] == disc &&
                    brd[i+3][j ] == disc)
                    return true;
            }
        }
        return false;
    }
    bool isDiagonalWin(char disc) {
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < cols - 3; j++) {
                if (brd[i][j] == disc &&
                    brd[i + 1][j+1] == disc &&
                    brd[i + 2][j+2] == disc &&
                    brd[i + 3][j+3] == disc)
                    return true;
            }
        }
        for (int i = 0; i < rows-3; i++) {
            for (int j = cols - 1; j >= 3; j--) {
                if (brd[i][j] == disc &&
                    brd[i + 1][j -1] == disc &&
                    brd[i + 2][j - 2] == disc &&
                    brd[i + 3][j - 3] == disc)
                    return true;
            }
        }
        return false;

    }
    bool checkWin(char disc) {
        return isRowWin(disc) || isColWin(disc) || isDiagonalWin(disc);
    }

};
int main()
{
    Board* board = new Board();
    bool gameOver = false;
    int currentPlayer = 1;
    int col;
    char disc;
    while (!gameOver) {
        board->printBoard();
        if (currentPlayer == 1) {
            cout << "Player 1 (X), choose column (0-6): ";
            disc = 'X';
        }
        else {
            cout << "Player 2 (O), choose column (0-6): ";
            disc = 'O';
        }
        cin >> col;
        if (col < 0 || col >= cols) {
            cout << " Please choose a valid column (0-6)." << endl;
            continue;
        }

        if (!board->AddDisc(col, disc)) {
            cout << "Column full. choose other column." << endl;
            continue;
        }

        if (board->checkWin(disc)) {
            board->printBoard(); 
            cout << "Player " << currentPlayer << " wins!" << endl;
            gameOver = true;
        }
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        
    }
    delete board; 
    return 0;
}
