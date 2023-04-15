#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Ray2<Real>>
    {
        static std::string convert(Ray2<Real> const& ray)
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
    using namespace mathlib;

    template <class Real>
    class Ray2Matcher final : public Catch::Matchers::MatcherBase<Ray2<Real>>
    {
    public:
        Ray2Matcher(const Ray2<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Ray2<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Ray2<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Ray2Matcher<Real> WithinAbs(const Ray2<Real>& target, double margin = 1e-3)
    {
        return Ray2Matcher<Real>(target, margin);
    }
}
