struct UState { // stato dei singoli uccelli. Posizione e velocità in x,y
  double x{};
  double y{};
  double vx{};
  double vy{};
  bool operator==(UState other) {  // serve per i test
    return x == other.x && y == other.y && vx == other.vx && vy == other.vy;
  }
};

// seguono le 3 interazioni

class Sep {};

class All {};

class Coe {};

class Boids {}; // classe per applicare le regole di interazione a tutto lo stormo
