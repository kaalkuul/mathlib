#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Ray3<Real>>
    {
        static std::string convert(Ray3<Real> const& ray)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
                << "[" << ray.start.x << "," << ray.start.y << "," << ray.start.z << "]"
                << "-"
                << "[" << ray.direction.x << "," << ray.direction.y << "," << ray.direction.z << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class Ray3Matcher final : public Catch::Matchers::MatcherBase<Ray3<Real>>
    {
    public:
        Ray3Matcher(const Ray3<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Ray3<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Ray3<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Ray3Matcher<Real> WithinAbs(const Ray3<Real>& target, double margin = 1e-3)
    {
        return Ray3Matcher<Real>(target, margin);
    }
}
