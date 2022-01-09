#include "Sprite.h"
#include "GameWindow.h"
#include <Shader.h>

Sprite::Sprite(unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) {
	scale = scaling;
	trans = offset;
	rot = rotation;
	texture = textureID;
	renderEnabled = true;
	//spriteList.push_back(std::move(std::shared_ptr<Sprite>(this)));
}

std::shared_ptr<Sprite> Sprite::makeSprite(unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) {
	std::shared_ptr<Sprite> s = std::make_shared<Sprite>(textureID, scaling, offset, rotation);
	spriteList.push_back(s);
	return s;
}

void Sprite::draw() {
	if (!renderEnabled) { return; }
	Shader* shader = GameWindow::shader;
	shader->use();
	shader->setVec4("color", color);
	shader->setInt("texture1", 0);
	glm::mat4 transmatrix = glm::mat4(1.0f);
	transmatrix = glm::translate(transmatrix, trans);
	transmatrix = glm::rotate(transmatrix, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
	transmatrix = glm::scale(transmatrix, scale);
	shader->setMat4("transformation", transmatrix);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(1.0f / GameWindow::halfWidth, 1.0f / GameWindow::halfHeight, 0.0f));
	shader->setMat4("projection", scaleMatrix);
	shader->setBool("shouldBlend", false);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //do this to forget about EBO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::rotate(float angle) {
	rot += angle;
}

void Sprite::rotate(glm::vec2 dir) {
	if (isZeroVec(dir)) { return; }
	rot += glm::degrees(glm::orientedAngle(glm::vec2(0, 1), glm::normalize(dir)));
}

void Sprite::setRotation(glm::vec2 dir) {
	if (isZeroVec(dir)) { return; }
	rot = glm::degrees(glm::orientedAngle(glm::vec2(0, 1), glm::normalize(dir)));
}

bool Sprite::isOnScreen() {
	//assumes that VAO is a square centered at 0. 
	return -GameWindow::halfWidth < trans.x + scale.x && trans.x - scale.x < GameWindow::halfWidth && 
		-GameWindow::halfHeight < trans.y + scale.y && trans.y - scale.y < GameWindow::halfHeight;
}

Hitbox Sprite::getHitbox() {
	return Hitbox::None();
}

void Sprite::drawHitbox() {
	Shader* shader = GameWindow::shader;
	Hitbox hitbox = getHitbox();
	if (hitbox.type == HitboxType::None) {
		return;
	}
	if (hitbox.type == HitboxType::Circle) {
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
		glBindTexture(GL_TEXTURE_2D, circleHitboxTexture);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	return;
}