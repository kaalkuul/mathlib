#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Circle
{
public:
	typedef RealT Real;

public:
	// Constructors
	Circle();
	Circle(const Vec2<Real>& center, Real radius);

	// Setters
	Circle& set(const Vec2<Real>& center, Real radius);
	Circle& set(int count, const Vec2<Real>* points);
	Circle& set(int count, const Vec2<Real>* points, int stride);

	// Create from
	static Circle from(const Vec2<Real>& center, Real radius);
	static Circle from(int count, const Vec2<Real>* points);
	static Circle from(int count, const Vec2<Real>* points, int stride);

	// Assignments
	Circle& operator+=(const Vec2<Real>& t);
	Circle& operator-=(const Vec2<Real>& t);
	Circle& operator*=(Real k);
	Circle& operator/=(Real k);

	// Arithmetic operators
	Circle operator+ (const Vec2<Real>& t) const;
	Circle operator- (const Vec2<Real>& t) const;
	Circle operator* (Real k) const;
	Circle operator/ (Real k) const;

	// Comparison operators
	bool operator== (const Circle& rhs) const;
	bool operator!= (const Circle& rhs) const;

	// Functions
	bool contains(const Vec2<Real>& point) const;
	bool contains(const Circle<Real>& sphere) const;

	bool hits(Vec2<Real>& hit, Real& t, const Line3<Real>& line) const;

	bool intersects(const Circle<Real>& sphere) const;
	bool intersects(const Line3<Real>& line) const;

	bool intersects(Vec2<Real>& hit, Real& t, const Circle<Real>& sphere) const;
	bool intersects(Vec2<Real>& hit, Real& t, const Line3<Real>& line) const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Circle<CastReturnType> cast() const;

	static const Circle One;

public:
	Vec2<Real> center;
	Real radius;
};

MATHLIB_NS_END
