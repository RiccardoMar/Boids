#IFNDEF NEIGHBOURS.CHECK_HPP
#DEFINE NEIGHBOURS.CHECK_HPP


#include <cmath>

#include "Ustate.hpp"


struct Check {
  bool operator()(Ustate const& u1, UState const& u2) const {
      return abs((u1.x^2 + u1.y^2)^0.5 - (u2.x^2 + u2.y^2)^0.5)
  }
}




//qual è la distanza limite per la definizione di un vicino? 
//siccome il check prende due punti e vede se sono vicini, non ha var private -> lo implemento come struct?
#endif
