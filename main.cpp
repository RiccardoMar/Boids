#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "boids.hpp"

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t) {
  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.evolve(dt);
  }

  return boids.state();
}

// valori in input
int main() {
  auto const delta_t{sf::milliseconds(1)};
  int const fps = 150;
  int const steps_per_evolution{1000/fps};
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  std::cout << "Display width = " << display_width << " ; "
            << "Display height : " << display_height << '\n';

  int n;
  std::cout << "Inserire il numero desiderato di boids : ";
  std::cin >> n;
  if (n <= 2) {
    throw std::runtime_error{"Has to be a positive integer > 2"};
  };

  std::vector<UState> uccelli(n);

  // Creazione n uccelli a random e inserimento con for loop dentro std::vector
  // uccelli
  std::random_device r;
  std::default_random_engine gen{r()};

  for (unsigned int i = 0; i != uccelli.size(); ++i) {
    std::uniform_real_distribution<double> random_height(0.,
                                                         display_height -
                                                         200);
    std::uniform_real_distribution<double> random_width(0.,
                                                        display_width - 200);

    std::uniform_real_distribution<double> random_velocity(5., 100.);

    uccelli[i].P.x = random_width(gen);
    uccelli[i].P.y = random_height(gen);
    uccelli[i].V.vx = random_velocity(gen);
    uccelli[i].V.vy = random_velocity(gen);

    uccelli[i].UPN = i;
  };

  // Input parametri funzionamento

  double s;
  std::cout << "Inserire il parametro di separazione : ";
  std::cin >> s;
  // if (s > 1 || s < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  Sep separazione{s};

  double a;
  std::cout << "Inserire il parametro di allineamento : ";
  std::cin >> a;
  // if (a > 1 || a < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  All allineamento{a};

  double c;
  std::cout << "Inserire il parametro di coesione : ";
  std::cin >> c;
  // if (c > 1 || c < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  Coe coesione{c};

  unsigned int distance;
   std::cout << "Inserire la distanza di interazione fra boids (in pixel; ricordare che il parametro distanza della separazione è 10 pixel) : ";
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  // Start interazione boids

  Boids boids{uccelli, separazione, allineamento, coesione,
              distance};  // bisogna fargli il costruttore

  // valori in output
  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità

  for (auto const& u : boids.state()) {
    std::cout << u << '\n';
  }

  std::cout << "/////////////////////////////////////////////////////////////"
            << '\n';

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SFML works!");

  sf::RenderWindow window1(sf::VideoMode(300, 200), "Double window works!");

  sf::Vector2i v1(100, 200);

  sf::Texture texture;
  if (!texture.loadFromFile("freccia.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(0.10f, 0.10f);

  sf::Texture texture1;
  if (!texture1.loadFromFile("windowsxp.jpg")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite1;
  sprite1.setTexture(texture1);
  sprite1.setScale(2.5f, 2.5f);

  sf::Font font;
  if (!font.loadFromFile("RachelBrown.ttf")) {
    std::cout << "Could not load font" << std::endl;
    return 0;
  }
  sf::Text text;
  text.setFont(font);
  text.setString("Click here to drop down menu");
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::Black);
  text.setPosition(1000, 100);

  window.setFramerateLimit(fps);
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window1.close();
    }

    if (window1.isOpen() == false &&
        sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      window1.create(sf::VideoMode(700, 600), "Double window works!");
    }

    window.clear();
    window.draw(sprite1);

    auto const state = evolve(boids, steps_per_evolution, delta_t);
    auto b = boids.state();
    
    for (unsigned int i = 0; i != uccelli.size(); ++i) {
      //auto arg = (180./3.1415926535) * std::atan(std::tan(b[i].V.vx/b[i].V.vy)); 
      if(b[i].P.x > display_width -1000 || b[i].P.x < 0. ) {
        b[i].V.vx =  b[i].V.vx -b[i].V.vx ; 
        sprite.setPosition(b[i].P.x, b[i].P.y);
        window.draw(sprite);
      }
     
        
        sprite.setPosition(b[i].P.x, b[i].P.y);
        window.draw(sprite);
      }
      //sprite.setRotation(arg);
      sprite.setPosition(b[i].P.x, b[i].P.y);
      window.draw(sprite);
      std::cout << b[i].P.x << "  " << b[i].P.y << b[i].UPN << std::endl;
    }
    
    
    
    // for (auto& u : state) {
    
    // auto arg = (180./3.1415926535) * std::atan(std::tan(u.V.vx/u.V.vy));  
      
    //   sprite.setPosition(u.P.x, u.P.y);
    //   sprite.setRotation(arg);
    //   window.draw(sprite);
    //   std::cout << u.P.x << "  " << u.P.y << std::endl;
    // }

    if (window1.isOpen() == false) {
      window.draw(text);
    }

    window.display();

    window1.clear(sf::Color::White);
    window1.draw(sprite);
    window1.display();
  }

  return 0;
}

// std::vector<Velocity> Velocities1(uccelli.size());
//   for (unsigned int i = 0; i != Vicini.size(); ++i) {
//       if (dist(Vicini[i].u1, Vicini[i].u2) < 1.) {
//         Velocities1[Vicini[i].u1.UPN] += convertPtoV(
//             uccelli[Vicini[i].u2.UPN].P - uccelli[Vicini[i].u1.UPN].P);
//         Velocities1[Vicini[i].u2.UPN] += convertPtoV(
//             uccelli[Vicini[i].u1.UPN].P - uccelli[Vicini[i].u2.UPN].P);
//       }
//       }  //-> così velocities è un vettore con le velocità v1, però che non
//       sono
//        // ancora state moltiplicate per il fattore s

//     for (unsigned int i = 0; i != Velocities1.size(); ++i) {
//       Velocities1[i] = Velocities1[i] / (-1 / s);
//     }
//     auto vs = Velocities1;

// for (unsigned int i = 0; i != Vicini.size(); ++i) {
//       if (dist(Vicini[i].u1, Vicini[i].u2) < 5.) {
//         std::cout<< "Distanza ok";
//       }
// }