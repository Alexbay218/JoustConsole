#include <ncurses.h>
#include <string>
#include <vector>
#include <SFML\Window\Keyboard.hpp>
#include "bird.h"

class player {
public:
  player();
  
  std::string name;
  int color;
  int score;
  int deathTimer;
  bird playerBird;
  sf::Keyboard::Key leftKey;
  sf::Keyboard::Key rightKey;
  sf::Keyboard::Key jumpKey;
  bool jumpKeyWasPressed;
  
  void update();
  void checkPlayerCollision(std::vector<player> players);
};