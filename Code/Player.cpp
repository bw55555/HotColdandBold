#include "Player.h"
#include "GameWindow.h"
#include "BulletSpawner.h"
#include "Audio.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	superchargeHeatMax = 240.0f;
	speed = 25.0f;
	continues = 3;
	initialize();
}

void Player::initialize() {
	lastFired = 0.0f;
	lastHomingFired = 0.0f;
	currTime = 0.0f;

	grazeAmount = 0;
	
	superchargeHeatPermanent = 0.0f;
	
	useContinue();
	deaths = 0;
	bombsUsed = 0;
	continues = 3;
	noInstantHeatTimer = 0.0f;
	invTimer = -1.0f;
}

void Player::useContinue() {
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	bombs = 10.0f;
	overHeatTime = -1.0f;
	heat = 2000.0f;
	continues -= 1;
	destroyed = false;
	collisionEnabled = true;
	renderEnabled = true;
	deathbombTimer = -1.0f;
	superchargeHeatInstant = 0.0f;
	noInstantHeatTimer = 60.0f;
	invTimer = 180.0f;
	if (GameWindow::Instance->settings.mode == GameMode::All) {
		health = 3.0f;
	}
	else {
		health = 100.0f;
	}
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
		overHeatTime = 420.0f;
		AnimatedSprite::makePresetAnimatedSprite(AnimationType::BarrierAnim);
		superchargeHeatInstant = 0.0f;
		superchargeHeatPermanent = 0.0f;
	}
	invTimer -= (invTimer > 0) * 1.0f;
	if (overHeatTime >= 0.0f) {
		if (overHeatTime == 0.0f) {
			health += 1;
			SoundEffect::play("resources/audio/1up.mp3", false);
		}
		overHeatTime -= 1.0f;
		float fluc = sin(overHeatTime / (6 - 2 * (overHeatTime < 180.0f) - 2 * (overHeatTime < 60.0f)));
		color = glm::vec4(1.0f, 0.5f - 0.5f * fluc, 0.5f - 0.5f * fluc, 1.0f);
	}
	else if (invTimer > 0) {
		color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f + 0.5f * sin(invTimer / 3));
	}
	else {
		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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
		speed = std::min(8.0f * (overHeatTime > 0.0f) + sqrt(heat), 8.0f);
		focus = true;
	}
	else {
		speed = std::min(20.0f * (overHeatTime > 0.0f) + sqrt(heat), 20.0f); //idk but better formula is probably needed...
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
				std::shared_ptr<Bullet> bullet = Bullet::makeBullet(Hitbox::Circle(bulletSize / 2.0f - 2), getPos() + glm::vec2(50.0f * (2.0f * i - 1.0f), 10.0f), BulletSpawner::bulletPresetTextures[18], BulletMovement::homingBullet, glm::vec3(bulletSize));
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
		//AnimatedSprite::makePresetAnimatedSprite(AnimationType::BombAnim);
		SoundEffect::play("resources/audio/roar.mp3", false, 1.0f);
		GameWindow::Instance->clearBullets();
		return;
	}
	//std::cout << deathbombTimer << "\n";
	if (invTimer <= 0 && deathbombTimer == -1.0f) {
		collisionEnabled = false;
		deathbombTimer = 6.0f;
		SoundEffect::play("resources/audio/roar.mp3", false, 2.0f);
	} else if (deathbombTimer == 0.0f) {
		if (GameWindow::Instance->settings.mode == GameMode::Prac1 || GameWindow::Instance->settings.mode == GameMode::Prac2) {
			if (heat < 400) { heat = 1200.0f; }
		}
		health -= 1;
		deaths += 1;
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
		superchargeHeatInstant += 4 * amt / 5.0f;
	}
	superchargeHeatPermanent += amt / 5.0f;
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
	if (invTimer > 0.0f || bombs <= 0 || heat < 300.0f) { return; }
	if (deathbombTimer > 0.0f) {
		deathbombTimer = -1.0f;
		collisionEnabled = true;
	}
	AnimatedSprite::makePresetAnimatedSprite(AnimationType::BombAnim);
	SoundEffect::play("resources/audio/echo5.wav", false, 0.4f);
	noInstantHeatTimer = 60.0f;
	bombs -= 1;
	bombsUsed += 1;
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