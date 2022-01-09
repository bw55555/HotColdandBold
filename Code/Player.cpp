#include "Player.h"
#include "GameWindow.h"
#include "BulletSpawner.h"


Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	speed = 25.0f;
	currTime = 0.0f;
	lastFired = 0.0f;
	health = 3.0f;
	invTimer = 0.0f;
	destroyed = false;
}

void Player::update(GLFWwindow* window) {
	currTime += 1;
	if (lastFired > 0) {
		lastFired -= 1;
	}
	checkMovement(window);
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

void Player::checkMovement(GLFWwindow* window) {

	//rshift?
	if (KeyInput::isPressed("LSHIFT")) {
		speed = 8.0f;
		focus = true;
	}
	else {
		speed = 20.0f;
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
	lastFired = 0.0f;
	float bulletSize = 50.0f;
	Hitbox bulletHitbox;
	bulletHitbox.type = HitboxType::Circle;
	bulletHitbox.radius = bulletSize/2.0f;
	std::shared_ptr<Bullet> bullet = Bullet::makeBullet(bulletHitbox, getPos() + glm::vec2(0.0f, 10.0f), BulletSpawner::bulletPresetTextures[2], BulletMovement::homingBullet, glm::vec3(bulletSize));
	bullet->firedByPlayer = true;
	bullet->initializeCustomVars(Movement::Speed{ 50.0f });
}

void Player::takeDamage() {
	if (invTimer <= 0) {
		health -= 1;
		if (health == 0) {
			destroy();
		}
		invTimer = 180.0f;
	}
	
}

void Player::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}