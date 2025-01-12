/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a){
    for (unsigned int city = 0u; city < CITIES; ++city){
        for (unsigned int season = 0u; season < SEASONS; ++season){
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}


unsigned int best_profit(BakeryProductTable a){
    unsigned int max_profit = 0u;
    unsigned int ganancia = 0u;
    for (unsigned int cities = 0; cities < CITIES; cities++){
        for (unsigned int seasons = 0; seasons < SEASONS; seasons++){
            ganancia = a[cities][seasons].sale_value - ((a[cities][seasons].butter_cant * a[cities][seasons].butter_price)
                        + (a[cities][seasons].yeast_cant * a[cities][seasons].yeast_price)
                        + (a[cities][seasons].flour_cant * a[cities][seasons].flour_price));
            if (max_profit <= ganancia){
                max_profit = ganancia;
            }
        }
    }
    return max_profit;
}


void array_from_file(BakeryProductTable array, const char* filepath){
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL){
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (!feof(file)){
        unsigned int city;
        unsigned int season;
        int res = fscanf (file, "##%u??%u", &city, &season);
        if (res != EXPECTED_DIM_VALUE){
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        if (season != 0 && season != 1){
            fprintf(stderr, "Invalid season.\n");
            exit(EXIT_FAILURE);
        }
        if (city > 4){
            fprintf(stderr, "Invalid code.\n");
            exit(EXIT_FAILURE);
        }
        /* COMPLETAR: Leer y guardar product en el array multidimensional*/
        /* Agregar las validaciones que considere necesarias*/
        /* Completar*/
        array[city][season] = bakery_product_from_file(file);
        ++i;
    }
    fclose(file);
}
