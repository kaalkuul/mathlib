#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Vec4
{
public:
	// Constructors
	Vec4();
	explicit Vec4(Real k);
	Vec4(Real x, Real y, Real z, Real w = Real(0));
	Vec4(const Vec3<Real>& u, Real w = Real(0));

	// Setters
	Vec4& set(Real x, Real y, Real z, Real w = Real(0));
	Vec4& set(const Vec3<Real>& v, Real w = Real(0));
	Vec4& set(const Vec4& v);

	// Assignments
	Vec4& operator+=(const Vec3<Real>& u);
	Vec4& operator-=(const Vec3<Real>& u);
	Vec4& operator+=(const Vec4& u);
	Vec4& operator-=(const Vec4& u);
	Vec4& operator*=(Real k);
	Vec4& operator/=(Real k);

	// Arithmetic operators
	Vec4 operator+ (const Vec4& u) const;
	Vec4 operator- () const;
	Vec4 operator- (const Vec4& u) const;
	Real operator* (const Vec4& u) const;
	Vec4 operator* (Real k) const;
	Vec4 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const Vec4& u) const;
	bool operator!= (const Vec4& u) const;

	// Functions
	Real length() const;
	Real lengthSqr() const;
	Vec3<Real> toVec3() const;
	bool isNull() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Vec4<CastReturnType> cast() const;

	static const Vec4 Zero;
	static const Vec4 OneX;
	static const Vec4 OneY;
	static const Vec4 OneZ;
	static const Vec4 OneW;

public:
	Real x, y, z, w;
};

MATHLIB_NS_END
