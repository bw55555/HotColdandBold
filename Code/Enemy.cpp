#include "Enemy.h"
#include "GameWindow.h"

Enemy::Enemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling), UpdateTime<Enemy>(func) {
	//never use this, use makeEnemy instead. Ever. It screws with shared pointers. 
	destroyed = false;
	health = _health;
	invTimer = 0.0f;
}

std::shared_ptr<Enemy> Enemy::makeEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) {
	std::shared_ptr<Enemy> e = std::make_shared<Enemy>(_health, collisionbox, initialPos, textureID, func, scaling);
	e->dfunc = Enemy::spawnDropOnDeath(DropItemType::Heat);
	enemies.push_back(e);
	return e;
}

std::shared_ptr<Enemy> Enemy::makePresetEnemy(EnemyType type, glm::vec2 initialPos, void (*func)(Enemy*)) {
	switch (type) {
	case EnemyType::WeakFairy:
		return makeEnemy(3.0f, Hitbox::Circle(20.0f), initialPos, GameWindow::enemyTextures[0], func, glm::vec3(100.0f));
	case EnemyType::Fairy:
		return makeEnemy(dchoice(15.0f, 20.0f, 30.0f), Hitbox::Circle(20.0f), initialPos, GameWindow::enemyTextures[0], func, glm::vec3(100.0f));
	case EnemyType::StrongFairy:
		return makeEnemy(dchoice(60.0f, 80.0f, 100.0f), Hitbox::Circle(20.0f), initialPos, GameWindow::enemyTextures[0], func, glm::vec3(100.0f));
	case EnemyType::Doppel:
		return makeEnemy(30.0f, Hitbox::Circle(50.0f), initialPos, GameWindow::enemyTextures[1], func, glm::vec3(100.0f));
	}
	return nullptr;
}

std::shared_ptr<Enemy> Enemy::findNearestEnemy(glm::vec2 pos) {
	float minDistance = -1.0f;
	std::shared_ptr<Enemy> minDistEnemy = std::shared_ptr<Enemy>(nullptr);
	for (std::shared_ptr<Enemy> e : Enemy::enemies) {
		if (!e->isOnScreen()) { continue; }
		float dist = glm::distance(pos, e->getPos());
		if (minDistance < 0 || dist < minDistance) {
			minDistance = dist;
			minDistEnemy = e;
		}
	}
	return minDistEnemy;
}

void Enemy::update() {
	frameUpdate(this);
	if (invTimer > 0) {
		invTimer -= 1;
	}
}

void Enemy::takeDamage(float damage) {
	if (invTimer <= 0) {
		health -= damage;
		if (health <= 0) {
			destroy();
		}
	}
}

void Enemy::destroy() {
	dfunc(this);
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}

Enemy::~Enemy() {
	//should delete the pointers in the spawners vector
	spawners.clear();
}

BulletSpawner* Enemy::createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
	
	std::unique_ptr<BulletSpawner> s = std::make_unique<BulletSpawner>(shared_from_this(), initialPos, func);
	spawners.push_back(std::move(s));
	return spawners[spawners.size() - 1].get();
}

Enemy::DestroyFunc Enemy::spawnDropOnDeath(DropItemType d) {
	switch (d) {
	case DropItemType::Heat:
		return [](Enemy* e) {DropItem::makeDropItem(DropItemType::Heat, e->getPos(), DropItem::gravityDropFunc); };
	case DropItemType::Life:
		return [](Enemy* e) {DropItem::makeDropItem(DropItemType::Life, e->getPos(), DropItem::gravityDropFunc); };
	}
	return nullptr;
}