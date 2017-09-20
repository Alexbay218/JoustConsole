#include <cmath>

class bird {
public:
  bird();
  
  int direction;
  double posX, velX;
  double posY, velY;
  double maxV;
  int posXGrid, posYGrid;
  bool ground;
  
  void update();
};