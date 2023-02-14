#pragma once

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Mat2<Real>>
    {
        static std::string convert(Mat2<Real> const& m)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(4)
                << "["
                << "[" << m.x.x << "," << m.x.y << "],"
                << "[" << m.y.x << "," << m.y.y << "]"
                << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class Mat2Matcher final : public Catch::Matchers::MatcherBase<Mat2<Real>>
    {
    public:
        Mat2Matcher(const Mat2<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Mat2<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Mat2<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Mat2Matcher<Real> WithinAbs(const Mat2<Real>& target, double margin = 1e-3)
    {
        return Mat2Matcher<Real>(target, margin);
    }
}
