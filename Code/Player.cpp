#include "Player.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, glm::vec2(0.0f, -0.6f), textureID, glm::vec3(0.1f, 0.1f, 0.1f)) {
	speed = 0.01;
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