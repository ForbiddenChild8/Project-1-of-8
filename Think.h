#pragma once
#include "Move.h"
#include "Player.h"
#include "GenerateBoard.h"
#include <cmath>
#include <algorithm>

class Think {

    public : Think(char playerBoard[3][3], int pNodeMap[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                evalBoard[i][j] = playerBoard[i][j];
                nodeMap[i][j] = pNodeMap[i][j];
            }
        }
    }

    char evalBoard[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };

    int nodeMap[3][3] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};

    float heatMap[3][3] =  {{0.2, 0.1, 0.2},
                            {0.1, 0.3, 0.1},
                            {0.2, 0.1, 0.2}};

    Move pCoordinate[9] = {};
    GenerateBoard gen;

    int countEmptySpaces(char board[3][3]) {
    int count = 0;

    for(int r = 0; r < 3; r++) {
        for(int c = 0; c < 3; c++) {
            if(board[r][c] == ' ')
                count++;
        }
    }

    return count;
    }

    void undoMoveTree(int target, int depth) {
            int a = -1;
            int b = -1;

            if(target > 0) {
                // Restore previous target
                a = pCoordinate[depth].y;
                b = pCoordinate[depth].x;
                nodeMap[a][b] = target;

                // Increment all >= pTarget except previous move
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(!(j == b && i == a) && nodeMap[i][j] >= target) {
                        nodeMap[i][j]++;
                        }
                    }
                }
            }

            evalBoard[pCoordinate[depth].y][pCoordinate[depth].x] = ' ';
}

    public : void undoMove(int target, int depth, char (&board)[3][3], int (&nodeMap)[3][3]) {
            int a = -1;
            int b = -1;

            if(target > 0) {
                // Restore previous target
                a = pCoordinate[depth].y;
                b = pCoordinate[depth].x;
                nodeMap[a][b] = target;

                // Increment all >= pTarget except previous move
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(!(j == b && i == a) && nodeMap[i][j] >= target) {
                        nodeMap[i][j]++;
                        }
                    }
                }
            }

            board[pCoordinate[depth].y][pCoordinate[depth].x] = ' ';
}

    void playMoveTree(int target, int depth) {
            bool targetFound = false;

            for(int i = 0; i < 3 && targetFound == false; i++) {
                for(int j = 0; j < 3 && targetFound == false; j++) {
                    if(nodeMap[i][j] == target && targetFound == false) {
                        // Target Found
                        targetFound = true;
                        nodeMap[i][j] = 0;

                        // Save the coordinates of target
                        pCoordinate[depth].x = j;
                        pCoordinate[depth].y = i;
                    }
                }
            }

            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(targetFound == true) {
                        // When numbers bigger than target are found, decrement them by 1
                        if(nodeMap[i][j] > target) {
                        nodeMap[i][j]--;
                        }
                    }
                }
            }

            evalBoard[pCoordinate[depth].y][pCoordinate[depth].x] = getPlayer(evalBoard);
}

    public : void playMove(int target, int depth, char (&board)[3][3], int (&nodeMap)[3][3]) {
            bool targetFound = false;

            for(int i = 0; i < 3 && targetFound == false; i++) {
                for(int j = 0; j < 3 && targetFound == false; j++) {
                    if(nodeMap[i][j] == target && targetFound == false) {
                        // Target Found
                        targetFound = true;
                        nodeMap[i][j] = 0;

                        // Save the coordinates of target
                        pCoordinate[depth].x = j;
                        pCoordinate[depth].y = i;
                    }
                }
            }

            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(targetFound == true) {
                        // When numbers bigger than target are found, decrement them by 1
                        if(nodeMap[i][j] > target) {
                        nodeMap[i][j]--;
                        }
                    }
                }
            }

            board[pCoordinate[depth].y][pCoordinate[depth].x] = getPlayer(board);
}

    public : int checkForWin(char board[3][3], char player) {
        // Check rows + columns
        for(int i = 0; i < 3; i++) {
            // Row
            if(board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
            return 1;

            // Column
            if(board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
            return 1;
        }

        // Main diagonal
        if(board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
        return 1;

        // Anti-diagonal
        if(board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
        return 1;

        return 0;
}

    public : int possibleWinChecker(char player) {
        int winCounter = 0, counter = 0;
        bool possibleWin = false;

        // Horizontal Checker
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(evalBoard[i][j] == player)
                    counter++;

                if(evalBoard[i][j] == ' ')
                    possibleWin = true;

                if(counter == 2 && possibleWin == true)
                    winCounter++;
            }
            counter = 0;
            possibleWin = false;
        }

        // Vertical Check.
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(evalBoard[j][i] == player)
                    counter++;

                if(evalBoard[j][i] == ' ')
                    possibleWin = true;

                if(counter == 2 && possibleWin == true)
                    winCounter++;
            }
            counter = 0;
            possibleWin = false;
        }

        // First Diagonal Check.
        for(int i = 0; i < 3; i++) {
            if(evalBoard[i][i] == player)
                counter++;

            if(evalBoard[i][i] == ' ')
                possibleWin = true;

            if(counter == 2 && possibleWin == true)
                winCounter++;
        }

        counter = 0;
        possibleWin = false;

        // Second Diagonal Check
        for(int i = 0; i < 3; i++) {
            if(evalBoard[2-i][i] == player)
                counter++;

            if(evalBoard[2-i][i] == ' ')
                possibleWin = true;

            if(counter == 2 && possibleWin == true)
                winCounter++;
        }

        counter = 0;
        possibleWin = false;

        return winCounter;
}

    public : int eval(int startingDepth) {
        int maxBranches = 9;
        int maxDepth = 8;
        int depth = startingDepth;

        float score = 0;
        float maxScorePlayer = -100000;
        string maxScorePlayerLine;

        int bestMoveChoice = 0;

        float playerScore[9] = {0};
        float predictiveScore[9] = {0};

        int k[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int pDepth[9] = {0};

        char player = 'x';
        char opponent = 'o';
        bool multipleBacktrackings = false;

        while(true) {

            //this_thread::sleep_for(std::chrono::milliseconds(800));

            if(depth == startingDepth && pDepth[startingDepth] >= k[startingDepth]) {
                break;     // all options exhausted at the root
            }

            if(pDepth[depth] >= k[depth]) {
                if(multipleBacktrackings == false) {
                    undoMoveTree(pDepth[depth], depth);
                    if(playerScore[depth] != 0) {
                        score -= playerScore[depth];
                        playerScore[depth] = 0;
                    }

                    predictiveScore[depth] = 0;
                    multipleBacktrackings = true;
                }

                pDepth[depth] = 0;
                k[depth] = maxBranches - depth;

                depth--;

                undoMoveTree(pDepth[depth], depth);
                if(playerScore[depth] != 0) {
                    score -= playerScore[depth];
                    playerScore[depth] = 0;
                }

                predictiveScore[depth] = 0;
                continue;
            }

            player = getPlayer(evalBoard);
            int playerInt = (player == 'x') ? -1 : 1;
            opponent = (player == 'x') ? 'o' : 'x';

            multipleBacktrackings = false;
            pDepth[depth]++;

            /// Start of analysis
            float depthWeight = (16.0f - 2*(depth - startingDepth))/16;
            float attackWeight = 1.375f;
            float defendWeight = 1.1f;

            // Initialize predictiveScore for current depth
            predictiveScore[depth] = (player == 'x') ? 1000 : -1000;

            int prePlayer = possibleWinChecker(player);
            int preOpponent = possibleWinChecker(opponent);

            for(int move = 1; move <= k[depth]; move++) {
                float simScore = 0;
                playMoveTree(move, depth);

                if(depth == 1 || depth == 2) {
                    simScore += heatMap[pCoordinate[depth].y][pCoordinate[depth].x];
                }

                int postPlayer = possibleWinChecker(player);
                int postOpponent = possibleWinChecker(opponent);

                // Award for threat reduction
                int opponentDelta = preOpponent - postOpponent;
                simScore += depthWeight * defendWeight * opponentDelta * playerInt;

                // Penalize for not resolving threat
                opponentDelta = preOpponent == postOpponent ? postOpponent * 4 : 0;
                simScore += depthWeight * defendWeight * opponentDelta * -playerInt;

                // Award for creating threats.
                int playerDelta = std::pow(postPlayer - prePlayer, 2);
                simScore += depthWeight * attackWeight * playerDelta * playerInt;

                // Award for fulfilling threats
                playerDelta = prePlayer - postPlayer == 1 ? 10 : 0;
                simScore += depthWeight * attackWeight * playerDelta * playerInt;

                // Update predictiveScore based on player
                if(player == 'x')
                    {if(simScore < predictiveScore[depth]) predictiveScore[depth] = simScore;}
                    else {if(simScore > predictiveScore[depth]) predictiveScore[depth] = simScore;}
                undoMoveTree(move, depth);
            }

            if(predictiveScore[depth] == 1000 || predictiveScore[depth] == -1000)
                predictiveScore[depth] = 0;

            playMoveTree(pDepth[depth], depth);
            //gen.generate(evalBoard, nodeMap, nodeMap);

            int checkInt = checkForWin(evalBoard, player);
            if(checkInt != 0) {
                playerScore[depth] += depthWeight * attackWeight * playerInt * 10;
                score += playerScore[depth];

                if(score > maxScorePlayer) {
                    maxScorePlayer = score;
                    bestMoveChoice = pDepth[startingDepth];
                    maxScorePlayerLine = "";
                    for(int moveDepth : pDepth)
                        if(moveDepth > 0) maxScorePlayerLine += std::to_string(moveDepth);
                }

                score -= playerScore[depth];
                playerScore[depth] = 0;
                predictiveScore[depth] = 0;

                undoMoveTree(pDepth[depth], depth);
                k[depth] = pDepth[depth];
                multipleBacktrackings = true;
                continue;
            }

            int postPlayer = possibleWinChecker(player);
            int postOpponent = possibleWinChecker(opponent);

            // Award for threat reduction
            int opponentDelta = preOpponent - postOpponent;
            playerScore[depth] += depthWeight * defendWeight * opponentDelta * playerInt;

            // Penalize for not resolving threat
            opponentDelta = preOpponent == postOpponent ? postOpponent * 4 : 0;
            playerScore[depth] += depthWeight * defendWeight * opponentDelta * -playerInt;

            // Award for creating threats.
            int playerDelta = std::pow(postPlayer - prePlayer, 2);
            playerScore[depth] += depthWeight * attackWeight * playerDelta * playerInt;

            if(depth == 1 || depth == 2) {
                playerScore[depth] += heatMap[pCoordinate[depth].y][pCoordinate[depth].x];
            }

            if(playerScore[depth] != predictiveScore[depth]) {
                undoMoveTree(pDepth[depth], depth);

                playerScore[depth] = 0;
                predictiveScore[depth] = 0;
                continue;
            }

            score += playerScore[depth];
            /// End of analysis.

            // If we haven't reached max depth yet, go deeper
            if(depth < maxDepth) {
                depth++;
            }
            else {
                if(score > maxScorePlayer) {
                    maxScorePlayer = score;
                    bestMoveChoice = pDepth[startingDepth];
                    maxScorePlayerLine = "";
                    for(int moveDepth : pDepth)
                        if(moveDepth > 0) maxScorePlayerLine += std::to_string(moveDepth);
                }

                if(playerScore[depth] != 0) {
                    score -= playerScore[depth];
                    playerScore[depth] = 0;
                }

                predictiveScore[depth] = 0;

                undoMoveTree(pDepth[depth], depth);
                multipleBacktrackings = true;
                continue;
            }
        }
        return bestMoveChoice;
    }
};
