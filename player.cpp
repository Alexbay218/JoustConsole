#include "player.h"

player::player() {
	name = "";
	color = COLOR_RED;
	score = 0;
	deathTimer = 0;
	jumpKeyWasPressed = false;
	playerBird.posX = rand() % COLS;
	playerBird.posY = rand() % LINES;
}

void player::update() {
	if(deathTimer == 0) {
		if(sf::Keyboard::isKeyPressed(jumpKey) && !jumpKeyWasPressed) {
			playerBird.ground = false;
			playerBird.velY -= 0.35;
			if(sf::Keyboard::isKeyPressed(leftKey)) {
			  playerBird.velX -= 0.25;
			  playerBird.direction = -1;
			}
			if(sf::Keyboard::isKeyPressed(rightKey)) {
			  playerBird.velX += 0.25;
			  playerBird.direction = 1;
			}
			jumpKeyWasPressed = true;
		}
		else if(!sf::Keyboard::isKeyPressed(jumpKey)) {
			jumpKeyWasPressed = false;
		}
		if(playerBird.ground) {
			if(sf::Keyboard::isKeyPressed(leftKey)) {
				playerBird.velX -= 0.25;
				playerBird.direction = -1;
			}
			if(sf::Keyboard::isKeyPressed(rightKey)) {
				playerBird.velX += 0.25;
				playerBird.direction = 1;
			}
			if(playerBird.velX > 0.2) {
				playerBird.velX -= 0.1;
			}
			else if(playerBird.velX < -0.2) {
				playerBird.velX += 0.1;
			}
			else {
				playerBird.velX = 0;
			}
		}
		else {
			playerBird.velY += 0.0075;
		}
		playerBird.update();
	}
	else {
		playerBird.posX = rand() % COLS;
		playerBird.posY = rand() % LINES;
		deathTimer--;
	}
}

void player::checkPlayerCollision(std::vector<player> players) {
	if(deathTimer == 0) {
		int i = 0;
		while(i < players.size()) {
			if(players[i].deathTimer == 0) {
				if(playerBird.posYGrid == players[i].playerBird.posYGrid) {
					if(playerBird.posX >= players[i].playerBird.posX - 1.5 && playerBird.posX < players[i].playerBird.posX) {
						playerBird.velX = -playerBird.velX;
						playerBird.posX = players[i].playerBird.posX - 2;
					}
					if(playerBird.posX <= players[i].playerBird.posX + 1.5 && playerBird.posX > players[i].playerBird.posX) {
						playerBird.velX = -playerBird.velX;
						playerBird.posX = players[i].playerBird.posX + 2;
					}
				}
				else {
					if(playerBird.posY < players[i].playerBird.posY && playerBird.posY >= players[i].playerBird.posY - 2.5) {
						if(playerBird.posX >= players[i].playerBird.posX - 2.5 && playerBird.posX <= players[i].playerBird.posX + 2.5) {
							score++;
						}
					}
					if(playerBird.posY > players[i].playerBird.posY && playerBird.posY <= players[i].playerBird.posY + 2.5) {
						if(playerBird.posX >= players[i].playerBird.posX - 2.5 && playerBird.posX <= players[i].playerBird.posX + 2.5) {
							deathTimer = 250;
							playerBird.posX = rand() % COLS;
							playerBird.posY = rand() % LINES;
						}
					}
				}
			}
			i++;
		}
	}
}