#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define CELL_MAX (3 * 3 - 1)

struct winner_data {
    bool is_winner;
    char winner;
};

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[3][3]){
    int cell = 0;
    print_sep(3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}

struct winner_data hayFila(char board[3][3]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    for (int fila = 0; fila < 3; fila++) {
        if (board[fila][0] == board[fila][1] && board[fila][1] == board[fila][2] && board[fila][0] != '-') {
            res.is_winner = true;
            res.winner = board[fila][0];
            break;
        }
    }
    return res;
}
struct winner_data hayColumna(char board[3][3]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    for (int columna = 0; columna < 3; columna++) {
        if (board[0][columna] == board[1][columna] && board[1][columna] == board[2][columna] && board[0][columna] != '-') {
            res.is_winner = true;
            res.winner = board[0][columna];
            break;
        }
    }
    return res;
}

struct winner_data hayDiag(char board[3][3]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') {
        res.is_winner = true;
        res.winner = board[0][0];
    }
    return res;
}

struct winner_data hayDiagInv(char board[3][3]) {
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-') {
        res.is_winner = true;
        res.winner = board[0][2];
    }
    return res;
}

/*
char hayFila (char board[3][3]){
    int filas=0, columnas=1;
    char guardavalor = '-';

    while (filas<3){
        if (board[filas][columnas] != board[filas][columnas-1]){
            filas++;
        }
        else if (board[filas][columnas] == board[filas][columnas-1]){
            columnas++;
            if (board[filas][columnas] == board[filas][columnas-1]){
                guardavalor = board[filas][columnas];
                filas=3;
            }
        }
    }
    return guardavalor;
}*/

/*
char hayCol (char board[3][3]){
    int columnas=0, filas=1;
    char guardavalor = '-';
    while (columnas<3){
        if (board[filas][columnas] != board[filas-1][columnas]){
            columnas++;
        }
        else if (board[filas][columnas] == board[filas-1][columnas]){
            filas++;
            if (board[filas][columnas] == board[filas-1][columnas]){
                guardavalor = board[filas][columnas];
                columnas=3;
            }
        }
    }
    return guardavalor;
}
*/

/*
char hayDiag (char board[3][3]){
    char guardavalor = '-';
    if (board[2][2] == board[1][1] && board[1][1] == board[0][0]){
        guardavalor = board[2][2];
    }
    else if (board[0][0] != board[1][1]){
        guardavalor = '-';
    }
    return guardavalor;  
}
*/
/*
char hayDiagInv (char board[3][3]){
    char guardavalor = '-';
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        guardavalor = board[2][0];
    }
    else if (board[0][2] != board[1][1]){
        guardavalor = '-';
    }
    return guardavalor;
}
*/

char get_winner(char board[3][3]){
    struct winner_data res;
    res.is_winner = false;
    res.winner = '-';
    res = hayFila(board);
    if (res.is_winner) {return res.winner;}
    res = hayColumna(board);
    if (res.is_winner) {return res.winner;}
    res = hayDiag(board);
    if (res.is_winner) {return res.winner;}
    res = hayDiagInv(board);
    if (res.is_winner){return res.winner;}
    return res.winner;
}

bool has_free_cell(char board[3][3]){

    bool free_cell=false;
    for ( int i=0;i < 3 && !free_cell;i++ ){
      for ( int j=0;j < 3 && !free_cell;j++ ){
        free_cell=(board[i][j] =='-');
      }
    } 
return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[3][3] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posicion (numero del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un numero desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda invÃ¡lida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("GanÃ³ %c\n", winner);
    }
    return 0;
}

//gcc -Wall -Wextra -std=c99 tictactoe.c -o tictactoe
// ./tictactoe