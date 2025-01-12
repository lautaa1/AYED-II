/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    printf("Operations:\n"
     "1 ........ Print tree\n"
     "2 ........ Add element\n"
     "3 ........ Remove element\n"
     "4 ........ Check if element exists\n"
     "5 ........ Show tree length\n"
     "6 ........ Show root, maximum and minimum elements of tree\n"
     "7 ........ Exit\n"
    "\n");

    int value;
    do{
        printf("Choose operation: ");
        scanf("%d",&value);
        printf("\n");
        switch (value){
            case 1:
                    abb_dump(tree);
                    printf("\n");
                break;

            case 2:
                    printf("Element to add: ");
                    int elem1;
                    scanf("%d", &elem1);
                    printf("\n");
                    tree = abb_add(tree,elem1);
                    printf("Element %d added \n", elem1);
                break;

            case 3:
                    printf("Element to remove: ");
                    int elem2;
                    printf("\n");
                    scanf("%d", &elem2);
                    tree = abb_remove(tree,elem2);
                    printf("Element %d removed \n", elem2);
                break;

            case 4:
                    printf("Element to check: ");
                    bool exists;
                    int elem3;
                    scanf("%d", &elem3);
                    printf("\n");
                    exists = abb_exists(tree,elem3);
                    printf("The element exists in tree: %d \n",exists);
                break;

            case 5:
                    printf("Tree length: %u \n", abb_length(tree));
                break;

            case 6:
                    if (!abb_is_empty(tree)) {
                    printf("\n");
                    printf("root: %d\n minimum: %d\n maximum: %d\n", abb_root(tree),
                                                                abb_min(tree),
                                                                abb_max(tree));
                    } else {
                        printf("\nEmpty tree\n");
                    }
                break;

            case 7:
                    tree = abb_destroy(tree);
                    return (EXIT_SUCCESS);
                break;
            
            default:
                    printf("Invalid argument, exiting program \n");
                break;
        }
    } while (value != 7);

    return (EXIT_SUCCESS);
}
