#include "GameLevel.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

GameLevel::GameLevel(void (*func)(GameLevel*)) : UpdateTime(func) {
    initialize();
}

void GameLevel::initialize() {

}

void GameLevel::update() {
	frameUpdate(this);
    //update player, enemy, spawners, bullets
    GameWindow::Instance->player->update(GameWindow::Instance->window);

    //update bullets before enemies so that spawned bullets are not updated on the same frame
    for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
        bullet->update();
    }

    auto bulletsize = Bullet::bullets.size();
    for (auto i = 0; i < bulletsize; i++) {
        for (auto& s : Bullet::bullets[i]->spawners) {
            s->update();
        }
    }

    for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
        enemy->update();

        for (auto& s : enemy->spawners) {
            s->update();
        }
    }

    GameWindow::Instance->checkCollisions();

    //check for and destroy bullets with a true destroyed tag at the end
    if (Bullet::bullets.size() > 0) {

        Bullet::bullets.erase(std::remove_if(Bullet::bullets.begin(), Bullet::bullets.end(), [](const std::shared_ptr<Bullet>& bullet) {
            return bullet->destroyed;
            }), Bullet::bullets.end());

    }

    if (Enemy::enemies.size() > 0) {

        Enemy::enemies.erase(std::remove_if(Enemy::enemies.begin(), Enemy::enemies.end(), [](const std::shared_ptr<Enemy>& enemy) {
            return enemy->destroyed;
            }), Enemy::enemies.end());

    }

    if (DropItem::dropItems.size() > 0) {

        DropItem::dropItems.erase(std::remove_if(DropItem::dropItems.begin(), DropItem::dropItems.end(), [](const std::shared_ptr<DropItem>& dropItem) {
            return dropItem->destroyed;
            }), DropItem::dropItems.end());

    }
}

void GameLevel::render() {

    glBindFramebuffer(GL_FRAMEBUFFER, GameWindow::Instance->fbo);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Shader* shader = GameWindow::Instance->shader;
    glViewport(0, 0, 2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight);
    for (std::shared_ptr<Sprite> sprite : Sprite::spriteList) {
        sprite->draw(shader);
    }

    GameWindow::Instance->player->draw(shader);
    GameWindow::Instance->player->drawHitbox(shader);
    for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
        enemy->draw(shader);
    }

    for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
        bullet->draw(shader);
    }

    for (std::shared_ptr<DropItem> dropItem : DropItem::dropItems) {
        dropItem->draw(shader);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    float ratio = GameWindow::halfHeight / GameWindow::halfWidth;
    glViewport(GameWindow::screenSize.x / 2 - GameWindow::screenSize.y / 2 / ratio, 0, GameWindow::Instance->screenSize.y / ratio, GameWindow::Instance->screenSize.y);
    GameWindow::Instance->screenShader->use();
    GameWindow::Instance->screenShader->setInt("screenTexture", 0);
    glm::mat4 tmat = glm::mat4(1.0f);
    tmat = glm::scale(tmat, glm::vec3(2.0f));
    GameWindow::Instance->screenShader->setMat4("transform", tmat);
    glBindVertexArray(Sprite::VAO);
    glBindTexture(GL_TEXTURE_2D, GameWindow::Instance->textureColorbuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}