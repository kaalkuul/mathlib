#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Vec3
{
public:
	// Constructors
	Vec3();
	explicit Vec3(Real k);
	Vec3(Real x, Real y, Real z);
	Vec3(const Vec2<Real>& u, Coord c = Coord::Z);

	// Create from
	static Vec3 fromSlerp(const Vec3& u, const Vec3& v, Real ratio);
	static Vec3 fromSlerpMaxAngle(const Vec3& u, const Vec3& v, Real maxAngle);

	// Setters
	Vec3& set(Real x, Real y, Real z);
	Vec3& set(const Vec3& v);
	Vec3& slerp(const Vec3& u, const Vec3& v, Real ratio);
	Vec3& slerpMaxAngle(const Vec3& u, const Vec3& v, Real maxAngle);

	// Transformations
	Real normalize(Real k = Real(1));
	Vec3& rotate(Coord axis, Real angle);
	Vec3& mirror(Coord plane);

	// Access operators
	Real& operator[](Coord c);
    Real operator[](Coord c) const;

	// Assignments
	Vec3& operator+=(const Vec3& u);
	Vec3& operator-=(const Vec3& u);
	Vec3& operator*=(Real k);
	Vec3& operator*=(const Mat3<Real>& m);
	Vec3& operator/=(Real k);
	Vec3& operator%=(const Vec3& u);
	Vec3& operator%=(Coord v);

	// Arithmetic operators
	Vec3 operator+ (const Vec3& u) const;
	Vec3 operator- () const;
	Vec3 operator- (const Vec3& u) const;
	Real operator* (const Vec3& u) const;
	Vec3 operator* (const Mat3<Real>& m) const;
	Vec3 operator% (const Vec3& u) const;
	Vec3 operator% (Coord v) const;
	Vec3 operator* (Real k) const;
	Vec3 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const Vec3& u) const;
	bool operator!= (const Vec3& u) const;

	// Functions
	Real length() const;
	Real lengthSqr() const;
	Vec3 rotated(Coord axis, Real angle) const;
	Vec3 normalized(Real k = Real(1)) const;
	Vec3 mirrored(Coord plane) const;
	Coord majorCoord() const;
	Coord minorCoord() const;
	bool isNull() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Vec3<CastReturnType> cast() const;

	static Vec3 randomUnitVector();

	static const Vec3 Zero;
	static const Vec3 OneX;
	static const Vec3 OneY;
	static const Vec3 OneZ;

public:
	Real x, y, z;
};

MATHLIB_NS_END
