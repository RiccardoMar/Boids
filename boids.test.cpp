#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"
#include "doctest.h"

// Quello che segue è il test per quanto riguarda la classe Boids, implementata
// in boids.hpp; Essa include le tre regole Sep, All, Coe, e anche UState, che
// però verrà testato in un altro file.

TEST_CASE("Testing Sep") {
  SUBCASE("Test S e ds") { CHECK_THROWS(Sep{-4}); }
  SUBCASE("Test") { CHECK_THROWS(All{3}); }
  SUBCASE("Test2") { CHECK_THROWS(Coe{-1}); }
  //SUBCASE("Test3") { CHECK_THROWS( ); }
}
TEST_CASE("Testing ") {
  SUBCASE("Test funzionamento Sep") {
    unsigned int distanza = 50;
    Sep sep{.5};
    UState u1;
    u1.P.x = 0.;
    u1.P.y = 0.;
    u1.V.vx = 0.;
    u1.V.vy = 0.;
    u1.UPN = 0;
    UState u2;
    u2.P.x = 10.;
    u2.P.y = 10.;
    u2.V.vx = 10.;
    u2.V.vy = 10.;
    u2.UPN = 1;
    std::vector<UState> uccelli{u1, u2};
    auto Vicini = Check(uccelli, distanza);
    auto v_1 = sep(Vicini, uccelli);

    CHECK(v_1[0].vx == doctest::Approx(-5.0));
    CHECK(v_1[0].vy == doctest::Approx(-5.0));
    CHECK(v_1[1].vx == doctest::Approx(5.0));
    CHECK(v_1[1].vy == doctest::Approx(5.0));

  }
}

// TEST_CASE("Testing All") {}
TEST_CASE("Testing Coe") {
  unsigned int distanza = 50;
    Coe c{.5};
    UState u1;
    u1.P.x = 0.;
    u1.P.y = 0.;
    u1.V.vx = 0.;
    u1.V.vy = 0.;
    u1.UPN = 0;
    UState u2;
    u2.P.x = 10.;
    u2.P.y = 10.;
    u2.V.vx = 10.;
    u2.V.vy = 10.;
    u2.UPN = 1;
    std::vector<UState> uccelli{u1, u2};
    auto Vicini = Check(uccelli, distanza);
    auto v_3 = c(Vicini, uccelli);

    CHECK(v_3[0].vx == doctest::Approx(-5.0));
    CHECK(v_3[0].vy == doctest::Approx(-5.0));
    CHECK(v_3[1].vx == doctest::Approx(5.0));
    CHECK(v_3[1].vy == doctest::Approx(5.0));
}
//   SUBCASE("Testing ") {}
// }
// TEST_CASE("Testing Boids with 2 elements") {}
// TEST_CASE("Testing Boids with ... elements") {}
