#ifndef _ELEM_H_
#define _ELEM_H_

#include <stdbool.h>   /* Type bool */

typedef int t_elem;

void t_elem_dump(t_elem e);
/*
 * Shows the element `e` on the screen
 *
 */

bool t_elem_less(t_elem e1, t_elem e2);
/* 
 * Indicates whether e1 is less than e2.
 *
 */

bool t_elem_eq(t_elem e1, t_elem e2);
/* 
 * Indicates whether e1 equals to e2.
 *
 */

bool t_elem_greater(t_elem e1, t_elem e2);
/* 
 * Indicates whether e1 is greater than e2.
 *
 */

#endif /* _ELEM_H_ */

