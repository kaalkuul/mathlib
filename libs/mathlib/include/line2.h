#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Line2
{
public:
	typedef RealT Real;

public:
	// Constructors
	Line2();

	// Create from
	static Line2 from(const Vec2<Real>& start, const Vec2<Real>& end);

	// Comparison operators
	bool operator== (const Line2& rhs) const;
	bool operator!= (const Line2& rhs) const;

	// Functions
	Real length() const;
	Real lengthSqr() const;
	bool isNull() const;

	Vec2<Real> pointAt(Real t) const;

	Real distance(const Vec2<Real>& point) const;

	template <class CastReturnType>
	Line2<CastReturnType> cast() const;

public:
	Vec2<Real> start;
	Vec2<Real> end;
};

MATHLIB_NS_END
