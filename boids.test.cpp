#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"
#include "doctest.h"

// Quello che segue è il test per quanto riguarda la classe Boids, implementata
// in boids.hpp; Essa include le tre regole Sep, All, Coe, e anche UState, che
// però verrà testato in un altro file.

TEST_CASE("Testing Sep") {
    SUBCASE("Test S e ds") { CHECK_THROWS(Sep{-4}); }
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

TEST_CASE("Testing Coe") {
  SUBCASE("Test2") { CHECK_THROWS(Coe{-1}); }
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

    CHECK(v_3[0].vx == doctest::Approx(5.0));
    CHECK(v_3[0].vy == doctest::Approx(5.0));
    CHECK(v_3[1].vx == doctest::Approx(-5.0));
    CHECK(v_3[1].vy == doctest::Approx(-5.0));
}
TEST_CASE("Testing open space environment") {
  unsigned int distanza = 50;
  UState u1;
  u1.P.x = 10.;
  u1.P.y = 0.;
  u1.V.vx = -10.;
  u1.V.vy = 0.;
  u1.UPN = 0;
  UState u2;
  u2.P.x = 1000.;
  u2.P.y = 1000.;
  u2.V.vx = 10.;
  u2.V.vy = 10.;
  u2.UPN = 1;
  std::vector<UState> uccelli{u1, u2};
  Sep sep{.5};
  All allineamento{0.5};
  Coe c{.5};
  Boids boids{uccelli, sep, allineamento, c, distanza};
  boids.evolve(2, 2000, 1000);
  auto uccelli_new = boids.state();
  CHECK(uccelli_new[0].P.x == doctest::Approx(1840));
  CHECK(u1.V.vx == -10.);
}

TEST_CASE("Testing Boids with invalid distance") {
  double delta_t{1.};
  unsigned int distanza = -1;
    Sep sep{.5};
    All all{0.5};
    Coe coe{.5};
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
    
    Boids boids{uccelli, sep, all, coe, distanza};
    SUBCASE("Test2") {CHECK_THROWS(Boids{uccelli, sep, all, coe, distanza});}
    boids.evolve(delta_t, 1000, 1000);
    
}
// TEST_CASE("Testing Boids with ... elements") {}
