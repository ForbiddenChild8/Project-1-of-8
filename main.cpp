#include <iostream>
#include <cmath>
#include "Move.h"
#include "GenerateBoard.h"
#include "Think.h"

using namespace std;

int main()
{
    char board[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };

    int nodeMap[3][3] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};

    GenerateBoard gen;
    Think human(board, nodeMap);

    int choice = -1;
    int x = -1, y = -1;

    gen.generate(board, nodeMap, nodeMap);

    for(int i = 0; i < 9;) {
        int maxChoices = human.countEmptySpaces(board);

        cout << "Choose a move from 1 to " << human.countEmptySpaces(board) << ":" << endl;
        cin >> choice;

        while(choice > maxChoices || choice < 1) {
            cout << "Invalid move. Try again" << endl;
            cout << "Choose a move from 1 to " << human.countEmptySpaces(board) << ":" << endl;
            cin >> choice;
        }

        cout << endl;

        human.playMove(choice, i, board, nodeMap);

        int checkInt = human.checkForWin(board, 'x');
        if(checkInt != 0) {
            cout << "X WINS!!!" << endl;
            return 1;
        }

        i++;

        Think think(board, nodeMap);
        int choiceAI = think.eval(i);

        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                if(nodeMap[j][k] == choiceAI) {
                    y = j;
                    x = k;
                }
            }
        }

        think.playMove(nodeMap[y][x], i, board, nodeMap);
        gen.generate(board, nodeMap, nodeMap);

        checkInt = human.checkForWin(board, 'o');
        if(checkInt != 0) {
            cout << "O WINS!!!" << endl;
            return 1;
        }

        i++;
    }

    return 0;
}
