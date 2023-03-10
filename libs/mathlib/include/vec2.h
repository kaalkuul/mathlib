#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Vec2
{
public:
	// Constructors
	Vec2();
	explicit Vec2(Real k);
	Vec2(Real x, Real y);
	Vec2(const Vec3<Real>& u, Coord drop = Coord::Z);

	// Create from
	static Vec2 fromAngle(Real angle, Real length = Real(1));
	static Vec2 fromClerp(const Vec2& u, const Vec2& v, Real ratio);
	static Vec2 fromClerpMaxAngle(const Vec2& u, const Vec2& v, Real maxAngle);

	// Setters
	Vec2& set(Real x, Real y);
	Vec2& set(const Vec2& v);
	Vec2& setAngle(Real angle, Real length = Real(1));
	Vec2& clerp(const Vec2& u, const Vec2& v, Real ratio);
	Vec2& clerpMaxAngle(const Vec2& u, const Vec2& v, Real maxAngle);

	// Transformations
	Real normalize(Real k = Real(1));
	Vec2& rotate(Real angle);
	Vec2& mirror(Coord axis);
	Vec2& rotate90();
	Vec2& rotate180();
	Vec2& rotate270();

	// Access operators
	Real& operator[](Coord c);
    Real operator()(Coord c) const;

	// Assignments
	Vec2& operator+=(const Vec2& u);
	Vec2& operator-=(const Vec2& u);
	Vec2& operator*=(Real k);
	Vec2& operator*=(const Mat2<Real>& m);
	Vec2& operator/=(Real k);

	// Arithmetic operators
	Vec2 operator+(const Vec2& u) const;
	Vec2 operator-() const;
	Vec2 operator-(const Vec2& u) const;
	Real operator*(const Vec2& u) const;
	Vec2 operator*(const Mat2<Real>& m) const;
	Real operator%(const Vec2& u) const;
	Vec2 operator*(Real k) const;
	Vec2 operator/(Real k) const;

	// Comparison operators
	bool operator==(const Vec2& u) const;
	bool operator!=(const Vec2& u) const;

	// Functions
	Real length() const;
	Real lengthSqr() const;
	Vec2 rotated(Real angle) const;
	Vec2 normalized(Real k = Real(1)) const;
	Vec2 rotated90() const;
	Vec2 rotated180() const;
	Vec2 rotated270() const;
	Vec2 mirrored(Coord c) const;
	Real angle() const;
	Coord majorCoord() const;
	Coord minorCoord() const;
	bool isNull() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Vec2<CastReturnType> cast() const;

	static Vec2 randomUnitVector();

	static const Vec2 Zero;
	static const Vec2 OneX;
	static const Vec2 OneY;

public:
	Real x, y;
};

template <class Real>
int intersection(const Vec2<Real>& from, const Vec2<Real>& to,
	const Vec2<Real>& a, const Vec2<Real>& b,
	Real& ftp, Real& abp);

MATHLIB_NS_END
