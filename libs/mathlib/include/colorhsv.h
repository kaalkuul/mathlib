#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class ColorHSV
{
public:
	// Constructors
	ColorHSV();
	ColorHSV(Real h, Real s, Real v);

	// Create from
	static ColorHSV fromInterp(const ColorHSV& a, const ColorHSV& b, Real ratio);

	// Setters
	ColorHSV& set(Real h, Real s, Real v);
	ColorHSV& set(const ColorHSV& c);
	ColorHSV& interp(const ColorHSV& a, const ColorHSV& b, Real ratio);

	// Comparison operators
	bool operator==(const ColorHSV& c) const;
	bool operator!=(const ColorHSV& c) const;

	// Functions
	ColorRGB<Real> toRGB() const;
	ColorRGBA<Real> toRGBA(Real alpha = Real(1)) const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	ColorHSV<CastReturnType> cast() const;

	static ColorHSV random();

	static const ColorHSV Black;
	static const ColorHSV White;
	static const ColorHSV Red;
	static const ColorHSV Green;
	static const ColorHSV Blue;

public:
	Real h, s, v;
};

MATHLIB_NS_END
