#include "Sprite.h"

Sprite::Sprite(unsigned int textureID, glm::vec3 scaling, glm::vec3 offset, float rotation) {
	scale = scaling;
	trans = offset;
	rot = rotation;
	texture = textureID;
	spriteList.push_back(this);
}

void Sprite::draw(Shader* shader) {
	shader->use();
	shader->setInt("texture1", 0);
	glm::mat4 transmatrix = glm::mat4(1.0f);
	transmatrix = glm::translate(transmatrix, trans);
	transmatrix = glm::rotate(transmatrix, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
	transmatrix = glm::scale(transmatrix, scale);
	shader->setMat4("transformation", transmatrix);
	shader->setMat4("projection", glm::mat4(1.0f));

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