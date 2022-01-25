#include "AnimatedSprite.h"
#include "GameWindow.h"

AnimatedSprite::AnimatedSprite(unsigned int textureID, UpdateFunc func, glm::vec2 initialPos, glm::vec3 scaling, float rotation) : CollidableObject(Hitbox::None(), initialPos, textureID, scaling, rotation), UpdateTime<AnimatedSprite>(func) {
	collisionEnabled = false;
}

std::shared_ptr<AnimatedSprite> AnimatedSprite::makeAnimatedSprite(unsigned int textureID, UpdateFunc func, glm::vec2 initialPos, glm::vec3 scaling, float rotation) {
	std::shared_ptr<AnimatedSprite> asprite = std::make_shared<AnimatedSprite>(textureID, func, initialPos, scaling, rotation);
	animatedSprites.push_back(asprite);
	return asprite;
}

std::shared_ptr<AnimatedSprite> AnimatedSprite::makePresetAnimatedSprite(AnimationType t) {
	switch (t) {
	case AnimationType::BombAnim:
		return makeAnimatedSprite(spriteTextures[0], [](AnimatedSprite* a) {
			a->scale += glm::vec3(10.0f * a->currTime, 10.0f * a->currTime, 0.0f);
			a->rotate(5.0f);
			if (a->wait(120)) { a->destroy(); }
			}, GameWindow::Instance->player->getPos(), glm::vec3(100.0f), 0.0f);
	case AnimationType::BarrierAnim:
		return makeAnimatedSprite(spriteTextures[0], [](AnimatedSprite* a) {
			a->trans = GameWindow::Instance->player->trans;
			a->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
			a->rotate(3.0f);
			a->scale -= glm::vec3(0.5f);
			if (a->waitForTrigger(GameWindow::Instance->player->overHeatTime < 0.0f, 420)) { a->destroy(); }
			}, GameWindow::Instance->player->getPos(), glm::vec3(400.0f), 0.0f);
	}
	return nullptr;
}

void AnimatedSprite::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}

void AnimatedSprite::update() {
	frameUpdate(this);
}