#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const ColorRGBA<Real> ColorRGBA<Real>::Black = ColorRGBA<Real>(Real(0), Real(0), Real(0), Real(1));

template <class Real>
const ColorRGBA<Real> ColorRGBA<Real>::White = ColorRGBA<Real>(Real(1), Real(1), Real(1), Real(1));

template <class Real>
const ColorRGBA<Real> ColorRGBA<Real>::Red = ColorRGBA<Real>(Real(1), Real(0), Real(0), Real(1));

template <class Real>
const ColorRGBA<Real> ColorRGBA<Real>::Green = ColorRGBA<Real>(Real(0), Real(1), Real(0), Real(1));

template <class Real>
const ColorRGBA<Real> ColorRGBA<Real>::Blue = ColorRGBA<Real>(Real(0), Real(0), Real(1), Real(1));

//
// Constructors
//

template <class Real>
ColorRGBA<Real>::ColorRGBA()
{
}

template <class Real>
ColorRGBA<Real>::ColorRGBA(Real k, Real pa)
	: r(k), g(k), b(k), a(pa)
{
}

template <class Real>
ColorRGBA<Real>::ColorRGBA(Real pr, Real pg, Real pb, Real pa)
	: r(pr), g(pg), b(pb), a(pa)
{
}

template <class Real>
ColorRGBA<Real>::ColorRGBA(int pr, int pg, int pb, int pa)
	: r(Real(pr) / Real(255)), g(Real(pg) / Real(255)), b(Real(pb) / Real(255)), a(Real(pa) / Real(255))
{
}

//
// Create from
//

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::fromInterp(const ColorRGBA<Real>& a, const ColorRGBA<Real>& b, Real ratio)
{
	ColorRGBA c;
	c.interp(a, b, ratio);
	return c;
}

//
// Setters
// 

template <class Real>
ColorRGBA<Real>& ColorRGBA<Real>::set(Real r, Real g, Real b, Real a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	return *this;
}

template <class Real>
ColorRGBA<Real>& ColorRGBA<Real>::set(const ColorRGBA& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
	return *this;
}

template <class Real>
ColorRGBA<Real>& ColorRGBA<Real>::interp(const ColorRGBA<Real>& a, const ColorRGBA<Real>& b, Real ratio)
{
	if (ratio == Real(0))
		return set(a);

	if (ratio == Real(1))
		return set(b);

	this->r = a.r + (b.r - a.r) * ratio;
	this->g = a.g + (b.g - a.g) * ratio;
	this->b = a.b + (b.b - a.b) * ratio;
	this->a = a.a + (b.a - a.a) * ratio;
	
	return *this;
}

//
//  Assignments
//

template <class Real>
ColorRGBA<Real> & ColorRGBA<Real>::operator+= (const ColorRGBA &c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return *this;
}

template <class Real>
ColorRGBA<Real> & ColorRGBA<Real>::operator-= (const ColorRGBA &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	return *this;
}

template <class Real>
ColorRGBA<Real> & ColorRGBA<Real>::operator*= (Real k)
{
	r *= k;
	g *= k;
	b *= k;
	return *this;
}

template <class Real>
ColorRGBA<Real> & ColorRGBA<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	r /= k;
	g /= k;
	b /= k;
	return *this;
}

//
// Arithmetic operators
//

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::operator+ (const ColorRGBA &c) const
{
	return ColorRGBA(r + c.r, g + c.g, b + c.b, a);
}

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::operator- () const
{
	return ColorRGBA(-r, -g, -b, a);
}

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::operator- (const ColorRGBA &c) const
{
	return ColorRGBA(r - c.r, g - c.g, b - c.b, a);
}

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::operator* (Real k) const
{
	return ColorRGBA(r * k, g * k, b * k, a);
}

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return ColorRGBA(r / k, g / k, b / k, a);
}


//
// Comparison operators
//

template <class Real>
bool ColorRGBA<Real>::operator== (const ColorRGBA &c) const
{
	return r == c.r && g == c.g && b == c.b && a == c.a;
}

template <class Real>
bool ColorRGBA<Real>::operator!= (const ColorRGBA &c) const
{
	return r != c.r || g != c.g || b != c.b || a != c.a;
}


//
//  Functions
//

template <class Real>
ColorRGB<Real> ColorRGBA<Real>::toRGB() const
{
	return ColorRGB<Real>(r, g, b);
}

template <class Real>
ColorHSV<Real> ColorRGBA<Real>::toHSV() const
{
	return toRGB().toHSV();
}

template <class Real>
const Real* ColorRGBA<Real>::data() const
{
	return &r;
}

template <class Real>
Real* ColorRGBA<Real>::data()
{
	return &r;
}

template <class Real>
template <class CastReturnType>
ColorRGBA<CastReturnType> ColorRGBA<Real>::cast() const
{
	return ColorRGBA<CastReturnType>(
		static_cast<CastReturnType>(r),
		static_cast<CastReturnType>(g), 
		static_cast<CastReturnType>(b), 
		static_cast<CastReturnType>(a)
	);
}

template <class Real>
ColorRGBA<Real> ColorRGBA<Real>::random(Real a)
{
	ColorRGBA<Real> c;
	c.r = rand(Real(1));
	c.g = rand(Real(1));
	c.b = rand(Real(1));
	c.a = a;
	return c;
}

MATHLIB_NS_END
