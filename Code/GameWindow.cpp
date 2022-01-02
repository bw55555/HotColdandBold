#include "GameWindow.h"
#include "Level1.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include "stb_image.h"


extern std::string PATH_START;

GameWindow::GameWindow(GLFWwindow* w, Shader* s) {
	window = w;
    shader = s;
	initialize();
}

void GameWindow::initialize() {
    float vertices[] = {
         -0.5f, -0.5f, 0.0f, //bl
         -0.5f, 0.5f, 0.0f, //tl
         0.5f, -0.5f, 0.0f, //br
         0.5f, 0.5f, 0.0f //tr
    };

    unsigned int indices[] = {
        0, 2, 1,
        1, 2, 3
    };

    float textureVertices[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    unsigned int VAO;
    unsigned int VBO;
    unsigned int textureVBO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    Sprite::VAO = VAO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    unsigned int playerTexture = 0;
    loadTexture(PATH_START + "resources/textures/awesomeface.png", &playerTexture);
    Hitbox playerHitbox;
    playerHitbox.type = HitboxType::Circle;
    playerHitbox.radius = 15.0f;
    //dosmth with the player hitbox
    player = std::make_shared<Player>(playerHitbox, playerTexture);
    
    //note that we may end up needing to put all of these into a spritesheet and use another function to choose the right texture when drawing
    loadTexture(PATH_START + "resources/textures/Bullet.png", &BulletSpawner::bulletPresetTextures[0]);
    loadTexture(PATH_START + "resources/textures/KnifeBlue.png", &BulletSpawner::bulletPresetTextures[1]);
    loadTexture(PATH_START + "resources/textures/PlayerBullet.png", &BulletSpawner::bulletPresetTextures[2]);
    loadTexture(PATH_START + "resources/textures/KnifeRed.png", &BulletSpawner::bulletPresetTextures[3]);
    loadTexture(PATH_START + "resources/textures/BallBlackBorder.png", &BulletSpawner::bulletPresetTextures[4]);
    loadTexture(PATH_START + "resources/textures/Circle.png", &Player::hitboxTexture);

    static unsigned int enemyTextures[10]; // Why is this 10?
    createEnemyTextures();
    level = std::make_shared<GameLevel>(Level::Level1);



    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    

    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2 * halfWidth, 2 * halfHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GameWindow::render() {

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight);
    for (std::shared_ptr<Sprite> sprite : Sprite::spriteList) {
        sprite->draw(shader); 
    }
    
    player->draw(shader);
    player->drawHitbox(shader);
    for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
        enemy->draw(shader);
    }
    
    for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
        bullet->draw(shader);
    }
    
    for (std::shared_ptr<DropItem> dropItem : DropItem::dropItems) {
        dropItem->draw(shader);
    }

    glfwSwapBuffers(window);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    float ratio = GameWindow::halfHeight / GameWindow::halfWidth;
    glViewport(screenSize.x / 2 - screenSize.y / 2 / ratio, 0, screenSize.y / ratio, screenSize.y);
    screenShader->use();
    screenShader->setInt("screenTexture", 0);
    glm::mat4 tmat = glm::mat4(1.0f);
    tmat = glm::scale(tmat, glm::vec3(2.0f));
    screenShader->setMat4("transform", tmat);
    glBindVertexArray(Sprite::VAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GameWindow::update() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //bomb!
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        clearBullets();

    level->update();

    //update player, enemy, spawners, bullets
    player->update(window);

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
    
    checkCollisions();

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

void GameWindow::loadTexture(std::string filePath, unsigned int* texturePointer) {
    loadTexture(filePath.c_str(), texturePointer);
}

void GameWindow::loadTexture(const char* filePath, unsigned int* texturePointer) {
    glGenTextures(1, texturePointer);
    glBindTexture(GL_TEXTURE_2D, *texturePointer); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = GL_RGBA;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
    }
}

void GameWindow::createEnemyTextures() {
    //This is not an ideal implementation! Simply a placeholder for now
    //Add more textures here as you make more enemies, but ideally we're looping through everything in a file
    loadTexture(PATH_START + "resources/textures/TouhouFairy.png", &enemyTextures[0]);
    loadTexture(PATH_START + "resources/textures/scaryface.png", &enemyTextures[1]);
}

void GameWindow::checkCollisions() {
    for (std::shared_ptr<Bullet> b : Bullet::bullets) {
        if (b->firedByPlayer) {
            for (std::shared_ptr<Enemy> e : Enemy::enemies) {
                if (e->checkCollision(std::static_pointer_cast<CollidableObject>(b))) {
                    //collision detected between enemy and player bullet, do something!
                    std::cout << "Hit enemy!" << std::endl;
                    b->destroy();
                }
            }
        }
        else {
            if (player->checkCollision(std::static_pointer_cast<CollidableObject>(b))) {
                //Collision detected between player and enemy bullet, do something!
                //std::cout << "Got hit :(" << std::endl;
                b->destroy();
            }
        }
    }

    for (std::shared_ptr<Enemy> e : Enemy::enemies) {
        if (player->checkCollision(std::static_pointer_cast<CollidableObject>(e))) {
            //Collision detected between enemy and player, do something!
            std::cout << "Got hit by enemy :(" << std::endl;
        }
    }
}

void GameWindow::clearScreen() {
    clearBullets();
    clearEnemies();
}

void GameWindow::clearEnemies() {
    Enemy::enemies.clear();
}

void GameWindow::clearBullets() {
    Bullet::bullets.clear();
}
