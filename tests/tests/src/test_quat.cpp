#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Quat", "")
    {
        SECTION("Quatf::One")
        {
            REQUIRE(Quatf::One.x == 0.0f);
            REQUIRE(Quatf::One.y == 0.0f);
            REQUIRE(Quatf::One.z == 0.0f);
            REQUIRE(Quatf::One.w == 1.0f);
        }

        SECTION("setIdentity()")
        {
            Quatf q;
            q.setIdentity();
            REQUIRE(q == Quatf::One);
        }

        SECTION("set(const Quat &q)")
        {
            Quatf q;
            Quatf a = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            q.set(a);
            REQUIRE(q == a);
        }

        SECTION("set(const Mat3<Real> &m)")
        {
            Quatf q;
            Quatf a = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat3f m = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            q.set(m);
            REQUIRE_THAT(q, Matches::WithinAbs(a));
        }

        SECTION("set(const Vec3<Real> &axis, Real angle)")
        {
            Quatf q;
            q.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Quatf expect(0, 0, SPI6, CPI6);
            REQUIRE_THAT(q, Matches::WithinAbs(expect));
        }

        SECTION("set(const Vec3<Real> &from, const Vec3<Real> &to)")
        {
            Quatf q;
            q.set(Vec3f::OneX, Vec3f::OneY);
            Quatf expect = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_2);
            REQUIRE_THAT(q, Matches::WithinAbs(expect));
        }

        SECTION("lerp(const Quat &from, const Quat &to, Real weight)")
        {
            Quatf a = Quatf::One;
            Quatf b = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Quatf q0, qdot5, q1;
            q0.lerp(a, b, 0.0f);
            qdot5.lerp(a, b, 0.5f);
            q1.lerp(a, b, 1.0f);
            Quatf expect = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_6);
            REQUIRE_THAT(q0, Matches::WithinAbs(a));
            REQUIRE_THAT(qdot5, Matches::WithinAbs(expect));
            REQUIRE_THAT(q1, Matches::WithinAbs(b));
        }

        SECTION("slerp(const Quat &from, const Quat &to, Real weight)")
        {
            Quatf a = Quatf::One;
            Quatf b = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Quatf q0, qdot25, qdot5, qdot75, q1;
            q0.slerp(a, b, 0.0f);
            qdot25.slerp(a, b, 0.25f);
            qdot5.slerp(a, b, 0.5f);
            qdot75.slerp(a, b, 0.75f);
            q1.slerp(a, b, 1.0f);
            REQUIRE_THAT(q0, Matches::WithinAbs(a));
            REQUIRE_THAT(qdot25, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3 * 0.25f)));
            REQUIRE_THAT(qdot5, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3 * 0.5f)));
            REQUIRE_THAT(qdot75, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3 * 0.75f)));
            REQUIRE_THAT(q1, Matches::WithinAbs(b));
        }

        SECTION("slerpMaxAngle(const Quat &from, const Quat &to, Real maxAngle)")
        {
            Quatf a = Quatf::One;
            Quatf b = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Quatf q;
            q.slerpMaxAngle(a, b, 0.0f);
            REQUIRE_THAT(q, Matches::WithinAbs(a));
            q.slerpMaxAngle(a, b, Constantsf::PI_OVER_2);
            REQUIRE_THAT(q, Matches::WithinAbs(b));
            q.slerpMaxAngle(a, b, Constantsf::PI_OVER_6);
            REQUIRE_THAT(q, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_6)));
        }

        SECTION("slerpNoInvert(const Quat &from, const Quat &to, Real weight)")
        {
            Quatf a = Quatf::One;
            Quatf b = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_2 * 3);
            Quatf q0, qdot25, qdot5, qdot75, q1;
            q0.slerpNoInvert(a, b, 0.0f);
            qdot25.slerpNoInvert(a, b, 0.25f);
            qdot5.slerpNoInvert(a, b, 0.5f);
            qdot75.slerpNoInvert(a, b, 0.75f);
            q1.slerpNoInvert(a, b, 1.0f);
            REQUIRE_THAT(q0, Matches::WithinAbs(a));
            REQUIRE_THAT(qdot25, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_2 * 3 * 0.25f)));
            REQUIRE_THAT(qdot5, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_2 * 3 * 0.5f)));
            REQUIRE_THAT(qdot75, Matches::WithinAbs(Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_2 * 3 * 0.75f)));
            REQUIRE_THAT(q1, Matches::WithinAbs(b));
        }

        SECTION("cast()")
        {
            REQUIRE(Quatf::One.cast<double>() == Quatd::One);

            REQUIRE(Quatd::One.cast<float>() == Quatf::One);
        }
    }
}
