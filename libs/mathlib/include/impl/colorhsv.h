#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const ColorHSV<Real> ColorHSV<Real>::Black = ColorHSV<Real>(Real(0), Real(0), Real(0));

template <class Real>
const ColorHSV<Real> ColorHSV<Real>::White = ColorHSV<Real>(Real(0), Real(0), Real(1));

template <class Real>
const ColorHSV<Real> ColorHSV<Real>::Red = ColorHSV<Real>(Real(0), Real(1), Real(1));

template <class Real>
const ColorHSV<Real> ColorHSV<Real>::Green = ColorHSV<Real>(Real(120), Real(1), Real(1));

template <class Real>
const ColorHSV<Real> ColorHSV<Real>::Blue = ColorHSV<Real>(Real(240), Real(1), Real(1));

//
// Constructors
//

template <class Real>
ColorHSV<Real>::ColorHSV()
{
}

template <class Real>
ColorHSV<Real>::ColorHSV(Real ph, Real ps, Real pv)
	: h(ph), s(ps), v(pv)
{
}

//
// Create from
//

template <class Real>
ColorHSV<Real> ColorHSV<Real>::fromInterp(const ColorHSV<Real>& a, const ColorHSV<Real>& b, Real ratio)
{
	ColorHSV c;
	c.interp(a, b, ratio);
	return c;
}

//
// Setters
// 

template <class Real>
ColorHSV<Real>& ColorHSV<Real>::set(Real h, Real s, Real v)
{
	this->h = h;
	this->s = s;
	this->v = v;
	return *this;
}

template <class Real>
ColorHSV<Real>& ColorHSV<Real>::set(const ColorHSV& c)
{
	this->h = c.h;
	this->s = c.s;
	this->v = c.v;
	return *this;
}

template <class Real>
ColorHSV<Real>& ColorHSV<Real>::interp(const ColorHSV<Real>& a, const ColorHSV<Real>& b, Real ratio)
{
	if (ratio == Real(0))
		return set(a);

	if (ratio == Real(1))
		return set(b);

    Real d = b.h - a.h;
    Real delta = d + ((abs(d) > Real(180)) ? ((d < Real(0)) ? Real(360) : -Real(360)) : Real(0));

	this->h = fmodPositive(a.h + delta * ratio, Real(360));
	this->s = lerp(a.s, b.s, ratio);
	this->v = lerp(a.v, b.v, ratio);
	
	return *this;
}

//
// Comparison operators
//

template <class Real>
bool ColorHSV<Real>::operator== (const ColorHSV &c) const
{
	return h == c.h && s == c.s && v == c.v;
}

template <class Real>
bool ColorHSV<Real>::operator!= (const ColorHSV &c) const
{
	return h != c.h || s != c.s || v != c.v;
}


//
//  Functions
//

template <class Real>
ColorRGB<Real> ColorHSV<Real>::toRGB() const
{
    Real p0 = fmodPositive(h / Real(60), Real(6));

    int i = (int)p0;
    Real f = p0 - i;
    Real p1 = v * (Real(1) - s);
    Real p2 = v * (Real(1) - s * f);
    Real p3 = v * (Real(1) - s * (Real(1) - f));

    ColorRGB<Real> rgb;

    switch (i)
    {
    case 0:
        rgb.r = v;
        rgb.g = p3;
        rgb.b = p1;
        break;

    case 1:
        rgb.r = p2;
        rgb.g = v;
        rgb.b = p1;
        break;

    case 2:
        rgb.r = p1;
        rgb.g = v;
        rgb.b = p3;
        break;

    case 3:
        rgb.r = p1;
        rgb.g = p2;
        rgb.b = v;
        break;

    case 4:
        rgb.r = p3;
        rgb.g = p1;
        rgb.b = v;
        break;

    case 5:
        rgb.r = v;
        rgb.g = p1;
        rgb.b = p2;
        break;
    }

    return rgb;
}

template <class Real>
ColorRGBA<Real> ColorHSV<Real>::toRGBA(Real alpha) const
{
	return toRGB().toRGBA(alpha);
}

template <class Real>
const Real* ColorHSV<Real>::data() const
{
	return &h;
}

template <class Real>
Real* ColorHSV<Real>::data()
{
	return &h;
}

template <class Real>
template <class CastReturnType>
ColorHSV<CastReturnType> ColorHSV<Real>::cast() const
{
	return ColorHSV<CastReturnType>(
		static_cast<CastReturnType>(h),
		static_cast<CastReturnType>(s), 
		static_cast<CastReturnType>(v)
	);
}

template <class Real>
ColorHSV<Real> ColorHSV<Real>::random()
{
	ColorHSV<Real> c;
	c.h = rand(Real(360));
	c.s = rand(Real(1));
	c.v = rand(Real(1));
	return c;
}

MATHLIB_NS_END
