#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"
#include "doctest.h"

// Quello che segue è il test per quanto riguarda la classe Boids, implementata
// in boids.hpp; Essa include le tre regole Sep, All, Coe, e anche UState, che
// però verrà testato in un altro file.

TEST_CASE("Testing Sep") {
  SUBCASE("Test S e ds") { CHECK_THROWS(Sep{-4, 3}); }
  SUBCASE("Test") { CHECK_THROWS(Sep{3, -3}); }
  SUBCASE("Test2") { CHECK_THROWS(Sep{-4, 0}); }
  SUBCASE("Test3") { CHECK_THROWS(Sep{0, -3}); }
}
TEST_CASE("Testing ") {
  SUBCASE("Test funzionamento Sep") {
    Sep const sep{1.0, 3.0};
    UState u1;
    u1.P.x = 5.;
    u1.P.y = 5.;
    u1.V.vx = 10.;
    u1.V.vy = 10.;
    u1.UPN = 1;
    UState u2;
    u2.P.x = 5.;
    u2.P.y = 5.;
    u2.V.vx = 10.;
    u2.V.vy = 10.;
    u2.UPN = 2;

    std::vector<UState> uccelli{u1, u2};
    std::cout << "Primo uccello:" << uccelli[0];
    std::cout << "Secondo uccello:" << uccelli[1];

    // CHECK(sep(u1, u2) == doctest::Approx(8.485).epsilon(0.01));
  }
}

TEST_CASE("Testing All") {
  SUBCASE("Testing throws") { CHECK_THROWS(All{4.}); }
  SUBCASE("Testing throws") { CHECK_THROWS(All{-1.}); }
  SUBCASE("Testing funzionamento All") {
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
    Coppia coppia{u1, u2};
    std::vector<Coppia> vicini{coppia};
    All allineamento{0.5};
    auto velocities1 = allineamento(vicini, uccelli);
    CHECK(velocities1[0].vx == doctest::Approx(+5.0));
    CHECK(velocities1[1].vx == doctest::Approx(-5.0));
  }
}

// TEST_CASE("Testing Coe") {
//   SUBCASE("Testing ") {}
// }
// TEST_CASE("Testing Boids with 2 elements") {}
// TEST_CASE("Testing Boids with ... elements") {}
