#pragma once
#include "Sprite.h"

class UIRect : public Sprite {
public:
	static unsigned int UIVAO;
	static void initializeVAO();
	UIRect(glm::vec4 _color, glm::vec3 scaling = glm::vec3(1.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	
	void draw();
};