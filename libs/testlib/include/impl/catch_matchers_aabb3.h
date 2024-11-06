#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::AABB3<Real>>
    {
        static std::string convert(mathlib::AABB3<Real> const& box)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << box.inf.x << "," << box.inf.y << "," << box.inf.z << "]"
                << "-"
                << "[" << box.sup.x << "," << box.sup.y << "," << box.sup.z << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class AABB3Matcher final : public Catch::Matchers::MatcherBase<mathlib::AABB3<Real>>
    {
    public:
        AABB3Matcher(const mathlib::AABB3<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::AABB3<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::AABB3<Real> m_target;
        double m_margin;
    };

    template <class Real>
    AABB3Matcher<Real> WithinAbs(const mathlib::AABB3<Real>& target, double margin = 1e-3)
    {
        return AABB3Matcher<Real>(target, margin);
    }
}
