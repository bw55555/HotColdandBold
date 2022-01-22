#include "GameLevel.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

GameLevel::GameLevel(void (*func)(GameLevel*)) : UpdateTime(func) {
    initialize();
}

void GameLevel::initialize() {
    ui = std::make_unique<UI>();
    int level = -1;
    switch (GameWindow::Instance->currScene) {
    case SceneName::Level1:
        level = 1;
        break;
    case SceneName::Level2:
        level = 2;
        break;
    }
    if (level != -1) {
        makeSprite(Sprite::backgroundTextures[level], Pos(0.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));
    }
}

void GameLevel::update() {
    if (!GameWindow::Instance->paused && KeyInput::isPressed("ESC")) {
        GameWindow::Instance->setPause(true);
    }

    if (!GameWindow::Instance->over && GameWindow::Instance->player->destroyed) {
        GameWindow::Instance->setLost(true);
    }

    if (!GameWindow::Instance->paused && !GameWindow::Instance->over) {

        frameUpdate(this);
        //update player, enemy, spawners, bullets
        GameWindow::Instance->player->update();

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

        bool autoCollect = GameWindow::Instance->player->getPos().y > 400.0f;
        for (auto item : DropItem::dropItems) {
            if (autoCollect) { 
                item->autoCollected = true; 
            }
            item->update();
            
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
    ui->update();
}

void GameLevel::render() {
    if (!GameWindow::Instance->paused) {
        glBindFramebuffer(GL_FRAMEBUFFER, ui->fbo);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, 2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight);
        for (std::shared_ptr<Sprite> sprite : sprites) {
            sprite->draw();
        }

        GameWindow::Instance->player->draw();
        GameWindow::Instance->player->drawHitbox();
        for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
            enemy->draw();
        }

        for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
            bullet->draw();
        }

        for (std::shared_ptr<DropItem> dropItem : DropItem::dropItems) {
            dropItem->draw();
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        float ratio = UI::UIsize.y / UI::UIsize.x;
        glViewport(GameWindow::screenSize.x / 2 - GameWindow::screenSize.y / 2 / ratio, 0, GameWindow::Instance->screenSize.y / ratio, GameWindow::Instance->screenSize.y);
        
    }
    ui->render();
}