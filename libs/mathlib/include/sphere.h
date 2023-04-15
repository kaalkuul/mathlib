#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Sphere
{
public:
	// Constructors
	Sphere();
	Sphere(const Vec3<Real>& center, Real radius);

	// Create from
	static Sphere from(const Vec3<Real>& center, Real radius);

	// Comparison operators
	bool operator== (const Sphere& rhs) const;
	bool operator!= (const Sphere& rhs) const;

	// Functions
	bool contains(const Vec3<Real>& point) const;

	bool hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;

	bool intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Sphere<CastReturnType> cast() const;

	static const Sphere One;

public:
	Vec3<Real> center;
	Real radius;
};

MATHLIB_NS_END
