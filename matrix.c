#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/*

Representación de matrices booleanas

M =
|0 1 1|
|0 1 0|

          M ---v
[ | | | | |r|c|0|1|1|0|1|0| | | |]
     S-----^
 */

//********************************************************************************* Constructor
matrix_t *new_matrix(size_t rows, size_t cols, bool init)
{
    // Reserva memoria para la matriz.
    size_t *S = (size_t *)malloc(rows * cols * sizeof(bool) + 2 * sizeof(size_t));
    if (S == NULL) return NULL;

    // Guardo el num de columnas y renglones de la matriz.
    S[0] = rows;
    S[1] = cols;

    // Inicializa los elementos de la matriz.
    bool *M = (bool *)(S + 2);
    for (size_t i = 0; i < rows * cols; ++i) M[i] = init;

    return (matrix_t *)M;
}

//********************************************************************************* Destructor
void free_matrix(matrix_t *m)
{
    if (m == NULL) return;
    free(((size_t *)m) - 2);
}

//********************************************************************************* matrix_rows
size_t matrix_rows(matrix_t *m)
{
    size_t *S = (size_t *)m;
    return S[-2];
}

//********************************************************************************* matrix_cols
size_t matrix_cols(matrix_t *m)
{
    size_t *S = (size_t *)m;
    return S[-1];
}

//********************************************************************************* matrix_get
bool matrix_get(matrix_t *m, size_t row, size_t col)
{
    size_t cols = matrix_cols(m);
    bool *M = (bool *)m;
    return M[row * cols + col];
}

//********************************************************************************* matrix_set
void matrix_set(matrix_t *m, size_t row, size_t col, bool v)
{
    size_t cols = matrix_cols(m);
    bool *M = (bool *)m;
    M[row * cols + col] = v;
}

//********************************************************************************* matrix_print
void matrix_print(matrix_t *m)
{
    bool *M = (bool *)m;

    for(size_t j = 0; j < matrix_rows(m); ++j) { 
	for(size_t i = 0; i < matrix_cols(m); ++i) {
	    printf("%d ", M[j * matrix_cols(m) + i]); //Este parece el problema: solo veo M[0] hasta M[matrixcols -1 ]
	}
	printf("\n");
    }

    printf("\n\n");
}


/*
  ¿De dónde sale eso de `row * cols + col`?

  M = 
  |0 1 0 1 1 0|           | 0   1   2   3   4   5 |
  |1 1 1 0 0 0|           | 6   7   8   9  10  11 |
  |1 1 1 1 1 1|           |12  13  14  15  16  17 |

  M --------v         *           *           *
...| | |3|6|0|1|0|1|1|0|1|1|1|0|0|0|1|1|1|1|1|1| | | |...
  S ----^   0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1
                                0 1 2 3 4 5 6 7
 */

