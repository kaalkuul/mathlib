#pragma once

namespace Matches
{
    template <class Real>
    bool marginCheck(Real matchee, Real target, double margin)
    {
        return (matchee + margin >= target) && (target + margin >= matchee);
    }

    template <class Real>
    bool marginCheck(const mathlib::Vec2<Real>& matchee, const mathlib::Vec2<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Vec3<Real>& matchee, const mathlib::Vec3<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Vec4<Real>& matchee, const mathlib::Vec4<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.w, target.w, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Mat2<Real>& matchee, const mathlib::Mat2<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Mat3<Real>& matchee, const mathlib::Mat3<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Mat4<Real>& matchee, const mathlib::Mat4<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.t, target.t, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Mat34<Real>& matchee, const mathlib::Mat34<Real>& target, double margin)
    {
        return marginCheck(matchee.rs, target.rs, margin)
            && marginCheck(matchee.t, target.t, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Quat<Real>& matchee, const mathlib::Quat<Real>& target, double margin)
    {
        return marginCheck(matchee.x, target.x, margin)
            && marginCheck(matchee.y, target.y, margin)
            && marginCheck(matchee.z, target.z, margin)
            && marginCheck(matchee.w, target.w, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::AABB2<Real>& matchee, const mathlib::AABB2<Real>& target, double margin)
    {
        return marginCheck(matchee.inf, target.inf, margin)
            && marginCheck(matchee.sup, target.sup, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::CAABB2<Real>& matchee, const mathlib::CAABB2<Real>& target, double margin)
    {
        return marginCheck(matchee.center, target.center, margin)
            && marginCheck(matchee.extents, target.extents, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::AABB3<Real>& matchee, const mathlib::AABB3<Real>& target, double margin)
    {
        return marginCheck(matchee.inf, target.inf, margin)
            && marginCheck(matchee.sup, target.sup, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::CAABB3<Real>& matchee, const mathlib::CAABB3<Real>& target, double margin)
    {
        return marginCheck(matchee.center, target.center, margin)
            && marginCheck(matchee.extents, target.extents, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::ColorRGB<Real>& matchee, const mathlib::ColorRGB<Real>& target, double margin)
    {
        return marginCheck(matchee.r, target.r, margin)
            && marginCheck(matchee.g, target.g, margin)
            && marginCheck(matchee.b, target.b, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::ColorRGBA<Real>& matchee, const mathlib::ColorRGBA<Real>& target, double margin)
    {
        return marginCheck(matchee.r, target.r, margin)
            && marginCheck(matchee.g, target.g, margin)
            && marginCheck(matchee.b, target.b, margin)
            && marginCheck(matchee.a, target.a, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::ColorHSV<Real>& matchee, const mathlib::ColorHSV<Real>& target, double margin)
    {
        return marginCheck(matchee.h, target.h, margin)
            && marginCheck(matchee.s, target.s, margin)
            && marginCheck(matchee.v, target.v, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Line2<Real>& matchee, const mathlib::Line2<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Line3<Real>& matchee, const mathlib::Line3<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.end, target.end, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Ray2<Real>& matchee, const mathlib::Ray2<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.direction, target.direction, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Ray3<Real>& matchee, const mathlib::Ray3<Real>& target, double margin)
    {
        return marginCheck(matchee.start, target.start, margin)
            && marginCheck(matchee.direction, target.direction, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Plane<Real>& matchee, const mathlib::Plane<Real>& target, double margin)
    {
        return marginCheck(matchee.normal, target.normal, margin)
            && marginCheck(matchee.d, target.d, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Circle<Real>& matchee, const mathlib::Circle<Real>& target, double margin)
    {
        return marginCheck(matchee.center, target.center, margin)
            && marginCheck(matchee.radius, target.radius, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Sphere<Real>& matchee, const mathlib::Sphere<Real>& target, double margin)
    {
        return marginCheck(matchee.center, target.center, margin)
            && marginCheck(matchee.radius, target.radius, margin);
    }

    template <class Real>
    bool marginCheck(const mathlib::Frustum<Real>& matchee, const mathlib::Frustum<Real>& target, double margin)
    {
        return marginCheck(matchee.corners[0], target.corners[0], margin)
            && marginCheck(matchee.corners[1], target.corners[1], margin)
            && marginCheck(matchee.corners[2], target.corners[2], margin)
            && marginCheck(matchee.corners[3], target.corners[3], margin)
            && marginCheck(matchee.corners[4], target.corners[4], margin)
            && marginCheck(matchee.corners[5], target.corners[5], margin)
            && marginCheck(matchee.corners[6], target.corners[6], margin)
            && marginCheck(matchee.corners[7], target.corners[7], margin);
    }
}
