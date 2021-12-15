#include "CollidableObject.h"

CollidableObject::CollidableObject(Hitbox collisionBox, unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) : Sprite(textureID, scaling, offset, rotation) {
	hitbox = collisionBox;
	collisionEnabled = false;
}

bool CollidableObject::checkCollision(CollidableObject* other) {
	return false;
}