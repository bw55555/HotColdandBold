#include "Player.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	speed = 15.0f;
	currTime = 0.0f;
	lastFired = 0.0f;
}

void Player::update(GLFWwindow* window) {
	currTime += 1;
	if (lastFired > 0) {
		lastFired -= 1;
	}
	checkMovement(window);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		fire();
}

void Player::checkMovement(GLFWwindow* window) {
	float hMove = 0;
	float vMove = 0;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		vMove -= speed;
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		vMove += speed;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		hMove -= speed;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		hMove += speed;
	move(glm::vec2(hMove, vMove));
}

void Player::fire() {
	if (lastFired > 0) {
		return;
	}
	lastFired = 0.0f;
	float bulletSize = 100.0f;
	Hitbox bulletHitbox;
	bulletHitbox.type = HitboxType::Circle;
	bulletHitbox.radius = bulletSize/2.0f;
	std::shared_ptr<Bullet> bullet = Bullet::makeBullet(bulletHitbox, getPos() + glm::vec2(0.0f, 10.0f), BulletSpawner::bulletPresetTextures[2], Bullet::homingBullet, glm::vec3(bulletSize));
	bullet->firedByPlayer = true;
	bullet->customFloats.push_back(110.0f);
	bullet->customFloats.push_back(0.0f);
	bullet->customFloats.push_back(1.0f);
}