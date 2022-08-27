#include "boids.hpp"

void Boids::evolve(double delta_t, unsigned int const display_width,
                   unsigned int const display_height) {
  auto Vicini = Check(UState_, distanza_);
  auto v_1 = sep_(Vicini, UState_);
  auto v_2 = all_(Vicini, UState_);
  auto v_3 = coe_(Vicini, UState_);

  // spazio chiuso
/*
  for (unsigned int i = 0; i != UState_.size(); ++i) {
    UState_[i].V.vx += v_1[i].vx + v_2[i].vx + v_3[i].vx;
    UState_[i].V.vy += v_1[i].vy + v_2[i].vy + v_3[i].vy;
    UState_[i].P += convertVtoP(UState_[i].V) / (1.0 / delta_t);
    if (UState_[i].P.x < 0) {
      UState_[i].V.vx = abs(UState_[i].V.vx);
    };
    if (UState_[i].P.x > display_width - 200) {
      UState_[i].V.vx = (-1) * abs(UState_[i].V.vx);
    };
    if (UState_[i].P.y < 0) {
      UState_[i].V.vy = abs(UState_[i].V.vy);
    };
    if (UState_[i].P.y > display_height - 200) {
      UState_[i].V.vy = (-1) * abs(UState_[i].V.vy);
    };
  };
*/
  // spazio aperto ai lati
/*
  for (unsigned int i = 0; i != UState_.size(); ++i) {
    UState_[i].V.vx += v_1[i].vx + v_2[i].vx + v_3[i].vx;
    UState_[i].V.vy += v_1[i].vy + v_2[i].vy + v_3[i].vy;
    UState_[i].P += convertVtoP(UState_[i].V) / (1.0 / delta_t);
    if (UState_[i].P.x < 0) {
      UState_[i].P.x = display_width;
    };
    if (UState_[i].P.x > display_width - 200) {
      UState_[i].P.x = 0;
    };
    if (UState_[i].P.y < 0) {
      UState_[i].V.vy = abs(UState_[i].V.vy);
    };
    if (UState_[i].P.y > display_height - 200) {
      UState_[i].V.vy = (-1) * abs(UState_[i].V.vy);
    };
  };
*/
  // spazio totalmente aperto

  for (unsigned int i = 0; i != UState_.size(); ++i) {
    UState_[i].V.vx += v_1[i].vx + v_2[i].vx + v_3[i].vx;
    UState_[i].V.vy += v_1[i].vy + v_2[i].vy + v_3[i].vy;
    UState_[i].P += convertVtoP(UState_[i].V) / (1.0 / delta_t);
    if (UState_[i].P.x < 0) {
      UState_[i].P.x = display_width;
    };
    if (UState_[i].P.x > display_width) {
      UState_[i].P.x = 0;
    };
    if (UState_[i].P.y < 0) {
      UState_[i].P.y = display_height;
    };
    if (UState_[i].P.y > display_height ) {
      UState_[i].P.y = 0;
    };
  };

  // for(unsigned int i = 0; i != Vicini.size(); ++i){
  //   std::cout << Vicini[i].u1.UPN << "  with  " << Vicini[i].u2.UPN << '\n';
  // }
}

// void Boids::bordi(Boids& boids, const unsigned int display_width,
//                   const unsigned int display_height) {
//   auto u = boids.state();
//   for (unsigned int i = 0; i != u.size(); ++i) {
//     if (u[i].P.x > display_width - 100 || u[i].P.x < 0.) {
//       std::cout << "Prima: " << u[i].V.vx << "UPN : " << u[i].UPN <<
//       std::endl; u[i].V.vx = -u[i].V.vx; std::cout << "Dopo: " << u[i].V.vx
//       << std::endl;
//     }
//     if (u[i].P.y > display_height || u[i].P.y < 0.) {
//       u[i].V.vy = u[i].V.vy - u[i].V.vy;
//     }
//   }
// }