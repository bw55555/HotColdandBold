#include "DropItem.h"
#include "GameWindow.h"

DropItem::DropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, itemTextures[static_cast<int>(type)], scaling), UpdateTime<DropItem>(func) {
	itemType = type;
}

std::shared_ptr<DropItem> DropItem::makeDropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling) {
	std::shared_ptr<DropItem> drop = std::make_shared<DropItem>(collisionbox, initialPos, type, func, scaling);
	dropItems.push_back(drop);
	return drop;
}

std::shared_ptr<DropItem> DropItem::makeDropItem(DropItemType type, glm::vec2 pos) {
	return makeDropItem(Hitbox::Circle(25.0f), pos, type, DropItem::standardFunc, glm::vec3(50.0f));
}

void DropItem::standardFunc(DropItem* item) {
	//bullet with constant speed in a direction
	//customFloats: speed
	glm::vec2 mvec = 10.0f * glm::vec2(0.0f, -1.0f);
	if (item->autoCollected) { 
		float dist = glm::length(GameWindow::Instance->player->getPos() - item->getPos());
		mvec = std::min(sqrt(dist), 10.0f) * BulletMovement::targetPlayer(item->getPos()); 
	}
	item->move(mvec);
}

void DropItem::update() {
	frameUpdate(this);
}

void DropItem::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}

void DropItem::collect() {
	destroy();
	//idk do something
}