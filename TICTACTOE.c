#include <stdio.h>
#include <limits.h>
#include <math.h>
#define HUMAN 'X'
#define AI 'O'

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        printf("-------------\n");
    }
}

int isMovesLeft() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 1;
            }
        }
    }
    return 0;
}

int evaluate() {
    // Checking rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }

    // Checking columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }

    // Checking diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }

    // No one has won
    return 0;
}

int minimax(int depth, int isMax, int alpha, int beta) {
    int score = evaluate();

    // If AI has won the game return evaluated score
    if (score == 10) return score;

    // If Human has won the game return evaluated score
    if (score == -10) return score;

    // If there are no more moves and no winner then it is a draw
    if (!isMovesLeft()) return 0;

    // If this is maximizer's move
    if (isMax) {
        int best = INT_MIN;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = AI;

                    // Call minimax recursively and choose the maximum value
                    best = fmax(best, minimax(depth + 1, !isMax, alpha, beta));
                    alpha = fmax(alpha, best);

                    // Undo the move
                    board[i][j] = ' ';

                    // Alpha Beta Pruning
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }

    // If this is minimizer's move
    else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = HUMAN;

                    // Call minimax recursively and choose the minimum value
                    best = fmin(best, minimax(depth + 1, !isMax, alpha, beta));
                    beta = fmin(beta, best);

                    // Undo the move
                    board[i][j] = ' ';

                    // Alpha Beta Pruning
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

void findBestMove(int* bestMoveRow, int* bestMoveCol) {
    int bestVal = INT_MIN;

    *bestMoveRow = -1;
    *bestMoveCol = -1;

    // Traverse all cells, evaluate minimax function for all empty cells.
    // And return the cell with the optimal value.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == ' ') {
                // Make the move
                board[i][j] = AI;

                // Compute evaluation function for this move
                int moveVal = minimax(0, 0, INT_MIN, INT_MAX);

                // Undo the move
                board[i][j] = ' ';

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal) {
                    *bestMoveRow = i;
                    *bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

void playGame() {
    int x, y;
    while (1) {
        printBoard();

        if (evaluate() == 10) {
            printf("AI wins!\n");
            break;
        } else if (evaluate() == -10) {
            printf("You win!\n");
            break;
        } else if (!isMovesLeft()) {
            printf("It's a draw!\n");
            break;
        }

        printf("Enter your move (row and column): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
            printf("Invalid move, try again.\n");
            continue;
        }

        board[x][y] = HUMAN;

        if (evaluate() == 10) {
            printBoard();
            printf("AI wins!\n");
            break;
        } else if (evaluate() == -10) {
            printBoard();
            printf("You win!\n");
            break;
        } else if (!isMovesLeft()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        int bestMoveRow, bestMoveCol;
        findBestMove(&bestMoveRow, &bestMoveCol);
        board[bestMoveRow][bestMoveCol] = AI;

        if (evaluate() == 10) {
            printBoard();
            printf("AI wins!\n");
            break;
        } else if (evaluate() == -10) {
            printBoard();
            printf("You win!\n");
            break;
        } else if (!isMovesLeft()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
    }
}

int main() {
    initializeBoard();
    playGame();
    return 0;
}
