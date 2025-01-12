#ifndef _PLIST_H_
#define _PLIST_H_

#include <stdbool.h>    /* Definition of bool            */
#include "elem.h"   /* Definitions for t_elem type */

typedef struct s_plist * plist;

plist plist_create(t_elem pivot);
/*
 * DESC: Creates a new instance of plist with pivot element <pivot>.
 *
 *   l = plist_create()
 * POS: {l --> plist && plist_is_empty(l)}
 */

plist plist_add(plist l, t_elem e);
/*
 * DESC: Adds a element <e> to the plist <l>, in the correct order
 * elems are always added either in the left or right side of the pivot element.
 * pivot cannot be added to the list
 * 
 * PRE: {l --> plist && ! e == pivot)}
 *   l = plist_add(l, e);
 * POS: {l --> plist && !plist_is_emtpy(l)}
 */

bool plist_is_empty(plist l);
/*
 * Indicates whether the plist <l> is empty.
 * PRE: {l --> plist}
 *   b = plist_is_empty(l);
 */

t_elem plist_get_pivot(plist l);
/*
 * Returns the value of the pivot element.
 * PRE: {l --> plist}
 *   e = plist_get_pivot(l);
 */

unsigned int plist_length(plist l);
/*
 * DESC: Returns the number of elements in <l>, counting the pivot element.
 * PRE: {l --> plist}
 *   n = plist_length(l);
 * POS: {(n == 1) == plist_is_empty(l)}
 */

plist plist_delete_prev(plist l);
/*
 * DESC: Eliminates the t_elem to the left of the pivot element.
 * if the pivot is the first element, the function does nothing.
 * PRE: {l --> plist}
 *   l = plist_delete_prev(l); 
 * POS: {l --> plist}
 */

plist plist_delete_next(plist l);
/*
 * DESC: Eliminates the t_elem to the right of the pivot element.
 * if the pivot is the last element, the function does nothing.
 * PRE: {l --> plist}
 *   l = plist_delete_next(l); 
 * POS: {l --> plist}
 */

unsigned int plist_count(plist l, t_elem e);
/*
 * DESC: Returns the amount od occurrences of some element <e> in the plist <l>.
 * PRE: {l --> plist && !plist_is_empty(l)}
 *   c = plist_count(l);
 * POS: {l --> plist}
 */

t_elem * plist_to_array(plist l);
/*
 * DESC: Returns an array with all elements that belong to <l>. The returned
 *       array is stored in dynamic memory and has enough room for
 *       plist_length(l) elements. The caller must free the memory when it is
 *       no longer in use.
 * PRE: {l --> plist}
 *   array = plist_to_array(l);
 * POS: {!plist_is_empty(l) ==> (array!=NULL)
 */

void plist_dump(plist l);
/*
 * DESC: Shows the plist elements in stdout
 * PRE: {l --> plist}
 *   plist_dump(l);
 */

plist plist_destroy(plist l);
/*
 * DESC: Destroys the plist <l>, freeing all memory used by the data structure
 * PRE: {l --> plist}
 *   l = plist_destroy(l);
 * POS: {l == NULL}
 */

#endif /* _PLIST_H_ */

