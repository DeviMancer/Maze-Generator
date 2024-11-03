#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdbool.h>
#include <stddef.h>

typedef void matrix_t;

/**************************************/
/* Constructor de matriz de booleanos */
/**************************************/

/*
Precondiciones:
a) rows > 0
b) cols > 0
 */
matrix_t *new_matrix(size_t rows, size_t cols, bool init);

/*************************************/
/* Destructor de matriz de booleanos */
/*************************************/

void free_matrix(matrix_t *m);

/****************************************************/
/* Selectores de propiedades de matriz de booleanos */
/****************************************************/

/*
Precondiciones:
a) m != NULL
 */
size_t matrix_rows(matrix_t *m);

/*
Precondiciones:
a) m != NULL
 */
size_t matrix_cols(matrix_t *m);

/*
Precondiciones:
a) m != NULL
b) row < matrix_rows(m)
c) col < matrix_cols(m)
 */
bool matrix_get(matrix_t *m, size_t row, size_t col);

/******************************************************************************/
/* Operación para modificar el valor en una componente de matriz de booleanos */
/******************************************************************************/

/*
Precondiciones:
a) m != NULL
b) row < matrix_rows(m)
c) col < matrix_cols(m)
 */
void matrix_set(matrix_t *m, size_t row, size_t col, bool v);

void matrix_print(matrix_t *m);




#endif /* __MATRIX_H__ */

