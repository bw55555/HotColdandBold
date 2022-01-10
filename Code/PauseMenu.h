#pragma once

#include "Menu.h"
class PauseMenu : public Menu {
public:
	PauseMenu() { initialize(); }
	void initialize() override;
	void render() override;
	void update() override;
	~PauseMenu() {};
};