#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Line3<Real>>
    {
        static std::string convert(mathlib::Line3<Real> const& line)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << line.start.x << "," << line.start.y << "," << line.start.z << "]"
                << "-"
                << "[" << line.end.x << "," << line.end.y << "," << line.end.z << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class Line3Matcher final : public Catch::Matchers::MatcherBase<mathlib::Line3<Real>>
    {
    public:
        Line3Matcher(const mathlib::Line3<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Line3<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Line3<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Line3Matcher<Real> WithinAbs(const mathlib::Line3<Real>& target, double margin = 1e-3)
    {
        return Line3Matcher<Real>(target, margin);
    }
}
