#ifndef BOIDS_HPP
#define BOIDS_HPP
//#include "UState.hpp" : forse si può togliere perché c'è in neighbours
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>


#include "flight.rules.hpp"
#include "neighbours.check.hpp"

class Boids {
  std::vector<UState> UState_;

  Sep sep_;

  All all_;

  Coe coe_;

 public:
  Boids(std::vector<UState> UState, Sep sep, All all, Coe coe)
      : UState_{UState}, sep_{sep}, all_{all}, coe_{coe} {
    // assertions here?
  }

  std::vector<UState> const& state() const
  {
    return UState_;
  } 
  
  void evolve(double delta_t);

};  // classe per applicare le regole di interazione a tutto lo stormo

#endif