#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class AABB3
{
public:
	typedef RealT Real;

public:
	// Constructors
	AABB3();
	AABB3(const Vec3<Real>& inf, const Vec3<Real>& sup);

	// Setters
	AABB3& set(const Vec3<Real>& point);
	AABB3& set(const Vec3<Real>& inf, const Vec3<Real>& sup);
	AABB3& set(const CAABB3<Real>& box);
	AABB3& set(int count, const Vec3<Real>* points);
	AABB3& set(int count, const Vec3<Real>* points, int stride);

	AABB3<Real>& add(const Vec3<Real>& point);

	// Create from
	static AABB3 from(const Vec3<Real>& point);
	static AABB3 from(const Vec3<Real>& inf, const Vec3<Real>& sup);
	static AABB3 from(const CAABB3<Real>& box);
	static AABB3 from(int count, const Vec3<Real>* points);
	static AABB3 from(int count, const Vec3<Real>* points, int stride);

	// Assignments
	AABB3& operator+=(const Vec3<Real>& t);
	AABB3& operator-=(const Vec3<Real>& t);
	AABB3& operator*=(Real k);
	AABB3& operator/=(Real k);

	// Arithmetic operators
	AABB3 operator+ (const Vec3<Real>& t) const;
	AABB3 operator- (const Vec3<Real>& t) const;
	AABB3 operator* (Real k) const;
	AABB3 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const AABB3& rhs) const;
	bool operator!= (const AABB3& rhs) const;

    // Transformations
    AABB3& scaleCentered(Real k);

    // Functions
	Vec3<Real> center() const;
	Vec3<Real> extents() const;
	Vec3<Real> size() const;
	Sphere<Real> innerSphere() const;
	Sphere<Real> outerSphere() const;
	Real volume() const;
	bool isNull() const;

	Vec3<Real> pointAt(const Vec3<Real>& t) const;

	bool contains(const Vec3<Real>& point) const;
	bool contains(const Sphere<Real>& sphere) const;
	bool contains(const AABB3<Real>& box) const;

	bool intersects(const AABB3<Real>& box) const;

	template <class CastReturnType>
	AABB3<CastReturnType> cast() const;

	static const AABB3 One;

public:
	Vec3<Real> inf;
	Vec3<Real> sup;
};

MATHLIB_NS_END
