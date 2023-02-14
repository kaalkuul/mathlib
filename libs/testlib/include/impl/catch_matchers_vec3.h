#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Vec3<Real>>
    {
        static std::string convert(Vec3<Real> const& v)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << v.x << "," << v.y << "," << v.z << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class Vec3Matcher final : public Catch::Matchers::MatcherBase<Vec3<Real>>
    {
    public:
        Vec3Matcher(const Vec3<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Vec3<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Vec3<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Vec3Matcher<Real> WithinAbs(const Vec3<Real>& target, double margin = 1e-3)
    {
        return Vec3Matcher<Real>(target, margin);
    }
}
