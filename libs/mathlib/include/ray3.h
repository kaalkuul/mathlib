#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Ray3
{
public:
	typedef Real Real;

public:
	// Constructors
	Ray3();

	// Create from
	static Ray3 from(const Vec3<Real>& start, const Vec3<Real>& direction);

	// Comparison operators
	bool operator== (const Ray3& rhs) const;
	bool operator!= (const Ray3& rhs) const;

	// Functions
	Vec3<Real> pointAt(Real dist) const;

	Real distance(const Vec3<Real>& point) const;

	template <class CastReturnType>
	Ray3<CastReturnType> cast() const;

public:
	Vec3<Real> start;
	Vec3<Real> direction;
};

MATHLIB_NS_END
