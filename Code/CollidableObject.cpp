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

bool CollidableObject::checkCollision(Hitbox otherHitbox, glm::vec2 otherPos) {
	if (!collisionEnabled) { return false; }
	glm::vec2 firstCenter = hitbox.center + pos;
	glm::vec2 secondCenter = otherHitbox.center + otherPos;
	if (hitbox.type == HitboxType::Circle && otherHitbox.type == HitboxType::Circle) {
		float dist = glm::distance(firstCenter, secondCenter);
		return dist < otherHitbox.radius + hitbox.radius;
	}

	if (hitbox.type == HitboxType::Circle && otherHitbox.type == HitboxType::Box) {
		glm::vec2 closest = secondCenter + glm::clamp(firstCenter - secondCenter, -1.0f * otherHitbox.half_extents, otherHitbox.half_extents);
		return glm::length(closest - firstCenter) < hitbox.radius;
	}

	if (hitbox.type == HitboxType::Box && otherHitbox.type == HitboxType::Circle) {
		glm::vec2 closest = firstCenter + glm::clamp(secondCenter - firstCenter, -1.0f * hitbox.half_extents, hitbox.half_extents);
		return glm::length(closest - secondCenter) < otherHitbox.radius;
	}

	if (hitbox.type == HitboxType::Box && otherHitbox.type == HitboxType::Box) {
		glm::vec2 diff = firstCenter - secondCenter;
		return abs(diff.x) < abs(hitbox.half_extents.x + otherHitbox.half_extents.x) &&
			abs(diff.y) < abs(hitbox.half_extents.y + otherHitbox.half_extents.y);
	}

	//code collision between 2 boxes and 1 box, 1 circle
	return false;
}

bool CollidableObject::checkCollision(CollidableObject* other) {
	if (other->collisionEnabled == false) { return false; }
	return checkCollision(other->hitbox, other->getPos());
}

bool CollidableObject::checkCollision(std::shared_ptr<CollidableObject> other) {
	return checkCollision(other.get());
}

void CollidableObject::move(glm::vec2 movement) {
	pos = pos + movement;
	trans = glm::vec3(pos, 0.0f);
}

void CollidableObject::move(glm::vec2 movement, glm::vec4 clampBox) {
	pos = pos + movement;
	pos.x = std::clamp(pos.x, clampBox[0], clampBox[2]);
	pos.y = std::clamp(pos.y, clampBox[1], clampBox[3]);

	trans = glm::vec3(pos, 0.0f);
}

void CollidableObject::moveTo(glm::vec2 movement, float numFramesLeft) {
	move((1.0f / numFramesLeft) * (movement - pos));
}

glm::vec2 CollidableObject::rotateAround(glm::vec2 center, float angle) {
	glm::vec2 moveVec = Movement::rotateAround(pos, center, angle);
	move(moveVec);
	return (moveVec);
}

glm::vec2 CollidableObject::getPos() {
	return pos;
}

void CollidableObject::setPos(glm::vec2 aPos) {
	pos = aPos;
	trans = glm::vec3(pos, 0.0f);
}

float CollidableObject::getX() {
	return pos.x;
}

float CollidableObject::getY() {
	return pos.y;
}

bool CollidableObject::touchingWall(WallDirection dir) {
	switch (dir) {
	case WallDirection::Any:
		return touchingWall(WallDirection::AnyHorizontal) || touchingWall(WallDirection::AnyVertical);
	case WallDirection::AnyHorizontal:
		return touchingWall(WallDirection::Left) || touchingWall(WallDirection::Right);
	case WallDirection::AnyVertical:
		return touchingWall(WallDirection::Up) || touchingWall(WallDirection::Down);
	case WallDirection::Up:
		return pos.y + scale.y/2.0f > GameWindow::halfHeight;
	case WallDirection::Down:
		return pos.y - scale.y/2.0f < -GameWindow::halfHeight;
	case WallDirection::Right:
		return pos.x + scale.x/2.0f > GameWindow::halfWidth;
	case WallDirection::Left:
		return pos.x - scale.x/2.0f < -GameWindow::halfWidth;
	}
	return false;
}