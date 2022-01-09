#include "UIRect.h"
#include "GameWindow.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <Shader.h>


void UIRect::initializeVAO() {
    float vertices[4][2] = {
        { -0.5f, -0.5f},
        { -0.5f, 0.5f},
        { 0.5f, -0.5f},
        { 0.5f, 0.5f}
    };
    unsigned int VBO;
    glGenVertexArrays(1, &UIVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(UIVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

UIRect::UIRect(glm::vec4 _color, glm::vec3 scaling, glm::vec3 offset, float rotation) : Sprite(0, scaling, offset, rotation) {
	color = _color;
}

void UIRect::draw() {
    
	if (!renderEnabled) { return; }
	Shader* shader = GameWindow::rectShader;
	shader->use();
	shader->setVec4("color", color);
	glm::mat4 transmatrix = glm::mat4(1.0f);
	transmatrix = glm::translate(transmatrix, trans);
	transmatrix = glm::rotate(transmatrix, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
	transmatrix = glm::scale(transmatrix, scale);
	shader->setMat4("transform", transmatrix);
    shader->setMat4("projection", UI::UIprojection);
	glBindVertexArray(UIVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //do this to forget about EBO
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}