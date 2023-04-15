#pragma once

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
    bool marginCheck(const Vec4<Real>& matchee, const Vec4<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.w, target.w, margin);
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
    bool marginCheck(const Mat4<Real>& matchee, const Mat4<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.t, target.t, margin);
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

    template <class Real>
    bool marginCheck(const ColorRGB<Real>& matchee, const ColorRGB<Real>& target, double margin)
    {
        return marginCheck(matchee.r, target.r, margin)
            && marginCheck(matchee.g, target.g, margin)
            && marginCheck(matchee.b, target.b, margin);
    }

    template <class Real>
    bool marginCheck(const ColorRGBA<Real>& matchee, const ColorRGBA<Real>& target, double margin)
    {
        return marginCheck(matchee.r, target.r, margin)
            && marginCheck(matchee.g, target.g, margin)
            && marginCheck(matchee.b, target.b, margin)
            && marginCheck(matchee.a, target.a, margin);
    }

    template <class Real>
    bool marginCheck(const ColorHSV<Real>& matchee, const ColorHSV<Real>& target, double margin)
    {
        return marginCheck(matchee.h, target.h, margin)
            && marginCheck(matchee.s, target.s, margin)
            && marginCheck(matchee.v, target.v, margin);
    }

    template <class Real>
    bool marginCheck(const Line2<Real>& matchee, const Line2<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const Line3<Real>& matchee, const Line3<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const Ray2<Real>& matchee, const Ray2<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const Ray3<Real>& matchee, const Ray3<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const Plane<Real>& matchee, const Plane<Real>& target, double margin)
    {
        return marginCheck(matchee.normal, target.normal, margin)
            && marginCheck(matchee.d, target.d, margin);
    }

    template <class Real>
    bool marginCheck(const Sphere<Real>& matchee, const Sphere<Real>& target, double margin)
    {
        return marginCheck(matchee.center, target.center, margin)
            && marginCheck(matchee.radius, target.radius, margin);
    }
}
