#pragma once
#include "CollidableObject.h"
#include "UpdateTime.h"

enum class AnimationType {BombAnim, BarrierAnim};

class AnimatedSprite : public CollidableObject, public UpdateTime<AnimatedSprite> {
public:
	static unsigned int spriteTextures[];
	//AnimatedSprite(glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
	AnimatedSprite(unsigned int textureID, UpdateFunc func, glm::vec2 initialPos, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
	static std::vector<std::shared_ptr<AnimatedSprite>> animatedSprites;

	static std::shared_ptr<AnimatedSprite> makeAnimatedSprite(unsigned int textureID, UpdateFunc func, glm::vec2 initialPos, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
	static std::shared_ptr<AnimatedSprite> makePresetAnimatedSprite(AnimationType t);

	bool destroyed = false;
	void destroy();
	void update();

};