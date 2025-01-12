#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "plist.h"

plist plist_from_file(const char *filepath) {
    FILE *file = NULL;
    file = fopen(filepath, "r");
    int pivot;
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int pivot_res = fscanf(file, " %d ", &pivot);
    if (pivot_res != 1) {
        fprintf(stderr, "Invalid plist pivot on file.\n");
        exit(EXIT_FAILURE);
    }
    plist output = plist_create(pivot);
    while (!feof(file)) {
        int elem;
        int res = fscanf(file," %d ", &elem);
        if (res != 1) {
            fprintf(stderr, "Invalid plist elem on file.\n");
            exit(EXIT_FAILURE);
        }
        output = plist_add(output, elem);
    }
    fclose(file);
    assert(output != NULL);
    return output;
}
