#include "UI.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

unsigned int UI::fbo = 0;
unsigned int UI::textureColorbuffer = 0;
glm::vec2 UI::UIsize{2 * GameWindow::halfWidth + 1600, 2 * GameWindow::halfHeight + 200};
glm::mat4 UI::UIprojection = glm::ortho(-UI::UIsize.x / 2, UI::UIsize.x / 2, -UI::UIsize.y / 2, UI::UIsize.y / 2);

void UI::initialize() {
    makeText("Score", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(500.0f, 200.0f), glm::vec2(1.0f));
    makeText("X", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f));
    makeRect(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Pos(0.0f), Scale(UIsize.x, UIsize.y));
}

void UI::update() {

}

void UI::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& s : sprites) {
        s->draw();
    }
    drawScreen();
	for (auto& t : texts) {
		t->draw();
	}
    
}

void UI::drawScreen() {
    
    GameWindow::screenShader->use();
    GameWindow::screenShader->setInt("screenTexture", 0);
    glm::mat4 tmat = glm::mat4(1.0f);
    tmat = glm::translate(tmat, glm::vec3(-600.0f, 0.0f, 0.0f));
    tmat = glm::scale(tmat, glm::vec3(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight, 1.0f));
    
    GameWindow::screenShader->setMat4("transform", tmat);
    GameWindow::screenShader->setMat4("projection", UI::UIprojection);
    glBindVertexArray(Sprite::VAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}