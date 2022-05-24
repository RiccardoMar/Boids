#include "UState.hpp"

#include <iostream>

bool UState::operator==(UState const other) const {}

std::ostream& operator<<(std::ostream& os, UState const& u) {
  os << "Posizione: (" <<u.P.x << ", " <<u.P.y <<") \n Velocità: (" << u.V.vx << ", " <<u.V.vy <<')';
  return os;
}