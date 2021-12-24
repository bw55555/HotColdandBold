#include "CollidableObject.h"
#include "GameWindow.h"

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, initialPos, rotation) {
	hitbox = collisionBox;
	pos = initialPos;
	collisionEnabled = true;
}

CollidableObject::CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling, float rotation) : Sprite(textureID, scaling, glm::vec3(initialPos, 0.0f), rotation) {
	hitbox = collisionBox;
	pos = initialPos;
	collisionEnabled = true;
}

bool CollidableObject::checkCollision(CollidableObject* other) {
	glm::vec2 firstCenter = hitbox.center + pos;
	glm::vec2 secondCenter = other->hitbox.center + other->getPos();
	if (hitbox.type == HitboxType::Circle && other->hitbox.type == HitboxType::Circle) {
		float dist = glm::distance(firstCenter, secondCenter);
		return dist < other->hitbox.radius + hitbox.radius;
	}

	if (hitbox.type == HitboxType::Circle && other->hitbox.type == HitboxType::Box) {
		glm::vec2 closest = secondCenter + glm::clamp(firstCenter - secondCenter, -1.0f * other->hitbox.half_extents, other->hitbox.half_extents);
		return glm::length(closest - firstCenter) < hitbox.radius;
	}

	if (hitbox.type == HitboxType::Box && other->hitbox.type == HitboxType::Circle) {
		glm::vec2 closest = firstCenter + glm::clamp(secondCenter - firstCenter, -1.0f * hitbox.half_extents, hitbox.half_extents);
		return glm::length(closest - secondCenter) < other->hitbox.radius;
	}

	if (hitbox.type == HitboxType::Box && other->hitbox.type == HitboxType::Box) {
		glm::vec2 diff = firstCenter - secondCenter;
		return abs(diff.x) < abs(hitbox.half_extents.x + other->hitbox.half_extents.x) &&
			abs(diff.y) < abs(hitbox.half_extents.y + other->hitbox.half_extents.y);
	}

	//code collision between 2 boxes and 1 box, 1 circle
	return false;
	//remember to copy this code to the shared pointer version
}

bool CollidableObject::checkCollision(std::shared_ptr<CollidableObject> other) {
	if (!other->collisionEnabled || !collisionEnabled) { return false; }
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
	trans = glm::vec3(pos, 0.0f);
}

void CollidableObject::move(glm::vec2 movement, glm::vec4 clampBox) {
	pos = pos + movement;
	if (pos.x > clampBox[2]) {
		pos.x = clampBox[2];
	}
	else if (pos.x < clampBox[0]) {
		pos.x = clampBox[0];
	}
	if (pos.y > clampBox[3]) {
		pos.y = clampBox[3];
	}
	else if (pos.y < clampBox[1]) {
		pos.y = clampBox[1];
	}

	trans = glm::vec3(pos, 0.0f);
}

glm::vec2 CollidableObject::getPos() {
	return pos;
}

void CollidableObject::setPos(glm::vec2 aPos) {
	pos = aPos;
	trans = glm::vec3(pos, 0.0f);
}