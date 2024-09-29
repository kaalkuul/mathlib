#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Mat3
{
public:
	typedef RealT Real;
	typedef MatrixTolerance<Real> Tolerance;

public:
	// Constructors
	Mat3();
	Mat3(Real k);
	Mat3(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z);

	// Setters
	Mat3& setIdentity();
	Mat3& set(const Mat3<Real>& m);
	Mat3& set(const Quat<Real>& q);
	Mat3& set(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z);
	Mat3& set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	Mat3& set(const Vec3<Real>& axis, Real angle);
	Mat3& set(Coord axis, Real angle);
	Mat3& slerp(const Mat3& a, const Mat3& b, Real weight);
	Mat3& slerpMaxAngle(const Mat3& a, const Mat3& b, Real maxAngle);

	// Create from
	static Mat3 from(const Quat<Real>& q);
	static Mat3 from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z);
	static Mat3 from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	static Mat3 from(const Vec3<Real>& axis, Real angle);
	static Mat3 from(Coord axis, Real angle);
	static Mat3 fromSlerp(const Mat3& a, const Mat3& b, Real weight);
	static Mat3 fromSlerpMaxAngle(const Mat3& a, const Mat3& b, Real maxAngle);

	// Assignments
	Mat3& operator*=(Real k);
	Mat3& operator*=(const Mat3 &m);
	Mat3& operator/=(Real k);

	// Arithmetic operators
	Mat3 operator-() const;
	Mat3 operator*(const Mat3 &m) const;
	Mat3 operator*(Real k) const;
	Vec3<Real> operator*(const Vec3<Real> &u) const;
	Mat3 operator/(Real k) const;

	// Comparison operators
	bool operator==(const Mat3 &m) const;
	bool operator!=(const Mat3 &m) const;

	// Transformations
	Mat3& scale(const Vec3<Real>& coefficients);

	Mat3& rotate(const Mat3& m);
	Mat3& rotate(const Quat<Real>& m);
	Mat3& rotate(const Vec3<Real>& axis, Real angle);
	Mat3& rotate(Coord axis, Real angle);

	Mat3& rotatePre(const Mat3& m);
	Mat3& rotatePre(const Quat<Real>& m);
	Mat3& rotatePre(const Vec3<Real>& axis, Real angle);
	Mat3& rotatePre(Coord axis, Real angle);

	Mat3& orthonormalise();
	Mat3& optimize(const Tolerance *tolerance = nullptr);
	Mat3& transpose();
	Mat3& invert();

	// Functions
	Mat3 scaled(const Vec3<Real>& coefficients) const;

    Mat3 rotated(const Mat3& m) const;
    Mat3 rotated(const Quat<Real>& m) const;
    Mat3 rotated(const Vec3<Real>& axis, Real angle) const;
    Mat3 rotated(Coord axis, Real angle) const;

    Mat3 rotatedPre(const Mat3& m) const;
    Mat3 rotatedPre(const Quat<Real>& m) const;
    Mat3 rotatedPre(const Vec3<Real>& axis, Real angle) const;
    Mat3 rotatedPre(Coord axis, Real angle) const;

    Mat3 transposed() const;
	Mat3 cofactors() const;
	Mat3 adjoint() const;
	Real trace() const;
	Real determinant() const;
	Mat3 inversed() const;
	Real normalError() const;
	Real orthogonalError() const;
	Real identityError() const;
	bool isNormal() const;
	bool isOrthogonal() const;
	bool isOrthonormal() const;
	bool isIdentity() const;
	bool isInitialized() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Mat3<CastReturnType> cast() const;

	void transform(Vec3<Real>& dest, const Vec3<Real>& src) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;

	static void multiply(Mat3& dest, const Mat3& a, const Mat3& b);

private:
	enum Flags : unsigned int
	{
		Normal = 0x1,
		Orthogonal = 0x2,
		Orthonormal = 0x3,
		Identity = 0x4,
		Uninitialized = 0x8
	};

	unsigned int flags;

public:
    Vec3<Real> x;
    Vec3<Real> y;
    Vec3<Real> z;

	static const Mat3 Zero;
	static const Mat3 One;

	static const Tolerance DefaultTolerance;
};

MATHLIB_NS_END
