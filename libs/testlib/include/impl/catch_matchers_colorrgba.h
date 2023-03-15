#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<ColorRGBA<Real>>
    {
        static std::string convert(ColorRGBA<Real> const& c)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << c.r << "," << c.g << "," << c.b << "," << c.a << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class ColorRGBAMatcher final : public Catch::Matchers::MatcherBase<ColorRGBA<Real>>
    {
    public:
        ColorRGBAMatcher(const ColorRGBA<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(ColorRGBA<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        ColorRGBA<Real> m_target;
        double m_margin;
    };

    template <class Real>
    ColorRGBAMatcher<Real> WithinAbs(const ColorRGBA<Real>& target, double margin = 1e-3)
    {
        return ColorRGBAMatcher<Real>(target, margin);
    }
}
