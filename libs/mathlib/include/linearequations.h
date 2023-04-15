#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class TriDiagonal
{
public:
    // Solves for a vector u the tridiagonal linear set given by equation: M.u = r
    // a is an input vectors (lower diagonal of M) of size n-1 and is not modified
    // b is an input vectors (diagonal of M) of size n and is not modified
    // c is an input vectors (upper diagonal of M) of size n-1 and is not modified
    // r is an input vectors of size n and is not modified
    // r is an output vectors of size n

    static bool solve(const Real* a, const Real* b, const Real* c,
        const Real* r, Real* u, int n);

    static bool solve(const Real* a, const Real* b, const Real* c,
        const Vec3<Real>* r, Vec3<Real>* u, int n);

    // Solves for a vector x the “cyclic” set of linear equations given by: M.x = r
    // a is an input vectors (lower diagonal of M) of size n-1 and is not modified
    // b is an input vectors (diagonal of M) of size n and is not modified
    // c is an input vectors (upper diagonal of M) of size n-1 and is not modified
    // alpha and beta are the corner entries in the matrix M
    // r is an input vectors of size n and is not modified
    // r is an output vectors of size n

    static bool solveCyclic(const Real* a, const Real* b, const Real* c,
        Real alpha, Real beta, const Real* r, Real* x, int n);
};

// Linear equation solution by Gauss-Jordan elimination.
//  a[1..n][1..n] is the input matrix.
//  b[1..n][1..m] is input containing the m right-hand side vectors.
// On output, a is replaced by its matrix inverse, and b is replaced
// by the corresponding set of solution vectors.

template <class Real>
class GaussJordan
{
public:
    static bool solve(Real* a, int n, Real* b, int m);
    static bool solve(Real* a, int n, Vec2<Real>* b);
    static bool solve(Real* a, int n, Vec3<Real>* b);
};

MATHLIB_NS_END
