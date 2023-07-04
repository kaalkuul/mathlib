#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::AABB<Real>>
    {
        static std::string convert(mathlib::AABB<Real> const& box)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << box.center.x << "," << box.center.y << "," << box.center.z << "]"
                << "-"
                << "[" << box.extents.x << "," << box.extents.y << "," << box.extents.z << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class AABBMatcher final : public Catch::Matchers::MatcherBase<mathlib::AABB<Real>>
    {
    public:
        AABBMatcher(const mathlib::AABB<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::AABB<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::AABB<Real> m_target;
        double m_margin;
    };

    template <class Real>
    AABBMatcher<Real> WithinAbs(const mathlib::AABB<Real>& target, double margin = 1e-3)
    {
        return AABBMatcher<Real>(target, margin);
    }
}
