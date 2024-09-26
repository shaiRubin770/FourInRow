
#include <iostream>
#include<vector>
#include <cstdlib>  
#include <ctime>
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
    bool isBoardFull() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (brd[i][j] == ' ') return false;
            }
            return true;
        }
    }
};
class Player {
public:
    char disc;
    string name;
    Player(char disc,const string & name):disc(disc),name(name){}
};
class TwoPlayersGame {
private:
    Board board;
    Player p1;
    Player p2;
    bool gameOver = false;
public:
    TwoPlayersGame():p1('X', "player1"), p2('O', "player2") {}
    void Play() {
        bool isPlayer1 = true;
        while (!gameOver) {
            board.printBoard();
            int col;
            Player& player= (isPlayer1) ? p1 : p2;
            cout << player.name << " enter number of col from 0 to 6 :";
            cin >> col;
            if (col<0 || col>=cols|| !board.AddDisc(col, player.disc)) {
                cout << " not good, try again" << endl;
                continue;
            }
            if (board.checkWin(player.disc)) {
                board.printBoard();
                cout<< player.name<<" wins!";
                gameOver=true;
            }
            if (board.isBoardFull()) {
                cout << "the board is full, the game is finised in TEKO" << endl;
                gameOver = true;
            }
            isPlayer1 = (!isPlayer1);
        }
    }
};
class ComputerVsUser {
private:
    Board board;
    Player human;
    Player computer;
    bool gameOver = false;

public:
    ComputerVsUser() : human('X', "Human"), computer('O', "Computer") {}
    bool CanWinInTheNextTurn(int col, char disc) {
        Board tmpBoard= board;
        if (tmpBoard.AddDisc(col, disc)) {
            return tmpBoard.checkWin(disc);
        }
        return false;
    }


    void Play() {
        bool humanTurn = true;
        while (!gameOver) {
            board.printBoard();
            int col;

            if (humanTurn) {
                cout << human.name << " enter number of col from 0 to 6: ";
                cin >> col;
            }
            else {
                bool isOneMoveToWin = false;
                for (int i = 0; i < cols; i++) {
                    if (CanWinInTheNextTurn(i, computer.disc) ){
                        col=i;
                        cout << "the computer choose in the winning col " << col << endl;
                        isOneMoveToWin=true;
                        break;
                    }
                }
                if (!isOneMoveToWin) {
                    for (int i = 0; i < cols; i++) {
                        if (CanWinInTheNextTurn(i, human.disc)) {
                            col = i;
                            cout << "the computer block the user from win and choose: " << col << endl;
                            isOneMoveToWin = true;
                            break;
                        }
                    }
                }
                if (!isOneMoveToWin) {
                    col = rand() % cols;
                    cout << "Computer chooses random column: " << col << endl;
                }
            }

            Player& currentPlayer = humanTurn ? human : computer;

            if (col < 0 || col >= cols || !board.AddDisc(col, currentPlayer.disc)) {
                if (humanTurn) {
                    cout << "Not a valid move, try again" << endl;
                    continue;
                }
                continue;
            }

            if (board.checkWin(currentPlayer.disc)) {
                board.printBoard();
                cout << currentPlayer.name << " wins!" << endl;
                gameOver = true;
            }
            
            if (board.isBoardFull()) {
                cout << "the board is full, the game is finised in TEKO" << endl;
                gameOver = true;
            }
            humanTurn = !humanTurn;  
        }
    }
};

int main()
{
    /*woPlayersGame twoPlayerGame;
    twoPlayerGame.Play();*/
    ComputerVsUser computerGame;
    computerGame.Play();
    return 0;
}

