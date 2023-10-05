#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Line3
{
public:
	typedef RealT Real;

public:
	// Constructors
	Line3();

	// Create from
	static Line3 from(const Vec3<Real>& start, const Vec3<Real>& end);

	// Comparison operators
	bool operator== (const Line3& rhs) const;
	bool operator!= (const Line3& rhs) const;

	// Functions
	Real length() const;
	Real lengthSqr() const;
	bool isNull() const;

	Vec3<Real> pointAt(Real t) const;

	Real distance(const Vec3<Real>& point) const;

	template <class CastReturnType>
	Line3<CastReturnType> cast() const;

public:
	Vec3<Real> start;
	Vec3<Real> end;
};

MATHLIB_NS_END
