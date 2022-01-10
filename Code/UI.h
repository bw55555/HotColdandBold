#pragma once

#include "Scene.h"
class UI : public Scene {
public:
	UI() { initialize(); }
	void initialize() override;
	void update() override;
	void render() override;
	~UI() {};

	static unsigned int fbo;
	static unsigned int textureColorbuffer;
	static glm::vec2 UIsize;
	static glm::mat4 UIprojection;

	int screenPriority = 0;
	void drawScreen();
};