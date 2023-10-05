#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Mat4
{
public:
	typedef RealT Real;
	typedef MatrixTolerance<Real> Tolerance;

public:
	// Constructors
	Mat4();
	Mat4(Real k);
	Mat4(const Mat3<Real>& m, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat4(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat4(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t = Vec4<Real>::OneW);

	// Setters
	Mat4& setIdentity();
	Mat4& set(const Mat4<Real>& m);
	Mat4& set(const Mat3<Real>& rs, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat4& set(const Quat<Real>& q, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat4& set(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t = Vec3<Real>::Zero);
	Mat4& set(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t = Vec4<Real>::OneW);
	Mat4& set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	Mat4& set(const Vec3<Real>& axis, Real angle);
	Mat4& set(Coord axis, Real angle);

	// Create from
	static Mat4 from(const Quat<Real>& q, const Vec3<Real>& t = Vec3<Real>::Zero);
	static Mat4 from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t = Vec3<Real>::Zero);
	static Mat4 from(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t = Vec4<Real>::OneW);
	static Mat4 from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx);
	static Mat4 from(const Vec3<Real>& axis, Real angle);
	static Mat4 from(Coord axis, Real angle);

	// Access operators
	Vec4<Real>& operator[](Coord c);
	Vec4<Real> operator[](Coord c) const;

	// Assignments
	Mat4& operator*=(Real k);
	Mat4& operator/=(Real k);

	// Arithmetic operators
	Mat4 operator-() const;
	Mat4 operator*(Real k) const;
	Mat4 operator/(Real k) const;
	Mat4 operator*(const Mat4& m) const;
	Vec3<Real> operator*(const Vec3<Real>& u) const;
	Vec4<Real> operator*(const Vec4<Real>& u) const;

	// Comparison operators
	bool operator==(const Mat4& m) const;
	bool operator!=(const Mat4& m) const;

	// Transformations
	Mat4& rotate(const Quat<Real>& q);
	Mat4& rotate(const Vec3<Real>& axis, Real angle);
	Mat4& rotate(Coord axis, Real angle);
	Mat4& translate(const Vec3<Real>& translation);
	Mat4& scale(const Vec3<Real>& coefficients);
	Mat4& transform(const Mat4& m);

	Mat4& rotatePre(const Quat<Real>& q);
	Mat4& rotatePre(const Vec3<Real>& axis, Real angle);
	Mat4& rotatePre(Coord axis, Real angle);
	Mat4& translatePre(const Vec3<Real>& translation);
	Mat4& scalePre(const Vec3<Real>& coefficients);
	Mat4& transformPre(const Mat4& m);

	Mat4& orthonormalise();
	Mat4& optimize(const Tolerance* tolerance = nullptr);
	Mat4& transpose();
	Mat4& invert();

	// Functions
	Ray3<Real> localAxis(Coord axis) const;
	Plane<Real> localPlane(Coord normal) const;
	Mat4 transposed() const;
	Real trace() const;
	Real determinant() const;
	Mat4 inversed() const;
	Real normalError() const;
	Real orthogonalError() const;
	Real identityError() const;
	bool isNormal() const;
	bool isOrthogonal() const;
	bool isOrthonormal() const;
	bool isIdentity() const;
	bool isTrs() const;
	bool isInitialized() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Mat4<CastReturnType> cast() const;

	void transform(Vec3<Real>& dest, const Vec3<Real>& src) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const;
	void transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;
	void transform(Vec4<Real>& dest, const Vec4<Real>& src) const;
	void transform(Vec4<Real>* dest, const Vec4<Real>* src, size_t count) const;
	void transform(Vec4<Real>* dest, const Vec4<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;

	void transformVector(Vec3<Real>& dest, const Vec3<Real>& src) const;
	void transformVector(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const;
	void transformVector(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;
	void transformVector(Vec4<Real>& dest, const Vec4<Real>& src) const;
	void transformVector(Vec4<Real>* dest, const Vec4<Real>* src, size_t count) const;
	void transformVector(Vec4<Real>* dest, const Vec4<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;

	static void multiply(Mat4& dest, const Mat4& a, const Mat4& b);

private:
	enum Flags : unsigned int
	{
		Normal = 0x1,
		Orthogonal = 0x2,
		Orthonormal = 0x3,
		Identity = 0x4,
		Trs = 0x8,
		Uninitialized = 0x10
	};

	unsigned int flags;

public:
	Vec4<Real> x;
	Vec4<Real> y;
	Vec4<Real> z;
	Vec4<Real> t;

	static const Mat4 Zero;
	static const Mat4 One;

	static const Tolerance DefaultTolerance;
};

MATHLIB_NS_END
