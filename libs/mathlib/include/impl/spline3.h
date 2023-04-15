#pragma once

MATHLIB_NS_BEGIN

//
// HermiteSplineSegment3
//

template <class Real>
HermiteSplineSegment3<Real>::HermiteSplineSegment3()
{
}

template <class Real>
HermiteSplineSegment3<Real>::HermiteSplineSegment3(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4)
:	P1(p1),
	P4(p4),
	R1(r1),
	R4(r4)
{
}

template <class Real>
void HermiteSplineSegment3<Real>::set(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4)
{
	P1 = p1;
	P4 = p4;
	R1 = r1;
	R4 = r4;
}

template <class Real>
const Vec3<Real>& HermiteSplineSegment3<Real>::p1() const
{
	return P1;
}

template <class Real>
const Vec3<Real>& HermiteSplineSegment3<Real>::p4() const
{
	return P4;
}

template <class Real>
const Vec3<Real>& HermiteSplineSegment3<Real>::r1() const
{
	return R1;
}

template <class Real>
const Vec3<Real>& HermiteSplineSegment3<Real>::r4() const
{
	return R4;
}

template <class Real>
Vec3<Real> HermiteSplineSegment3<Real>::pointAt(Real t) const
{
	assert(t >= Real(0) && t <= Real(1));

	Real t2 = t * t;
	Real t3 = t2 * t;

	Real cp4 = -Real(2)*t3 + Real(3)*t2;
	Real cp1 = Real(1) - cp4;
	Real cr1 = t3 - Real(2)*t2 + t;
	Real cr4 = t3 - t2;

	return (P1 * cp1) + (P4 * cp4) + (R1 * cr1) + (R4 * cr4);
}

template <class Real>
Vec3<Real> HermiteSplineSegment3<Real>::tangentAt(Real t) const
{
	assert(t >= Real(0) && t <= Real(1));
	Real t2 = t * t;

	Real cp4 = -Real(6)*t2 + Real(6)*t;
	Real cp1 = -cp4;
	Real cr1 = Real(3)*t2 - Real(4)*t + Real(1);
	Real cr4 = Real(3)*t2 - Real(2)*t;

	return (P1 * cp1) + (P4 * cp4) + (R1 * cr1) + (R4 * cr4);
}

template <class Real>
Real HermiteSplineSegment3<Real>::hp1(Real t)
{
	Real t2 = t * t;
	return Real(2) * t * t2 - Real(3) * t2 + Real(1);
}

template <class Real>
Real HermiteSplineSegment3<Real>::hp4(Real t)
{
	Real t2 = t * t;
	return -Real(2) * t * t2 + Real(3) * t2;
}

template <class Real>
Real HermiteSplineSegment3<Real>::hr1(Real t)
{
	Real t2 = t * t;
	return t * t2 - Real(2) * t2 + t;
}

template <class Real>
Real HermiteSplineSegment3<Real>::hr4(Real t)
{
	Real t2 = t * t;
	return t * t2 - t2;
}

template <class Real>
Real HermiteSplineSegment3<Real>::dhp1(Real t)
{
	Real t2 = t * t;
	return Real(6) * t2 - Real(6) * t;
}

template <class Real>
Real HermiteSplineSegment3<Real>::dhp4(Real t)
{
	Real t2 = t * t;
	return -Real(6) * t2 + Real(6) * t;
}

template <class Real>
Real HermiteSplineSegment3<Real>::dhr1(Real t)
{
	Real t2 = t * t;
	return Real(3) * t2 - Real(4) * t + Real(1);
}

template <class Real>
Real HermiteSplineSegment3<Real>::dhr4(Real t)
{
	Real t2 = t * t;
	return Real(3) * t2 - Real(2) * t;
}

//
// BezierSegment3
//

template <class Real>
BezierSegment3<Real>::BezierSegment3()
{
}

template <class Real>
BezierSegment3<Real>::BezierSegment3(const Vec3<Real>& p1, const Vec3<Real>& p2, const Vec3<Real>& p3, const Vec3<Real>& p4)
:	P1(p1),
	P2(p2),
	P3(p3),
	P4(p4)
{
}

template <class Real>
void BezierSegment3<Real>::set(const Vec3<Real>& p1, const Vec3<Real>& p2, const Vec3<Real>& p3, const Vec3<Real>& p4)
{
	P1 = p1;
	P2 = p2;
	P3 = p3;
	P4 = p4;
}

template <class Real>
const Vec3<Real>& BezierSegment3<Real>::p1() const
{
	return P1;
}

template <class Real>
const Vec3<Real>& BezierSegment3<Real>::p2() const
{
	return P2;
}

template <class Real>
const Vec3<Real>& BezierSegment3<Real>::p3() const
{
	return P3;
}

