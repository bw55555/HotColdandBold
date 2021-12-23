#include "GameWindow.h"

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
    player = new Player(playerHitbox, playerTexture);
    
    loadTexture(PATH_START + "resources/textures/TouhouFairy.png", &enemyTextures[0]);
    
    //note that we may end up needing to put all of these into a spritesheet and use another function to choose the right texture when drawing
    loadTexture(PATH_START + "resources/textures/Bullet.png", &BulletSpawner::bulletPresetTextures[0]);
    loadTexture(PATH_START + "resources/textures/Knife.png", &BulletSpawner::bulletPresetTextures[1]);
    loadTexture(PATH_START + "resources/textures/PlayerBullet.png", &BulletSpawner::bulletPresetTextures[2]);
    loadTexture(PATH_START + "resources/textures/Circle.png", &Player::hitboxTexture);

    level = new GameLevel(Level1);
}

void GameWindow::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    
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
}

void GameWindow::update() {
    //bomb!
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        clearScreen();

    level->update();

    //update player, enemy, spawners, bullets
    player->update(window);
    for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
        enemy->update();
        for (int i = 0; i < enemy->spawners.size(); i++) {
            enemy->spawners[i]->update();
        }
    }
    for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
        bullet->update();
    }
    checkCollisions();

    //check for and destroy bullets with a true destroyed tag at the end
    if (Bullet::bullets.size() > 0) {
        
        Bullet::bullets.erase(std::remove_if(Bullet::bullets.begin(), Bullet::bullets.end(), [](const std::shared_ptr<Bullet>& bullet) {
            return bullet->destroyed;
        }), Bullet::bullets.end());
        
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
                std::cout << "Got hit :(" << std::endl;
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
    Bullet::bullets.clear();
}

void enemyTestFunc(Enemy* enemy) {
    //how to use void* like this?
    if (enemy->customFloats.size() <= 0) { 
        std::cout << "Custom Floats not initialized" << std::endl;
        return; 
    }
    float xpos = enemy->getPos().x;
    float spd = 10.0f;
    
    if (xpos <= -800.0f) {
        enemy->customFloats[0] = 1.0f;
    }
    if (xpos >= 800.0f) {
        enemy->customFloats[0] = -1.0f;
    }
    
    float dir = enemy->customFloats[0];
    //enemy->move(glm::vec2(dir * spd, 0.0f));
    
}

void bulletSpawnerTestFunc(BulletSpawner* spawner) {
    if ((int) (spawner->currTime) % 1 == 0) {
        
        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(1, spawner->pos, Bullet::directionalBullet);
        bullet->customFloats.push_back(10.0f);
        glm::vec2 dir{ sin(90 + 45 * spawner->currTime), cos(90 + 45 * spawner->currTime) };
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->setRotation(dir);
    }

    if ((int)(spawner->currTime) % 5 == 0 && (int) (spawner->currTime) % 100 != 5 && (int)(spawner->currTime) % 100 != 10) {
        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(0, spawner->pos, Bullet::directionalBullet);
        bullet->customFloats.push_back(20.0f);
        glm::vec2 dir = glm::normalize(GameWindow::player->getPos() - bullet->getPos());
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->setRotation(dir);
    }
}

void Level1(GameLevel* level) {
    float ct = level->currTime;
    if (ct == 30) {
        Hitbox enemyHitbox;
        enemyHitbox.type = HitboxType::Circle;
        enemyHitbox.radius = 50.0f;
        std::shared_ptr<Enemy> e = Enemy::makeEnemy(enemyHitbox, glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[0], enemyTestFunc);
        e->customFloats.push_back(1.0f);
        e->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestSpinning);
        /*
        std::shared_ptr<Enemy> e2 = Enemy::makeEnemy(enemyHitbox, glm::vec2(-500.0f, 500.0f), enemyTextures[0], enemyTestFunc);
        e2->customFloats.push_back(1.0f);
        e2->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);
        std::shared_ptr<Enemy> e3 = Enemy::makeEnemy(enemyHitbox, glm::vec2(500.0f, 500.0f), enemyTextures[0], enemyTestFunc);
        e3->customFloats.push_back(1.0f);
        e3->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);
        */
    }
}

void bulletSpawnerTestFunc2(BulletSpawner* spawner) {
    if ((int)(spawner->currTime) % 1 == 0) {

        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(0, spawner->pos, testFunc2);
        bullet->customFloats.push_back(10.0f);
        float angle = glm::radians(60 * spawner->currTime);
        glm::vec2 dir{ sin(angle), cos(angle) };
        dir = glm::normalize(dir);
        bullet->customFloats.push_back(spawner->pos.x);
        bullet->customFloats.push_back(spawner->pos.y);
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->setRotation(dir);
    }
}

void testFunc2(Bullet* b) {
    //speed, centerX, centerY, directionX, directionY

    glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
    glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x));
    glm::vec2 finalDir = glm::normalize(1.2f * spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]));

    if (b->currTime < 15) {
        b->move(glm::vec2(0.0f, -1.0f) * b->customFloats[0]);
    }
    else {
        b->move(finalDir * b->customFloats[0]);
    }
}

void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner) {
    if ((int)(spawner->currTime) % 1 == 0) {

        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(1, spawner->pos, testFunc2);
        bullet->customFloats.push_back(10.0f);
        float angle = glm::radians(63 * spawner->currTime);
        glm::vec2 dir{ sin(angle), cos(angle) };
        dir = glm::normalize(dir);
        bullet->customFloats.push_back(spawner->pos.x);
        bullet->customFloats.push_back(spawner->pos.y);
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->setRotation(dir);
    }
}

void spinningDirectionalBulletDisplay(Bullet* b) {
    //speed, centerX, centerY, directionX, directionY

    glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
    glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x));
    glm::vec2 finalDir = glm::normalize(spinDir * 1.05f + glm::vec2(b->customFloats[3], b->customFloats[4]));

    if (b->currTime < 15) {
        b->move(glm::vec2(b->customFloats[3], b->customFloats[4]) * b->customFloats[0]);
    }
    else {
        b->move(finalDir * b->customFloats[0]);
        b->setRotation(finalDir);
    }
}

void bulletSpawnerTestSpinning(BulletSpawner* spawner) {
    if ((int)(spawner->currTime) % 1 == 0) {

        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(1, spawner->pos, spinningDirectionalBullet);
        bullet->customFloats.push_back(10.0f);
        float angle = glm::radians(64.513f * spawner->currTime);
        glm::vec2 dir{ sin(angle), cos(angle) };
        dir = glm::normalize(dir);
        bullet->customFloats.push_back(spawner->pos.x);
        bullet->customFloats.push_back(spawner->pos.y);
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->setRotation(dir);
    }
}

void spinningDirectionalBullet(Bullet* b) {
    //speed, centerX, centerY, directionX, directionY

    glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
    glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x)) * (1 + b->currTime/500);
    glm::vec2 finalDir = spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]);

    if (b->currTime < 15) {
        b->move(glm::vec2(b->customFloats[3], b->customFloats[4]) * b->customFloats[0]);
    }
    else if (b->currTime < 360) {
        b->move(finalDir * b->customFloats[0]);
        b->setRotation(finalDir);
    }
    else if (b->currTime == 360) {
        b->customFloats.push_back(finalDir.x);
        b->customFloats.push_back(finalDir.y);
    }
    else {
        b->move(glm::vec2(b->customFloats[0] * glm::vec2(b->customFloats[5], b->customFloats[6])));
    }
}