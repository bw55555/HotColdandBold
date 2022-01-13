#include "Player.h"
#include "GameWindow.h"
#include "BulletSpawner.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	health = 3.0f;
	grazeAmount = 0;
	bombs = 100.0f;
	initialize();
}

void Player::initialize() {
	currTime = 0.0f;
	speed = 25.0f;
	invTimer = 0.0f;
	destroyed = false;
	collisionEnabled = true;
	renderEnabled = true;
	heat = 500.0f;
}

void Player::update() {
	currTime += 1;
	if (static_cast<int>(currTime) % 6 == 0) {
		heat -= 1.0f;
	}
	if (lastFired > 0) {
		lastFired -= 1;
	}
	checkMovement();
	if (KeyInput::isPressed("Z"))
		fire();
	if (invTimer > 0) {
		invTimer -= 1;
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void Player::checkMovement() {

	//rshift?
	if (KeyInput::isPressed("LSHIFT")) {
		speed = std::min(heat / 20, 8.0f);
		focus = true;
	}
	else {
		speed = std::min(heat / 20, 20.0f); //idk but better formula is probably needed...
		focus = false;
	}

	float hMove = 0;
	float vMove = 0;
	if (KeyInput::isPressed("DOWN"))
		vMove -= speed;
	else if (KeyInput::isPressed("UP"))
		vMove += speed;

	if (KeyInput::isPressed("LEFT"))
		hMove -= speed;
	else if (KeyInput::isPressed("RIGHT"))
		hMove += speed;
	
	glm::vec4 clampBox{0.0f - GameWindow::halfWidth + scale.x/2, 0.0f - GameWindow::halfHeight + scale.y/2, 0.0f + GameWindow::halfWidth - scale.x/2, 0.0f + GameWindow::halfHeight - scale.y/2};

	move(glm::vec2(hMove, vMove), clampBox);
}


void Player::fire() {
	if (lastFired > 0) {
		return;
	}
	lastFired = 3.0f;
	float bulletSize = 100.0f;
	Hitbox bulletHitbox;
	bulletHitbox.type = HitboxType::Circle;
	bulletHitbox.radius = bulletSize/2.0f;
	std::shared_ptr<Bullet> bullet = Bullet::makeBullet(bulletHitbox, getPos() + glm::vec2(0.0f, 10.0f), BulletSpawner::bulletPresetTextures[2], BulletMovement::homingBullet, glm::vec3(bulletSize));
	bullet->firedByPlayer = true;
	bullet->initializeCustomVars(Movement::Direction{ glm::vec2(0.0f, 1.0f) }, Movement::Speed{ 50.0f });
	bullet->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.3f);
}

void Player::takeDamage() {
	if (invTimer <= 0) {
		health -= 1;
		if (health == 0) {
			destroy();
		}
		respawn();
	}
	
}

void Player::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}

void Player::respawn() {
	invTimer = 180.0f;
	//do something!
}

void Player::collect(DropItem* item) {
	switch (item->itemType) {
	case DropItemType::Life:
		health += 1.0f;
		break;
	case DropItemType::Heat:
		heat += 5.0f;
	}
	item->destroy();
}

bool Player::checkGraze(Bullet* b) {
	if (collisionEnabled && !b->grazed && b->checkCollision(Hitbox::Circle(50.0f), getPos())) {
		grazeAmount += 1;
		b->grazed = true;
		return true;
	}
	else {
		return false;
	}
}