MATHLIB_NS_BEGIN

template <class Real>
bool TriDiagonal<Real>::solve(const Real* a, const Real* b, const Real* c, const Real* r,
	Real* u, int n)
{
	assert(n > 0);

	if (b[0] == Real(0))
		return false;

	Real* gam = new Real[n];
	assert(gam != NULL);

	Real bet = b[0];
	u[0] = r[0] / bet;
	for (int j = 1; j < n; j++)
	{
		gam[j] = c[j-1] / bet;
		bet = b[j] - a[j-1] * gam[j];
		if (bet == Real(0))
		{
			delete [] gam;
			return false;
		}
		u[j] = (r[j] - a[j-1] * u[j-1]) / bet;
	}

	for (int j = n-2; j >= 0; j--)
		u[j] -= gam[j+1] * u[j+1];

	delete [] gam;
	
	return true;
}

template <class Real>
bool TriDiagonal<Real>::solve(const Real* a, const Real* b, const Real* c, const Vec3<Real>* r,
	Vec3<Real>* u, int n)
{
	int j;
	
	if (b[0] == Real(0))
		return false;

	Real* gam = new Real[n];
	assert(gam != NULL);

	Real bet = b[0];
	u[0] = r[0] / bet;
	for (j = 1; j < n; j++)
	{
		gam[j] = c[j-1] / bet;
		bet = b[j] - a[j-1] * gam[j];
		if (bet == Real(0))
		{
			delete [] gam;
			return false;
		}
		u[j] = (r[j] - u[j-1] * a[j-1]) / bet;
	}

	for (j = n-2; j >= 0; j--)
		u[j] -= u[j+1] * gam[j+1];

	delete [] gam;
	
	return true;
}

template <class Real>
bool TriDiagonal<Real>::solveCyclic(const Real* a, const Real* b, const Real* c,
	Real alpha, Real beta, const Real* r, Real* x, int n)
{
	if (n <= 2)
		return false;

	if (alpha == Real(0) && beta == Real(0))
	{
		return solve(a, b, c, r, x, n);
	}

	Real* bb = new Real[n];
	Real* u = new Real[n];
	Real* z = new Real[n];

	Real gamma = -b[0]; // Avoid subtraction error in forming bb[1].
	bb[0] = b[0] - gamma; // Set up the diagonal of the modified tridiagonal system.
	bb[n-1] = b[n-1] - alpha * beta / gamma;
	for (int i = 1; i < n-1; i++)
		bb[i] = b[i];
	
	bool result = solve(a, bb, c, r, x, n); // Solve A · x = r
	if (result)
	{
		// Set up the vector u
		u[0] = gamma;
		u[n-1] = alpha;
		for (int i = 1; i < n-1; i++)
			u[i] = Real(0);

		result = solve(a, bb, c, u, z, n); // Solve A · z = u.
		if (result)
		{
			// Form v · x / (1 + v · z).
			Real fact = (x[0] + beta * x[n-1] / gamma) / (Real(1) + z[0] + beta * z[n-1] / gamma);

			// Now get the solution vector x
			for (int i = 0; i < n; i++)
				x[i] -= fact * z[i];
		}
	}
	
	delete [] z;
	delete [] u;
	delete [] bb;

	return result;
}

template <class Real>
static inline void SWAP(Real &a, Real &b)
{
	Real temp=a;
	a = b;
	b = temp;
}

template <class Real>
bool GaussJordan<Real>::solve(Real* a, int n, Real* b, int m)
{
	int *indxc,*indxr,*ipiv;
	int i,icol,irow,j,k,l,ll;
	Real big,dum,pivinv;
	
	// The integer arrays ipiv, indxr, and indxc are used for bookkeeping on the pivoting.
	indxc	= new int[n];
	indxr	= new int[n];
	ipiv	= new int[n];
	assert(indxc != NULL && indxr != NULL && ipiv != NULL);
	
	for (j = 0; j < n; j++)
		ipiv[j] = -1;
	
	for (i = 0; i < n; i++)
	{
		// This is the main loop over the columns to be reduced.
		big = Real(0);
		for (j = 0; j < n; j++)
		{
			// This is the outer loop of the search for a pivot element.
			if (ipiv[j] != 0)
			{
				for (k = 0; k < n; k++)
				{
					if (ipiv[k] == -1)
					{
						if (fabsf(a[j*n+k]) >= big)
						{
							big = fabsf(a[j*n+k]);
							irow = j;
							icol = k;
						}
					}
				}
			}
		}
		
		++(ipiv[icol]);
		
		//	We now have the pivot element, so we interchange rows, if needed, to put the pivot
		//	element on the diagonal. The columns are not physically interchanged, only relabeled:
		//	indxc[i], the column of the ith pivot element, is the ith column that is reduced, while
		//	indxr[i] is the row in which that pivot element was originally located. If indxr[i] .=
		//	indxc[i] there is an implied column interchange. With this form of bookkeeping, the
		//	solution b�s will end up in the correct order, and the inverse matrix will be scrambled
		//	by columns.
		if (irow != icol)
		{
			for (l = 0; l < n; l++)
			{
				SWAP(a[irow*n+l], a[icol*n+l]);
			}
			
			for (l = 0; l < m; l++)
			{
				SWAP(b[irow*m+l], b[icol*m+l]);
			}
		}

		// We are now ready to divide the pivot row by the pivot element, located at irow and icol.
		indxr[i] = irow;
		indxc[i] = icol;
		if (a[icol*n+icol] == Real(0))
		{
			// Singular Matrix
			delete [] indxc;
			delete [] indxr;
			delete [] ipiv;
			return false;
		}

		// Normalize row
		pivinv = Real(1) / a[icol*n+icol];
		for (l = 0; l < n; l++)
			a[icol*n+l] *= pivinv;
		a[icol*n+icol] = Real(1);
		for (l = 0; l < m; l++)
			b[icol*m+l] *= pivinv;

		// Next, we reduce the rows...
		for (ll = 0; ll < n; ll++)
		{
			if (ll != icol)
			{
				// ...except for the pivot one, of course.
				dum = a[ll*n+icol];
				for (l = 0; l < n; l++)
					a[ll*n+l] -= a[icol*n+l]*dum;
				a[ll*n+icol] = Real(0);
				for (l = 0; l < m; l++)
					b[ll*m+l] -= b[icol*m+l]*dum;
			}
		}
	}
	
	//	This is the end of the main loop over columns of the reduction. It only remains to unscramble
	//	the solution in view of the column interchanges. We do this by interchanging pairs of
	//	columns in the reverse order that the permutation was built up.
	for (l = n-1; l >= 0; l--)
	{
		if (indxr[l] != indxc[l])
		{
			for (k = 0; k < n; k++)
			{
				SWAP(a[k*n+indxr[l]], a[k*n+indxc[l]]);
			}
		}
	}
	
	// And we are done.
	delete[] indxc;
	delete[] indxr;
	delete[] ipiv;

	return true;
}

template <class Real>
bool GaussJordan<Real>::solve(Real* a, int n, Vec2<Real>* b)
{
	return GaussJordan<Real>::solve(a, n, &b->x, 2);
}

template <class Real>
bool GaussJordan<Real>::solve(Real* a, int n, Vec3<Real>* b)
{
	return GaussJordan<Real>::solve(a, n, &b->x, 3);
}

MATHLIB_NS_END