template <class Real>
const Vec3<Real>& BezierSegment3<Real>::p4() const
{
	return P4;
}

template <class Real>
Vec3<Real> BezierSegment3<Real>::r1() const
{
	return (P2 - P1) * Real(3);
}

template <class Real>
Vec3<Real> BezierSegment3<Real>::r4() const
{
	return (P4 - P3) * Real(3);
}

template <class Real>
Vec3<Real> BezierSegment3<Real>::pointAt(Real t) const
{
	assert(t >= Real(0) && t <= Real(1));
	Real t2 = t * t;
	Real t3 = t2 * t;

	Real cp1 = -t3 + Real(3)*t2 - Real(3)*t + Real(1);
	Real cp2 = Real(3)*t3 - Real(6)*t2 + Real(3)*t;
	Real cp3 = -Real(3)*t3 + Real(3)*t2;
	Real cp4 = t3;

	return (P1 * cp1) + (P2 * cp2) + (P3 * cp3) + (P4 * cp4);
}

template <class Real>
Vec3<Real> BezierSegment3<Real>::tangentAt(Real t) const
{
	assert(t >= Real(0) && t <= Real(1));
	Real t2 = t * t;

	Real cp1 = -Real(3)*t2 + Real(6)*t - Real(3);
	Real cp2 = Real(9)*t2 - Real(12)*t + Real(3);
	Real cp3 = -Real(9)*t2 + Real(6)*t;
	Real cp4 = Real(3)*t2;

	return (P1 * cp1) + (P2 * cp2) + (P3 * cp3) + (P4 * cp4);
}

template <class Real>
bool BezierSegment3<Real>::frenetFrameAt(Mat3<Real>& frame, Real t) const
{
	assert(t >= Real(0) && t <= Real(1));

	Real t2 = t * t;

	Real fd1 = -Real(3)*t2 + Real(6)*t - Real(3);
	Real fd2 = Real(9)*t2 - Real(12)*t + Real(3);
	Real fd3 = -Real(9)*t2 + Real(6)*t;
	Real fd4 = Real(3)*t2;

	Vec3<Real> tangent = (P1 * fd1) + (P2 * fd2) + (P3 * fd3) + (P4 * fd4);

	Real sd1 = -Real(6)*t + Real(6);
	Real sd2 = Real(18)*t - Real(12);
	Real sd3 = -Real(18)*t + Real(6);
	Real sd4 = Real(6)*t;

	Vec3<Real> sd = (P1 * sd1) + (P2 * sd2) + (P3 * sd3) + (P4 * sd4);

	// Unit tangent vector (normalized derivative, C '(t) ):
	// T(t) = C't) / |C'(t)|

	// binormal vector (cross product of derivative and second derivative, C''(t) ):
	// B(t) = C't) x C''(t) / |C'(t) x C''(t)|

	// Vector perpendicular to both T(t) and B(t) (normalized since both T(t) and B(t) are normalized)
	// N(t) = B(t) x T(t)

	Vec3<Real> binormal = tangent % sd;

	if (tangent.normalize() == Real(0))
		return false;

	if (binormal.normalize() == Real(0))
		return false;

	Vec3<Real> n = binormal % tangent;
	if (n.isNull())
		return false;

	frame.set(binormal, tangent, n);

	return true;
}

template <class Real>
void BezierSegment3<Real>::split(Real a, BezierSegment3 &start, BezierSegment3 &end) const
{
	assert(a >= Real(0) && a <= Real(1));

	Real a2 = a * a;
	Real a3 = a * a2;

	Real ca = Real(1) - a;
	Real ca2 = ca * ca;
	Real ca3 = ca * ca2;

	start.P1	= P1;
	start.P2	= P1 * ca	+ P2 * a;
	start.P3	= P1 * ca2	+ P2 * (Real(2)*a*ca)	+ P3 * a2;
	start.P4	= P1 * ca3	+ P2 * (Real(3)*a*ca2)	+ P3 * (Real(3)*a2*ca)	+ P4 * a3;
	
	end.P1		= P1 * ca3	+ P2 * (Real(3)*a*ca2)	+ P3 * (Real(3)*a2*ca)	+ P4 * a3;
	end.P2		=			  P2 * ca2				+ P3 * (Real(2)*a*ca)	+ P4 * a2;
	end.P3		=									  P3 * ca				+ P4 * a;
	end.P4		=															  P4;
}

