#pragma once

namespace Catch
{
    template <class Real>
    struct StringMaker<mathlib::Mat4<Real>>
    {
        static std::string convert(mathlib::Mat4<Real> const& m)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(4)
                << "["
                << "[" << m.x.x << "," << m.x.y << "," << m.x.z << "," << m.x.w << "],"
                << "[" << m.y.x << "," << m.y.y << "," << m.y.z << "," << m.y.w << "],"
                << "[" << m.z.x << "," << m.z.y << "," << m.z.z << "," << m.z.w << "],"
                << "[" << m.t.x << "," << m.t.y << "," << m.t.z << "," << m.t.w << "]"
                << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    template <class Real>
    class Mat4Matcher final : public Catch::Matchers::MatcherBase<mathlib::Mat4<Real>>
    {
    public:
        Mat4Matcher(const mathlib::Mat4<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(mathlib::Mat4<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        mathlib::Mat4<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Mat4Matcher<Real> WithinAbs(const mathlib::Mat4<Real>& target, double margin = 1e-3)
    {
        return Mat4Matcher<Real>(target, margin);
    }
}
