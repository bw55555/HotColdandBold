#pragma once

#include "Menu.h"

class SettingsMenu : public Menu {
public:
	SettingsMenu() { initialize(); }
	void initialize() override;
	//void render() override;
	void update() override;
};