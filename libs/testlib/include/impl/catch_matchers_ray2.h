#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Ray2<Real>>
    {
        static std::string convert(mathlib::Ray2<Real> const& ray)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << ray.start.x << "," << ray.start.y << "]"
                << "-"
                << "[" << ray.direction.x << "," << ray.direction.y << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class Ray2Matcher final : public Catch::Matchers::MatcherBase<mathlib::Ray2<Real>>
    {
    public:
        Ray2Matcher(const mathlib::Ray2<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Ray2<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Ray2<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Ray2Matcher<Real> WithinAbs(const mathlib::Ray2<Real>& target, double margin = 1e-3)
    {
        return Ray2Matcher<Real>(target, margin);
    }
}
