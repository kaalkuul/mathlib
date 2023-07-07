#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class AABB
{
public:
	// Constructors
	AABB();
	AABB(const Vec3<Real>& center, const Vec3<Real>& size);

	// Setters
	AABB& set(const Vec3<Real>& point);
	AABB& set(const Vec3<Real>& center, const Vec3<Real>& size);
	AABB& setInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup);
	AABB& set(int count, const Vec3<Real>* points);

	AABB<Real>& add(const Vec3<Real>& point);

	// Create from
	static AABB from(const Vec3<Real>& point);
	static AABB from(const Vec3<Real>& center, const Vec3<Real>& size);
	static AABB fromInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup);
	static AABB from(int count, const Vec3<Real>* points);

	// Assignments
	AABB& operator+=(const Vec3<Real>& t);
	AABB& operator-=(const Vec3<Real>& t);
	AABB& operator*=(Real k);
	AABB& operator/=(Real k);

	// Arithmetic operators
	AABB operator+ (const Vec3<Real>& t) const;
	AABB operator- (const Vec3<Real>& t) const;
	AABB operator* (Real k) const;
	AABB operator/ (Real k) const;

	// Comparison operators
	bool operator== (const AABB& rhs) const;
	bool operator!= (const AABB& rhs) const;

	// Functions
	Vec3<Real> inf() const;
	Vec3<Real> sup() const;
	Vec3<Real> size() const;
	Sphere<Real> innerSphere() const;
	Sphere<Real> outerSphere() const;
	Real volume() const;
	bool isNull() const;

	Vec3<Real> pointAt(const Vec3<Real>& t) const;

	bool contains(const Vec3<Real>& point) const;
	bool contains(const Sphere<Real>& sphere) const;
	bool contains(const AABB<Real>& box) const;

	bool intersects(const AABB<Real>& box) const;

	template <class CastReturnType>
	AABB<CastReturnType> cast() const;

	static const AABB One;

public:
	Vec3<Real> center;
	Vec3<Real> extents;
};

MATHLIB_NS_END
