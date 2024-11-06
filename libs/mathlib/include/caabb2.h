#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class CAABB2
{
public:
	typedef RealT Real;

public:
	// Constructors
	CAABB2();
	CAABB2(const Vec2<Real>& center, const Vec2<Real>& size);

	// Setters
	CAABB2& set(const Vec2<Real>& point);
	CAABB2& set(const Vec2<Real>& center, const Vec2<Real>& size);
	CAABB2& set(const AABB2<Real>& box);
	CAABB2& set(int count, const Vec2<Real>* points);
	CAABB2& set(int count, const Vec2<Real>* points, int stride);

	CAABB2<Real>& add(const Vec2<Real>& point);

	// Create from
	static CAABB2 from(const Vec2<Real>& point);
	static CAABB2 from(const Vec2<Real>& center, const Vec2<Real>& size);
	static CAABB2 fromInfSup(const Vec2<Real>& inf, const Vec2<Real>& sup);
	static CAABB2 from(int count, const Vec2<Real>* points);
	static CAABB2 from(int count, const Vec2<Real>* points, int stride);

	// Assignments
	CAABB2& operator+=(const Vec2<Real>& t);
	CAABB2& operator-=(const Vec2<Real>& t);
	CAABB2& operator*=(Real k);
	CAABB2& operator/=(Real k);

	// Arithmetic operators
	CAABB2 operator+ (const Vec2<Real>& t) const;
	CAABB2 operator- (const Vec2<Real>& t) const;
	CAABB2 operator* (Real k) const;
	CAABB2 operator/ (Real k) const;

	// Comparison operators
	bool operator== (const CAABB2& rhs) const;
	bool operator!= (const CAABB2& rhs) const;

	// Functions
	Vec2<Real> inf() const;
	Vec2<Real> sup() const;
	Vec2<Real> size() const;
	Circle<Real> innerCircle() const;
	Circle<Real> outerCircle() const;
	Real area() const;
	bool isNull() const;

	Vec2<Real> pointAt(const Vec2<Real>& t) const;

	bool contains(const Vec2<Real>& point) const;
	bool contains(const CAABB2<Real>& box) const;

	bool intersects(const CAABB2<Real>& box) const;

	template <class CastReturnType>
	CAABB2<CastReturnType> cast() const;

	static const CAABB2 One;

public:
	Vec2<Real> center;
	Vec2<Real> extents;
};

MATHLIB_NS_END
