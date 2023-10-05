#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Ray2
{
public:
	typedef RealT Real;

public:
	// Constructors
	Ray2();

	// Create from
	static Ray2 from(const Vec2<Real>& start, const Vec2<Real>& direction);

	// Comparison operators
	bool operator== (const Ray2& rhs) const;
	bool operator!= (const Ray2& rhs) const;

	// Functions
	Vec2<Real> pointAt(Real dist) const;

	Real distance(const Vec2<Real>& point) const;

	template <class CastReturnType>
	Ray2<CastReturnType> cast() const;

public:
	Vec2<Real> start;
	Vec2<Real> direction;
};

MATHLIB_NS_END
