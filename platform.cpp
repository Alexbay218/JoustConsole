#include "platform.h"

platform::platform() {
	x = rand() % COLS;
	y = rand() % LINES;
	width = rand () % 15 + 10;
	height = 2;
}