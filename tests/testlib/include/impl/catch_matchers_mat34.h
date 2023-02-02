#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Mat34<Real>>
    {
        static std::string convert(Mat34<Real> const& m)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(4)
                << "[["
                << "[" << m.rs.x.x << "," << m.rs.x.y << "," << m.rs.x.z << "],"
                << "[" << m.rs.y.x << "," << m.rs.y.y << "," << m.rs.y.z << "],"
                << "[" << m.rs.z.x << "," << m.rs.z.y << "," << m.rs.z.z << "]],"
                << "[" << m.t.x << "," << m.t.y << "," << m.t.z << "]"
                << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class Mat34Matcher final : public Catch::Matchers::MatcherBase<Mat34<Real>>
    {
    public:
        Mat34Matcher(const Mat34<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Mat34<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Mat34<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Mat34Matcher<Real> WithinAbs(const Mat34<Real>& target, double margin = 1e-3)
    {
        return Mat34Matcher<Real>(target, margin);
    }
}
