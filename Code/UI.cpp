#include "UI.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include <sstream>
#include <iomanip>
#include "BossEnemy.h"

unsigned int UI::fbo = 0;
unsigned int UI::textureColorbuffer = 0;
glm::vec2 UI::UIsize{2 * GameWindow::halfWidth + 1600, 2 * GameWindow::halfHeight + 100};
glm::mat4 UI::UIprojection = glm::ortho(-UI::UIsize.x / 2, UI::UIsize.x / 2, -UI::UIsize.y / 2, UI::UIsize.y / 2);

void UI::initialize() {
    makeText("Score", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 650.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Lives", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 550.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("3", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(530.0f, 550.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Bombs", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 450.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("100", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(530.0f, 450.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Graze", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 350.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("0", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(530.0f, 350.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Heat", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 250.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("0", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(530.0f, 250.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Continues", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 150.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("3", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(730.0f, 150.0f), glm::vec2(1.5f), 0, HTA::Left);

    makeText("60", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1200.0f, -900.0f), glm::vec2(1.5f), 0, HTA::Left);
    //Reference X
    makeText("X", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f));
    makeRect(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Pos(0.0f), Scale(UIsize.x, UIsize.y));
}

void UI::update() {
    texts[2]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->health));
    texts[4]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->bombs));
    texts[6]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->grazeAmount));
    texts[8]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->heat));
    texts[10]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->continues));
    std::stringstream s;
    s << std::setprecision(3) << GameWindow::Instance->frameRate << "fps";
    texts[11]->text = s.str();
    if (GameWindow::Instance->paused) {
        GameWindow::Instance->pauseMenu->update();
    }
    if (GameWindow::Instance->over) {
        GameWindow::Instance->overMenu->update();
    }
    if (GameWindow::Instance->won) {
        GameWindow::Instance->winMenu->update();
    }
    if (GameWindow::Instance->credit) {
        GameWindow::Instance->credits->update();
    }
}

void UI::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < sprites.size(); i++) {
        if (screenPriority < 0) { drawScreen(); }
        sprites[i]->draw();
        if (i == screenPriority) { drawScreen(); }
    }

    if (BossEnemy::bossHealthBar != nullptr) {
        BossEnemy::bossHealthBar->draw();
    }

	for (auto& t : texts) {
		t->draw();
	}

    if (GameWindow::Instance->paused && !GameWindow::Instance->over) {
        GameWindow::Instance->pauseMenu->render();
    }

    if (GameWindow::Instance->over) {
        GameWindow::Instance->overMenu->render();
    }
    if (GameWindow::Instance->won) {
        GameWindow::Instance->winMenu->render();
    }
    if (GameWindow::Instance->credit) {
        GameWindow::Instance->credits->render();
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