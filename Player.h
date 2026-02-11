#pragma once

    char getPlayer(char board[3][3]) {
        int counterX = 0;
        int counterO = 0;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == 'x')
                    counterX++;

                if(board[i][j] == 'o')
                    counterO++;
            }
        }

        if(counterX <= counterO)
            return 'x';

        if(counterX > counterO)
            return 'o';

        return 'x';
    }
