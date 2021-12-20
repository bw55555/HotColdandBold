#include "DropItem.h"

DropItem::DropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, itemTextures[static_cast<int>(type)], scaling) {
	currTime = 0.0f;
	itemType = type;
	updatefunc = func;
}

std::shared_ptr<DropItem> DropItem::makeDropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) {
	std::shared_ptr<DropItem> drop = std::make_shared<DropItem>(collisionbox, initialPos, type, func, scaling);
	return drop;
}

std::shared_ptr<DropItem> DropItem::makeDropItem(DropItemType type) {
	Hitbox collisionbox;
	collisionbox.type = HitboxType::Box;
	collisionbox.radius = 10.0f;
	std::shared_ptr<DropItem> drop = std::make_shared<DropItem>(collisionbox, glm::vec2(0.0f, 0.0f), type, standardFunc, glm::vec3(10.0f));
	return drop;
}

void DropItem::standardFunc(DropItem* item) {
	//bullet with constant speed in a direction
	//customFloats: speed
	if (item->customFloats.size() == 0) {
		item->customFloats.push_back(10.0f);
	}
	glm::vec2 dir = glm::vec2(0.0f, -1.0f);
	item->move(item->customFloats[0] * dir);
}

void DropItem::update() {
	currTime += 1.0f;
	updatefunc(this);
}

void DropItem::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}