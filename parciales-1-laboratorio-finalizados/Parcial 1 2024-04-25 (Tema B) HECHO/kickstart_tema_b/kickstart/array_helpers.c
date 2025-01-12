/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

void array_dump(RankingTable a) {
    for (unsigned int ranking = 0u; ranking < NO_PLAYERS; ranking++) {
        for (unsigned int type = road; type <= track; type++) {
            Ranking aux = a[ranking][type];
            fprintf(stdout, " %u %s %i %i %s %s %f\n",
                    ranking+1, (type==0?"road":"track"), aux.pos_prev, aux.diff, aux.name, aux.team, aux.points
            );
        }
    }
}

void array_from_file(RankingTable array, const char *filepath) {
    FILE *file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    type_t type;
    int i = 0;
    while (!feof(file) && i < NO_PLAYERS * TYPES) {
        int res = fscanf(file, "@%u", &type);
        if (res != 1) {
            fprintf(stderr, "Invalid ranking type.\n");
            exit(EXIT_FAILURE);
        }
        if (type != 0 && type !=1){
            fprintf(stderr, "Invalid ranking type, type != 0 || type != 1.\n");
            exit(EXIT_FAILURE);
        }
        
        /* COMPLETAR: Leer Ranking */
        Ranking ranking_row = ranking_from_file(file);
        if (ranking_row.pos > 100){
            fprintf(stderr, "Invalid pos player.\n");
            exit(EXIT_FAILURE); 
        }
        if (ranking_row.pos_prev < 0){
            fprintf(stderr, "Invalid pos prev player.\n");
            exit(EXIT_FAILURE); 
        }
        if (ranking_row.points < 0){
            fprintf(stderr, "Invalid points player.\n");
            exit(EXIT_FAILURE); 
        }
        /* COMPLETAR: guardar ranking en array */
        array[ranking_row.pos-1][type] = ranking_row;
        i++;
    }
    fclose(file);
}

/*
$ gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -c array_helpers.c ranking.c main.c
$ gcc -Wall -Werror -Wextra -pedantic -std=c99 array_helpers.o ranking.o main.o -g -o ranking

./ranking inputs/uci_rank.in
*/
