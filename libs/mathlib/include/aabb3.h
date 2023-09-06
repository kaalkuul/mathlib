#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class AABB3
{
public:
	typedef Real Real;

public:
	// Constructors
	AABB3();
	AABB3(const Vec3<Real>& center, const Vec3<Real>& size);

	// Setters
	AABB3& set(const Vec3<Real>& point);
	AABB3& set(const Vec3<Real>& center, const Vec3<Real>& size);
	AABB3& setInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup);
	AABB3& set(int count, const Vec3<Real>* points);
	AABB3& set(int count, const Vec3<Real>* points, int stride);

	AABB3<Real>& add(const Vec3<Real>& point);

	// Create from
	static AABB3 from(const Vec3<Real>& point);
	static AABB3 from(const Vec3<Real>& center, const Vec3<Real>& size);
	static AABB3 fromInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup);
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
	bool contains(const AABB3<Real>& box) const;

	bool intersects(const AABB3<Real>& box) const;

	template <class CastReturnType>
	AABB3<CastReturnType> cast() const;

	static const AABB3 One;

public:
	Vec3<Real> center;
	Vec3<Real> extents;
};

MATHLIB_NS_END
