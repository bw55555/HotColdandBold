#include "Sprite.h"
#include "GameWindow.h"

Sprite::Sprite(unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) {
	scale = scaling;
	trans = offset;
	rot = rotation;
	texture = textureID;
	isBullet = false;
	//spriteList.push_back(std::move(std::shared_ptr<Sprite>(this)));
}

std::shared_ptr<Sprite> Sprite::makeSprite(unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) {
	std::shared_ptr<Sprite> s = std::make_shared<Sprite>(textureID, scaling, offset, rotation);
	spriteList.push_back(s);
	return s;
}

void Sprite::draw(Shader* shader) {
	shader->use();
	shader->setInt("texture1", 0);
	glm::mat4 transmatrix = glm::mat4(1.0f);
	transmatrix = glm::translate(transmatrix, trans);
	transmatrix = glm::rotate(transmatrix, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
	transmatrix = glm::scale(transmatrix, scale);
	shader->setMat4("transformation", transmatrix);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(1.0f / GameWindow::width, 1.0f / GameWindow::height, 0.0f));
	shader->setMat4("projection", scaleMatrix);
	shader->setBool("shouldBlend", false);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::rotate(float angle) {
	rot += angle;
}

void Sprite::rotate(glm::vec2 dir) {
	rot += glm::degrees(glm::orientedAngle(glm::vec2(0, 1), glm::normalize(dir)));
}

void Sprite::setRotation(glm::vec2 dir) {
	rot = glm::degrees(glm::orientedAngle(glm::vec2(0, 1), glm::normalize(dir)));
}

Sprite::~Sprite() {
	//spriteList.erase(std::begin(spriteList));
}