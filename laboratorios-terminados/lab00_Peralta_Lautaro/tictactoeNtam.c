#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define N 4  // Puedes cambiar este valor para ajustar el tamaño del tablero
#define CELL_MAX (N * N - 1)

struct winner_data {
    bool is_winner;
    char winner;
};

void print_sep(int length) {
    printf("\t ");
    for (int i = 0; i < length; i++) printf("................");
    printf("\n");
}

void print_board(char board[N][N]) {
    int cell = 0;
    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

struct winner_data hayFila(char board[N][N]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    for (int fila = 0; fila < N; fila++) {
        bool fila_ganadora = true;
        for (int columna = 1; columna < N; columna++) {
            if (board[fila][columna] != board[fila][0] || board[fila][0] == '-') {
                fila_ganadora = false;
                break;
            }
        }
        if (fila_ganadora) {
            res.is_winner = true;
            res.winner = board[fila][0];
            break;
        }
    }
    return res;
}

struct winner_data hayColumna(char board[N][N]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    for (int columna = 0; columna < N; columna++) {
        bool columna_ganadora = true;
        for (int fila = 1; fila < N; fila++) {
            if (board[fila][columna] != board[0][columna] || board[0][columna] == '-') {
                columna_ganadora = false;
                break;
            }
        }
        if (columna_ganadora) {
            res.is_winner = true;
            res.winner = board[0][columna];
            break;
        }
    }
    return res;
}

struct winner_data hayDiag(char board[N][N]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    bool diag_ganadora = true;
    for (int i = 1; i < N; i++) {
        if (board[i][i] != board[0][0] || board[0][0] == '-') {
            diag_ganadora = false;
            break;
        }
    }
    if (diag_ganadora) {
        res.is_winner = true;
        res.winner = board[0][0];
    }
    return res;
}

struct winner_data hayDiagInv(char board[N][N]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    bool diag_inv_ganadora = true;
    for (int i = 1; i < N; i++) {
        if (board[i][N - i - 1] != board[0][N - 1] || board[0][N - 1] == '-') {
            diag_inv_ganadora = false;
            break;
        }
    }
    if (diag_inv_ganadora) {
        res.is_winner = true;
        res.winner = board[0][N - 1];
    }
    return res;
}

char get_winner(char board[N][N]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    res = hayFila(board);
    if (res.is_winner) { return res.winner; }
    res = hayColumna(board);
    if (res.is_winner) { return res.winner; }
    res = hayDiag(board);
    if (res.is_winner) { return res.winner; }
    res = hayDiagInv(board);
    if (res.is_winner) { return res.winner; }
    return res.winner;
}

bool has_free_cell(char board[N][N]) {
    bool free_cell = false;
    for (int i = 0; i < N && !free_cell; i++) {
        for (int j = 0; j < N && !free_cell; j++) {
            free_cell = (board[i][j] == '-');
        }
    }
    return free_cell;
}

int main(void) {
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posicion (numero del 0 al %d): ", turn, CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un numero desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / N;
            int colum = cell % N;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}