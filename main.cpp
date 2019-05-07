#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

int board[4][4];
pair<int, int> generateUnoccupiedPosition(){
    int occupied = 1, row, column;
    while (occupied) {
        row = rand() % 4;
        column = rand() % 4;
        if (board[row][column] == 0) {
            occupied = 0;
        }
    }
    return make_pair(row, column);
}

/*Movement*/
/*Up = 2, right = 1, down = 0, left = 3*/

int directionRow[] = {1, 0, -1, 0};
int directionColumn[] = {0, 1, 0, -1};

void generateNewNumber(){
    pair<int, int> position = generateUnoccupiedPosition();
    board[position.first][position.second] = 2;
}

void newGame(){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = 0;
        }
    }
    generateNewNumber();
    pair<int, int> position = generateUnoccupiedPosition();
    board[position.first][position.second] = 2;
}

void printUI(){
    system("cls");
    for (auto &i : board) {
        for (int j : i) {
            if (j == 0) {
                cout << ".      ";
            } else {
                cout << j << "      ";
            }
        }
        cout << endl;
    }
    cout << "n - new game" << endl;
    cout << "wasd - controls" << endl;
    cout << "q - quit" << endl;
}

bool canMakeMove(int row, int column, int nextRow, int nextColumn){
    return !(nextRow < 0 || nextColumn < 0 || nextRow >= 4 || nextColumn >= 4 || (board[row][column] != board[nextRow][nextColumn] && board[nextRow][nextColumn] !=0));
}

void applyMove(int direction){
    int startRow = 0;
    int startColumn = 0;
    int stepRow = 1;
    int stepColumn = 1;

    if (direction == 0) {
        startRow = 3;
        stepRow = -1;
    }
    if (direction == 1) {
        startColumn = 3;
        stepColumn = -1;
    }

    int movePossible = 0;
    for (int i = startRow; i>= 0 && i < 4; i += stepRow) {
        for (int j = startColumn; j >= 0 && j < 4; j += stepColumn) {
            int nextI = i + directionRow[direction];
            int nextJ = j + directionColumn[direction];

            if (canMakeMove(i, j, nextI, nextJ)) {
                board[nextI][nextJ] += board[i][j];
                board[i][j] = 0;
                movePossible = 1;
            }
        }
    }
    if (movePossible) {
        generateNewNumber();
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main() {

    srand(time(0));
    char commandToDirection[128];
    commandToDirection['s'] = 0;
    commandToDirection['d'] = 1;
    commandToDirection['w'] = 2;
    commandToDirection['a'] = 3;

    newGame();
    while (true) {
        printUI();
        char command;
        cin >> command;

        if (command == 'n') {
            newGame();
        } else if (command == 'q') {
            break;
        } else {
            int currentDirection = commandToDirection[command];
            applyMove(currentDirection);
        }
    }

    return 0;
}
#pragma clang diagnostic pop