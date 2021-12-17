#include "CollidableObject.h"

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, initialPos, rotation) {
	hitbox = collisionBox;
	pos = initialPos;
	collisionEnabled = false;
}

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, glm::vec3(initialPos, 0.0f), rotation) {
	hitbox = collisionBox;
	pos = initialPos;
	collisionEnabled = false;
}

bool CollidableObject::checkCollision(CollidableObject* other) {
	glm::vec2 firstCenter = hitbox.center + pos;
	glm::vec2 secondCenter = other->hitbox.center + other->getPos();
	if (hitbox.type == HitboxType::Circle && other->hitbox.type == HitboxType::Circle) {
		float dist = glm::distance(firstCenter, secondCenter);
		return dist < other->hitbox.radius + hitbox.radius;
	}
	//code collision between 2 boxes and 1 box, 1 circle
	return false;
	//remember to copy this code to the shared pointer version
}

bool CollidableObject::checkCollision(std::shared_ptr<CollidableObject> other) {
	
	glm::vec2 firstCenter = hitbox.center + pos;
	glm::vec2 secondCenter = other->hitbox.center + other->getPos();
	if (hitbox.type == HitboxType::Circle && other->hitbox.type == HitboxType::Circle) {
		float dist = glm::distance(firstCenter, secondCenter);
		return dist < other->hitbox.radius + hitbox.radius;
	}
	//code collision between 2 boxes and 1 box, 1 circle
	return false;
}

void CollidableObject::move(glm::vec2 movement) {
	pos = pos + movement;
	trans = glm::vec3(pos, 0);
}

glm::vec2 CollidableObject::getPos() {
	return pos;
}