template <class Real>
Real BezierSegment3<Real>::length(int steps) const
{
	assert(steps > 0);

	Real d = Real(1) / steps;
	Real d2 = d * d;
	Real d3 = d2 * d;

	Vec3<Real> P4_P1 = P4 - P1;
	Vec3<Real> P3_P2 = P3 - P2;
	Vec3<Real> P2_P1 = P2 - P1;

	Vec3<Real> P = P1;
	Vec3<Real> dP = P4_P1 * d3 + P3_P2 * ((d2 - d3) * Real(3)) + P2_P1 * ((d - d2) * Real(3));
	Vec3<Real> d2P = P4_P1 * (d3 * Real(6)) + P3_P2 * ((d2 - d3 * Real(3)) * Real(6)) + P2_P1 * (-d2 * Real(6));
	Vec3<Real> d3P = P4_P1 * (d3 * Real(6)) + P3_P2 * (-d3 * Real(18));

	Real result = Real(0);
	for (int i = 0; i < steps - 1; i++)
	{
		result += dP.length();

		P += dP;
		dP += d2P;
		d2P += d3P;
	}

	result += (P4 - P).length();

	return result;
}

template <class Real>
Real BezierSegment3<Real>::hp1(Real t)
{
	Real ct = Real(1) - t;
	return ct * ct * ct;
}

template <class Real>
Real BezierSegment3<Real>::hp2(Real t)
{
	Real ct = Real(1) - t;
	return Real(3) * t * ct * ct;
}

template <class Real>
Real BezierSegment3<Real>::hp3(Real t)
{
	Real ct = Real(1) - t;
	return Real(3) * t * t * ct;
}

template <class Real>
Real BezierSegment3<Real>::hp4(Real t)
{
	return t * t * t;
}

template <class Real>
Real BezierSegment3<Real>::dhp1(Real t)
{
	Real ct = Real(1) - t;
	return -Real(3) * ct * ct;
}

template <class Real>
Real BezierSegment3<Real>::dhp2(Real t)
{
	Real ct = Real(1) - t;
	return Real(3) * ct * ct - Real(6) * t * ct;
}

template <class Real>
Real BezierSegment3<Real>::dhp3(Real t)
{
	Real ct = Real(1) - t;
	return Real(6) * t * ct - Real(3) * t * t;
}

template <class Real>
Real BezierSegment3<Real>::dhp4(Real t)
{
	return Real(3) * t * t;
}

//
// BezierSegment3FwdDiff
//
//	Now, given four control points A, B, C, and D, the basic algorithm can be written as follows: 
//	First calculate coefficients: 
//
//		PreCalc1 = (3*dt)        // possible precalculations
//		PreCalc2 = (3*dt^2)
//		PreCalc3 = (dt^3)
//		PreCalc4 = (6*dt^2)
//		PreCalc5 = (6*dt^3)
//
//		Temp1 = (A-2*B+C)        // repeated values
//		Temp2 = (3*(B-C)-A+D)
//
//		f    = A
//		df   = (B-A)*PreCalc1 + Temp1*PreCalc2 + Temp2*PreCalc3
//		ddf  = Temp1*PreCalc4 + Temp2*PreCalc5
//		dddf = Temp2*PreCalc5
//
//	Then find Bezier curve points incrementally (inner loop): 
//
//		for t = 0 to 1 in steps of dt
//		begin
//			CurvePoint = f;
//			f = f + df;
//			df = df + ddf;
//			ddf = ddf + dddf;
//		end

template <class Real>
BezierSegment3FwdDiff<Real>::BezierSegment3FwdDiff(const Vec3<Real>& P1, const Vec3<Real>& P2, const Vec3<Real>& P3, const Vec3<Real>& P4, Real d)
{
	Real d2 = d * d;
	Real d3 = d2 * d;

	Vec3<Real> P4_P1 = P4 - P1;
	Vec3<Real> P3_P2 = P3 - P2;
	Vec3<Real> P2_P1 = P2 - P1;

	P	= P1;
	dP	= P4_P1 * d3			+ P3_P2 * ((d2-d3)*Real(3))			+ P2_P1 * ((d-d2)*Real(3));
	d2P	= P4_P1 * (d3*Real(6))	+ P3_P2 * ((d2-d3*Real(3))*Real(6))	+ P2_P1 * (-d2*Real(6));
	d3P	= P4_P1 * (d3*Real(6))	+ P3_P2 * (-d3*Real(18));

	T	= P2_P1 * Real(3);
	dT	= P4_P1 * (d2*Real(3))	+ P3_P2 * (d*Real(6)-d2*Real(9))	+ P2_P1 * (-d*Real(6));
	d2T	= P4_P1 * (d2*Real(6))	+ P3_P2 * (-d2*Real(18));
}

template <class Real>
void BezierSegment3FwdDiff<Real>::stepForward()
{
	P	+= dP;
	dP	+= d2P;
	d2P	+= d3P;

	T	+= dT;
	dT	+= d2T;
}

template <class Real>
const Vec3<Real>& BezierSegment3FwdDiff<Real>::currentPoint() const
{
	return P;
}

template <class Real>
const Vec3<Real>& BezierSegment3FwdDiff<Real>::currentTangent() const
{
	return T;
}

