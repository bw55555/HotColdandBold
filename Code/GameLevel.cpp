#include "GameLevel.h"

GameLevel::GameLevel(void (*func)(GameLevel*)) : UpdateTime(func) {

}

void GameLevel::update() {
	frameUpdate(this);
}

