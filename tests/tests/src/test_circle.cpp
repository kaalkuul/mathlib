#include "utils.h"

using namespace mathlib;

TEST_CASE("Circle", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(Circlef::Real) == sizeof(float));
        REQUIRE(sizeof(Circled::Real) == sizeof(double));
    }

    // Constants

    SECTION("Circlef::One")
    {
        REQUIRE(Circlef::One.center == Vec2f::Zero);
        REQUIRE(Circlef::One.radius == 1.0f);
    }

    // Constructors

    SECTION("Circle(const Vec2<Real>& center, Real radius)")
    {
        Circlef sphere(Vec2f::Zero, 10.0f);
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 10.0f);
    }

    // Setters

    SECTION("set(const Vec2<Real>& center, Real radius)")
    {
        Circlef sphere;

        sphere.set(Vec2f::Zero, 2.0f);
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 2.0f);

        sphere.set(Vec2f::OneX, 3.0f);
        REQUIRE(sphere.center == Vec2f::OneX);
        REQUIRE(sphere.radius == 3.0f);
    }

    SECTION("set(int count, const Vec2<Real>* points)")
    {
        SECTION("Case 1")
        {
            Vec2f points[] = {
                Vec2f(10, 0),
                Vec2f(-10, 0),
                Vec2f(0, 10),
                Vec2f(0, -10),
                Vec2f(0, 0),
                Vec2f(0, 0),
                Vec2f(-1, -1),
                Vec2f(1, 1),
            };

            Circlef sphere;
            sphere.set(4, points);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec2f points[] = {
                Vec2f(-10, -10),
                Vec2f(-1, -1),
                Vec2f(1, 1),
                Vec2f(10, 10)
            };

            Circlef sphere;
            sphere.set(4, points);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(14.1421356, 1e-6));
        }
    }

    SECTION("set(int count, const Vec2<Real>* points, int stride)")
    {
        SECTION("Case 1")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(10, 0),
                Vec2f::OneX * 1000,
                Vec2f(-10, 0),
                Vec2f::OneX * 1000,
                Vec2f(0, 10),
                Vec2f::OneX * 1000,
                Vec2f(0, -10),
                Vec2f::OneX * 1000,
                Vec2f(0, 0),
                Vec2f::OneX * 1000,
                Vec2f(0, 0),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
            };

            Circlef sphere;
            sphere.set(4, &points[1], sizeof(Vec2f)*2);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(-10, -10),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
                Vec2f(10, 10),
                Vec2f::OneX * 1000,
            };

            Circlef sphere;
            sphere.set(4, &points[1], sizeof(Vec2f)*2);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(14.1421356, 1e-6));
        }
    }

    // Create from

    SECTION("from(const Vec2<Real>& center, Real radius)")
    {
        Circlef sphere;

        sphere = Circlef::from(Vec2f::Zero, 2.0f);
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 2.0f);

        sphere = Circlef::from(Vec2f::OneX, 3.0f);
        REQUIRE(sphere.center == Vec2f::OneX);
        REQUIRE(sphere.radius == 3.0f);
    }

    SECTION("from(int count, const Vec2<Real>* points)")
    {
        SECTION("Case 1")
        {
            Vec2f points[] = {
                Vec2f(10, 0),
                Vec2f(-10, 0),
                Vec2f(0, 10),
                Vec2f(0, -10),
                Vec2f(0, 0),
                Vec2f(0, 0),
                Vec2f(-1, -1),
                Vec2f(1, 1),
            };

            Circlef sphere = Circlef::from(4, points);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec2f points[] = {
                Vec2f(-10, -10),
                Vec2f(-1, -1),
                Vec2f(1, 1),
                Vec2f(10, 10)
            };

            Circlef sphere = Circlef::from(4, points);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(14.1421356, 1e-6));
        }
    }

    SECTION("from(int count, const Vec2<Real>* points, int stride)")
    {
        SECTION("Case 1")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(10, 0),
                Vec2f::OneX * 1000,
                Vec2f(-10, 0),
                Vec2f::OneX * 1000,
                Vec2f(0, 10),
                Vec2f::OneX * 1000,
                Vec2f(0, -10),
                Vec2f::OneX * 1000,
                Vec2f(0, 0),
                Vec2f::OneX * 1000,
                Vec2f(0, 0),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
            };

            Circlef sphere = Circlef::from(4, &points[1], sizeof(Vec2f) * 2);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE(sphere.radius == 10.0f);
        }

        SECTION("Case 2")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(-10, -10),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
                Vec2f(10, 10),
                Vec2f::OneX * 1000,
            };

            Circlef sphere = Circlef::from(4, &points[1], sizeof(Vec2f) * 2);
            REQUIRE(sphere.center == Vec2f::Zero);
            REQUIRE_THAT(sphere.radius, Catch::Matchers::WithinAbs(14.1421356, 1e-6));
        }
    }

    // Assignment operators

    SECTION("operator+= (const Vec2& t)")
    {
        Circlef sphere = Circlef::One;
        sphere += Vec2f::OneX;
        REQUIRE(sphere.center == Vec2f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator-= (const Vec2& t)")
    {
        Circlef sphere = Circlef::One;
        sphere -= Vec2f::OneX;
        REQUIRE(sphere.center == -Vec2f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator*= (Real k)")
    {
        Circlef sphere = Circlef::One;
        sphere *= 2.0f;
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 2.0f);
    }

    SECTION("operator/= (Real k)")
    {
        Circlef sphere = Circlef::One;
        sphere /= 2.0f;
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 0.5f);
    }


    // Arithmetic operators

    SECTION("operator+ (const Vec2& t)")
    {
        Circlef sphere = Circlef::One + Vec2f::OneX;
        REQUIRE(sphere.center == Vec2f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator- (const Vec2& t)")
    {
        Circlef sphere = Circlef::One - Vec2f::OneX;
        REQUIRE(sphere.center == -Vec2f::OneX);
        REQUIRE(sphere.radius == 1.0f);
    }

    SECTION("operator* (Real k)")
    {
        Circlef sphere = Circlef::One * 2.0f;
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 2.0f);
    }

    SECTION("operator/ (Real k)")
    {
        Circlef sphere = Circlef::One / 2.0f;
        REQUIRE(sphere.center == Vec2f::Zero);
        REQUIRE(sphere.radius == 0.5f);
    }


    // Comparison operators

    SECTION("operator== (const Circle &rhs)")
    {
        Circlef sphere = Circlef::from(Vec2f::Zero, 2.0f);
        REQUIRE(sphere == sphere);
        REQUIRE(sphere == Circlef::from(Vec2f::Zero, 2.0f));
    }

    SECTION("operator!= (const Circle &rhs)")
    {
        Circlef sphere = Circlef::from(Vec2f::Zero, 2.0f);
        REQUIRE(!(sphere != sphere));
        REQUIRE(!(sphere != Circlef::from(Vec2f::Zero, 2.0f)));
    }

    //  Functions

    SECTION("contains(const Vec2<Real>& p)")
    {
        Circlef sphere = Circlef::One;
        
        REQUIRE(sphere.contains(Vec2f::Zero));
        REQUIRE(sphere.contains(Vec2f::OneX));
        REQUIRE(sphere.contains(Vec2f::OneY));
        REQUIRE(!sphere.contains(Vec2f(1.01f, 0.0f)));
        REQUIRE(!sphere.contains(Vec2f(-1.01f, 0.0f)));
        REQUIRE(!sphere.contains(Vec2f(0.0f, 1.01f)));
        REQUIRE(!sphere.contains(Vec2f(0.0f, -1.01f)));
    }

    SECTION("contains(const Circle<Real>& sphere)")
    {
        Circlef sphere = Circlef::One;

        REQUIRE(sphere.contains(Circlef::One));
        REQUIRE(sphere.contains(Circlef::One * 0.5f));
        REQUIRE(sphere.contains(Circlef::One * 0.5f + Vec2f::OneX * 0.5f));
        REQUIRE(!sphere.contains(Circlef::One * 1.01f));
        REQUIRE(!sphere.contains(Circlef::One * 0.51f + Vec2f::OneX * 0.5f));
        REQUIRE(!sphere.contains(Circlef::One * 0.5f + Vec2f::OneX * 0.51f));
    }

    SECTION("hits(Vec2<Real>& hit, Real& t, const Line3<Real>& line)")
    {
        Circlef sphere = Circlef::One;

        Vec2f hit;
        float t;

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec2f(-2.0f, 0.0f), Vec2f(2.0f, 0.0f))));
        REQUIRE(hit == Vec2f(-1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec2f(2.0f, 0.0f), Vec2f(-2.0f, 0.0f))));
        REQUIRE(hit == Vec2f(1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec2f(0.0f, -2.0f), Vec2f(0.0f, 2.0f))));
        REQUIRE(hit == Vec2f(0.0f, -1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec2f(0.0f, 2.0f), Vec2f(0.0f, -2.0f))));
        REQUIRE(hit == Vec2f(0.0f, 1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.hits(hit, t, Line3f::from(Vec2f(-2.0f, 1.0f), Vec2f(2.0f, 1.0f))));
        REQUIRE(hit == Vec2f(0.0f, 1.0f));
        REQUIRE(t == 0.5f);

        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec2f(-2.0f, 1.01f), Vec2f( 2.0f, 1.01f))));
        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec2f( 2.0f, 1.01f), Vec2f(-2.0f, 1.01f))));

        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec2f(1.01f, -2.0f), Vec2f(1.01f,  2.0f))));
        REQUIRE(!sphere.hits(hit, t, Line3f::from(Vec2f(1.01f,  2.0f), Vec2f(1.01f, -2.0f))));
    }

    SECTION("intersects(const Circle<Real>& line)")
    {
        Circlef sphere = Circlef::One;

        REQUIRE(sphere.intersects(Circlef::One));

        REQUIRE(sphere.intersects(Circlef::One + Vec2f::OneX));

        REQUIRE(sphere.intersects(Circlef::One + Vec2f::OneX * 2.0f));

        REQUIRE(!sphere.intersects(Circlef::One + Vec2f::OneX * 2.01f));
    }

    SECTION("intersects(const Line3<Real>& line)")
    {
        Circlef sphere = Circlef::One;

        REQUIRE(sphere.intersects(Line3f::from(Vec2f(-2.0f, 0.0f), Vec2f(2.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec2f(2.0f, 0.0f), Vec2f(-2.0f, 0.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec2f(0.0f, -2.0f), Vec2f(0.0f, 2.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec2f(0.0f, 2.0f), Vec2f(0.0f, -2.0f))));

        REQUIRE(sphere.intersects(Line3f::from(Vec2f(-2.0f, 1.0f), Vec2f(2.0f, 1.0f))));

        REQUIRE(!sphere.intersects(Line3f::from(Vec2f(-2.0f, 1.01f), Vec2f( 2.0f, 1.01f))));
        REQUIRE(!sphere.intersects(Line3f::from(Vec2f( 2.0f, 1.01f), Vec2f(-2.0f, 1.01f))));

        REQUIRE(!sphere.intersects(Line3f::from(Vec2f(1.01f, -2.0f), Vec2f(1.01f,  2.0f))));
        REQUIRE(!sphere.intersects(Line3f::from(Vec2f(1.01f,  2.0f), Vec2f(1.01f, -2.0f))));
    }

    SECTION("intersects(Vec2<Real>& hit, Real& t, const Circle<Real>& line)")
    {
        Circlef sphere = Circlef::One;

        Vec2f hit;
        float t;

        REQUIRE(sphere.intersects(hit, t, Circlef::One));
        REQUIRE(hit == Vec2f::Zero);
        REQUIRE(t == 2.0f);

        REQUIRE(sphere.intersects(hit, t, Circlef::One + Vec2f::OneX));
        REQUIRE(hit == Vec2f::Zero);
        REQUIRE(t == 1.0f);

        REQUIRE(sphere.intersects(hit, t, Circlef::One + Vec2f::OneX * 2.0f));
        REQUIRE(hit == Vec2f::OneX);
        REQUIRE(t == 0.0f);

        REQUIRE(!sphere.intersects(hit, t, Circlef::One + Vec2f::OneX * 2.01f));
    }

    SECTION("intersects(Vec2<Real>& hit, Real& t, const Line3<Real>& line)")
    {
        Circlef sphere = Circlef::One;

        Vec2f hit;
        float t;

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec2f(-2.0f, 0.0f), Vec2f(2.0f, 0.0f))));
        REQUIRE(hit == Vec2f(-1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec2f(2.0f, 0.0f), Vec2f(-2.0f, 0.0f))));
        REQUIRE(hit == Vec2f(1.0f, 0.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec2f(0.0f, -2.0f), Vec2f(0.0f, 2.0f))));
        REQUIRE(hit == Vec2f(0.0f, -1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec2f(0.0f, 2.0f), Vec2f(0.0f, -2.0f))));
        REQUIRE(hit == Vec2f(0.0f, 1.0f));
        REQUIRE(t == 0.25f);

        REQUIRE(sphere.intersects(hit, t, Line3f::from(Vec2f(-2.0f, 1.0f), Vec2f(2.0f, 1.0f))));
        REQUIRE(hit == Vec2f(0.0f, 1.0f));
        REQUIRE(t == 0.5f);

        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec2f(-2.0f, 1.01f), Vec2f(2.0f, 1.01f))));
        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec2f(2.0f, 1.01f), Vec2f(-2.0f, 1.01f))));

        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec2f(1.01f, -2.0f), Vec2f(1.01f, 2.0f))));
        REQUIRE(!sphere.intersects(hit, t, Line3f::from(Vec2f(1.01f, 2.0f), Vec2f(1.01f, -2.0f))));
    }

    SECTION("data()")
    {
        Circlef s = Circlef::One;
        const float* cdata = s.data();
        float* data = s.data();

        REQUIRE(cdata == data);
        REQUIRE(cdata[0] == 0.0f);
        REQUIRE(cdata[1] == 0.0f);
        REQUIRE(cdata[2] == 1.0f);
    }

    SECTION("cast()")
    {
        REQUIRE(Circlef::One.cast<double>() == Circled::One);

        REQUIRE(Circled::One.cast<float>() == Circlef::One);
    }

    SECTION("Matches::WithinAbs")
    {
        REQUIRE_THAT(Circlef::One, Matches::WithinAbs(Circlef::One));
    }
}
