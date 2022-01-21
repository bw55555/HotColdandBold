#include <windows.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <numeric>
#include <functional>
#include "GameWindow.h"
#include "KeyInput.h"
#include "UIRect.h"
#include "BossEnemy.h"
#include "Audio.h"
#include <irrklang/irrKlang.h>

extern std::string PATH_START = "";
std::shared_ptr<GameWindow> gameWindow;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int mainloop();

irrklang::ISoundEngine* Audio::SoundEngine = irrklang::createIrrKlangDevice();

std::unique_ptr<Sprite> BossEnemy::bossHealthBar = nullptr;
KeyInput::KeyMap KeyInput::keys;
int KeyInput::currFrame = -1;
std::shared_ptr<GameWindow> GameWindow::Instance;
unsigned int Sprite::circleHitboxTexture;
unsigned int DropItem::itemTextures[10];
unsigned int Sprite::VAO;
unsigned int UIRect::UIVAO;
std::shared_ptr<Player> GameWindow::player;
std::vector<std::shared_ptr<DropItem>> DropItem::dropItems;
std::vector<std::shared_ptr<Enemy>> Enemy::enemies;
std::vector<std::shared_ptr<Sprite>> Sprite::spriteList;
unsigned int BulletSpawner::bulletPresetTextures[20];
unsigned int Sprite::backgroundTextures[10];
unsigned int GameWindow::enemyTextures[10];
std::vector<std::shared_ptr<Bullet>> Bullet::bullets;
glm::vec2 GameWindow::screenSize;
const float GameWindow::halfWidth = 800.0f;
const float GameWindow::halfHeight = 1000.0f;

struct stat info;

float frameRateLog[60];
int currFrameNum = 0;
float currFrameRateSum = 1.0f;

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    return mainloop();
}

int main() {
    return mainloop();
}



int mainloop() {
    for (int i = 0; i < 60; i++) {
        frameRateLog[i] = 1.0f / 60.0f;
    }

    if (stat("resources", &info) != 0) {
        std::cout << "Changed path";
        PATH_START = "../../";
    }
    else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
        PATH_START = "";
    else
        std::cout << "Welp something happened and the path is not recognized";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    std::cout << "Initializing GLFW window" << std::endl;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(UI::UIsize.x / 2, UI::UIsize.y / 2, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    if (!gladLoadWGLLoader((GLADloadproc)wglGetProcAddress, wglGetCurrentDC()))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    wglSwapIntervalEXT(1.0f);
    Shader* s = Shader::makeShader(PATH_START + std::string("resources/shaders/SpriteShader_U.vert"), PATH_START + std::string("resources/shaders/SpriteShader_U.frag"));
    Shader* screenShader = Shader::makeShader(PATH_START + std::string("resources/shaders/ScreenShader.vert"), PATH_START + std::string("resources/shaders/ScreenShader.frag"));
    Shader* textShader = Shader::makeShader(PATH_START + std::string("resources/shaders/TextShader.vert"), PATH_START + std::string("resources/shaders/TextShader.frag"));
    Shader* rectShader = Shader::makeShader(PATH_START + std::string("resources/shaders/RectShader.vert"), PATH_START + std::string("resources/shaders/RectShader.frag"));
    gameWindow = std::make_shared<GameWindow>(window);
    GameWindow::shader = s;
    GameWindow::screenShader = screenShader;
    GameWindow::textShader = textShader;
    GameWindow::rectShader = rectShader;
    GameWindow::screenSize = UI::UIsize / 2.0f;
    float ratio = UI::UIsize.y / UI::UIsize.x;
    glViewport(GameWindow::screenSize.x / 2 - GameWindow::screenSize.y / 2 / ratio, 0, GameWindow::Instance->screenSize.y / ratio, GameWindow::Instance->screenSize.y);
    UIRect::initializeVAO();
    GameWindow::Instance = gameWindow;
    float currFrame = glfwGetTime();

    bool debugMode = false;
    bool canAdvance = false;



    KeyInput::track("ESC", GLFW_KEY_ESCAPE, 1000000);
    KeyInput::track("P", GLFW_KEY_P, 1000000);
    KeyInput::track("PERIOD", GLFW_KEY_PERIOD, 20000);
    KeyInput::track("DOWN", GLFW_KEY_DOWN, -1);
    KeyInput::track("UP", GLFW_KEY_UP, -1);
    KeyInput::track("LEFT", GLFW_KEY_LEFT, -1);
    KeyInput::track("RIGHT", GLFW_KEY_RIGHT, -1);
    KeyInput::track("Z", GLFW_KEY_Z, -1);
    KeyInput::track("X", GLFW_KEY_X, 1000000);
    KeyInput::track("ENTER", GLFW_KEY_ENTER, 1000000);
    KeyInput::track("LSHIFT", GLFW_KEY_LEFT_SHIFT, -1);
    KeyInput::track("A", GLFW_KEY_A, 1000000);
    KeyInput::track("S", GLFW_KEY_S, 1000000);
    KeyInput::track("D", GLFW_KEY_D, 1000000);
    KeyInput::track("W", GLFW_KEY_W, 1000000);
    KeyInput::track("-", GLFW_KEY_MINUS, 1000000);
    KeyInput::track("=", GLFW_KEY_EQUAL, 1000000);
    KeyInput::track("`", GLFW_KEY_GRAVE_ACCENT, 1000000);
    KeyInput::track("0", GLFW_KEY_0, 1000000);
    KeyInput::track("1", GLFW_KEY_1, 1000000);
    KeyInput::track("2", GLFW_KEY_2, 1000000);
    KeyInput::track("3", GLFW_KEY_3, 1000000);
    KeyInput::track("4", GLFW_KEY_4, 1000000);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        currFrame = glfwGetTime();
        glfwPollEvents();
        KeyInput::checkEvents();
        if (KeyInput::isPressed("P")) {
            debugMode = !debugMode;
        }

        if (KeyInput::isPressed("PERIOD", 60)) {
            canAdvance = true;
        }
        WindowVar::updatewvar();
        if (canAdvance || !debugMode) {
            canAdvance = false;
            gameWindow->update();
        }
        else if (KeyInput::isPressed("ESC")) {
            GameWindow::Instance->quit();
        }

        //std::cout << glfwGetTime() - currFrame << " U " << Bullet::bullets.size() << std::endl;
        gameWindow->render();
        //std::cout << glfwGetTime() - currFrame << " R " << Bullet::bullets.size() << std::endl;
        if (glfwGetTime() - currFrame > 1000.0f / 60.0f) {
            std::cout << "FR: " << 1.0f / (glfwGetTime() - currFrame) << std::endl;
        }

        //_sleep(1000.0f / 60.0f - (glfwGetTime() - currFrame) - 0.06f);
        currFrameRateSum -= frameRateLog[currFrameNum];
        frameRateLog[currFrameNum] = glfwGetTime() - currFrame;
        currFrameRateSum += frameRateLog[currFrameNum];
        currFrameNum += 1;
        GameWindow::Instance->frameRate = 60.0f / currFrameRateSum;
        if (currFrameNum == 60) {
            currFrameNum = 0;
            std::cout << "TFR: " << GameWindow::Instance->frameRate << " B: " << Bullet::bullets.size() << std::endl;
        }

    }

    Audio::dropEngine();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    GameWindow::screenSize = glm::vec2(width, height);
    float ratio = UI::UIsize.y / UI::UIsize.x;
    glViewport(GameWindow::screenSize.x / 2 - GameWindow::screenSize.y / 2 / ratio, 0, GameWindow::Instance->screenSize.y / ratio, GameWindow::Instance->screenSize.y);
}