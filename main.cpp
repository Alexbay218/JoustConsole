#include <ncurses.h>
#include <chrono>
#include <time.h>
#include <string>
#include <vector>
#include "player.h"
#include "platform.h"

int main() {	
	srand (time(NULL));
	WINDOW *mainWin;
  
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	
	start_color();
	
	mainWin = newwin(22, 58, LINES/2-22/2, COLS/2-58/2);
	int colorVal = 0;
	bool willContinue = false;
	while(!willContinue) {
		if(std::chrono::system_clock::now().time_since_epoch().count()%100000 == 0) {
			wclear(mainWin);
			init_pair(1, colorVal, COLOR_BLACK);
			colorVal++;
			if(colorVal > 7) {
				colorVal = 1;
			}
			wattron(mainWin,COLOR_PAIR(1));
			wprintw(mainWin, "        ***** **                                        \n");
			wprintw(mainWin, "     ******  **** *                               *     \n");
			wprintw(mainWin, "    **   *  * ****                               **     \n");
			wprintw(mainWin, "   *    *  *   **                                **     \n");
			wprintw(mainWin, "       *  *    ****   **   ****       ****     ******** \n");
			wprintw(mainWin, "      ** **   * ***  * **    ***  *  * **** * ********  \n");
			wprintw(mainWin, "      ** **  *   ****  **     ****  **  ****     **     \n");
			wprintw(mainWin, "    **** ** **    **   **      **  ****          **     \n");
			wprintw(mainWin, "   * *** ** **    **   **      **    ***         **     \n");
			wprintw(mainWin, "      ** ** **    **   **      **      ***       **     \n");
			wprintw(mainWin, "      ** ** **    **   **      **        ***     **     \n");
			wprintw(mainWin, "      ** ** **    **   **      **   ****  **     **     \n");
			wprintw(mainWin, "      ** **  ******     ******* ** * **** *      **     \n");
			wprintw(mainWin, "      *  *    ****       *****   **   ****        **    \n");
			wprintw(mainWin, "  **     *                                              \n");
			wprintw(mainWin, " ****   *                                               \n");
			wprintw(mainWin, " *  * **                                                \n");
			wprintw(mainWin, "*    **                                                 \n");
			wprintw(mainWin, "     *              ");
			wattroff(mainWin,COLOR_PAIR(1));
			wprintw(mainWin, "Press the Enter key to continue\n");
			wprintw(mainWin, "                    Press the Esc key to quit");
			wrefresh(mainWin);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			willContinue = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return 0;
		}
	}
	
	mainWin = newwin(LINES, COLS, 0, 0);
	std::vector<player> players;
	players.push_back(*new player);
	players.push_back(*new player);
	
	players[0].leftKey = sf::Keyboard::A;
	players[0].rightKey = sf::Keyboard::D;
	players[0].jumpKey = sf::Keyboard::W;
	players[0].color = COLOR_CYAN;
	
	players[1].leftKey = sf::Keyboard::Left;
	players[1].rightKey = sf::Keyboard::Right;
	players[1].jumpKey = sf::Keyboard::Up;
	players[1].color = COLOR_MAGENTA;
	
	std::vector<platform> platforms;
	for(int i = rand() % 10;i < 15;i++) {
		platforms.push_back(*new platform);
	}
	
	for(int i = 0;i < players.size();i++) {
		init_pair(i+1, players[i].color, COLOR_BLACK);
	}
  
	int count = 0;
	int totaltime = 10000;
	auto lastUpdate = std::chrono::system_clock::now();
	while(count < totaltime) {
		if((lastUpdate.time_since_epoch().count() + 10*1000000) < std::chrono::system_clock::now().time_since_epoch().count()) {
			if(std::chrono::system_clock::now().time_since_epoch().count()%5 == 0) {
				werase(mainWin);
			}
			box(mainWin, 0, 0);
			
			for(int i = 0;i < players.size();i++) {
				players[i].checkPlayerCollision(players);
				players[i].update();
			}	
			
			for(int i = 0;i < players.size();i++) {
				players[i].playerBird.ground = false;
				if(players[i].playerBird.posY >= LINES-2) {
					players[i].playerBird.posY = LINES-2.25;
					players[i].playerBird.velY = 0;
					players[i].playerBird.ground = true;
				}				
				if(players[i].playerBird.posY <= 1) {
					players[i].playerBird.posY = 1.25;
					players[i].playerBird.velY = 0.1;
				}
				if(players[i].playerBird.posXGrid > COLS-1) {
					players[i].playerBird.posX = 1;
				}
				if(players[i].playerBird.posXGrid < 1) {
					players[i].playerBird.posX = COLS-1;
				}
				
				for(int j = 0;j < platforms.size();j++) {
					if(players[i].playerBird.posX >= platforms[j].x && players[i].playerBird.posX <= platforms[j].x + platforms[j].width) {
						if(players[i].playerBird.posY >= platforms[j].y-1 && players[i].playerBird.posY <= platforms[j].y + 1) {
							players[i].playerBird.posY = platforms[j].y-1.25;
							players[i].playerBird.velY = 0;
							players[i].playerBird.ground = true;
						}					
						if(players[i].playerBird.posY >= platforms[j].y+platforms[j].height && players[i].playerBird.posY <= platforms[j].y+platforms[j].height + 1) {
							players[i].playerBird.posY = platforms[j].y+platforms[j].height+1.25;
							players[i].playerBird.velY = 0;
						}
					}
					for(int x = 0;x < platforms[j].width;x++) {
						for(int y = 0;y < platforms[j].height;y++) {
							if(x == 0) {
								if(y == 0) {
									mvwaddch(mainWin, platforms[j].y, platforms[j].x, ACS_ULCORNER);
								}
								else if(y == platforms[j].height-1) {
									mvwaddch(mainWin, platforms[j].y + platforms[j].height - 1, platforms[j].x, ACS_LLCORNER);
								}
							}
							else if(x == platforms[j].width-1) {
								if(y == 0) {
									mvwaddch(mainWin, platforms[j].y, platforms[j].x + platforms[j].width - 1, ACS_URCORNER);
								}
								else if(y == platforms[j].height-1) {
									mvwaddch(mainWin, platforms[j].y + platforms[j].height - 1, platforms[j].x + platforms[j].width - 1, ACS_LRCORNER);
								}
							}
							else {
								mvwaddch(mainWin, platforms[j].y + y, platforms[j].x + x, ACS_HLINE);
							}
						}
					}
				}
				
				if(players[i].deathTimer == 0) {
					wattron(mainWin, COLOR_PAIR(i+1));
					if(players[i].playerBird.direction > 0) {
						mvwprintw(mainWin, players[i].playerBird.posYGrid, players[i].playerBird.posXGrid, "O_");
					}
					else {
						mvwprintw(mainWin, players[i].playerBird.posYGrid, players[i].playerBird.posXGrid-1, "_O");
					}
					wattroff(mainWin, COLOR_PAIR(i+1));
				}
			}
			mvwprintw(mainWin, 0, COLS/2-9, ("Time: " + std::to_string((int) (totaltime-count)/100)).c_str());
			mvwprintw(mainWin, 0, 0, ("P1: " + std::to_string(players[0].score)).c_str());
			mvwprintw(mainWin, 0, COLS-6, ("P2: " + std::to_string(players[1].score)).c_str());
			
			count++;
			wrefresh(mainWin);
			lastUpdate = std::chrono::system_clock::now();
		}
	}
	endwin();

	return 0;
}
