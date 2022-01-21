#include "DropItem.h"
#include "GameWindow.h"
#include "Enemy.h"

DropItem::DropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, itemTextures[static_cast<int>(type)], scaling), UpdateTime<DropItem>(func) {
	itemType = type;
	if (GameWindow::Instance->player->overHeatTime > 0.0f) {
		autoCollected = true;
	}
}

std::shared_ptr<DropItem> DropItem::makeDropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) {
	std::shared_ptr<DropItem> drop = std::make_shared<DropItem>(collisionbox, initialPos, type, func, scaling);
	dropItems.push_back(drop);
	return drop;
}

std::shared_ptr<DropItem> DropItem::makeDropItem(DropItemType type, glm::vec2 pos) {
	return makeDropItem(type, pos, DropItem::standardFunc);
}

std::shared_ptr<DropItem> DropItem::makeDropItem(DropItemType type, glm::vec2 pos, void (*func)(DropItem*)) {
	switch (type) {
	case DropItemType::Heat:
		return makeDropItem(Hitbox::Box(glm::vec2(25.0f)), pos, type, func, glm::vec3(50.0f));
	case DropItemType::LargeHeat:
		return makeDropItem(Hitbox::Box(glm::vec2(50.0f)), pos, type, func, glm::vec3(100.0f));
	case DropItemType::Life:
		return makeDropItem(Hitbox::Box(glm::vec2(50.0f)), pos, type, func, glm::vec3(100.0f));
	default:
		return makeDropItem(Hitbox::Box(glm::vec2(25.0f)), pos, type, func, glm::vec3(50.0f));
	}
}

bool DropItem::checkAutoCollect(DropItem* item) {
	if (!item->autoCollected && glm::length(GameWindow::Instance->player->getPos() - item->getPos()) < 150.0f) {
		item->autoCollected = true;
	}

	if (item->autoCollected) {
		float dist = glm::length(GameWindow::Instance->player->getPos() - item->getPos());
		item->move(std::max(dist / 10.0f, 40.0f - 3.0f * (dist / 50.0f)) * BulletMovement::targetPlayer(item->getPos()));
	}
	return item->autoCollected;
}

void DropItem::standardFunc(DropItem* item) {
	//bullet with constant speed in a direction
	//customFloats: speed
	if (checkAutoCollect(item)) { return; }
	glm::vec2 mvec = 10.0f * glm::vec2(0.0f, -1.0f);
	item->move(mvec);
}

void DropItem::gravityDropFunc(DropItem* item) {
	if (checkAutoCollect(item)) { return; }
	float initialSpeed = 10.0f;
	if (item->currTime < 60) {
		item->move(glm::vec2(0.0f, 1.0f) * (initialSpeed - item->currTime / 3));
	}
	else {
		item->move(10.0f * glm::vec2(0.0f, -1.0f));
	}
}

void DropItem::update() {
	frameUpdate(this);
	if (!autoCollected && scale.y + getPos().y < -GameWindow::halfHeight) { destroy(); }
}

void DropItem::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}