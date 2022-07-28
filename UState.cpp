#include "UState.hpp"

#include <iostream>
#include <cmath>

//Segue implementazione metodi Position
  Position Position::operator+=(Position const& other){
    x += other.x;
    y += other.y;
    return *this;
  }
  Position Position::operator-(Position const& P1, Position const& P2){
    return Position{P1.x-P2.x, P1.y-P2.y};
  }
  Position Position::operator/(Position const& P, double const& den){
    return Position{P.x/den, P.y/den};
  }
  Position Position::move(Velocity const& V, double const& dt){
    x += V.vx*dt;
    y += V.vy*dt;
  }
//Segue implementazione metodi Velocity
  Velocity Velocity::operator+=(Velocity const& other){
    vx += other.vx;
    vy += other.vy;
    return *this;
  }
  Velocity Velocity::operator-(Velocity const& V1, Velocity const& V2){
    return Velocity{V1.vx-V2.vx, V1.vy-V2.vy};
  }
  Velocity Velocity::operator/(Velocity const& V, double const& den){
    return Velocity{V.vx/den, V.vy/den};
  }
//Segue implementazione metodi UState
  bool UState::operator==(UState const& other) const {}
  double UState::dist(UState const& other) const {
    double d = sqrt((P.x-other.P.x)*(P.x-other.P.x)+(P.y-other.P.y)*(P.y-other.P.y));
    return d;
  }
  std::ostream& operator<<(std::ostream& os, UState const& u) {
    os << "Posizione: (" <<u.P.x << ", " <<u.P.y <<") \n Velocità: (" << u.V.vx << ", " <<u.V.vy <<')';
    return os;
}

//Segue implementazione funzioni libere
  double dist(UState const& u1, UState const& u2) {
    return u1.dist(u2);
  }