#include "boids.hpp"

void Boids::evolve(double delta_t)
{
  auto Vicini = Check(UState_,  distanza_);
  auto v_1 = sep_(Vicini);
  auto v_2 = all_(Vicini);
  auto v_3 = coe_(Vicini);


  for (unsigned int i=0; i != UState_.size(); ++i) {
    UState_[i].V.vx += v_1[i].vx + v_2[i].vx + v_3[i].vx ;
    UState_[i].V.vy += v_1[i].vy + v_2[i].vy + v_3[i].vy ;
    UState_[i].P +=  convertVtoP(UState_[i].V) / (1.0 / delta_t );
}
}