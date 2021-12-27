#include "Player.h"
#include "GameWindow.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -600.0f), textureID, glm::vec3(100.0f, 100.0f, 100.0f)) {
	speed = 25.0f;
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
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
		speed = 10.0f;
		focus = true;
	}
	else {
		speed = 25.0f;
		focus = false;
	}

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
	
	glm::vec4 clampBox{0.0f - GameWindow::halfWidth + scale.x/2, 0.0f - GameWindow::halfHeight + scale.y/2, 0.0f + GameWindow::halfWidth - scale.x/2, 0.0f + GameWindow::halfHeight - scale.y/2};

	move(glm::vec2(hMove, vMove), clampBox);
}

void Player::drawHitbox(Shader* shader) {
	if (!renderEnabled) { return; }
	shader->use();
	shader->setInt("texture1", 0);
	glm::mat4 transmatrix = glm::mat4(1.0f);
	transmatrix = glm::translate(transmatrix, trans);
	transmatrix = glm::scale(transmatrix, glm::vec3(hitbox.radius));
	shader->setMat4("transformation", transmatrix);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(1.0f / GameWindow::halfWidth, 1.0f / GameWindow::halfHeight, 0.0f));
	shader->setMat4("projection", scaleMatrix);
	shader->setBool("shouldBlend", false);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, hitboxTexture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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