//
// SplineSolver
//

// https://www.michael-joost.de/bezierfit.pdf
// https://www.stkent.com/2015/07/03/building-smooth-paths-using-bezier-curves.html

template <class Real>
bool SplineSolver3<Real>::naturalBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3)
{
	assert(n >= 2);

	if (n == 2)
	{
		Vec3<Real> t = (p1[1] - p1[0]) / Real(3);
		p2[0] = p1[0] + t;
		p3[0] = p1[1] - t;
		return true;
	}

	int i;

	n = n-1;

	Real *a = new Real[n-1];
	Real *b = new Real[n];
	Real *c = new Real[n-1];
	Vec3<Real> *r = new Vec3<Real>[n];
	assert(a != nullptr && b != nullptr && c != nullptr && r != nullptr);

	for (i = 0; i < n-1; i++)
	{
		a[i] = Real(1);
		b[i] = Real(4);
		c[i] = Real(1);
	}

	b[0] = Real(2);
	a[n-2] = Real(2); b[n-1] = Real(7);

	for (i = 1; i < n-1; i++)
	{
		r[i] = p1[i] * Real(4) + p1[i+1] * Real(2);
	}

	r[0]	= p1[0] + p1[1] * Real(2);
	r[n-1]	= p1[n-1] * Real(8) + p1[n];

	if (!TriDiagonal<Real>::solve(a, b, c, r, p2, n))
	{
		delete [] a;
		delete [] b;
		delete [] c;
		delete [] r;
		return false;
	}

	for (i = 0; i < n-1; i++)
	{
		p3[i] = p1[i+1] * Real(2) - p2[i+1];
	}

	p3[n-1]	= (p1[n] + p2[n-1]) / Real(2);

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] r;

	return true;
}

template <class Real>
bool SplineSolver3<Real>::bezierSpline(int n, const Vec3<Real>* p1, const Vec3<Real>& p2start, const Vec3<Real>& p3end, Vec3<Real>* p2, Vec3<Real>* p3)
{
	assert(n >= 2);

	if (n == 2)
	{
		Vec3<Real> t = (p1[1] - p1[0]) / Real(3);
		p2[0] = p2start;
		p3[0] = p3end;
		return true;
	}

	int i;

	n = n-1;

	Real *a = new Real[n-1];
	Real *b = new Real[n];
	Real *c = new Real[n-1];
	Vec3<Real> *r = new Vec3<Real>[n];
	assert(a != nullptr && b != nullptr && c != nullptr && r != nullptr);

	for (i = 0; i < n-1; i++)
	{
		a[i] = Real(1);
		b[i] = Real(4);
		c[i] = Real(1);
	}

	b[0] = Real(1);
	b[n - 1] = Real(4);
	c[0] = Real(0);

	for (i = 1; i < n - 1; i++)
	{
		r[i] = p1[i] * Real(4) + p1[i + 1] * Real(2);
	}

	r[0]	= p2start;
	r[n-1]	= p3end + p1[n-1] * Real(4);

	if (!TriDiagonal<Real>::solve(a, b, c, r, p2, n))
	{
		delete [] a;
		delete [] b;
		delete [] c;
		delete [] r;
		return false;
	}

	for (i = 0; i < n-1; i++)
	{
		p3[i] = p1[i + 1] * Real(2) - p2[i + 1];
	}

	p3[n-1]	= p3end;

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] r;

	return true;
}

template <class Real>
bool SplineSolver3<Real>::closedBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3)
{
	assert(n >= 2);

	int i;

	Real *a = new Real[n * n];
	assert(a != nullptr);

	i = n * n;
	while (--i >= 0)
		a[i] = Real(0);

	for (i = 1; i < n-1; i++)
	{
		a[i*n+i-1]	= Real(1);
		a[i*n+i]	= Real(4);
		a[i*n+i+1]	= Real(1);
	}

	a[0]       = Real(4);	a[1]           = Real(1);	a[n-1]         = Real(1);
	a[(n-1)*n] = Real(1);	a[(n-1)*n+n-2] = Real(1);	a[(n-1)*n+n-1] = Real(4);

	for (i = 0; i < n-1; i++)
	{
		p2[i] = p1[i] * Real(4) + p1[i+1] * Real(2);
	}

	p2[n-1]	= p1[n-1] * Real(4) + p1[0] * Real(2);

	if (!GaussJordan<Real>::solve(a, n, p2))
	{
		delete [] a;
		return false;
	}

	for (i = 0; i < n-1; i++)
	{
		p3[i]	= p1[i+1] * Real(2) - p2[i+1];
	}

	p3[n-1]	= p2[n-2] + p2[n-1] * Real(4) - p1[n-1] * Real(4);

	delete[] a;

	return true;
}

MATHLIB_NS_END
