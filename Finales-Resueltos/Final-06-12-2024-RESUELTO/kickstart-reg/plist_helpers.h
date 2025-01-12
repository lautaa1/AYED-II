#ifndef _PLIST_HELPERS_H_
#define _PLIST_HELPERS_H_

#include <stdbool.h>  /* Type bool */

plist plist_from_file(const char *filepath);
/*
 * Each element is read from the file located at 'filepath'.
 * The file must exist in disk and must have its contents in the following
 * format:
 *
 * <t_elem_pivot>
 * <t_elem_1> <t_elem_2> <t_elem_3> ... <t_elem_N>
 *
 * Those elements are stored in a new instance of plist.
 *
 * If something goes wrong in loading process, the funciton aborts.
 *
 * Returns the instance of plist where the elements were loaded. 
 *
 */

#endif /* _PLIST_HELPERS_H_ */

