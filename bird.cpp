#include "bird.h"

bird::bird() {
  direction = 1;
  posX = 0;
  posY - 0;
  velX = 0;
  velY = 0;
  maxV = 0.75;
  posXGrid = 0;
  posYGrid = 0;
  ground = false;
}
void bird::update() {
  if(velX > maxV) {
    velX = maxV;
  }
  if(velX < -maxV) {
    velX = -maxV;
  }
  if(velY > maxV) {
    velY = maxV;
  }
  if(velY < -maxV) {
    velY = -maxV;
  }
  posX += velX;
  posY += velY;
  posXGrid = (int) (posX + 0.5);
  posYGrid = (int) (posY + 0.5);
}