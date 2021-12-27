#include "GameLevel.h"
#include "GameWindow.h"

GameLevel::GameLevel(void (*func)(GameLevel*)) {
	updatefunc = func;
	currTime = 0.0f;
	waitTime = 0.0f;
}

void GameLevel::update() {
	currTime += 1.0f;
	numWaits = 0;
	updatefunc(this);
}

void GameLevel::setCurrentTime(float time) {
	currTime = time;
}

//returns true numTrue times after waiting for time. 
bool GameLevel::wait(float time, float numTrue) {
	numWaits += 1;
	if (currTime >= time + waitTime && numWaits > numWaitTrue) {
		waitTime += time;
		numWaitTrue += 1;
	}
	//std::cout << currTime << " " << waitTime << std::endl;
	if (currTime < waitTime + numTrue && currTime >= waitTime && numWaits <= numWaitTrue) {
		return true;
	}
	else {
		return false;
	}
}

//wait(30); wait(30); waitUntil(45); 
//this will break because waitUntil(45) executes before wait(30)
//wait(30); waitUntil(45); wait(30);
//this works :)

//use this with caution... the algorithm relies on all the waits being chronological. See example above
bool GameLevel::waitUntil(float time, float numTrue) {
	numWaits += 1;
	if (currTime >= time && numWaits > numWaitTrue) {
		waitTime = time;
		numWaitTrue += 1;
	}
	//std::cout << currTime << " " << waitTime << std::endl;
	if (currTime < waitTime + numTrue && currTime >= waitTime && numWaits <= numWaitTrue) {
		return runLevel;
	}
	else {
		return false;
	}
}

void GameLevel::updateWaitTime() {
	runLevel = false;
	updatefunc(this);
	runLevel = true;
}

void Level::enemyTestFunc(Enemy* enemy) {
	//how to use void* like this?
	if (enemy->customFloats.size() <= 0) {
		std::cout << "Custom Floats not initialized" << std::endl;
		return;
	}
	float xpos = enemy->getPos().x;
	float spd = 10.0f;

	if (xpos <= -800.0f) {
		enemy->customFloats[0] = 1.0f;
	}
	if (xpos >= 800.0f) {
		enemy->customFloats[0] = -1.0f;
	}

	float dir = enemy->customFloats[0];
	//enemy->move(glm::vec2(dir * spd, 0.0f));

}