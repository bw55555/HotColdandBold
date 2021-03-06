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

glm::vec2 overheatBarSLoc{ 530.0f, -300.0f };
glm::vec2 overheatBarSScale{ 800.0f, 64.0f };

void UI::initialize() {
    makeRect(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Pos(0.0f), Scale(UIsize.x, UIsize.y));

    std::string difficultyText = "Easy";
    if (GameWindow::Instance->settings.difficulty == Difficulty::Normal) { difficultyText = "Normal"; }
    if (GameWindow::Instance->settings.difficulty == Difficulty::Hard) { difficultyText = "Hard"; }

    makeText("Difficulty", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 650.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText(difficultyText, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(700.0f, 650.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Lives", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 550.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("3", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(550.0f, 550.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Bombs", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 450.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("100", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(550.0f, 450.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Graze", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 350.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("0", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(550.0f, 350.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Heat", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 250.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("0", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(550.0f, 250.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("Continues", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(280.0f, 150.0f), glm::vec2(1.5f), 0, HTA::Left);
    makeText("3", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(730.0f, 150.0f), glm::vec2(1.5f), 0, HTA::Left);

    makeText("60", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1200.0f, -900.0f), glm::vec2(1.5f), 0, HTA::Left);
    
    makeText("Supercharge Bar", glm::vec3(1.0f, 1.0f, 1.0f), overheatBarSLoc + overheatBarSScale * 0.5f + glm::vec2(0.0f, 150.0f), glm::vec2(1.5f), 0, HTA::Center);
    makeText("SUPERCHARGED", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), overheatBarSLoc + overheatBarSScale * 0.5f, glm::vec2(1.0f));
    //overheat bar
    makeRect(glm::vec4(0.6f, 1.0f, 1.0f, 1.0f), overheatBarSLoc + overheatBarSScale * 0.5f, overheatBarSScale);

    //permanent heat
    makeRect(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f), overheatBarSLoc + overheatBarSScale * 0.5f, overheatBarSScale);

    //instant heat
    makeRect(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f), overheatBarSLoc + overheatBarSScale * 0.5f, overheatBarSScale);
    

    //Reference X
    //makeText("X", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f));
    
}

void UI::update() {
    
    //playerData
    texts[3]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->health));
    texts[5]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->bombs));
    texts[7]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->grazeAmount));
    texts[9]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->heat));
    texts[11]->text = std::to_string(static_cast<int>(GameWindow::Instance->player->continues));
    
    //overheat
    sprites[2]->scale.x = overheatBarSScale.x* GameWindow::Instance->player->superchargeHeatPermanent / GameWindow::Instance->player->superchargeHeatMax;
    sprites[2]->trans.x = overheatBarSLoc.x + 0.5f * sprites[2]->scale.x;

    sprites[3]->scale.x = overheatBarSScale.x * GameWindow::Instance->player->superchargeHeatInstant / GameWindow::Instance->player->superchargeHeatMax;
    sprites[3]->trans.x = overheatBarSLoc.x + sprites[2]->scale.x + 0.5f * sprites[3]->scale.x;

    //framerate
    std::stringstream s;
    s << std::setprecision(2) << GameWindow::Instance->frameRate << "fps";
    texts[12]->text = s.str();

    texts[14]->renderEnabled = GameWindow::Instance->player->overHeatTime > 0;



    if (GameWindow::Instance->over) {
        GameWindow::Instance->overMenu->update();
    }
    else if (GameWindow::Instance->won) {
        GameWindow::Instance->winMenu->update();
    }
    else if (GameWindow::Instance->credit) {
        GameWindow::Instance->credits->update();
    }
    else if (GameWindow::Instance->paused) {
        GameWindow::Instance->pauseMenu->update();
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
    if (BossEnemy::bossTimerSprite != nullptr) {
        BossEnemy::bossTimerSprite->draw();
    }

	for (auto& t : texts) {
		t->draw();
	}

    

    if (GameWindow::Instance->over) {
        GameWindow::Instance->overMenu->render();
    }
    else if (GameWindow::Instance->won) {
        GameWindow::Instance->winMenu->render();
    }
    else if (GameWindow::Instance->credit) {
        GameWindow::Instance->credits->render();
    }
    else if (GameWindow::Instance->paused) {
        GameWindow::Instance->pauseMenu->render();
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