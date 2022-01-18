#pragma once
#include "Menu.h"
#include "Button.h"
class GameOver : public Menu {
public:
	GameOver() { initialize(); }
	void initialize() override;
	//void render() override;
	void update() override;
};