#include "Player.h"
#include "GameWindow.h"
#include "BulletSpawner.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	health = 3.0f;
	continues = 3;
	grazeAmount = 0;
	bombs = 100.0f;
	superchargeHeatMax = 250.0f;
	initialize();
}

void Player::initialize() {
	lastFired = 0.0f;
	lastHomingFired = 0.0f;
	currTime = 0.0f;
	speed = 25.0f;
	invTimer = -1.0f;
	destroyed = false;
	collisionEnabled = true;
	renderEnabled = true;
	heat = 2000.0f;
}

void Player::update() {
	currTime += 1;
	if (heat > 0 && static_cast<int>(currTime) % 6 == 0) {
		heat -= 1.0f - focus * 0.2f;
	}
	lastFired -= (lastFired > 0) * 1.0f;
	lastHomingFired -= (lastHomingFired > 0) * 1.0f;
	superchargeHeatInstant -= (superchargeHeatInstant > 0) * 1.0f;
	noInstantHeatTimer -= (noInstantHeatTimer > 0) * 1.0f;

	if (deathbombTimer >= 0.0f) {
		if (deathbombTimer == 0.0f) {
			takeDamage();
		}
		deathbombTimer -= 1.0f;
	}

	if (superchargeHeatInstant + superchargeHeatPermanent >= superchargeHeatMax) {
		overHeatTime = 480.0f;
		superchargeHeatInstant = 0.0f;
		superchargeHeatPermanent = 0.0f;
	}

	if (invTimer >= 0) {
		if (invTimer == 0.0f) {
			color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f + 0.5f * sin(invTimer / 3));
		}
		invTimer -= 1;
	}

	if (overHeatTime > 0) {
		overHeatTime -= 1.0f;
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (overHeatTime == 0.0f) {
		overHeatTime = -1.0f;
		health += 1;
		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//sound effect here
	}

	checkMovement();
	//bomb!
	if (KeyInput::isPressed("X")) {
		bomb();
	}
	if (KeyInput::isPressed("Z"))
		fire();


	
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
	if (lastFired <= 0) {
		lastFired = 3.0f;
		float bulletSize = 200.0f;
		std::shared_ptr<Bullet> bullet = Bullet::makeBullet(Hitbox::Circle(bulletSize / 2.0f - 2), getPos() + glm::vec2(0.0f, 10.0f), BulletSpawner::bulletPresetTextures[19], BulletMovement::directionalBullet, glm::vec3(bulletSize));
		bullet->firedByPlayer = true;
		bullet->initializeCustomVars(Movement::Direction{ glm::vec2(0.0f, 1.0f) }, Movement::Speed{ 100.0f });
		bullet->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
	}
	if (!focus) {
		if (lastHomingFired <= 0) {
			lastHomingFired = 12.0f;
			float bulletSize = 100.0f;
			for (int i = 0; i < 2; i++) {
				std::shared_ptr<Bullet> bullet = Bullet::makeBullet(Hitbox::Circle(bulletSize / 2.0f - 2), getPos() + glm::vec2(50.0f * (2.0f * i - 1.0f), 10.0f), BulletSpawner::bulletPresetTextures[2], BulletMovement::homingBullet, glm::vec3(bulletSize));
				bullet->firedByPlayer = true;
				bullet->initializeCustomVars(Movement::Direction{ glm::vec2(0.0f, 1.0f) }, Movement::Speed{ 50.0f });
				bullet->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.8f);
				bullet->isPlayerHomingBullet = true;
			}
		}
		
	}
}

void Player::takeDamage() {
	if (overHeatTime >= 0.0f) {
		overHeatTime = -1.0f;
		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		GameWindow::Instance->clearBullets();
		//sound effect here
		return;
	}

	if (deathbombTimer == -1.0f) {
		collisionEnabled = false;
		deathbombTimer = 10.0f;
		//sound effect here
	} else if (invTimer <= 0) {
		health -= 1;
		if (health <= 0) {
			destroy();
		}
		else {
			respawn();
		}
	}
	
}

void Player::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
	superchargeHeatInstant = 0.0f;
	GameWindow::Instance->clearBullets();
	GameWindow::Instance->setLost(true);
}

void Player::respawn() {
	GameWindow::Instance->clearBullets();
	collisionEnabled = true;
	invTimer = 180.0f;
	superchargeHeatInstant = 0.0f;
	//do something!
}

void Player::addHeat(float amt) {
	heat += amt;
	if (noInstantHeatTimer <= 0.0f && overHeatTime == -1.0f) {
		superchargeHeatInstant += 9 * amt / 10.0f;
	}
	superchargeHeatPermanent += amt / 10.0f;
}

void Player::collect(DropItem* item) {
	switch (item->itemType) {
	case DropItemType::Life:
		health += 1.0f;
		break;
	case DropItemType::Heat:
		addHeat(10.0f);
		break;
	case DropItemType::LargeHeat:
		addHeat(100.0f);
		break;
	}
	item->destroy();
}

bool Player::checkGraze(Bullet* b) {
	if (collisionEnabled && !b->grazed && b->checkCollision(Hitbox::Circle(100.0f), getPos())) {
		grazeAmount += 1;
		heat += 1;
		b->grazed = true;
		return true;
	}
	else {
		return false;
	}
}

void Player::bomb() {
	//maybe do something (sound effect here) if can't bomb for any reason?
	if (bombs <= 0 || heat < 300.0f) { return; }

	if (deathbombTimer > 0.0f) {
		deathbombTimer = -1.0f;
		collisionEnabled = true;
	}
	//sound effect here
	noInstantHeatTimer = 60.0f;
	bombs -= 1;
	superchargeHeatInstant = 0.0f;
	heat -= 300.0f;
	for (auto& e : Enemy::enemies) {
		e->takeDamage(100.0f);
	}
	GameWindow::Instance->clearBullets();
	for (auto& d : DropItem::dropItems) {
		d->autoCollected = true;
	}
}