#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class ColorRGB
{
public:
	typedef RealT Real;

public:
	// Constructors
	ColorRGB();
	explicit ColorRGB(Real k);
	explicit ColorRGB(Real r, Real g, Real b);
	explicit ColorRGB(int r, int g, int b);

	// Create from
	static ColorRGB fromInterp(const ColorRGB& a, const ColorRGB& b, Real ratio);

	// Setters
	ColorRGB& set(Real r, Real g, Real b);
	ColorRGB& set(const ColorRGB& c);
	ColorRGB& interp(const ColorRGB& a, const ColorRGB& b, Real ratio);

	// Assignments
	ColorRGB& operator+=(const ColorRGB& c);
	ColorRGB& operator-=(const ColorRGB& c);
	ColorRGB& operator*=(Real k);
	ColorRGB& operator/=(Real k);

	// Arithmetic operators
	ColorRGB operator+(const ColorRGB& c) const;
	ColorRGB operator-() const;
	ColorRGB operator-(const ColorRGB& c) const;
	ColorRGB operator*(Real k) const;
	ColorRGB operator/(Real k) const;

	// Comparison operators
	bool operator==(const ColorRGB& c) const;
	bool operator!=(const ColorRGB& c) const;

	// Functions
	ColorRGBA<Real> toRGBA(Real alpha = Real(1)) const;
	ColorHSV<Real> toHSV() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	ColorRGB<CastReturnType> cast() const;

	static ColorRGB random();

	static const ColorRGB Black;
	static const ColorRGB White;
	static const ColorRGB Red;
	static const ColorRGB Green;
	static const ColorRGB Blue;

public:
	Real r, g, b;
};

MATHLIB_NS_END
