/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "plist.h"
#include "plist_helpers.h"

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path> \n\n"
           "Loads elements given in a file on disk into a plist.\n"
           "\n"
           "The input file must have the following format:\n\n"
           " * One line that must contain only one integer element as pivot."
           " * One line that must contain the list elements"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<pivot>\n"
           "<elem_1> <elem_2> ... <elem_N>\n\n"
           ""
           "",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *filepath = NULL;
    // Check arguments
    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    // Take filepath parameter from command line arguments
    filepath = argv[1];
    return filepath;
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  /* Parse command line arguments */
  filepath = parse_filepath(argc, argv);
  /* Load data from file and construct a plist instance */
  plist l = plist_from_file(filepath);
  /* Get the list size*/
  unsigned int size = plist_length(l);
  /* Show plist content */
  printf("List of elements read in the file: ");
  plist_dump(l);
  printf("\n\n");
  /* Show amount of elements in the List */
  printf("The file '%s' has %u elements\n", filepath, size);
  /* Check that elements are found in the list */
  int pivot = plist_get_pivot(l);
  printf("The pivot element is %d\n", pivot);
  int *elems = plist_to_array(l);
  for (unsigned int i=0; i < size; i++) {
      printf("%d [%s]%s", elems[i], (elems[i] == pivot || plist_count(l, elems[i]) > 0) ? "OK": "FAIL", i==size - 1 ? "\n": ", ");
  }
  free(elems);
  /* Test remove operations*/
  printf("\n Removings elements test \n");
  l = plist_delete_prev(l);
  l = plist_delete_prev(l);
  printf("List after removing 2 previous element: ");
  plist_dump(l);
  printf("\n");
  l = plist_delete_next(l);
  l = plist_delete_next(l);
  printf("List after removing 2 next element: ");
  plist_dump(l);
  printf("\n");

  l = plist_destroy(l);
  return EXIT_SUCCESS;
}
