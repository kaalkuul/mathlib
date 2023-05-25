#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Quat<Real>>
    {
        static std::string convert(mathlib::Quat<Real> const& q)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << q.x << "," << q.y << "," << q.z << "," << q.w << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class QuatMatcher final : public Catch::Matchers::MatcherBase<mathlib::Quat<Real>>
    {
    public:
        QuatMatcher(const mathlib::Quat<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Quat<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Quat<Real> m_target;
        double m_margin;
    };

    template <class Real>
    QuatMatcher<Real> WithinAbs(const mathlib::Quat<Real>& target, double margin = 1e-3)
    {
        return QuatMatcher<Real>(target, margin);
    }
}
