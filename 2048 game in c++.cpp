#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _getch() function on Windows

const int SIZE = 4;

std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));

void PrintBoard() {
    system("cls"); // Clear the console
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0)
                std::cout << " . ";
            else
                std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GenerateRandom() {
    int emptyCount = 0;
    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyCells.push_back(std::make_pair(i, j));
                emptyCount++;
            }
        }
    }

    if (emptyCount == 0)
        return;

    int randomIndex = rand() % emptyCount;
    int value = (rand() % 2 + 1) * 2; // Randomly generate 2 or 4
    int x = emptyCells[randomIndex].first;
    int y = emptyCells[randomIndex].second;
    board[x][y] = value;
}

bool IsGameOver() {
    // Check if the board is full
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0)
                return false;
        }
    }

    // Check for possible moves
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
                return false;
        }
    }

    return true;
}

void MoveLeft() {
    for (int i = 0; i < SIZE; ++i) {
        std::vector<int> newRow;
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0)
                newRow.push_back(board[i][j]);
        }

        for (int j = 0; j < newRow.size() - 1; ++j) {
            if (newRow[j] == newRow[j + 1]) {
                newRow[j] *= 2;
                newRow[j + 1] = 0;
            }
        }

        int index = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (newRow[j] != 0)
                board[i][index++] = newRow[j];
        }
        while (index < SIZE)
            board[i][index++] = 0;
    }
}

void MoveRight() {
    for (int i = 0; i < SIZE; ++i) {
        std::vector<int> newRow;
        for (int j = SIZE - 1; j >= 0; --j) {
            if (board[i][j] != 0)
                newRow.push_back(board[i][j]);
        }

        for (int j = 0; j < newRow.size() - 1; ++j) {
            if (newRow[j] == newRow[j + 1]) {
                newRow[j] *= 2;
                newRow[j + 1] = 0;
            }
        }

        int index = SIZE - 1;
        for (int j = newRow.size() - 1; j >= 0; --j) {
            if (newRow[j] != 0)
                board[i][index--] = newRow[j];
        }
        while (index >= 0)
            board[i][index--] = 0;
    }
}

void MoveUp() {
    for (int j = 0; j < SIZE; ++j) {
        std::vector<int> newColumn;
        for (int i = 0; i < SIZE; ++i) {
            if (board[i][j] != 0)
                newColumn.push_back(board[i][j]);
        }

        for (int i = 0; i < newColumn.size() - 1; ++i) {
            if (newColumn[i] == newColumn[i + 1]) {
                newColumn[i] *= 2;
                newColumn[i + 1] = 0;
            }
        }

        int index = 0;
        for (int i = 0; i < SIZE; ++i) {
            if (newColumn[i] != 0)
                board[index++][j] = newColumn[i];
        }
        while (index < SIZE)
            board[index++][j] = 0;
    }
}

void MoveDown() {
    for (int j = 0; j < SIZE; ++j) {
        std::vector<int> newColumn;
        for (int i = SIZE - 1; i >= 0; --i) {
            if (board[i][j] != 0)
                newColumn.push_back(board[i][j]);
        }

        for (int i = 0; i < newColumn.size() - 1; ++i) {
            if (newColumn[i] == newColumn[i + 1]) {
                newColumn[i] *= 2;
                newColumn[i + 1] = 0;
            }
        }

        int index = SIZE - 1;
        for (int i = newColumn.size() - 1; i >= 0; --i) {
            if (newColumn[i] != 0)
                board[index--][j] = newColumn[i];
        }
        while (index >= 0)
            board[index--][j] = 0;
    }
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Initial setup
    GenerateRandom();
    GenerateRandom();

    while (true) {
        PrintBoard();

        if (IsGameOver()) {
            std::cout << "Game Over!" << std::endl;
            break;
        }

        char move = _getch(); // Wait for keyboard input

        switch (move) {
            case 'a':
                MoveLeft();
                break;
            case 'd':
                MoveRight();
                break;
            case 'w':
                MoveUp();
                break;
            case 's':
                MoveDown();
                break;
            default:
                std::cout << "Invalid move. Use 'a' (left), 'd' (right), 'w' (up), 's' (down)." << std::endl;
                break;
        }

        GenerateRandom();
    }

    return 0;
}
