#pragma once

;
using namespace std;

class GenerateBoard {
    public : void generate(char board[3][3]) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << " " << board[i][j] << " ";
                if(j < 2) cout << "|";
            }
            cout << endl;
            if(i < 2) cout << "---+---+---" << endl;
        }
    }

    public : void generate(int board[3][3]) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << " " << board[i][j] << " ";
                if(j < 2) cout << "|";
            }
            cout << endl;
            if(i < 2) cout << "---+---+---" << endl;
            }
    }

    public : void generate(char board1[3][3], int board2[3][3], int board3[3][3]) {
        for(int i = 0; i < 3; i++) {

        // Board 1
        for(int j = 0; j < 3; j++) {
            cout << " " << board1[i][j] << " ";
            if(j < 2) cout << "|";
        }

        cout << "     ";

        // Board 2
        for(int j = 0; j < 3; j++) {
            cout << " " << board2[i][j] << " ";
            if(j < 2) cout << "|";
        }

        cout << "     ";

        // Board 3
        for(int j = 0; j < 3; j++) {
            cout << " " << board3[i][j] << " ";
            if(j < 2) cout << "|";
        }

        cout << endl;

        if(i < 2) {
            cout << "---+---+---     ---+---+---     ---+---+---\n";
        }
        }

        cout << endl;
    }
};
