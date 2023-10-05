#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Tri2
{
public:
	typedef RealT Real;

public:
	// Constructors
	Tri2();

	// Create from
	static Tri2 from(const Vec2<Real>& a, const Vec2<Real>& b, const Vec2<Real>& c);

	// Comparison operators
	bool operator== (const Tri2& rhs) const;
	bool operator!= (const Tri2& rhs) const;

	// Functions
	bool contains(const Vec2<Real>& point) const;

	template <class CastReturnType>
	Tri2<CastReturnType> cast() const;

public:
	Vec2<Real> a;
	Vec2<Real> b;
	Vec2<Real> c;
};

MATHLIB_NS_END
