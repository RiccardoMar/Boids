#include "boids.hpp"
#include <iterator>

// namespace {

// UState solve(UState const& u, double f, double delta_t)
// {
  
//   Velocity const v += u.V;
//   Position const x = pps.x + (pps.v + 0.5 * a * delta_t) * delta_t;

//   return UState{x, v};
// }

// }

void Boids::evolve(double delta_t)
{
  auto Vicini = Check(UState_,  distanza_);
  auto v_1 = sep_(Vicini);
  auto v_2 = all_(Vicini);
  auto v_3 = coe_(Vicini);

  auto u_it      = UState_.begin();
  auto u_it_next = std::next(u_it);
  auto u_last    = std::prev(UState_.end());

  Velocity a;
  Velicity b;
auto result = a+b;
  for (int i; u_it != u_last; ++u_it, ++i) {
    UState_[i].V.vx += v_1[i].vx + v_2[i].vx + v_3[i].vx ;
    UState_[i].V.vy += v_1[i].vy + v_2[i].vy + v_3[i].vy ;
    UState_[i].P +=  UState_[i].V / (1.0 / delta_t );

    // //double f = m_inter(*pps_it, *pps_it_next);
    // *pps_it  = solve(*pps_it, f - f_prev, delta_t);
    // f_prev   = f;
  }

//   *pps_last = solve(*pps_last, -f_prev, delta_t);
}