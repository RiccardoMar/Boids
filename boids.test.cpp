#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"
#include "doctest.h"

// Quello che segue è il test per quanto riguarda la classe Boids, implementata
// in boids.hpp; Essa include le tre regole Sep, All, Coe, e anche UState, che
// però verrà testato in un altro file.

TEST_CASE("Testing boids.hpp") {
  SUBCASE("Testing Sep") {
    SUBCASE("Test S e ds") {
      std::cout
          << "Test su S (fattore di repulsione) e ds (distanza di attivazione)";
      CHECK_THROWS(Sep(-4, 3));
      CHECK_THROWS(Sep(3, -3));
      CHECK_THROWS(Sep(-4, 0));
      CHECK_THROWS(Sep(0, -3));
    }
    //per quanto riguarda la validazione dell'input (S = £ o S = ciao) -> mettere degli assert nel codice? negli hpp?
    SUBCASE("Test funzionamento Sep")
  }
  SUBCASE("Testing All") {}
  SUBCASE("Testing Coe") {}
  SUBCASE("Testing Boids with 2 elements") {}
  SUBCASE("Testing Boids with ... elements") {}
}
