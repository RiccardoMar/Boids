#ifndef BOIDS_HPP
#define BOIDS_HPP
//#include "UState.hpp" : forse si può togliere perché c'è in neighbours
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "flight.rules.hpp"
//#include "neighbours.check.hpp"

class Boids {
  std::vector<UState> UState_;

  Sep sep_;

  All all_;

  Coe coe_;

  int distance_;

 public:
  Boids(std::vector<UState> UState, Sep const& sep, All const& all,
        Coe const& coe, int distance)
      : UState_{UState}, sep_{sep}, all_{all}, coe_{coe}, distance_{distance} {}

  std::vector<UState> const& state() const { return UState_; }

  void evolve(double delta_t);

};  // classe per applicare le regole di interazione a tutto lo stormo

#endif