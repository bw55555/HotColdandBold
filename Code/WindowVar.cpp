#include "WindowVar.h"
#include <iostream>

float WindowVar::wvar1 = 0.0f;
float WindowVar::wvar2 = 0.0f;
glm::vec2 WindowVar::wvar3 = glm::vec2(0.0f);
glm::vec2 WindowVar::wvar4 = glm::vec2(0.0f);


void WindowVar::updatewvar() {
	if (KeyInput::isPressed("0", 1000000)) {
		activewvar = 0;
	}
	if (KeyInput::isPressed("1", 1000000)) {
		activewvar = 1;
	}
	if (KeyInput::isPressed("2", 1000000)) {
		activewvar = 2;
	}
	if (KeyInput::isPressed("3", 1000000)) {
		activewvar = 3;
	}
	if (KeyInput::isPressed("4", 1000000)) {
		activewvar = 4;
	}

	if (KeyInput::isPressed("=", 1000000)) {
		incr *= 2.0f;
	}

	if (KeyInput::isPressed("-", 1000000)) {
		incr /= 2.0f;
	}

	if (KeyInput::isPressed("A", 60)) {
		switch (activewvar) {
		case 1:
			wvar1 -= incr;
			break;
		case 2:
			wvar2 -= incr;
			break;
		case 3:
			wvar3.x -= incr;
			break;
		case 4:
			wvar4.x -= incr;
			break;
		}
	}
	if (KeyInput::isPressed("D", 60)) {
		switch (activewvar) {
		case 1:
			wvar1 += incr;
			break;
		case 2:
			wvar2 += incr;
			break;
		case 3:
			wvar3.x += incr;
			break;
		case 4:
			wvar4.x += incr;
			break;
		}
	}
	if (KeyInput::isPressed("W", 60)) {
		switch (activewvar) {
		case 1:
			wvar1 -= incr;
			break;
		case 2:
			wvar2 -= incr;
			break;
		case 3:
			wvar3.y += incr;
			break;
		case 4:
			wvar4.y += incr;
			break;
		}
	}
	if (KeyInput::isPressed("S", 60)) {
		switch (activewvar) {
		case 1:
			wvar1 += incr;
			break;
		case 2:
			wvar2 += incr;
			break;
		case 3:
			wvar3.y -= incr;
			break;
		case 4:
			wvar4.y -= incr;
			break;
		}
	}

	if (KeyInput::isPressed("`", 1000000)) {
		std::cout << "WVARS: \n";
		std::cout << wvar1 << "\n";
		std::cout << wvar2 << "\n";
		std::cout << wvar3.x << " " << wvar3.y << "\n";
		std::cout << wvar4.x << " " << wvar4.y << "\n";
	}
}