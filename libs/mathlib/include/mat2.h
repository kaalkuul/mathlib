#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Mat2
{
public:
	typedef RealT Real;
	typedef MatrixTolerance<Real> Tolerance;

public:
	// Constructors
	Mat2();
	Mat2(Real k);
	Mat2(const Vec2<Real>& x, const Vec2<Real>& y);

	// Setters
	Mat2& setIdentity();
	Mat2& set(const Mat2<Real>& m);
	Mat2& set(const Vec2<Real>& x, const Vec2<Real>& y);
	Mat2& set(Real angle);
	Mat2& slerp(const Mat2& a, const Mat2& b, Real weight);
	Mat2& slerpMaxAngle(const Mat2& a, const Mat2& b, Real maxAngle);

	// Create from
	static Mat2 from(const Vec2<Real>& x, const Vec2<Real>& y);
	static Mat2 from(Real angle);
	static Mat2 fromSlerp(const Mat2& a, const Mat2& b, Real weight);
	static Mat2 fromSlerpMaxAngle(const Mat2& a, const Mat2& b, Real maxAngle);

	// Assignments
	Mat2& operator*=(Real k);
	Mat2& operator*=(const Mat2 &m);
	Mat2& operator/=(Real k);

	// Arithmetic operators
	Mat2 operator-() const;
	Mat2 operator*(const Mat2 &m) const;
	Mat2 operator*(Real k) const;
	Vec2<Real> operator*(const Vec2<Real> &u) const;
	Mat2 operator/(Real k) const;

	// Comparison operators
	bool operator==(const Mat2 &m) const;
	bool operator!=(const Mat2 &m) const;

	// Transformations
	Mat2& scale(const Vec2<Real>& coefficients);
	Mat2& transpose();
	Mat2& rotate(Real angle);
	Mat2& rotatePre(Real angle);
	Mat2& orthonormalise();
	Mat2& optimize(const Tolerance *tolerance = nullptr);

	// Functions
	Mat2 scaled(const Vec2<Real>& coefficients) const;
	Mat2 transposed() const;
	Mat2 cofactors() const;
	Mat2 adjoint() const;
	Real trace() const;
	Real determinant() const;
	Mat2 inversed() const;
	Real angle() const;
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
	Mat2<CastReturnType> cast() const;

	void transform(Vec2<Real>& dest, const Vec2<Real>& src) const;
	void transform(Vec2<Real>* dest, const Vec2<Real>* src, size_t count) const;
	void transform(Vec2<Real>* dest, const Vec2<Real>* src, size_t count,
		size_t destStride, size_t srcStride) const;

	static void multiply(Mat2& dest, const Mat2& a, const Mat2& b);

public:
    Vec2<Real> x;
    Vec2<Real> y;

	static const Mat2 Zero;
	static const Mat2 One;

	static const Tolerance DefaultTolerance;

private:
	enum Flags : unsigned int
	{
		Normal			= 0x1,
		Orthogonal		= 0x2,
		Orthonormal		= 0x3,
		Mask			= 0x3,
		Identity		= 0x4,
		Uninitialized	= 0x8
	};

	unsigned int flags;
};

MATHLIB_NS_END
