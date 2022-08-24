#ifndef BOIDS_HPP
#define BOIDS_HPP
//#include "UState.hpp" : forse si può togliere perché c'è in neighbours

#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "flight.rules.hpp"

class Boids {
  std::vector<UState> UState_;

  Sep sep_;

  All all_;

  Coe coe_;

  unsigned int const distanza_;

 public:
  Boids(std::vector<UState>& UState, Sep const& sep, All const& all,
        Coe const& coe, unsigned int const& distanza)
      : UState_{UState}, sep_{sep}, all_{all}, coe_{coe}, distanza_{distanza} {}

  std::vector<UState> const& state() const { return UState_; }

  void evolve(double delta_t);

  std::vector<UState> const& state() const
  {
    return UState_;
  }

};  // classe per applicare le regole di interazione a tutto lo stormo

#endif