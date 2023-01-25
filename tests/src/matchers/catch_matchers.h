#pragma once

#include "../utils.h"

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    bool marginCheck(Real matchee, Real target, double margin)
    {
        return (matchee + margin >= target) && (target + margin >= matchee);
    }

    template <class Real>
    bool marginCheck(const Vec2<Real>& matchee, const Vec2<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin);
    }

    template <class Real>
    bool marginCheck(const Vec3<Real>& matchee, const Vec3<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin);
    }

    template <class Real>
    bool marginCheck(const Mat2<Real>& matchee, const Mat2<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin);
    }

    template <class Real>
    bool marginCheck(const Mat3<Real>& matchee, const Mat3<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin);
    }

    template <class Real>
    bool marginCheck(const Mat34<Real>& matchee, const Mat34<Real>& target, double margin)
    {
        return marginCheck(matchee.rs, target.rs, margin)
            && marginCheck(matchee.t, target.t, margin);
    }

    template <class Real>
    bool marginCheck(const Quat<Real>& matchee, const Quat<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.w, target.w, margin);
    }
}
