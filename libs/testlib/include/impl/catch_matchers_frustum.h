#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Frustum<Real>>
    {
        static std::string convert(mathlib::Frustum<Real> const& f)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(4)
                << "["
                << "[" << f.corners[0].x << "," << f.corners[0].y << "," << f.corners[0].z << "],"
                << "[" << f.corners[1].x << "," << f.corners[1].y << "," << f.corners[1].z << "],"
                << "[" << f.corners[2].x << "," << f.corners[2].y << "," << f.corners[2].z << "],"
                << "[" << f.corners[3].x << "," << f.corners[3].y << "," << f.corners[3].z << "],"
                << "[" << f.corners[4].x << "," << f.corners[4].y << "," << f.corners[4].z << "],"
                << "[" << f.corners[5].x << "," << f.corners[5].y << "," << f.corners[5].z << "],"
                << "[" << f.corners[6].x << "," << f.corners[6].y << "," << f.corners[6].z << "],"
                << "[" << f.corners[7].x << "," << f.corners[7].y << "," << f.corners[7].z << "]"
                << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class FrustumMatcher final : public Catch::Matchers::MatcherBase<mathlib::Frustum<Real>>
    {
    public:
        FrustumMatcher(const mathlib::Frustum<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Frustum<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Frustum<Real> m_target;
        double m_margin;
    };

    template <class Real>
    FrustumMatcher<Real> WithinAbs(const mathlib::Frustum<Real>& target, double margin = 1e-3)
    {
        return FrustumMatcher<Real>(target, margin);
    }
}
