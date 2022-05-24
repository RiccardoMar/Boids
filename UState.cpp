#include "UState.hpp"

#include <iostream>
#include <cmath>

bool UState::operator==(UState const& other) const {}

double UState::dist(UState const& other) const {
  double d = sqrt((P.x-other.P.x)*(P.x-other.P.x)+(P.y-other.P.y)*(P.y-other.P.y));
  return d;
}

double dist(UState const& u1, UState const& u2) {
  return u1.dist(u2);
}

std::ostream& operator<<(std::ostream& os, UState const& u) {
  os << "Posizione: (" <<u.P.x << ", " <<u.P.y <<") \n Velocità: (" << u.V.vx << ", " <<u.V.vy <<')';
  return os;
}