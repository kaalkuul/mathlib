#include "utils.h"

using namespace mathlib;

TEST_CASE("Sphere", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(Spheref::Real) == sizeof(float));
        REQUIRE(sizeof(Sphered::Real) == sizeof(double));
    }

    // Constants

    SECTION("Spheref::One")
    {
        REQUIRE(Spheref::One.center == Vec3f::Zero);
        REQUIRE(Spheref::One.radius == 1.0f);
    }

    // Constructors

    SECTION("Sphere(const Vec3<Real>& center, Real radius)")
    {
        Spheref sphere(Vec3f::Zero, 10.0f);
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 10.0f);
    }

    // Setters

    SECTION("set(const Vec3<Real>& center, Real radius)")
    {
        Spheref sphere;

        sphere.set(Vec3f::Zero, 2.0f);
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 2.0f);

        sphere.set(Vec3f::OneX, 3.0f);
        REQUIRE(sphere.center == Vec3f::OneX);
        REQUIRE(sphere.radius == 3.0f);
    }

    SECTION("set(int count, const Vec3<Real>* points)")
    {
        SECTION("Case 1")
        {
            Vec3f points[] = {
                Vec3f(10, 0, 0),
                Vec3f(-10, 0, 0),
                Vec3f(0, 10, 0),
                Vec3f(0, -10, 0),
                Vec3f(0, 0, 10),
                Vec3f(0, 0, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
            };

            Spheref sphere;
            sphere.set(4, points);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            Spheref sphere;
            sphere.set(4, points);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(17.3205090, 1e-6));
        }
    }

    SECTION("set(int count, const Vec3<Real>* points, int stride)")
    {
        SECTION("Case 1")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(10, 0, 0),
                Vec3f::OneX * 1000,
                Vec3f(-10, 0, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, 10, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, -10, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, 0, 10),
                Vec3f::OneX * 1000,
                Vec3f(0, 0, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
            };

            Spheref sphere;
            sphere.set(4, &points[1], sizeof(Vec3f)*2);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(-10, -10, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
                Vec3f(10, 10, 10),
                Vec3f::OneX * 1000,
            };

            Spheref sphere;
            sphere.set(4, &points[1], sizeof(Vec3f)*2);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(17.3205090, 1e-6));
        }
    }

    // Create from

    SECTION("from(const Vec3<Real>& center, Real radius)")
    {
        Spheref sphere;

        sphere = Spheref::from(Vec3f::Zero, 2.0f);
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 2.0f);

        sphere = Spheref::from(Vec3f::OneX, 3.0f);
        REQUIRE(sphere.center == Vec3f::OneX);
        REQUIRE(sphere.radius == 3.0f);
    }

    SECTION("from(int count, const Vec3<Real>* points)")
    {
        SECTION("Case 1")
        {
            Vec3f points[] = {
                Vec3f(10, 0, 0),
                Vec3f(-10, 0, 0),
                Vec3f(0, 10, 0),
                Vec3f(0, -10, 0),
                Vec3f(0, 0, 10),
                Vec3f(0, 0, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
            };

            Spheref sphere = Spheref::from(4, points);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            Spheref sphere = Spheref::from(4, points);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(17.3205090, 1e-6));
        }
    }

    SECTION("from(int count, const Vec3<Real>* points, int stride)")
    {
        SECTION("Case 1")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(10, 0, 0),
                Vec3f::OneX * 1000,
                Vec3f(-10, 0, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, 10, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, -10, 0),
                Vec3f::OneX * 1000,
                Vec3f(0, 0, 10),
                Vec3f::OneX * 1000,
                Vec3f(0, 0, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
            };

            Spheref sphere = Spheref::from(4, &points[1], sizeof(Vec3f) * 2);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(-10, -10, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
                Vec3f(10, 10, 10),
                Vec3f::OneX * 1000,
            };

            Spheref sphere = Spheref::from(4, &points[1], sizeof(Vec3f) * 2);
            REQUIRE(sphere.center == Vec3f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(17.3205090, 1e-6));
        }
    }

    // Assignment operators

    SECTION("operator+= (const Vec3& t)")
    {
        Spheref sphere = Spheref::One;
        sphere += Vec3f::OneX;
        REQUIRE(sphere.center == Vec3f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator-= (const Vec3& t)")
    {
        Spheref sphere = Spheref::One;
        sphere -= Vec3f::OneX;
        REQUIRE(sphere.center == -Vec3f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator*= (Real k)")
    {
        Spheref sphere = Spheref::One;
        sphere *= 2.0f;
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 2.0f);
    }

    SECTION("operator/= (Real k)")
    {
        Spheref sphere = Spheref::One;
        sphere /= 2.0f;
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 0.5f);
    }


    // Arithmetic operators

    SECTION("operator+ (const Vec3& t)")
    {
        Spheref sphere = Spheref::One + Vec3f::OneX;
        REQUIRE(sphere.center == Vec3f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator- (const Vec3& t)")
    {
        Spheref sphere = Spheref::One - Vec3f::OneX;
        REQUIRE(sphere.center == -Vec3f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator* (Real k)")
    {
        Spheref sphere = Spheref::One * 2.0f;
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 2.0f);
    }

    SECTION("operator/ (Real k)")
    {
        Spheref sphere = Spheref::One / 2.0f;
        REQUIRE(sphere.center == Vec3f::Zero);
        REQUIRE(sphere.radius == 0.5f);
    }


    // Comparison operators

    SECTION("operator== (const Sphere &rhs)")
    {
        Spheref sphere = Spheref::from(Vec3f::Zero, 2.0f);
        REQUIRE(sphere == sphere);
        REQUIRE(sphere == Spheref::from(Vec3f::Zero, 2.0f));
    }

    SECTION("operator!= (const Sphere &rhs)")
    {
        Spheref sphere = Spheref::from(Vec3f::Zero, 2.0f);
        REQUIRE(!(sphere != sphere));
        REQUIRE(!(sphere != Spheref::from(Vec3f::Zero, 2.0f)));
    }

    //  Functions

    SECTION("contains(const Vec3<Real>& p)")
    {
        Spheref sphere = Spheref::One;
        
        REQUIRE(sphere.contains(Vec3f::Zero));
        REQUIRE(sphere.contains(Vec3f::OneX));
        REQUIRE(sphere.contains(Vec3f::OneY));
        REQUIRE(sphere.contains(Vec3f::OneZ));
        REQUIRE(!sphere.contains(Vec3f(1.01f, 0.0f, 0.0f)));
        REQUIRE(!sphere.contains(Vec3f(-1.01f, 0.0f, 0.0f)));
        REQUIRE(!sphere.contains(Vec3f(0.0f, 1.01f, 0.0f)));
        REQUIRE(!sphere.contains(Vec3f(0.0f, -1.01f, 0.0f)));
        REQUIRE(!sphere.contains(Vec3f(0.0f, 0.0f, 1.01f)));
        REQUIRE(!sphere.contains(Vec3f(0.0f, 0.0f, -1.01f)));
    }

    SECTION("contains(const Sphere<Real>& sphere)")
    {
        Spheref sphere = Spheref::One;

        REQUIRE(sphere.contains(Spheref::One));
        REQUIRE(sphere.contains(Spheref::One * 0.5f));
        REQUIRE(sphere.contains(Spheref::One * 0.5f + Vec3f::OneX * 0.5f));
        REQUIRE(!sphere.contains(Spheref::One * 1.01f));
        REQUIRE(!sphere.contains(Spheref::One * 0.51f + Vec3f::OneX * 0.5f));
        REQUIRE(!sphere.contains(Spheref::One * 0.5f + Vec3f::OneX * 0.51f));
    }

    SECTION("hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line)")
    {
        Spheref sphere = Spheref::One;

        Vec3f hit;
        float t;

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f))));
        REQUIRE(hit == Vec3f(-1.0f, 0.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(2.0f, 0.0f, 0.0f), Vec3f(-2.0f, 0.0f, 0.0f))));
        REQUIRE(hit == Vec3f(1.0f, 0.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, -2.0f, 0.0f), Vec3f(0.0f, 2.0f, 0.0f))));
        REQUIRE(hit == Vec3f(0.0f, -1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 2.0f, 0.0f), Vec3f(0.0f, -2.0f, 0.0f))));
        REQUIRE(hit == Vec3f(0.0f, 1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, -1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, 1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 1.0f), Vec3f(2.0f, 0.0f, 1.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, 1.0f));
        REQUIRE(t == 0.5f);

        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 1.01f), Vec3f(2.0f, 0.0f, 1.01f))));
        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(2.0f, 0.0f, 1.01f), Vec3f(-2.0f, 0.0f, 1.01f))));

        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, -2.0f, 1.01f), Vec3f(0.0f, 2.0f, 1.01f))));
        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 2.0f, 1.01f), Vec3f(0.0f, -2.0f, 1.01f))));

        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 1.01f, -2.0f), Vec3f(0.0f, 1.01f, 2.0f))));
        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec3f(0.0f, 1.01f, 2.0f), Vec3f(0.0f, 1.01f, -2.0f))));
    }

    SECTION("intersects(const Sphere<Real>& line)")
    {
        Spheref sphere = Spheref::One;

        REQUIRE(sphere.intersects(Spheref::One));

        REQUIRE(sphere.intersects(Spheref::One + Vec3f::OneX));

        REQUIRE(sphere.intersects(Spheref::One + Vec3f::OneX * 2.0f));

        REQUIRE(!sphere.intersects(Spheref::One + Vec3f::OneX * 2.01f));
    }

    SECTION("intersects(const Line3<Real>& line)")
    {
        Spheref sphere = Spheref::One;

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(-2.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(2.0f, 0.0f, 0.0f), Vec3f(-2.0f, 0.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(0.0f, -2.0f, 0.0f), Vec3f(0.0f, 2.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(0.0f, 2.0f, 0.0f), Vec3f(0.0f, -2.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec3f(-2.0f, 0.0f, 1.0f), Vec3f(2.0f, 0.0f, 1.0f))));

        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(-2.0f, 0.0f, 1.01f), Vec3f(2.0f, 0.0f, 1.01f))));
        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(2.0f, 0.0f, 1.01f), Vec3f(-2.0f, 0.0f, 1.01f))));

        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(0.0f, -2.0f, 1.01f), Vec3f(0.0f, 2.0f, 1.01f))));
        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(0.0f, 2.0f, 1.01f), Vec3f(0.0f, -2.0f, 1.01f))));

        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(0.0f, 1.01f, -2.0f), Vec3f(0.0f, 1.01f, 2.0f))));
        REQUIRE(!sphere.intersects(Line3f::from(Vec3f(0.0f, 1.01f, 2.0f), Vec3f(0.0f, 1.01f, -2.0f))));
    }

    SECTION("intersects(Vec3<Real>& hit, Real& t, const Sphere<Real>& line)")
    {
        Spheref sphere = Spheref::One;

        Vec3f hit;
        float t;

        REQUIRE(sphere.intersects(hit, t, Spheref::One));
        REQUIRE(hit == Vec3f::Zero);
        REQUIRE(t == 2.0f);

        REQUIRE(sphere.intersects(hit, t, Spheref::One + Vec3f::OneX));
        REQUIRE(hit == Vec3f::Zero);
        REQUIRE(t == 1.0f);

        REQUIRE(sphere.intersects(hit, t, Spheref::One + Vec3f::OneX * 2.0f));
        REQUIRE(hit == Vec3f::OneX);
        REQUIRE(t == 0.0f);

        REQUIRE(!sphere.intersects(hit, t, Spheref::One + Vec3f::OneX * 2.01f));
    }

    SECTION("intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line)")
    {
        Spheref sphere = Spheref::One;

        Vec3f hit;
        float t;

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f))));
        REQUIRE(hit == Vec3f(-1.0f, 0.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(2.0f, 0.0f, 0.0f), Vec3f(-2.0f, 0.0f, 0.0f))));
        REQUIRE(hit == Vec3f(1.0f, 0.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, -2.0f, 0.0f), Vec3f(0.0f, 2.0f, 0.0f))));
        REQUIRE(hit == Vec3f(0.0f, -1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 2.0f, 0.0f), Vec3f(0.0f, -2.0f, 0.0f))));
        REQUIRE(hit == Vec3f(0.0f, 1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, -2.0f), Vec3f(0.0f, 0.0f, 2.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, -1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 0.0f, 2.0f), Vec3f(0.0f, 0.0f, -2.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, 1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 1.0f), Vec3f(2.0f, 0.0f, 1.0f))));
        REQUIRE(hit == Vec3f(0.0f, 0.0f, 1.0f));
        REQUIRE(t == 0.5f);

        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(-2.0f, 0.0f, 1.01f), Vec3f(2.0f, 0.0f, 1.01f))));
        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(2.0f, 0.0f, 1.01f), Vec3f(-2.0f, 0.0f, 1.01f))));

        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, -2.0f, 1.01f), Vec3f(0.0f, 2.0f, 1.01f))));
        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 2.0f, 1.01f), Vec3f(0.0f, -2.0f, 1.01f))));

        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 1.01f, -2.0f), Vec3f(0.0f, 1.01f, 2.0f))));
        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec3f(0.0f, 1.01f, 2.0f), Vec3f(0.0f, 1.01f, -2.0f))));
    }

    SECTION("data()")
    {
        Spheref s = Spheref::One;
        const float* cdata = s.data();
        float* data = s.data();

        REQUIRE(cdata == data);
        REQUIRE(cdata[0] == 0.0f);
        REQUIRE(cdata[1] == 0.0f);
        REQUIRE(cdata[2] == 0.0f);
        REQUIRE(cdata[3] == 1.0f);
    }

    SECTION("cast()")
    {
        REQUIRE(Spheref::One.cast<double>() == Sphered::One);

        REQUIRE(Sphered::One.cast<float>() == Spheref::One);
    }
    
    SECTION("Matches::WithinAbs")
    {
        Spheref value = Spheref::One;
        REQUIRE_THAT(value, Matches::WithinAbs(value));
    }
}
