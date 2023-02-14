#pragma once

#include <limits>

MATHLIB_NS_BEGIN

template <class Real>
const Real Constants<Real>::PI = Real(3.1415926535897932384626433832795);

template <class Real>
const Real Constants<Real>::PI_TIMES_2 = Real(Constants<Real>::PI * 2.0);

template <class Real>
const Real Constants<Real>::PI_OVER_2 = Real(Constants<Real>::PI * 0.5);

template <class Real>
const Real Constants<Real>::PI_OVER_4 = Real(Constants<Real>::PI * 0.25);

template <class Real>
const Real Constants<Real>::PI_OVER_8 = Real(Constants<Real>::PI * 0.125);

template <class Real>
const Real Constants<Real>::PI_OVER_16 = Real(Constants<Real>::PI * 0.0625);

template <class Real>
const Real Constants<Real>::PI_OVER_3 = Real(Constants<Real>::PI / 3.0);

template <class Real>
const Real Constants<Real>::PI_OVER_6 = Real(Constants<Real>::PI / 6.0);

// How to obtain the highest negative value of a floating point type?
// According to: https://stackoverflow.com/questions/1153548/minimum-double-value-in-c-c
// "Floating point numbers (IEEE 754) are symmetrical, so if you can represent
// the greatest value (DBL_MAX or numeric_limits<double>::max()), just prepend a minus sign."
// Proof: the binary format for float/double provides a dedicated sign bit. All the 31 or 63
// remaining bits are used to represent the absolute value, as shown here:
// https://en.wikipedia.org/wiki/IEEE_754
// https://en.wikipedia.org/wiki/Double-precision_floating-point_format

template <class Real>
const Real Constants<Real>::MIN_VALUE = std::numeric_limits<Real>::min();

template <class Real>
const Real Constants<Real>::MAX_VALUE = std::numeric_limits<Real>::max();

template <class Real>
const Real Constants<Real>::MAX_NEG_VALUE = -std::numeric_limits<Real>::max();

MATHLIB_NS_END
