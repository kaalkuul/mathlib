#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("HermiteSplineSegment3", "")
    {
        // Constructors

        SECTION("HermiteSplineSegment3()")
        {
            HermiteSplineSegment3f segment;
        }

        SECTION("HermiteSplineSegment3(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4)")
        {
            Vec3f p1(0, 0, 0), p4(1, 1, 1), r1(0, 1, 0), r4(1, 0, 1);
            HermiteSplineSegment3f segment(p1, p4, r1, r4);
            REQUIRE(segment.p1() == p1);
            REQUIRE(segment.p4() == p4);
            REQUIRE(segment.r1() == r1);
            REQUIRE(segment.r4() == r4);
        }

        SECTION("set(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4)")
        {
            HermiteSplineSegment3f segment;
            Vec3f p1(0, 0, 0), p4(1, 1, 1), r1(0, 1, 0), r4(1, 0, 1);
            segment.set(p1, p4, r1, r4);
            REQUIRE(segment.p1() == p1);
            REQUIRE(segment.p4() == p4);
            REQUIRE(segment.r1() == r1);
            REQUIRE(segment.r4() == r4);
        }

        SECTION("pointAt(Real t)")
        {
            Vec3f p1(0, 0, 0), p4(1, 1, 1), r1(0, 1, 0), r4(1, 0, 1);
            HermiteSplineSegment3f segment(p1, p4, r1, r4);
            for (float t = 0.0f; t <= 1.0f; t += 0.1f)
            {
                float hp1 = HermiteSplineSegment3f::hp1(t);
                float hp4 = HermiteSplineSegment3f::hp4(t);
                float hr1 = HermiteSplineSegment3f::hr1(t);
                float hr4 = HermiteSplineSegment3f::hr4(t);

                Vec3f p = p1 * hp1 + p4 * hp4 + r1 * hr1 + r4 * hr4;
                REQUIRE(segment.pointAt(t) == p);
            }
        }

        SECTION("tangentAt(Real t)")
        {
            Vec3f p1(0, 0, 0), p4(1, 1, 1), r1(0, 1, 0), r4(1, 0, 1);
            HermiteSplineSegment3f segment(p1, p4, r1, r4);
            for (float t = 0.0f; t <= 1.0f; t += 0.1f)
            {
                float dhp1 = HermiteSplineSegment3f::dhp1(t);
                float dhp4 = HermiteSplineSegment3f::dhp4(t);
                float dhr1 = HermiteSplineSegment3f::dhr1(t);
                float dhr4 = HermiteSplineSegment3f::dhr4(t);

                Vec3f p = p1 * dhp1 + p4 * dhp4 + r1 * dhr1 + r4 * dhr4;
                REQUIRE(segment.tangentAt(t) == p);
            }
        }

        SECTION("hp1(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.1), Catch::Matchers::WithinAbs(0.9720f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.2), Catch::Matchers::WithinAbs(0.8960f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.3), Catch::Matchers::WithinAbs(0.7840f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.4), Catch::Matchers::WithinAbs(0.6480f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.5), Catch::Matchers::WithinAbs(0.5000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.6), Catch::Matchers::WithinAbs(0.3520f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.7), Catch::Matchers::WithinAbs(0.2160f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.8), Catch::Matchers::WithinAbs(0.1040f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(0.9), Catch::Matchers::WithinAbs(0.0280f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("hp4(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.1), Catch::Matchers::WithinAbs(0.0280f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.2), Catch::Matchers::WithinAbs(0.1040f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.3), Catch::Matchers::WithinAbs(0.2160f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.4), Catch::Matchers::WithinAbs(0.3520f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.5), Catch::Matchers::WithinAbs(0.5000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.6), Catch::Matchers::WithinAbs(0.6480f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.7), Catch::Matchers::WithinAbs(0.7840f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.8), Catch::Matchers::WithinAbs(0.8960f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(0.9), Catch::Matchers::WithinAbs(0.9720f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hp4(1.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
        }

        SECTION("hr1(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.1), Catch::Matchers::WithinAbs(0.0810f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.2), Catch::Matchers::WithinAbs(0.1280f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.3), Catch::Matchers::WithinAbs(0.1470f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.4), Catch::Matchers::WithinAbs(0.1440f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.5), Catch::Matchers::WithinAbs(0.1250f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.6), Catch::Matchers::WithinAbs(0.0960f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.7), Catch::Matchers::WithinAbs(0.0630f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.8), Catch::Matchers::WithinAbs(0.0320f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(0.9), Catch::Matchers::WithinAbs(0.0090f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("hr4(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.1), Catch::Matchers::WithinAbs(-0.0090f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.2), Catch::Matchers::WithinAbs(-0.0320f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.3), Catch::Matchers::WithinAbs(-0.0630f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.4), Catch::Matchers::WithinAbs(-0.0960f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.5), Catch::Matchers::WithinAbs(-0.1250f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.6), Catch::Matchers::WithinAbs(-0.1440f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.7), Catch::Matchers::WithinAbs(-0.1470f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.8), Catch::Matchers::WithinAbs(-0.1280f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(0.9), Catch::Matchers::WithinAbs(-0.0810f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::hr4(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhp1(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.1), Catch::Matchers::WithinAbs(-0.5400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.2), Catch::Matchers::WithinAbs(-0.9600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.3), Catch::Matchers::WithinAbs(-1.2600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.4), Catch::Matchers::WithinAbs(-1.4400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.5), Catch::Matchers::WithinAbs(-1.5000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.6), Catch::Matchers::WithinAbs(-1.4400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.7), Catch::Matchers::WithinAbs(-1.2600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.8), Catch::Matchers::WithinAbs(-0.9600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(0.9), Catch::Matchers::WithinAbs(-0.5400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhp4(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.1), Catch::Matchers::WithinAbs(0.5400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.2), Catch::Matchers::WithinAbs(0.9600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.3), Catch::Matchers::WithinAbs(1.2600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.4), Catch::Matchers::WithinAbs(1.4400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.5), Catch::Matchers::WithinAbs(1.5000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.6), Catch::Matchers::WithinAbs(1.4400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.7), Catch::Matchers::WithinAbs(1.2600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.8), Catch::Matchers::WithinAbs(0.9600f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(0.9), Catch::Matchers::WithinAbs(0.5400f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhp4(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhr1(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.1), Catch::Matchers::WithinAbs(0.6300f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.2), Catch::Matchers::WithinAbs(0.3200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.3), Catch::Matchers::WithinAbs(0.0700f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.4), Catch::Matchers::WithinAbs(-0.1200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.5), Catch::Matchers::WithinAbs(-0.2500f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.6), Catch::Matchers::WithinAbs(-0.3200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.7), Catch::Matchers::WithinAbs(-0.3300f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.8), Catch::Matchers::WithinAbs(-0.2800f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(0.9), Catch::Matchers::WithinAbs(-0.1700f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhr4(Real t)")
        {
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.1), Catch::Matchers::WithinAbs(-0.1700f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.2), Catch::Matchers::WithinAbs(-0.2800f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.3), Catch::Matchers::WithinAbs(-0.3300f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.4), Catch::Matchers::WithinAbs(-0.3200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.5), Catch::Matchers::WithinAbs(-0.2500f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.6), Catch::Matchers::WithinAbs(-0.1200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.7), Catch::Matchers::WithinAbs(0.0700f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.8), Catch::Matchers::WithinAbs(0.3200f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(0.9), Catch::Matchers::WithinAbs(0.6300f, 1e-6));
            REQUIRE_THAT(HermiteSplineSegment3f::dhr4(1.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
        }

    }



    TEST_CASE("BezierSegment3", "")
    {
        // Constructors

        SECTION("BezierSegment3()")
        {
            BezierSegment3f segment;
        }

        SECTION("BezierSegment3(const Vec3<Real>& p1, const Vec3<Real>& p2, const Vec3<Real>& p3, const Vec3<Real>& p4)")
        {
            Vec3f p1(0, 0, 0), p2(0, 1, 0), p3(1, 0, 1), p4(1, 1, 1);
            BezierSegment3f segment(p1, p2, p3, p4);
            REQUIRE(segment.p1() == p1);
            REQUIRE(segment.p2() == p2);
            REQUIRE(segment.p3() == p3);
            REQUIRE(segment.p4() == p4);
        }

        SECTION("set(const Vec3<Real>& p1, const Vec3<Real>& p4, const Vec3<Real>& r1, const Vec3<Real>& r4)")
        {
            BezierSegment3f segment;
            Vec3f p1(0, 0, 0), p2(0, 1, 0), p3(1, 0, 1), p4(1, 1, 1);
            segment.set(p1, p2, p3, p4);
            REQUIRE(segment.p1() == p1);
            REQUIRE(segment.p2() == p2);
            REQUIRE(segment.p3() == p3);
            REQUIRE(segment.p4() == p4);
        }

        SECTION("pointAt(Real t)")
        {
            Vec3f p1(0, 0, 0), p2(0, 1, 0), p3(1, 0, 1), p4(1, 1, 1);
            BezierSegment3f segment(p1, p2, p3, p4);
            for (float t = 0.0f; t <= 1.0f; t += 0.1f)
            {
                float hp1 = BezierSegment3f::hp1(t);
                float hp2 = BezierSegment3f::hp2(t);
                float hp3 = BezierSegment3f::hp3(t);
                float hp4 = BezierSegment3f::hp4(t);

                Vec3f p = p1 * hp1 + p2 * hp2 + p3 * hp3 + p4 * hp4;
                REQUIRE_THAT(segment.pointAt(t), Matches::WithinAbs(p, 1e-6));
            }
        }

        SECTION("tangentAt(Real t)")
        {
            Vec3f p1(0, 0, 0), p2(0, 1, 0), p3(1, 0, 1), p4(1, 1, 1);
            BezierSegment3f segment(p1, p2, p3, p4);
            for (float t = 0.0f; t <= 1.0f; t += 0.1f)
            {
                float dhp1 = BezierSegment3f::dhp1(t);
                float dhp2 = BezierSegment3f::dhp2(t);
                float dhp3 = BezierSegment3f::dhp3(t);
                float dhp4 = BezierSegment3f::dhp4(t);

                Vec3f p = p1 * dhp1 + p2 * dhp2 + p3 * dhp3 + p4 * dhp4;
                REQUIRE_THAT(segment.tangentAt(t), Matches::WithinAbs(p, 1e-6));
            }
        }

        SECTION("length(int steps)")
        {
            SECTION("Case 1")
            {
                Vec3f p1(0, 0.0f, 0.0f), p2(0.5f, 0.0f, 0.0f), p3(0.5f, 0.0f, 0.0f), p4(1.0f, 0.0f, 0.0f);
                BezierSegment3f segment(p1, p2, p3, p4);
                REQUIRE_THAT(segment.length(), Catch::Matchers::WithinAbs(1.0f, 1e-6));
            }

            SECTION("Case 2")
            {
                Vec3f p1(0, 0.0f, 0.0f), p2(1.0f, 0.0f, 0.0f), p3(9.0f, 0.0f, 0.0f), p4(10.0f, 0.0f, 0.0f);
                BezierSegment3f segment(p1, p2, p3, p4);
                REQUIRE_THAT(segment.length(), Catch::Matchers::WithinAbs(10.0f, 1e-6));
            }
        }

        SECTION("hp1(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::hp1(0.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.1), Catch::Matchers::WithinAbs(0.7290f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.2), Catch::Matchers::WithinAbs(0.5120f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.3), Catch::Matchers::WithinAbs(0.3430f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.4), Catch::Matchers::WithinAbs(0.2160f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.5), Catch::Matchers::WithinAbs(0.1250f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.6), Catch::Matchers::WithinAbs(0.0640f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.7), Catch::Matchers::WithinAbs(0.0270f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.8), Catch::Matchers::WithinAbs(0.0080f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(0.9), Catch::Matchers::WithinAbs(0.0010f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("hp2(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::hp2(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.1), Catch::Matchers::WithinAbs(0.2430f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.2), Catch::Matchers::WithinAbs(0.3840f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.3), Catch::Matchers::WithinAbs(0.4410f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.4), Catch::Matchers::WithinAbs(0.4320f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.5), Catch::Matchers::WithinAbs(0.3750f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.6), Catch::Matchers::WithinAbs(0.2880f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.7), Catch::Matchers::WithinAbs(0.1890f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.8), Catch::Matchers::WithinAbs(0.0960f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(0.9), Catch::Matchers::WithinAbs(0.0270f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp2(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("hp3(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::hp3(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.1), Catch::Matchers::WithinAbs(0.0270f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.2), Catch::Matchers::WithinAbs(0.0960f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.3), Catch::Matchers::WithinAbs(0.1890f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.4), Catch::Matchers::WithinAbs(0.2880f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.5), Catch::Matchers::WithinAbs(0.3750f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.6), Catch::Matchers::WithinAbs(0.4320f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.7), Catch::Matchers::WithinAbs(0.4410f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.8), Catch::Matchers::WithinAbs(0.3840f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(0.9), Catch::Matchers::WithinAbs(0.2430f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp3(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("hp4(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::hp4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.1), Catch::Matchers::WithinAbs(0.0010f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.2), Catch::Matchers::WithinAbs(0.0080f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.3), Catch::Matchers::WithinAbs(0.0270f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.4), Catch::Matchers::WithinAbs(0.0640f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.5), Catch::Matchers::WithinAbs(0.1250f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.6), Catch::Matchers::WithinAbs(0.2160f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.7), Catch::Matchers::WithinAbs(0.3430f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.8), Catch::Matchers::WithinAbs(0.5120f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(0.9), Catch::Matchers::WithinAbs(0.7290f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::hp4(1.0), Catch::Matchers::WithinAbs(1.0000f, 1e-6));
        }

        SECTION("dhp1(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::dhp1(0.0), Catch::Matchers::WithinAbs(-3.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.1), Catch::Matchers::WithinAbs(-2.4300f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.2), Catch::Matchers::WithinAbs(-1.9200f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.3), Catch::Matchers::WithinAbs(-1.4700f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.4), Catch::Matchers::WithinAbs(-1.0800f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.5), Catch::Matchers::WithinAbs(-0.7500f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.6), Catch::Matchers::WithinAbs(-0.4800f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.7), Catch::Matchers::WithinAbs(-0.2700f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.8), Catch::Matchers::WithinAbs(-0.1200f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(0.9), Catch::Matchers::WithinAbs(-0.0300f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp1(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhp2(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::dhp2(0.0), Catch::Matchers::WithinAbs(3.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.1), Catch::Matchers::WithinAbs(1.8900f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.2), Catch::Matchers::WithinAbs(0.9600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.3), Catch::Matchers::WithinAbs(0.2100f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.4), Catch::Matchers::WithinAbs(-0.3600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.5), Catch::Matchers::WithinAbs(-0.7500f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.6), Catch::Matchers::WithinAbs(-0.9600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.7), Catch::Matchers::WithinAbs(-0.9900f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.8), Catch::Matchers::WithinAbs(-0.8400f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(0.9), Catch::Matchers::WithinAbs(-0.5100f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp2(1.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
        }

        SECTION("dhp3(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::dhp3(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.1), Catch::Matchers::WithinAbs(0.5100f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.2), Catch::Matchers::WithinAbs(0.8400f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.3), Catch::Matchers::WithinAbs(0.9900f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.4), Catch::Matchers::WithinAbs(0.9600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.5), Catch::Matchers::WithinAbs(0.7500f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.6), Catch::Matchers::WithinAbs(0.3600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.7), Catch::Matchers::WithinAbs(-0.2100f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.8), Catch::Matchers::WithinAbs(-0.9600f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(0.9), Catch::Matchers::WithinAbs(-1.8900f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp3(1.0), Catch::Matchers::WithinAbs(-3.0000f, 1e-6));
        }

        SECTION("dhp4(Real t)")
        {
            REQUIRE_THAT(BezierSegment3f::dhp4(0.0), Catch::Matchers::WithinAbs(0.0000f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.1), Catch::Matchers::WithinAbs(0.0300f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.2), Catch::Matchers::WithinAbs(0.1200f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.3), Catch::Matchers::WithinAbs(0.2700f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.4), Catch::Matchers::WithinAbs(0.4800f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.5), Catch::Matchers::WithinAbs(0.7500f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.6), Catch::Matchers::WithinAbs(1.0800f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.7), Catch::Matchers::WithinAbs(1.4700f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.8), Catch::Matchers::WithinAbs(1.9200f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(0.9), Catch::Matchers::WithinAbs(2.4300f, 1e-6));
            REQUIRE_THAT(BezierSegment3f::dhp4(1.0), Catch::Matchers::WithinAbs(3.0000f, 1e-6));
        }
    }


    TEST_CASE("SplineSolver3", "")
    {
        SECTION("naturalBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3)")
        {
            SECTION("Case 1")
            {
                Vec3f p1[] = {
                    Vec3f::Zero,
                    Vec3f::OneX
                };
                Vec3f p2[1], p3[1];
                REQUIRE(SplineSolver3f::naturalBezierSpline(2, p1, p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(1.0f / 3.0f, 0, 0), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(2.0f / 3.0f, 0, 0), 1e-6));
            }

            SECTION("Case 2")
            {
                Vec3f p1[] = {
                    Vec3f::Zero,
                    Vec3f::OneX + Vec3f::OneY,
                    Vec3f::OneX * 2.0f
                };
                Vec3f p2[2], p3[2];
                REQUIRE(SplineSolver3f::naturalBezierSpline(3, p1, p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(1.0f / 3.0f, 0.5f, 0), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(2.0f / 3.0f, 1.0f, 0), 1e-6));
                REQUIRE_THAT(p2[1], Matches::WithinAbs(Vec3f(4.0f / 3.0f, 1.0f, 0), 1e-6));
                REQUIRE_THAT(p3[1], Matches::WithinAbs(Vec3f(5.0f / 3.0f, 0.5f, 0), 1e-6));
            }

            SECTION("Case 3")
            {
                Vec3f p1[] = {
                    Vec3f(0.0f, 0.0f, 0.0f),
                    Vec3f(1.0f, 1.0f, 0.0f),
                    Vec3f(2.0f, 0.0f, 0.0f),
                    Vec3f(3.0f, 1.0f, 0.0f),
                    Vec3f(4.0f, 0.0f, 0.0f)
                };
                Vec3f p2[4], p3[4];
                REQUIRE(SplineSolver3f::naturalBezierSpline(5, p1, p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(1.0f / 3.0f, 4.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[1], Matches::WithinAbs(Vec3f(4.0f / 3.0f, 6.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[2], Matches::WithinAbs(Vec3f(7.0f / 3.0f, 0.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[3], Matches::WithinAbs(Vec3f(10.0f / 3.0f, 8.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(2.0f / 3.0f, 8.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[1], Matches::WithinAbs(Vec3f(5.0f / 3.0f, 0.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[2], Matches::WithinAbs(Vec3f(8.0f / 3.0f, 6.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[3], Matches::WithinAbs(Vec3f(11.0f / 3.0f, 4.0f / 7.0f, 0.0f), 1e-6));
            }
        }

        SECTION("bezierSpline(int n, const Vec3<Real>* p1, const Vec3<Real>& p2start, const Vec3<Real>& p3end, Vec3<Real>* p2, Vec3<Real>* p3)")
        {
            SECTION("Case 1")
            {
                Vec3f p1[] = {
                    Vec3f::Zero,
                    Vec3f::OneX
                };
                Vec3f p2[1], p3[1];
                REQUIRE(SplineSolver3f::bezierSpline(2, p1, Vec3f::OneY, -Vec3f::OneY, p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f::OneY, 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(-Vec3f::OneY, 1e-6));
            }

            SECTION("Case 2")
            {
                Vec3f p1[] = {
                    Vec3f::Zero,
                    Vec3f::OneX + Vec3f::OneY,
                    Vec3f::OneX * 2.0f
                };
                Vec3f p2[2], p3[2];
                REQUIRE(SplineSolver3f::bezierSpline(3, p1, 
                    Vec3f(1.0f / 3.0f, 0.5f, 0), Vec3f(5.0f / 3.0f, 0.5f, 0), p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(1.0f / 3.0f, 0.5f, 0), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(2.0f / 3.0f, 1.0f, 0), 1e-6));
                REQUIRE_THAT(p2[1], Matches::WithinAbs(Vec3f(4.0f / 3.0f, 1.0f, 0), 1e-6));
                REQUIRE_THAT(p3[1], Matches::WithinAbs(Vec3f(5.0f / 3.0f, 0.5f, 0), 1e-6));
            }

            SECTION("Case 3")
            {
                Vec3f p1[] = {
                    Vec3f(0.0f, 0.0f, 0.0f),
                    Vec3f(1.0f, 1.0f, 0.0f),
                    Vec3f(2.0f, 0.0f, 0.0f),
                    Vec3f(3.0f, 1.0f, 0.0f),
                    Vec3f(4.0f, 0.0f, 0.0f)
                };
                Vec3f p2[4], p3[4];
                REQUIRE(SplineSolver3f::bezierSpline(5, p1,
                    Vec3f(1.0f / 3.0f, 4.0f / 7.0f, 0.0f),
                    Vec3f(11.0f / 3.0f, 4.0f / 7.0f, 0.0f),
                    p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(1.0f / 3.0f, 4.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[1], Matches::WithinAbs(Vec3f(4.0f / 3.0f, 6.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[2], Matches::WithinAbs(Vec3f(7.0f / 3.0f, 0.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[3], Matches::WithinAbs(Vec3f(10.0f / 3.0f, 8.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(2.0f / 3.0f, 8.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[1], Matches::WithinAbs(Vec3f(5.0f / 3.0f, 0.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[2], Matches::WithinAbs(Vec3f(8.0f / 3.0f, 6.0f / 7.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[3], Matches::WithinAbs(Vec3f(11.0f / 3.0f, 4.0f / 7.0f, 0.0f), 1e-6));
            }
        }

        SECTION("closedBezierSpline(int n, const Vec3<Real>* p1, Vec3<Real>* p2, Vec3<Real>* p3)")
        {
            SECTION("Case 1")
            {
                Vec3f p1[] = {
                    -Vec3f::OneX,
                    Vec3f::OneY,
                    Vec3f::OneX,
                    -Vec3f::OneY
                };
                Vec3f p2[4], p3[4];
                REQUIRE(SplineSolver3f::closedBezierSpline(4, p1, p2, p3));

                REQUIRE_THAT(p2[0], Matches::WithinAbs(Vec3f(-1.0f,  0.5f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[1], Matches::WithinAbs(Vec3f( 0.5f,  1.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[2], Matches::WithinAbs(Vec3f( 1.0f, -0.5f, 0.0f), 1e-6));
                REQUIRE_THAT(p2[3], Matches::WithinAbs(Vec3f(-0.5f, -1.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[0], Matches::WithinAbs(Vec3f(-0.5f,  1.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[1], Matches::WithinAbs(Vec3f( 1.0f,  0.5f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[2], Matches::WithinAbs(Vec3f( 0.5f, -1.0f, 0.0f), 1e-6));
                REQUIRE_THAT(p3[3], Matches::WithinAbs(Vec3f(-1.0f, -0.5f, 0.0f), 1e-6));
            }
        }
    }
}
