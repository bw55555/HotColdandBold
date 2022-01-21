#pragma once

#include "Menu.h"
class Credits : public Menu {
public:
	Credits() { initialize(); }
	void initialize() override;
	void render() override;
	void update() override;
	int credTimer = 1560;
};