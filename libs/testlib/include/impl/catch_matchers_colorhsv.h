#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::ColorHSV<Real>>
    {
        static std::string convert(mathlib::ColorHSV<Real> const& c)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << c.h << "," << c.s << "," << c.v << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class ColorHSVMatcher final : public Catch::Matchers::MatcherBase<mathlib::ColorHSV<Real>>
    {
    public:
        ColorHSVMatcher(const mathlib::ColorHSV<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::ColorHSV<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::ColorHSV<Real> m_target;
        double m_margin;
    };

    template <class Real>
    ColorHSVMatcher<Real> WithinAbs(const mathlib::ColorHSV<Real>& target, double margin = 1e-3)
    {
        return ColorHSVMatcher<Real>(target, margin);
    }
}
