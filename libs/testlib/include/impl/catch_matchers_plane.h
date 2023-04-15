#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Plane<Real>>
    {
        static std::string convert(Plane<Real> const& plane)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << plane.normal.x << "," << plane.normal.y << "," << plane.normal.z << "]"
                << "-"
                << "(" << plane.d << ")";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class PlaneMatcher final : public Catch::Matchers::MatcherBase<Plane<Real>>
    {
    public:
        PlaneMatcher(const Plane<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Plane<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Plane<Real> m_target;
        double m_margin;
    };

    template <class Real>
    PlaneMatcher<Real> WithinAbs(const Plane<Real>& target, double margin = 1e-3)
    {
        return PlaneMatcher<Real>(target, margin);
    }
}
