#pragma once
#include "Menu.h"
#include "Button.h"
class WinMenu : public Menu {
public:
	WinMenu() { initialize(); }
	void initialize() override;
	//void render() override;
	void update() override;
	void render() override;
};