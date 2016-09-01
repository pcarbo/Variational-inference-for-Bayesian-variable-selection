#ifndef INCLUDE_MISC
#define INCLUDE_MISC

#include "types.h"

// FUNCTION DECLARATIONS
// -----------------------------------------------------------------
// Compute log(1 + exp(x)) in a numerically stable manner.
double logpexp (double x);

// Return the sigmoid function at x.
double sigmoid (double x);

// Return the logarithm of the sigmoid function at x. Computation is
// performed in a numerically stable manner.
double logsigmoid (double x);

// Copy entries of one vector to another vector.
void copy (const double* source, double* dest, Size n);

// Get a pointer to column j of matrix X. The entries in a single
// column of the matrix are assumed to be stored consecutively in
// memory. Input n is the number of rows in the matrix.
const MatrixElem* getColumn (const MatrixElem* X, Index j, Size n);

// Copy column j of matrix X. The entries in a single column of the
// matrix are assumed to be stored consecutively in memory. Input n
// is the number of rows in the matrix.
void copyColumn (const MatrixElem* X, double* y, Index j, Size n);

// Set the entries of the vector to a.
void setVector (double* x, Size n, double a);

// Return the sum of the entries in the vector.
double sum (const double* x, Size n);

// Return the largest entry in the vector.
double max (const double* x, Size n);

// Add a*x to vector y, and store the result in y.
void add (double* y, double a, const double* x, Size n);

// Return the dot product of two vectors.
double dot (const double* x, const double* y, Size n);

// Compute x'*D*y, the dot product of x and y scaled by D = diag(d).
double dotscaled (const double* x, const double* y, const double* d, Size n);

// Compute the matrix-vector product X'*y, the transposed matrix X
// times the vector y, and return the result in the entries of vector
// a. The entries in a single column of the matrix are assumed to be
// stored consecutively in memory. Inputs nr and nc are the number of
// rows and and columns of matrix X. Vector y is assumed to have one
// entry for every row of X, and vector a is assumed to have one entry
// for every column of X.
void matrixvec (const double* X, const double* y, double* a, Size nr, Size nc);

#endif
