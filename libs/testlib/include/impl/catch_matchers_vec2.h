#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Vec2<Real>>
    {
        static std::string convert(mathlib::Vec2<Real> const& v)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << v.x << "," << v.y << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class Vec2Matcher final : public Catch::Matchers::MatcherBase<mathlib::Vec2<Real>>
    {
    public:
        Vec2Matcher(const mathlib::Vec2<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Vec2<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Vec2<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Vec2Matcher<Real> WithinAbs(const mathlib::Vec2<Real>& target, double margin = 1e-3)
    {
        return Vec2Matcher<Real>(target, margin);
    }
}
