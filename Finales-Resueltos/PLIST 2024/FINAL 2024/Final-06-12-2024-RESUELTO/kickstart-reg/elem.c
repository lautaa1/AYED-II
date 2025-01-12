#include <stdio.h>    /* printf()  */
#include <stdbool.h>  /* Type bool */

#include "elem.h"  /* Interface */

void t_elem_dump(t_elem e) {
    printf("%d", e);
}

bool t_elem_less(t_elem e1, t_elem e2) {
    return e1 < e2;
}

bool t_elem_eq(t_elem e1, t_elem e2) {
    return e1 == e2;
}

bool t_elem_greater(t_elem e1, t_elem e2) {
    return e1 > e2;
}

