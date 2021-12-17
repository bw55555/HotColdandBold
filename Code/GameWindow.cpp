

#include "GameWindow.h"

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
    loadTexture("../../resources/textures/awesomeface.png", &playerTexture);
    Hitbox playerHitbox;
    playerHitbox.center = 0;
    //dosmth with the player hitbox
    player = new Player(playerHitbox, playerTexture);

    loadTexture("../../resources/textures/TouhouFairy.png", &enemyTextures[0]);
    std::shared_ptr<Enemy> e = Enemy::makeEnemy(playerHitbox, glm::vec2(-0.5, 0.5f), enemyTextures[0], enemyTestFunc);
    e->customFloats.push_back(1.0f);
    e->createBulletSpawner(glm::vec2(0,0), bulletSpawnerTestFunc);
    std::shared_ptr<Enemy> e2 = Enemy::makeEnemy(playerHitbox, glm::vec2(0, 0.5f), enemyTextures[0], enemyTestFunc);
    e2->customFloats.push_back(1.0f);
    e2->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);
    std::shared_ptr<Enemy> e3 = Enemy::makeEnemy(playerHitbox, glm::vec2(0.5, 0.5f), enemyTextures[0], enemyTestFunc);
    e3->customFloats.push_back(1.0f);
    e3->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);

    //note that we may end up needing to put all of these into a spritesheet and use another function to choose the right texture when drawing
    loadTexture("../../resources/textures/Bullet.png", &BulletSpawner::bulletPresetTextures[0]);
    loadTexture("../../resources/textures/Knife.png", &BulletSpawner::bulletPresetTextures[1]);
    loadTexture("../../resources/textures/PlayerBullet.png", &BulletSpawner::bulletPresetTextures[2]);
}

void GameWindow::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    
    for (std::shared_ptr<Sprite> sprite : Sprite::spriteList) {
        sprite->draw(shader); 
    }
    
    player->draw(shader);
    for (std::shared_ptr<Enemy> enemy : Enemy::enemies) {
        enemy->draw(shader);
    }
    
    for (std::shared_ptr<Bullet> bullet : Bullet::bullets) {
        bullet->draw(shader);
    }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void GameWindow::update() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        clearScreen();
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

void GameWindow::clearScreen() {
    Bullet::bullets.clear();
    Sprite::spriteList.clear();
}

void enemyTestFunc(Enemy* enemy) {
    //how to use void* like this?
    if (enemy->customFloats.size() <= 0) { 
        std::cout << "Custom Floats not initialized" << std::endl;
        return; }
    float xpos = enemy->getPos().x;
    float spd = 0.01f;
    
    if (xpos <= -0.8) {
        enemy->customFloats[0] = 1.0f;
    }
    if (xpos >= 0.8) {
        enemy->customFloats[0] = -1.0f;
    }
    
    float dir = enemy->customFloats[0];
    enemy->move(glm::vec2(dir * spd, 0.0f));
    
}

void bulletSpawnerTestFunc(BulletSpawner* spawner) {
    if ((int) (spawner->currTime) % 10 == 0) {
        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(0, glm::vec2(spawner->pos), Bullet::directionalBullet);
        bullet->customFloats.push_back(0.02f);
        bullet->customFloats.push_back(0.0f);
        bullet->customFloats.push_back(-1.0f);
        bullet.reset();
    }

    if ((int)(spawner->currTime) % 60 == 0) {
        std::shared_ptr<Bullet> bullet = spawner->spawnPreset(1, glm::vec2(spawner->pos), Bullet::directionalBullet);
        bullet->customFloats.push_back(0.02f);
        glm::vec2 dir = glm::normalize(glm::vec2(GameWindow::player->getPos() - spawner->pos));
        bullet->customFloats.push_back(dir.x);
        bullet->customFloats.push_back(dir.y);
        bullet->rotate(dir);
        bullet.reset();
    }
}

