#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::CAABB2<Real>>
    {
        static std::string convert(mathlib::CAABB2<Real> const& box)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << box.center.x << "," << box.center.y << "]"
                << "-"
                << "[" << box.extents.x << "," << box.extents.y << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class CAABB2Matcher final : public Catch::Matchers::MatcherBase<mathlib::CAABB2<Real>>
    {
    public:
        CAABB2Matcher(const mathlib::CAABB2<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::CAABB2<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::CAABB2<Real> m_target;
        double m_margin;
    };

    template <class Real>
    CAABB2Matcher<Real> WithinAbs(const mathlib::CAABB2<Real>& target, double margin = 1e-3)
    {
        return CAABB2Matcher<Real>(target, margin);
    }
}
