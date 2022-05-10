struct UState { // stato dei singoli uccelli. Posizione e velocità in x,y
  double x{};
  double y{};
  double vx{};
  double vy{};
  bool operator==(UState const other) const; //per i test
};
