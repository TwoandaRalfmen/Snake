#include <iostream>
#include <string>

class SnakeBoard {
public:
    void initBoard() {
        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 15; x++) {
                if (((x + y) % 2) == 0) {
                    board[y][x] = '.';
                }
                else {
                    board[y][x] = '*';
                }
            }
        }
    }
    void printBoard() {
        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 15; x++) {
                std::cout << board[y][x];
            }
            std::cout << std::endl;
        }
    }
private:
    char board[15][15];

};

int main() {
    SnakeBoard SnakeBoard;
    SnakeBoard.initBoard();
    SnakeBoard.printBoard();
}