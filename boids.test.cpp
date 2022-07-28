#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"
#include "doctest.h"

// Quello che segue è il test per quanto riguarda la classe Boids, implementata
// in boids.hpp; Essa include le tre regole Sep, All, Coe, e anche UState, che
// però verrà testato in un altro file.

TEST_CASE("Testing Sep") {
  SUBCASE("Test S e ds") {
    CHECK_THROWS(Sep(-4, 3));
    CHECK_THROWS(Sep(3, -3));
    CHECK_THROWS(Sep(-4, 0));
    CHECK_THROWS(Sep(0, -3));
  }
  // per quanto riguarda la validazione dell'input (S = £ o S = ciao) ->
  // mettere degli assert nel codice? negli hpp?
  Sep const sep{3.0, 3.0};
  SUBCASE("Test funzionamento Sep") {  // Cosa succede se metto ds non uguale a
                                       // 3? percjé è costante in
                                       // flightrules.hpp, invece in questo modo
                                       // potrebbe lamentarsi {

    UState u1{5, 5, 10, 10};
    UState u2{7, 7, 10, 10};
    CHECK(sep(u1, u2) == doctest::Approx(8.485).epsilon(0.01));
  }
}

/*Per quanto riguarda la parte sopra, bisogna implementare dentro flightrules i seguenti runtime errors, simili a quelli del prof: 
Hooke(double k, double l) : m_k(k), m_l(l) {
    if (m_k <= 0.) {
      throw std::runtime_error{"Hooke's parameter k must be > 0"};
    }
    if (m_l < 0.) {
      throw std::runtime_error{"Hooke's parameter l must be >= 0"};
    }
  }
*/

TEST_CASE("Testing All") {}
TEST_CASE("Testing Coe") {
  SUBCASE("Testing ")
}
TEST_CASE("Testing Boids with 2 elements") {}
TEST_CASE("Testing Boids with ... elements") {}

