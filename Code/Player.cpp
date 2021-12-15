#include "Player.h"

Player::Player(Hitbox collisionbox, unsigned int textureID): CollidableObject(collisionbox, textureID, glm::vec3(0.1f, 0.1f, 0.1f)) {
	hMove = 0;
	vMove = 0;
	speed = 0.01;
}

void Player::checkMovement(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		vMove -= speed;
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		vMove += speed;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		hMove -= speed;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		hMove += speed;
	trans = glm::vec3(hMove, vMove, 0.0f);
}