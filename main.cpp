#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "boids.hpp"

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t) {
  double const dt{delta_t.asSeconds()};
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;
  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.bordi(boids, display_width, display_height);
    boids.evolve(dt);
  }

  return boids.state();
}

// valori in input
int main() {
  auto const delta_t{sf::milliseconds(1)};
  int const fps = 30;
  int const steps_per_evolution{1000 / fps};
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
                                                         display_height - 200);
    std::uniform_real_distribution<double> random_width(0.,
                                                        display_width - 200);

    std::uniform_real_distribution<double> random_velocity(0., 100.);

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
  std::cout
      << "Inserire la distanza di interazione fra boids (in pixel; ricordare "
         "che il parametro distanza della separazione è 10 pixel) : ";
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

  bool wait = false;

  window.setFramerateLimit(fps);
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window1.close();
    }

    if ((event.type == sf::Event::KeyPressed) || (event.key.code == sf::Keyboard::Enter)){
        wait = true;}
    
    if((event.type == sf::Event::KeyPressed) || (event.key.code == sf::Keyboard::Escape)){
            wait = false;
        }
        
        if (window1.isOpen() == false &&
        sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      window1.create(sf::VideoMode(700, 600), "Double window works!");
    }

if(wait == true){ //codice quando il gioco è in pausa
        window.clear();
    window.draw(sprite1);
    auto b = boids.state();

      for (unsigned int i = 0; i != uccelli.size(); ++i) {
   
     sprite.setPosition(b[i].P.x, b[i].P.y);
     window.draw(sprite);
    } 
         
         if (window1.isOpen() == false) {
      window.draw(text);
    }

    window.display();

    window1.clear(sf::Color::White);
    window1.draw(sprite);
    window1.display();
        
    }

     if(wait == false) {
    window.clear();
    window.draw(sprite1);

    auto const state = evolve(boids, 1000/30, delta_t);
    auto b = boids.state();
    std::cout << "////////////////////////////////////////////////////////////"
              << '\n';  
    for (unsigned int i = 0; i != uccelli.size(); ++i) {
      // auto arg = (180./3.1415926535) *
      // std::atan(std::tan(b[i].V.vx/b[i].V.vy)); sprite.setRotation(arg);
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
  }

  return 0;
}
