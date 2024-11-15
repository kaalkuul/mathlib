#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class AABB2
{
public:
	typedef RealT Real;

public:
	// Constructors
	AABB2();
	AABB2(const Vec2<Real>& inf, const Vec2<Real>& sup);

	// Setters
	AABB2& set(const Vec2<Real>& point);
	AABB2& set(const Vec2<Real>& inf, const Vec2<Real>& sup);
	AABB2& set(const CAABB2<Real>& box);
	AABB2& set(int count, const Vec2<Real>* points);
	AABB2& set(int count, const Vec2<Real>* points, int stride);

	AABB2<Real>& add(const Vec2<Real>& point);

	// Create from
	static AABB2 from(const Vec2<Real>& point);
	static AABB2 from(const Vec2<Real>& inf, const Vec2<Real>& sup);
	static AABB2 from(const CAABB2<Real>& box);
	static AABB2 from(int count, const Vec2<Real>* points);
	static AABB2 from(int count, const Vec2<Real>* points, int stride);

    static AABB2 fromIntersection(const AABB2<Real>& a, const AABB2<Real>& b);
    static AABB2 fromUnion(const AABB2<Real>& a, const AABB2<Real>& b);

	// Assignments
	AABB2& operator+=(const Vec2<Real>& t);
	AABB2& operator-=(const Vec2<Real>& t);
	AABB2& operator*=(Real k);
	AABB2& operator/=(Real k);

	// Arithmetic operators
	AABB2 operator+ (const Vec2<Real>& t) const;
	AABB2 operator- (const Vec2<Real>& t) const;
	AABB2 operator* (Real k) const;
	AABB2 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const AABB2& rhs) const;
	bool operator!= (const AABB2& rhs) const;

    // Transformations
    AABB2& scaleCentered(Real k);

	// Functions
	Vec2<Real> center() const;
	Vec2<Real> extents() const;
	Vec2<Real> size() const;
	Circle<Real> innerCircle() const;
	Circle<Real> outerCircle() const;
	Real area() const;
	bool isNull() const;

	Vec2<Real> pointAt(const Vec2<Real>& t) const;

	bool contains(const Vec2<Real>& point) const;
	bool contains(const AABB2<Real>& box) const;

    bool hits(Real& t, const Ray2<Real>& ray) const;
    bool hits(Real& t, const Line2<Real>& line) const;

	bool intersects(const AABB2<Real>& box) const;
    bool intersects(Real& t1, Real& t2, const Ray2<Real>& ray) const;
    bool intersects(Real& t1, Real& t2, const Line2<Real>& ray) const;

	template <class CastReturnType>
	AABB2<CastReturnType> cast() const;

    static const AABB2 Zero;
    static const AABB2 One;

public:
	Vec2<Real> inf;
	Vec2<Real> sup;
};

MATHLIB_NS_END
