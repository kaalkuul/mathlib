#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class ColorRGBA
{
public:
	typedef Real Real;

public:
	// Constructors
	ColorRGBA();
	explicit ColorRGBA(Real k, Real a = Real(1));
	explicit ColorRGBA(Real r, Real g, Real b, Real a = Real(1));
	explicit ColorRGBA(int r, int g, int b, int a = 255);

	// Create from
	static ColorRGBA fromInterp(const ColorRGBA& a, const ColorRGBA& b, Real ratio);

	// Setters
	ColorRGBA& set(Real r, Real g, Real b, Real a = Real(1));
	ColorRGBA& set(const ColorRGBA& c);
	ColorRGBA& interp(const ColorRGBA& a, const ColorRGBA& b, Real ratio);

	// Assignments
	ColorRGBA& operator+=(const ColorRGBA& c);
	ColorRGBA& operator-=(const ColorRGBA& c);
	ColorRGBA& operator*=(Real k);
	ColorRGBA& operator/=(Real k);

	// Arithmetic operators
	ColorRGBA operator+(const ColorRGBA& c) const;
	ColorRGBA operator-() const;
	ColorRGBA operator-(const ColorRGBA& c) const;
	ColorRGBA operator*(Real k) const;
	ColorRGBA operator/(Real k) const;

	// Comparison operators
	bool operator==(const ColorRGBA& c) const;
	bool operator!=(const ColorRGBA& c) const;

	// Functions
	ColorRGB<Real> toRGB() const;
	ColorHSV<Real> toHSV() const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	ColorRGBA<CastReturnType> cast() const;

	static ColorRGBA random(Real a = Real(1));

	static const ColorRGBA Black;
	static const ColorRGBA White;
	static const ColorRGBA Red;
	static const ColorRGBA Green;
	static const ColorRGBA Blue;

public:
	Real r, g, b, a;
};

MATHLIB_NS_END
