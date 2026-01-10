#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"

char board[3][3];
const char PLAYER = 'X';
const char PLAYER2 = 'O';
const char COMPUTER = 'O';

char player1Name[50], player2Name[50];
int difficulty = 1;

void printlogo();
void resetboard();
void printboard();
int checkfreespaces();
void playermove();
void player2move();
void computermove();
char checkwinner();
void printwinner(char);
void printwinnerpvp(char);
void chooseDifficulty();
void displayResults();

int main() {
    printlogo();
    srand(time(0));

    printf("Enter Player 1 Name: ");
    scanf("%s", player1Name);

    int choice;
    char response;
    char winner;

    do {
        printf("\n1. Player vs Computer\n2. Player vs Player\n3. View Results\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            chooseDifficulty();
            do {
                resetboard();
                winner = ' ';

                while (winner == ' ' && checkfreespaces() > 0) {
                    printboard();
                    printf("%s's Turn (X)\n", player1Name);
                    playermove();
                    winner = checkwinner();
                    if (winner != ' ' || checkfreespaces() == 0) break;

                    computermove();
                    winner = checkwinner();
                }

                printboard();
                printwinner(winner);

                printf("Play again? (Y/N): ");
                scanf(" %c", &response);
                response = toupper(response);

            } while (response == 'Y');

        } else if (choice == 2) {
            printf("Enter Player 2 Name: ");
            scanf("%s", player2Name);

            do {
                resetboard();
                winner = ' ';

                while (winner == ' ' && checkfreespaces() > 0) {
                    printboard();
                    printf("%s's Turn (X)\n", player1Name);
                    playermove();
                    winner = checkwinner();
                    if (winner != ' ' || checkfreespaces() == 0) break;

                    printboard();
                    printf("%s's Turn (O)\n", player2Name);
                    player2move();
                    winner = checkwinner();
                }

                printboard();
                printwinnerpvp(winner);

                printf("Play again? (Y/N): ");
                scanf(" %c", &response);
                response = toupper(response);

            } while (response == 'Y');

        } else if (choice == 3) {
            displayResults();
        }

    } while (choice != 4);

    printf("Thanks for playing\n");
    return 0;
}

void chooseDifficulty() {
    do {
        printf("Select Difficulty (1 Easy, 2 Medium, 3 Hard): ");
        scanf("%d", &difficulty);
    } while (difficulty < 1 || difficulty > 3);
}

void resetboard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printboard() {
    printf("\n   1   2   3\n");
    printf("1  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("  ---|---|---\n");
    printf("2  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("  ---|---|---\n");
    printf("3  %c | %c | %c\n\n", board[2][0], board[2][1], board[2][2]);
}

int checkfreespaces() {
    int free = 9;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != ' ') free--;
    return free;
}

void playermove() {
    int row, col;
    while (1) {
        printf("Enter row (1-3) for X: ");
        scanf("%d", &row);
        printf("Enter column (1-3) for X: ");
        scanf("%d", &col);

        row--;
        col--;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = PLAYER;
            break;
        }
        printf("Invalid move, try again\n");
    }
}

void player2move() {
    int row, col;
    while (1) {
        printf("Enter row (1-3) for O: ");
        scanf("%d", &row);
        printf("Enter column (1-3) for O: ");
        scanf("%d", &col);

        row--;
        col--;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = PLAYER2;
            break;
        }
        printf("Invalid move, try again\n");
    }
}

void computermove() {
    int r, c;

    if (difficulty >= 2) {
        for (r = 0; r < 3; r++)
            for (c = 0; c < 3; c++)
                if (board[r][c] == ' ') {
                    board[r][c] = PLAYER;
                    if (checkwinner() == PLAYER) {
                        board[r][c] = COMPUTER;
                        return;
                    }
                    board[r][c] = ' ';
                }
    }

    if (difficulty == 3) {
        for (r = 0; r < 3; r++)
            for (c = 0; c < 3; c++)
                if (board[r][c] == ' ') {
                    board[r][c] = COMPUTER;
                    if (checkwinner() == COMPUTER) return;
                    board[r][c] = ' ';
                }
    }

    do {
        r = rand() % 3;
        c = rand() % 3;
    } while (board[r][c] != ' ');

    board[r][c] = COMPUTER;
}

char checkwinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    return ' ';
}

void printwinner(char winner) {
    FILE *f = fopen("results.txt", "a");

    if (winner == PLAYER) {
        printf("%s Wins\n", player1Name);
        fprintf(f, "PVC | %s vs Computer | Winner: %s | Diff: %d\n", player1Name, player1Name, difficulty);
    } else if (winner == COMPUTER) {
        printf("Computer Wins\n");
        fprintf(f, "PVC | %s vs Computer | Winner: Computer | Diff: %d\n", player1Name, difficulty);
    } else {
        printf("Tie\n");
        fprintf(f, "PVC | %s vs Computer | Tie | Diff: %d\n", player1Name, difficulty);
    }

    fclose(f);
}

void printwinnerpvp(char winner) {
    FILE *f = fopen("results.txt", "a");

    if (winner == PLAYER) {
        printf("%s Wins\n", player1Name);
        fprintf(f, "PVP | %s vs %s | Winner: %s\n", player1Name, player2Name, player1Name);
    } else if (winner == PLAYER2) {
        printf("%s Wins\n", player2Name);
        fprintf(f, "PVP | %s vs %s | Winner: %s\n", player1Name, player2Name, player2Name);
    } else {
        printf("Tie\n");
        fprintf(f, "PVP | %s vs %s | Tie\n", player1Name, player2Name);
    }

    fclose(f);
}

void displayResults() {
    FILE *f = fopen("results.txt", "r");
    if (!f) {
        printf("No results found\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), f))
        printf("%s", line);
    fclose(f);
}

void printlogo() {
    printf("%s************************\n", CYAN);
    printf("*      %sTIC TAC TOE%s      *\n", RED, CYAN);
    printf("************************%s\n", RESET);
}
