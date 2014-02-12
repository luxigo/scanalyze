// Template Numerical Toolkit (TNT) for Linear Algebra
//
// BETA VERSION INCOMPLETE AND SUBJECT TO CHANGE
// Please see http://math.nist.gov/tnt for updates
//
// R. Pozo
// Mathematical and Computational Sciences Division
// National Institute of Standards and Technology


#ifndef LU_H
#define LU_H

// Solve system of linear equations Ax = b.
//
//  Typical usage:
//
//    Matrix(double) A;
//    Vector(Subscript) ipiv;
//    Vector(double) b;
//
//    1)  LU_Factor(A,ipiv);
//    2)  LU_Solve(A,ipiv,b);
//
//   Now b has the solution x.  Note that both A and b
//   are overwritten.  If these values need to be preserved,
//   one can make temporary copies, as in
//
//    O)  Matrix(double) T = A;
//    1)  LU_Factor(T,ipiv);
//    1a) Vector(double) x=b;
//    2)  LU_Solve(T,ipiv,x);
//
//   See details below.
//


// for abs()
//
#include "tntmath.h"

// right-looking LU factorization algorithm (unblocked)
//
//   Factors matrix A into lower and upper  triangular matrices
//   (L and U respectively) in solving the linear equation Ax=b.
//
//
// Args:
//
// A        (input/output) Matrix(1:n, 1:n)  In input, matrix to be
//                  factored.  On output, overwritten with lower and
//                  upper triangular factors.
//
// indx     (output) Vector(1:n)    Pivot vector. Describes how
//                  the rows of A were reordered to increase
//                  numerical stability.
//
// Return value:
//
// int      (0 if successful, 1 otherwise)
//
//


template <class Matrix, class VectorSubscript>
int LU_factor( Matrix &A, VectorSubscript &indx)
{
    assert(A.lbound() == 1);                // currently for 1-offset
    assert(indx.lbound() == 1);             // vectors and matrices

    Subscript M = A.num_rows();
    Subscript N = A.num_cols();

    if (M == 0 || N==0) return 0;
    if (indx.dim() != M)
        indx.newsize(M);

    Subscript i=0,j=0,k=0;
    Subscript jp=0;

    typename Matrix::element_type t;

    Subscript minMN =  (M < N ? M : N) ;        // min(M,N);

    for (j=1; j<= minMN; j++)
    {

        // find pivot in column j and  test for singularity.

        jp = j;
        t = abs(A(j,j));
        for (i=j+1; i<=M; i++)
            if ( abs(A(i,j)) > t)
            {
                jp = i;
                t = abs(A(i,j));
            }

        indx(j) = jp;

        // jp now has the index of maximum element
        // of column j, below the diagonal

        if ( A(jp,j) == 0 )
            return 1;       // factorization failed because of zero pivot


        if (jp != j)            // swap rows j and jp
            for (k=1; k<=N; k++)
            {
                t = A(j,k);
                A(j,k) = A(jp,k);
                A(jp,k) =t;
            }

        if (j<M)                // compute elements j+1:M of jth column
        {
            // note A(j,j), was A(jp,p) previously which was
            // guarranteed not to be zero (Label #1)
            //
            typename Matrix::element_type recp =  1.0 / A(j,j);

            for (k=j+1; k<=M; k++)
                A(k,j) *= recp;
        }


        if (j < minMN)
        {
            // rank-1 update to trailing submatrix:   E = E - x*y;
            //
            // E is the region A(j+1:M, j+1:N)
            // x is the column vector A(j+1:M,j)
            // y is row vector A(j,j+1:N)

            Subscript ii,jj;

            for (ii=j+1; ii<=M; ii++)
                for (jj=j+1; jj<=N; jj++)
                    A(ii,jj) -= A(ii,j)*A(j,jj);
        }
    }

    return 0;
}




template <class Matrix, class Vector, class VectorSubscripts>
int LU_solve(const Matrix &A, const VectorSubscripts &indx, Vector &b)
{
    assert(A.lbound() == 1);                // currently for 1-offset
    assert(indx.lbound() == 1);             // vectors and matrices
    assert(b.lbound() == 1);

    Subscript i,ii=0,ip,j;
    Subscript n = b.dim();
    typename Matrix::element_type sum = 0.0;

    for (i=1;i<=n;i++)
    {
        ip=indx(i);
        sum=b(ip);
        b(ip)=b(i);
        if (ii)
            for (j=ii;j<=i-1;j++)
                sum -= A(i,j)*b(j);
        else if (sum) ii=i;
            b(i)=sum;
    }
    for (i=n;i>=1;i--)
    {
        sum=b(i);
        for (j=i+1;j<=n;j++)
            sum -= A(i,j)*b(j);
        b(i)=sum/A(i,i);
    }

    return 0;
}

#endif
// LU_H
