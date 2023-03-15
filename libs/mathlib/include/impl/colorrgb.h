#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const ColorRGB<Real> ColorRGB<Real>::Black = ColorRGB<Real>(Real(0), Real(0), Real(0));

template <class Real>
const ColorRGB<Real> ColorRGB<Real>::White = ColorRGB<Real>(Real(1), Real(1), Real(1));

template <class Real>
const ColorRGB<Real> ColorRGB<Real>::Red = ColorRGB<Real>(Real(1), Real(0), Real(0));

template <class Real>
const ColorRGB<Real> ColorRGB<Real>::Green = ColorRGB<Real>(Real(0), Real(1), Real(0));

template <class Real>
const ColorRGB<Real> ColorRGB<Real>::Blue = ColorRGB<Real>(Real(0), Real(0), Real(1));

//
// Constructors
//

template <class Real>
ColorRGB<Real>::ColorRGB()
{
}

template <class Real>
ColorRGB<Real>::ColorRGB(Real k)
	: r(k), g(k), b(k)
{
}

template <class Real>
ColorRGB<Real>::ColorRGB(Real pr, Real pg, Real pb)
	: r(pr), g(pg), b(pb)
{
}

template <class Real>
ColorRGB<Real>::ColorRGB(int pr, int pg, int pb)
	: r(Real(pr) / Real(255)), g(Real(pg) / Real(255)), b(Real(pb) / Real(255))
{
}

//
// Create from
//

template <class Real>
ColorRGB<Real> ColorRGB<Real>::fromInterp(const ColorRGB<Real>& a, const ColorRGB<Real>& b, Real ratio)
{
	ColorRGB c;
	c.interp(a, b, ratio);
	return c;
}

//
// Setters
// 

template <class Real>
ColorRGB<Real>& ColorRGB<Real>::set(Real r, Real g, Real b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	return *this;
}

template <class Real>
ColorRGB<Real>& ColorRGB<Real>::set(const ColorRGB& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	return *this;
}

template <class Real>
ColorRGB<Real>& ColorRGB<Real>::interp(const ColorRGB<Real>& a, const ColorRGB<Real>& b, Real ratio)
{
	if (ratio == Real(0))
		return set(a);

	if (ratio == Real(1))
		return set(b);

	this->r = a.r + (b.r - a.r) * ratio;
	this->g = a.g + (b.g - a.g) * ratio;
	this->b = a.b + (b.b - a.b) * ratio;
	
	return *this;
}

//
//  Assignments
//

template <class Real>
ColorRGB<Real> & ColorRGB<Real>::operator+= (const ColorRGB &c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return *this;
}

template <class Real>
ColorRGB<Real> & ColorRGB<Real>::operator-= (const ColorRGB &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	return *this;
}

template <class Real>
ColorRGB<Real> & ColorRGB<Real>::operator*= (Real k)
{
	r *= k;
	g *= k;
	b *= k;
	return *this;
}

template <class Real>
ColorRGB<Real> & ColorRGB<Real>::operator/= (Real k)
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
ColorRGB<Real> ColorRGB<Real>::operator+ (const ColorRGB &c) const
{
	return ColorRGB(r + c.r, g + c.g, b + c.b);
}

template <class Real>
ColorRGB<Real> ColorRGB<Real>::operator- () const
{
	return ColorRGB(-r, -g, -b);
}

template <class Real>
ColorRGB<Real> ColorRGB<Real>::operator- (const ColorRGB &c) const
{
	return ColorRGB(r - c.r, g - c.g, b - c.b);
}

template <class Real>
ColorRGB<Real> ColorRGB<Real>::operator* (Real k) const
{
	return ColorRGB(r * k, g * k, b * k);
}

template <class Real>
ColorRGB<Real> ColorRGB<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return ColorRGB(r / k, g / k, b / k);
}


//
// Comparison operators
//

template <class Real>
bool ColorRGB<Real>::operator== (const ColorRGB &c) const
{
	return r == c.r && g == c.g && b == c.b;
}

template <class Real>
bool ColorRGB<Real>::operator!= (const ColorRGB &c) const
{
	return r != c.r || g != c.g || b != c.b;
}


//
//  Functions
//
//

template <class Real>
ColorRGBA<Real> ColorRGB<Real>::toRGBA(Real alpha) const
{
	return ColorRGBA<Real>(r, g, b, alpha);
}

template <class Real>
ColorHSV<Real> ColorRGB<Real>::toHSV() const
{
    Real red   = Real(r);
    Real green = Real(g);
    Real blue  = Real(b);

	Real low = red;
	Real vee = red;
    if (green < low) low = green;
    if (green > vee) vee = green;
    if (blue < low) low = blue;
    if (blue > vee) vee = blue;

	ColorHSV<Real> hsv;
    if (vee > low)
    {
        Real s = (vee - low) / vee;

		Real h = Real(0);

		if (vee == red)
        {
            h = (green - blue) / (vee - low);
        }
        else if (vee == green)
        {
			h = Real(2) + (blue - red) / (vee - low);
		}
        else if (vee == blue)
        {
            h = Real(4) + (red - green) / (vee - low);
        }

        if (h < 0)
        {
            h += Real(6);
        }
        else if (h >= Real(6))
        {
            h -= Real(6);
        }

		hsv.h = h * Real(60);
        hsv.s = s;
        hsv.v = vee;
    }
    else
    {
		hsv.h = 0.0f;
        hsv.s = 0.0f;
        hsv.v = vee;
    }

	return hsv;
}

template <class Real>
const Real* ColorRGB<Real>::data() const
{
	return &r;
}

template <class Real>
Real* ColorRGB<Real>::data()
{
	return &r;
}

template <class Real>
template <class CastReturnType>
ColorRGB<CastReturnType> ColorRGB<Real>::cast() const
{
	return ColorRGB<CastReturnType>(
		static_cast<CastReturnType>(r),
		static_cast<CastReturnType>(g), 
		static_cast<CastReturnType>(b)
	);
}

template <class Real>
ColorRGB<Real> ColorRGB<Real>::random()
{
	ColorRGB<Real> c;
	c.r = rand(Real(1));
	c.g = rand(Real(1));
	c.b = rand(Real(1));
	return c;
}

MATHLIB_NS_END
