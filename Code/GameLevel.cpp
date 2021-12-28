#include "GameLevel.h"
#include "GameWindow.h"

GameLevel::GameLevel(void (*func)(GameLevel*)) : UpdateTime(func) {

}

void GameLevel::update() {
	frameUpdate(this);
}

