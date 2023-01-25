#pragma once

#include "../utils.h"

namespace Catch
{
    using namespace mathlib;

    template <class Real>
    struct StringMaker<Mat3<Real>>
    {
        static std::string convert(Mat3<Real> const& m)
        {
            std::ostringstream rss;
            rss << std::scientific
                << std::setprecision(4)
                << "["
                << "[" << m.x.x << "," << m.x.y << "," << m.x.z << "],"
                << "[" << m.y.x << "," << m.y.y << "," << m.y.z << "],"
                << "[" << m.z.x << "," << m.z.y << "," << m.z.z << "]"
                << "]";
            return rss.str();
        }
    };
}

namespace Matches
{
    using namespace mathlib;

    template <class Real>
    class Mat3Matcher final : public Catch::Matchers::MatcherBase<Mat3<Real>>
    {
    public:
        Mat3Matcher(const Mat3<Real>& target, double margin)
            : m_target(target), m_margin(margin)
        {
            CATCH_ENFORCE(margin >= 0, "Invalid margin: " << margin << '.'
                << " Margin has to be non-negative.");
        }

        bool match(Mat3<Real> const& matchee) const override
        {
            return marginCheck(matchee, m_target, m_margin);
        }

        std::string describe() const override
        {
            return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
        }

    private:
        Mat3<Real> m_target;
        double m_margin;
    };

    template <class Real>
    Mat3Matcher<Real> WithinAbs(const Mat3<Real>& target, double margin = 1e-3)
    {
        return Mat3Matcher<Real>(target, margin);
    }
}
