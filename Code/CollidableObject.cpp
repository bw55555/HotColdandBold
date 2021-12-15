#include "CollidableObject.h"

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, initialPos, rotation) {
	hitbox = collisionBox;
	pos = initialPos;
	collisionEnabled = false;
}

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, glm::vec3(initialPos, 0.0f), rotation) {
	hitbox = collisionBox;
	pos = glm::vec3(initialPos, 0.0f);
	collisionEnabled = false;
}

bool CollidableObject::checkCollision(CollidableObject* other) {
	return false;
}

void CollidableObject::move(glm::vec2 movement) {
	pos = pos + glm::vec3(movement, 0.0f);
	trans = pos;
}
glm::vec3 CollidableObject::getPos() {
	return pos;
}