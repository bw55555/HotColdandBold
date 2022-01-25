#include "GameWindow.h"
#include "Level1.h"
#include "Level2.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include "stb_image.h"
#include "Text.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "UI.h"
#include "PauseMenu.h"
#include "Audio.h"
#include "SoundEffect.h"
#include "GameOver.h"
#include "WinMenu.h"
#include "Credits.h"
#include <irrklang/irrKlang.h>

extern std::string PATH_START;

Settings GameWindow::settings;

Shader* GameWindow::shader;
Shader* GameWindow::rectShader;
Shader* GameWindow::screenShader;
Shader* GameWindow::textShader;

unsigned int GameWindow::playerTexture;

//unsigned int GameWindow::screenFBO;
//unsigned int GameWindow::screenFBOTexture;

GameWindow::GameWindow(GLFWwindow* w) {
	window = w;
    screenShader = nullptr;
    textShader = nullptr;
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
        0, 1, 2,
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
    
    
    loadTexture(PATH_START + "resources/textures/phoenix.png", &playerTexture);
    initializePlayer();

    //note that we may end up needing to put all of these into a spritesheet and use another function to choose the right texture when drawing
    loadTexture(PATH_START + "resources/textures/iceball.png", &BulletSpawner::bulletPresetTextures[0]);
    loadTexture(PATH_START + "resources/textures/icicle.png", &BulletSpawner::bulletPresetTextures[1]);
    loadTexture(PATH_START + "resources/textures/iceball2.png", &BulletSpawner::bulletPresetTextures[2]);
    loadTexture(PATH_START + "resources/textures/icicle2.png", &BulletSpawner::bulletPresetTextures[3]);
    loadTexture(PATH_START + "resources/textures/BallBlackBorder.png", &BulletSpawner::bulletPresetTextures[4]);
    loadTexture(PATH_START + "resources/textures/DotWhite.png", &BulletSpawner::bulletPresetTextures[5]);
    loadTexture(PATH_START + "resources/textures/RoundRed.png", &BulletSpawner::bulletPresetTextures[18]);
    loadTexture(PATH_START + "resources/textures/fireball.png", &BulletSpawner::bulletPresetTextures[19]);
    
    loadTexture(PATH_START + "resources/textures/Circle.png", &Sprite::circleHitboxTexture);
    loadTexture(PATH_START + "resources/textures/icevsfire.jpg", &Sprite::backgroundTextures[0]);
    loadTexture(PATH_START + "resources/textures/level1.jpg", &Sprite::backgroundTextures[1]);
    loadTexture(PATH_START + "resources/textures/level2.png", &Sprite::backgroundTextures[2]);

    loadTexture(PATH_START + "resources/textures/ringoffire.png", &AnimatedSprite::spriteTextures[0]);


    loadTexture(PATH_START + "resources/textures/sigil.png", &DropItem::itemTextures[0]);
    DropItem::itemTextures[1] = DropItem::itemTextures[0];
    loadTexture(PATH_START + "resources/textures/Life.png", &DropItem::itemTextures[2]);

    createEnemyTextures();
    
    Text::initializeFT();
    //scene = std::make_shared<GameLevel>(Level::Level1);
    loadScene(SceneName::MainMenu);
    
    glGenFramebuffers(1, &UI::fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, UI::fbo);

    

    glGenTextures(1, &UI::textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, UI::textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2 * halfWidth, 2 * halfHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, UI::textureColorbuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (!Audio::SoundEngine) {
        std::cout << "Failed to create Sound Engine";
    }

    //Audio::SoundEngine->addSoundSourceFromFile(std::string(PATH_START + "resources/audio/roar.mp3").c_str(), irrklang::ESM_AUTO_DETECT, true);

    mainLoopMusic = Audio::playSound("resources/audio/mainloop.mp3", true, true, 0.4f);

    /*
    glGenFramebuffers(1, &screenFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);



    glGenTextures(1, &screenFBOTexture);
    glBindTexture(GL_TEXTURE_2D, screenFBOTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2 * halfWidth, 2 * halfHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenFBOTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer2 is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    */
    
}

void GameWindow::render() {

    scene->render();
    glfwSwapBuffers(GameWindow::Instance->window);
    
}

void GameWindow::update() {
    scene->update();
    if (shouldLoadNextScene) {
        GameWindow::setWin(false);
        shouldLoadNextScene = false;
        if (settings.mode == GameMode::All) {
            switch (currScene) {
            case SceneName::Level1:
                GameWindow::Instance->loadScene(SceneName::Level2);
                break;
            case SceneName::Level2:
                GameWindow::Instance->loadScene(SceneName::Credits);
                break;
            }
        }
        else {
            GameWindow::Instance->loadScene(SceneName::LevelSelectMenu);
        }
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
    stbi_image_free(data);
}

void GameWindow::createEnemyTextures() {
    //This is not an ideal implementation! Simply a placeholder for now
    //Add more textures here as you make more enemies, but ideally we're looping through everything in a file
    loadTexture(PATH_START + "resources/textures/snowman.png", &enemyTextures[0]);
    loadTexture(PATH_START + "resources/textures/yeti.png", &enemyTextures[6]);
    loadTexture(PATH_START + "resources/textures/icedragon.png", &enemyTextures[7]);
}

void GameWindow::checkCollisions() {
    for (std::shared_ptr<Bullet> b : Bullet::bullets) {
        if (b->firedByPlayer) {
            for (std::shared_ptr<Enemy> e : Enemy::enemies) {
                if (e->checkCollision(std::static_pointer_cast<CollidableObject>(b))) {
                    //collision detected between enemy and player bullet, do something!
                    float ohmult = 1.0f + (player->overHeatTime > 0.0f) * 0.2f;
                    if (b->isPlayerHomingBullet) {
                        e->takeDamage(ohmult * dchoice(0.5f, 0.334f, 0.25f));
                        b->destroy();
                    }
                    else {
                        e->takeDamage(ohmult);
                        b->collisionEnabled = false;
                    }
                }
            }
        }
        else {
            if (player->checkCollision(std::static_pointer_cast<CollidableObject>(b))) {
                //Collision detected between player and enemy bullet, do something!
                //std::cout << "Got hit :(" << std::endl;
                b->destroy();
                player->takeDamage();
            }
            player->checkGraze(b.get());
        }
    }

    for (std::shared_ptr<Enemy> e : Enemy::enemies) {
        if (player->checkCollision(std::static_pointer_cast<CollidableObject>(e))) {
            //Collision detected between enemy and player, do something!
            player->takeDamage();
        }
    }

    for (std::shared_ptr<DropItem> d : DropItem::dropItems) {
        if (player->checkCollision(std::static_pointer_cast<CollidableObject>(d))) {
            //Collision detected between enemy and player, do something!
            player->collect(d.get());
        }
    }
}

void GameWindow::clearScreen() {
    clearBullets();
    clearEnemies();
}

void GameWindow::clearEnemies() {
    for (std::shared_ptr<Enemy> e : Enemy::enemies) {
        e->destroy();
    }
}

void GameWindow::clearBullets() {
    for (std::shared_ptr<Bullet> b : Bullet::bullets) {
        b->destroy();
    }
}

void GameWindow::initializePlayer() {
    Hitbox playerHitbox;
    playerHitbox.type = HitboxType::Circle;
    playerHitbox.radius = 8.0f;
    //dosmth with the player hitbox
    player = std::make_shared<Player>(playerHitbox, playerTexture);
}

void GameWindow::loadScene(SceneName name) {
    currScene = name; 
    Enemy::enemies.clear();
    Bullet::bullets.clear();
    DropItem::dropItems.clear();
    Sprite::spriteList.clear();
    switch (name) {
    case SceneName::MainMenu:
        scene = std::make_shared<MainMenu>();
        break;
    case SceneName::DifficultyMenu:
        scene = std::make_shared<DifficultyMenu>();
        break;
    case SceneName::LevelSelectMenu:
        scene = std::make_shared<LevelSelectMenu>();
        break;
    case SceneName::SettingsMenu:
        scene = std::make_shared<SettingsMenu>();
        break;
    case SceneName::Level1:
        scene = std::make_shared<GameLevel>(Level::Level1);
        break;
    case SceneName::Level2:
        scene = std::make_shared<GameLevel>(Level::Level2);
        break;
    case SceneName::Level3:
        //scene = std::make_shared<GameLevel>(Level::Level1);
        break;
    case SceneName::Credits:
        scene = std::make_shared<Credits>();
        break;
    }
}

void GameWindow::startGame(Difficulty d, GameMode g) {
    settings.difficulty = d;
    settings.mode = g;
    player->initialize();
    switch (settings.mode) {
    case GameMode::All:
    case GameMode::Prac1:
        loadScene(SceneName::Level1);
        break;
    case GameMode::Prac2:
        loadScene(SceneName::Level2);
        break;
    case GameMode::Prac3:
        loadScene(SceneName::Level3);
        break;
    }
}

void GameWindow::quit() { glfwSetWindowShouldClose(GameWindow::Instance -> window, true); }

void GameWindow::setPause(bool _pause) {
    paused = _pause;
    if (_pause == false) {
        pauseMenu = nullptr;
    }
    if (_pause == true) {
        pauseMenu = std::make_shared<PauseMenu>();
    }
}

void GameWindow::setLost(bool dead) {
    paused = dead;
    over = dead;
    if (over == false) {
        overMenu = nullptr;
    }
    if (over) {
        overMenu = std::make_shared<GameOver>();
    }
}

void GameWindow::setWin(bool win) {
    paused = win;
    won = win;
    if (won) {
        winMenu = std::make_shared<WinMenu>();
    }
    else {
        winMenu = nullptr;
    }
}

void GameWindow::setCredits(bool cred) {
    paused = cred;
    credit = cred;
    if (credit) {
        credits = std::make_shared<Credits>();
    }
    else {
        credits = nullptr;
    }
}

void GameWindow::undeadify() {
    if (player->continues > 0) {
        player->useContinue();
        setLost(false);
    }
}

void GameWindow::mainMenu() {
    setLost(false);
    GameWindow::Instance->loadScene(SceneName::MainMenu);
}

void GameWindow::restart() {
    setLost(false);
    GameWindow::Instance->loadScene(SceneName::Level1);
}