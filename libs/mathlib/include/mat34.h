#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Mat34
{
public:
	typedef RealT Real;
	typedef MatrixTolerance<Real> Tolerance;

public:
	// Constructors
	Mat34();
	Mat34(Real k);
	Mat34(const Mat3<Real> &r, const Vec3<Real> &t = Vec3<Real>::Zero);
	Mat34(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z, const Vec3<Real> &t);

	// Setters
	Mat34& setIdentity();
	Mat34& set(const Mat34 &m);
	Mat34& set(const Mat3<Real> &r, const Vec3<Real> &t = Vec3<Real>::Zero);
	Mat34& set(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z, const Vec3<Real> &t = Vec3<Real>::Zero);
	Mat34& set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	Mat34& set(const Vec3<Real> &axis, Real angle, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat34& set(Coord axis, Real angle, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat34& set(const Quat<Real> &q, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat34& slerp(const Mat34& a, const Mat34& b, Real weight);
	Mat34& slerpMaxAngle(const Mat34& a, const Mat34& b, Real maxAngle);

	// Create from
	static Mat34 from(const Quat<Real>& q, const Vec3<Real>& t = Vec3<Real>::Zero);
	static Mat34 from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t);
	static Mat34 from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	static Mat34 from(const Vec3<Real>& axis, Real angle, const Vec3<Real>& t = Vec3<Real>::Zero);
	static Mat34 from(Coord axis, Real angle, const Vec3<Real>& t = Vec3<Real>::Zero);
	static Mat34 fromSlerp(const Mat34& a, const Mat34& b, Real weight);
	static Mat34 fromSlerpMaxAngle(const Mat34& a, const Mat34& b, Real maxAngle);

	// Access operators
	Vec3<Real>& operator[](Coord c);
	Vec3<Real> operator[](Coord c) const;

	// Assignments
	Mat34& operator*=(const Mat3<Real>& m);
	Mat34& operator*=(const Mat34& m);

	// Arithmetic operators
	Mat34 operator-() const;
	Mat34 operator*(const Mat3<Real>& m) const;
	Mat34 operator*(const Mat34& m) const;
	Vec3<Real> operator*(const Vec3<Real>& u) const;

	// Comparison operators
	bool operator==(const Mat34& m) const;
	bool operator!=(const Mat34& m) const;

	// Transformations
	Mat34& rotate(const Quat<Real> &q);
	Mat34& rotate(const Vec3<Real>& axis, Real angle);
	Mat34& rotate(Coord axis, Real angle);
	Mat34& translate(const Vec3<Real>& translation);
	Mat34& scale(const Vec3<Real>& coefficients);
	Mat34& transform(const Mat3<Real>& mat);
	Mat34& transform(const Mat34& mat);

	Mat34& rotatePre(const Quat<Real> &q);
	Mat34& rotatePre(const Vec3<Real>& axis, Real angle);
	Mat34& rotatePre(Coord axis, Real angle);
	Mat34& translatePre(const Vec3<Real>& translation);
	Mat34& scalePre(const Vec3<Real>& coefficients);
	Mat34& transformPre(const Mat3<Real>& mat);
	Mat34& transformPre(const Mat34& mat);

	Mat34& optimize(const Tolerance *tolerance = nullptr);
	Mat34& invert();
	Mat34& transpose();

	// Functions
	Ray3<Real> localAxis(Coord axis) const;
	Plane<Real> localPlane(Coord normal) const;
	bool isNormal() const;
	bool isOrthogonal() const;
	bool isOrthonormal() const;
	bool isIdentity() const;
	bool isInitialized() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Mat34<CastReturnType> cast() const;

	void transform(Vec3<Real>& dest, const Vec3<Real>& src) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;

	static void multiply(Mat34& dest, const Mat34& a, const Mat34& b);

public:
	Mat3<Real> rs; // rotation & scale
	Vec3<Real> t;  // translation

	static const Mat34 Zero;
	static const Mat34 One;
};

MATHLIB_NS_END
