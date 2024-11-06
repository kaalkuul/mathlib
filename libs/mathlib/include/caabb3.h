#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class CAABB3
{
public:
	typedef RealT Real;

public:
	// Constructors
	CAABB3();
	CAABB3(const Vec3<Real>& center, const Vec3<Real>& size);

	// Setters
	CAABB3& set(const Vec3<Real>& point);
	CAABB3& set(const Vec3<Real>& center, const Vec3<Real>& size);
	CAABB3& set(const AABB3<Real>& box);
	CAABB3& set(int count, const Vec3<Real>* points);
	CAABB3& set(int count, const Vec3<Real>* points, int stride);

	CAABB3<Real>& add(const Vec3<Real>& point);

	// Create from
	static CAABB3 from(const Vec3<Real>& point);
	static CAABB3 from(const Vec3<Real>& center, const Vec3<Real>& size);
	static CAABB3 from(const AABB3<Real>& box);
	static CAABB3 from(int count, const Vec3<Real>* points);
	static CAABB3 from(int count, const Vec3<Real>* points, int stride);

	// Assignments
	CAABB3& operator+=(const Vec3<Real>& t);
	CAABB3& operator-=(const Vec3<Real>& t);
	CAABB3& operator*=(Real k);
	CAABB3& operator/=(Real k);

	// Arithmetic operators
	CAABB3 operator+ (const Vec3<Real>& t) const;
	CAABB3 operator- (const Vec3<Real>& t) const;
	CAABB3 operator* (Real k) const;
	CAABB3 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const CAABB3& rhs) const;
	bool operator!= (const CAABB3& rhs) const;

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
	bool contains(const CAABB3<Real>& box) const;

	bool intersects(const CAABB3<Real>& box) const;

	template <class CastReturnType>
	CAABB3<CastReturnType> cast() const;

	static const CAABB3 One;

public:
	Vec3<Real> center;
	Vec3<Real> extents;
};

MATHLIB_NS_END
