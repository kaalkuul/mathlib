#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class HermiteSplineSegment3
{
public:
	typedef RealT Real;

public:
    HermiteSplineSegment3();
    HermiteSplineSegment3(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4);

	void set(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4);

	const Vec3<Real>& p1() const;
	const Vec3<Real>& p4() const;
	const Vec3<Real>& r1() const;
	const Vec3<Real>& r4() const;

	Vec3<Real> pointAt(Real t) const;

	Vec3<Real> tangentAt(Real t) const;

	static Real hp1(Real t);
	static Real hp4(Real t);
	static Real hr1(Real t);
	static Real hr4(Real t);

	static Real dhp1(Real t);
	static Real dhp4(Real t);
	static Real dhr1(Real t);
	static Real dhr4(Real t);

private:
	Vec3<Real> P1, P4, R1, R4;
};

// A Primer on Bézier Curves
// A free, online book for when you really need to know how to do Bézier things.
// https://pomax.github.io/bezierinfo/

template <class RealT>
class BezierSegment3
{
public:
	typedef RealT Real;

public:
    BezierSegment3();
    BezierSegment3(const Vec3<Real>& p1, const Vec3<Real>& p2, const Vec3<Real>& p3, const Vec3<Real>& p4);

	void set(const Vec3<Real>& p1, const Vec3<Real>& p2, const Vec3<Real>& p3, const Vec3<Real>& p4);

	const Vec3<Real>& p1() const;
	const Vec3<Real>& p2() const;
	const Vec3<Real>& p3() const;
	const Vec3<Real>& p4() const;
	Vec3<Real> r1() const;
	Vec3<Real> r4() const;
	
	Vec3<Real> pointAt(Real t) const;

	Vec3<Real> tangentAt(Real t) const;

	bool frenetFrameAt(Mat3<Real>& frame, Real t) const;

	void split(Real a, BezierSegment3 &start, BezierSegment3 &end) const;

	Real length(int steps = 10) const;

	static Real hp1(Real t);
	static Real hp2(Real t);
	static Real hp3(Real t);
	static Real hp4(Real t);

	static Real dhp1(Real t);
	static Real dhp2(Real t);
	static Real dhp3(Real t);
	static Real dhp4(Real t);

private:
	Vec3<Real> P1, P2, P3, P4;
};

template <class RealT>
class BezierSegment3FwdDiff
{
public:
	typedef RealT Real;

public:
	BezierSegment3FwdDiff(const Vec3<Real>& P1, const Vec3<Real>& P2, const Vec3<Real>& P3, const Vec3<Real>& P4, Real d);

	void stepForward();

	const Vec3<Real>& currentPoint() const;

	const Vec3<Real>& currentTangent() const;
	
private:
	Vec3<Real> P;
	Vec3<Real> dP;
	Vec3<Real> d2P;
	Vec3<Real> d3P;

	Vec3<Real> T;
	Vec3<Real> dT;
	Vec3<Real> d2T;
};

template <class Real>
class SplineSolver3
{
public:
	static bool naturalBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3);

	static bool bezierSpline(int n, const Vec3<Real>* p1, const Vec3<Real>& p2start, const Vec3<Real>& p3end, Vec3<Real>* p2, Vec3<Real>* p3);

	static bool closedBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3);
};

MATHLIB_NS_END
