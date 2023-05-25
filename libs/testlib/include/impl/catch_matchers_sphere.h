#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Sphere<Real>>
    {
        static std::string convert(mathlib::Sphere<Real> const& sphere)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << sphere.center.x << "," << sphere.center.y << "," << sphere.center.z << "]"
                << "-"
                << "(" << sphere.radius << ")";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class SphereMatcher final : public Catch::Matchers::MatcherBase<mathlib::Sphere<Real>>
    {
    public:
        SphereMatcher(const mathlib::Sphere<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Sphere<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Sphere<Real> m_target;
        double m_margin;
    };

    template <class Real>
    SphereMatcher<Real> WithinAbs(const mathlib::Sphere<Real>& target, double margin = 1e-3)
    {
        return SphereMatcher<Real>(target, margin);
    }
}
