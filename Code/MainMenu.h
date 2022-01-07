#pragma once
#include "Menu.h"
#include "Button.h"
class MainMenu : public Menu {
public:
	MainMenu() { initialize(); }
	void initialize() override;
	void render() override;
	void update() override;
};