#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Plane", "")
    {
        // Constants

        SECTION("Planef::XY")
        {
            REQUIRE(Planef::XY.normal == Vec3f::OneZ);
            REQUIRE(Planef::XY.d == 0.0f);
        }

        SECTION("Planef::YZ")
        {
            REQUIRE(Planef::YZ.normal == Vec3f::OneX);
            REQUIRE(Planef::YZ.d == 0.0f);
        }

        SECTION("Planef::ZX")
        {
            REQUIRE(Planef::ZX.normal == Vec3f::OneY);
            REQUIRE(Planef::ZX.d == 0.0f);
        }

        // Constructors

        SECTION("Plane()")
        {
            Planef plane;
        }

        SECTION("Plane(const Vec3<Real>& normal, Real distance)")
        {
            Planef plane(Vec3f::OneZ, 10.0f);
            REQUIRE(plane.normal == Vec3f::OneZ);
            REQUIRE(plane.d == 10.0f);
        }

        // Create from

        SECTION("from(const Vec3<Real>& point, const Vec3<Real>& normal)")
        {
            Planef plane;

            plane = Planef::from(Vec3f::Zero, Vec3f::OneZ);
            REQUIRE(plane == Planef::XY);

            plane = Planef::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE(plane == Planef::ZX);

            plane = Planef::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(plane == Planef::YZ);

            plane = Planef::from(Vec3f(2.0f, 0.0f, 0.0f), Vec3f::OneX);
            REQUIRE(plane.normal == Vec3f::OneX);
            REQUIRE(plane.d == -2.0f);

            plane = Planef::from(Vec3f(0.0f, 2.0f, 0.0f), Vec3f::OneY);
            REQUIRE(plane.normal == Vec3f::OneY);
            REQUIRE(plane.d == -2.0f);

            plane = Planef::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneZ);
            REQUIRE(plane.normal == Vec3f::OneZ);
            REQUIRE(plane.d == -2.0f);
        }

        SECTION("fromPointAndTangents(const Vec3<Real>& point, const Vec3<Real>& u, const Vec3<Real>& v)")
        {
            Planef plane;

            plane = Planef::fromPointAndTangents(Vec3f::Zero, Vec3f::OneX, Vec3f::OneY);
            REQUIRE(plane == Planef::XY);

            plane = Planef::fromPointAndTangents(Vec3f::Zero, Vec3f::OneZ, Vec3f::OneX);
            REQUIRE(plane == Planef::ZX);

            plane = Planef::fromPointAndTangents(Vec3f::Zero, Vec3f::OneY, Vec3f::OneZ);
            REQUIRE(plane == Planef::YZ);

            plane = Planef::fromPointAndTangents(Vec3f(2.0f, 0.0f, 0.0f), Vec3f::OneY, Vec3f::OneZ);
            REQUIRE(plane.normal == Vec3f::OneX);
            REQUIRE(plane.d == -2.0f);

            plane = Planef::fromPointAndTangents(Vec3f(0.0f, 2.0f, 0.0f), Vec3f::OneZ, Vec3f::OneX);
            REQUIRE(plane.normal == Vec3f::OneY);
            REQUIRE(plane.d == -2.0f);

            plane = Planef::fromPointAndTangents(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneX, Vec3f::OneY);
            REQUIRE(plane.normal == Vec3f::OneZ);
            REQUIRE(plane.d == -2.0f);
        }

        // Comparison operators

        SECTION("operator== (const plane &rhs)")
        {
            Planef plane(Vec3f::OneZ, 2.0f);
            REQUIRE(plane == plane);
            REQUIRE(plane == Planef(Vec3f::OneZ, 2.0f));
        }

        SECTION("operator!= (const Plane &rhs)")
        {
            Planef plane(Vec3f::OneZ, 2.0f);
            REQUIRE(!(plane != plane));
            REQUIRE(!(plane != Planef(Vec3f::OneZ, 2.0f)));
        }

        //  Functions

        SECTION("contains(const Vec3<Real>& point, Real tolerance)")
        {
            Planef plane = Planef::XY;
            
            REQUIRE(plane.contains(Vec3f::Zero, 1e-10));
            REQUIRE(plane.contains(Vec3f::OneX, 1e-10));
            REQUIRE(plane.contains(Vec3f::OneY, 1e-10));
            REQUIRE(plane.contains(Vec3f(0.0f, 0.0f, 1.0f), 1.0f));
            REQUIRE(plane.contains(Vec3f(0.0f, 0.0f, -1.0f), 1.0f));
            REQUIRE(!plane.contains(Vec3f(0.0f, 0.0f, 1.01f), 1.0f));
            REQUIRE(!plane.contains(Vec3f(0.0f, 0.0f, -1.01f), 1.0f));
        }

        SECTION("distance(const Vec3<Real>& point)")
        {
            Planef plane = Planef::XY;

            REQUIRE(plane.distance(Vec3f::Zero) == 0.0f);
            REQUIRE(plane.distance(Vec3f::OneX) == 0.0f);
            REQUIRE(plane.distance(Vec3f::OneY) == 0.0f);
            REQUIRE(plane.distance(Vec3f(0.0f, 0.0f, 1.0f)) == 1.0f);
            REQUIRE(plane.distance(Vec3f(0.0f, 0.0f, -1.0f)) == -1.0f);
        }

        SECTION("hits(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray)")
        {
            Planef plane = Planef::XY;

            Vec3f hit;
            float t;

            REQUIRE(plane.hits(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, 2.0f), -Vec3f::OneZ)));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 2.0f);

            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f::OneZ)));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneZ)));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneX)));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneY)));
        }

        SECTION("hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line)")
        {
            Planef plane = Planef::XY;

            Vec3f hit;
            float t;

            REQUIRE(plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f))));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 0.5f);

            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f))));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(1.0f, 0.0f, -2.0f))));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 1.0f, 2.0f))));
        }

        SECTION("hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line, Real radius)")
        {
            Planef plane = Planef::XY;

            Vec3f hit;
            float t;

            REQUIRE(plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f)), 1.0f));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 1.0f));
            REQUIRE(t == 0.25f);

            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f)), 1.0f));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(1.0f, 0.0f, -2.0f)), 1.0f));
            REQUIRE(!plane.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 1.0f, 2.0f)), 1.0f));
        }

        SECTION("hits(Real& depth, const Sphere<Real>& pos)")
        {
            Planef plane = Planef::XY;

            float depth;

            REQUIRE(plane.hits(depth, Spheref::from(Vec3f(0.0f, 0.0f, 1.0f), 1.0f)));
            REQUIRE(depth == 0.0f);

            REQUIRE(plane.hits(depth, Spheref::from(Vec3f(0.0f, 0.0f, 0.5f), 1.0f)));
            REQUIRE(depth == 0.5f);

            REQUIRE(plane.hits(depth, Spheref::from(Vec3f(0.0f, 0.0f, 0.0f), 1.0f)));
            REQUIRE(depth == 1.0f);

            REQUIRE(!plane.hits(depth, Spheref::from(Vec3f(0.0f, 0.0f, -0.1f), 1.0f)));
        }

        SECTION("intersects(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray)")
        {
            Planef plane = Planef::XY;

            Vec3f hit;
            float t;

            REQUIRE(plane.intersects(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, 2.0f), -Vec3f::OneZ)));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 2.0f);

            REQUIRE(plane.intersects(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f::OneZ)));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 2.0f);

            REQUIRE(!plane.intersects(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f::OneZ)));
            REQUIRE(!plane.intersects(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f::OneX)));
            REQUIRE(!plane.intersects(hit, t, Ray3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f::OneY)));
        }

        SECTION("intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line)")
        {
            Planef plane = Planef::XY;

            Vec3f hit;
            float t;

            REQUIRE(plane.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f))));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 0.5f);

            REQUIRE(plane.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f))));
            REQUIRE(hit == Vec3f(0.0f, 0.0f, 0.0f));
            REQUIRE(t == 0.5f);

            REQUIRE(!plane.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(1.0f, 0.0f, -2.0f))));
            REQUIRE(!plane.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 1.0f, 2.0f))));
        }

        SECTION("intersects(Real& depth, const Sphere<Real>& pos)")
        {
            Planef plane = Planef::XY;

            float depth;

            REQUIRE(plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, 1.0f), 1.0f)));
            REQUIRE(depth == 0.0f);

            REQUIRE(plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, 0.5f), 1.0f)));
            REQUIRE(depth == 0.5f);

            REQUIRE(plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, 0.0f), 1.0f)));
            REQUIRE(depth == 1.0f);

            REQUIRE(plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, -0.5f), 1.0f)));
            REQUIRE(depth == 1.5f);

            REQUIRE(plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, -1.0f), 1.0f)));
            REQUIRE(depth == 2.0f);

            REQUIRE(!plane.intersects(depth, Spheref::from(Vec3f(0.0f, 0.0f, -1.1f), 1.0f)));
        }

        SECTION("data()")
        {
            Planef p = Planef::XY;
            const float* cdata = p.data();
            float* data = p.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[0] == 0.0f);
            REQUIRE(cdata[1] == 0.0f);
            REQUIRE(cdata[2] == 1.0f);
            REQUIRE(cdata[3] == 0.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(Planef::XY.cast<double>() == Planed::XY);
            REQUIRE(Planef::YZ.cast<double>() == Planed::YZ);
            REQUIRE(Planef::ZX.cast<double>() == Planed::ZX);

            REQUIRE(Planed::XY.cast<float>() == Planef::XY);
            REQUIRE(Planed::YZ.cast<float>() == Planef::YZ);
            REQUIRE(Planed::ZX.cast<float>() == Planef::ZX);
        }

        SECTION("intersectAtSinglePoint(Vec3<Real>& intersectionPoint, const Plane& p0, const Plane& p1, const Plane& p2)")
        {
            Vec3f point;

            SECTION("No intersection 1")
            {
                REQUIRE(!Planef::intersectAtSinglePoint(point, Planef::XY, Planef::XY, Planef::XY));
            }

            SECTION("No intersection 2")
            {
                REQUIRE(!Planef::intersectAtSinglePoint(point, Planef::YZ, Planef::XY, Planef::XY));
            }

            SECTION("No intersection 2")
            {
                REQUIRE(!Planef::intersectAtSinglePoint(point, Planef::XY, Planef::YZ, Planef::XY));
            }

            SECTION("No intersection 2")
            {
                REQUIRE(!Planef::intersectAtSinglePoint(point, Planef::XY, Planef::XY, Planef::YZ));
            }

            SECTION("Planes intersect at origin")
            {
                REQUIRE(Planef::intersectAtSinglePoint(point, Planef::XY, Planef::YZ, Planef::ZX));
                REQUIRE(point == Vec3f::Zero);
            }

            SECTION("Planes intersect 1")
            {
                REQUIRE(Planef::intersectAtSinglePoint(point,
                    Planef::from(Planef::YZ, 1.0f),
                    Planef::from(Planef::ZX, 2.0f),
                    Planef::from(Planef::XY, 3.0f)));
                REQUIRE(point == Vec3f(1.0f, 2.0f, 3.0f));
            }
        }
    }
}
