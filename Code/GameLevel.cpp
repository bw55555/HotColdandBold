#include "GameLevel.h"
#include "GameWindow.h"

GameLevel::GameLevel(void (*func)(GameLevel*)) {
	updatefunc = func;
	currTime = 0.0f;
}

void GameLevel::update() {
	currTime += 1.0f;
	updatefunc(this);
}

void GameLevel::setCurrentTime(float time) {
	currTime = time;
}