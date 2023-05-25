#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::ColorRGB<Real>>
    {
        static std::string convert(mathlib::ColorRGB<Real> const& c)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << c.r << "," << c.g << "," << c.b << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class ColorRGBMatcher final : public Catch::Matchers::MatcherBase<mathlib::ColorRGB<Real>>
    {
    public:
        ColorRGBMatcher(const mathlib::ColorRGB<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::ColorRGB<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::ColorRGB<Real> m_target;
        double m_margin;
    };

    template <class Real>
    ColorRGBMatcher<Real> WithinAbs(const mathlib::ColorRGB<Real>& target, double margin = 1e-3)
    {
        return ColorRGBMatcher<Real>(target, margin);
    }
}
