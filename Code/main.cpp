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



extern std::string PATH_START = "";
GameWindow* gameWindow;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1500;

unsigned int Player::hitboxTexture;
unsigned int DropItem::itemTextures[10];
unsigned int Sprite::VAO;
std::shared_ptr<Player> GameWindow::player;
std::vector<std::shared_ptr<DropItem>> DropItem::dropItems;
std::vector<std::shared_ptr<Enemy>> Enemy::enemies;
std::vector<std::shared_ptr<Sprite>> Sprite::spriteList;
unsigned int BulletSpawner::bulletPresetTextures[10];
unsigned int GameWindow::enemyTextures[10];
std::vector<std::shared_ptr<Bullet>> Bullet::bullets;
const glm::vec2 GameWindow::normalized_coordinate_axes = glm::vec2(1000.0f, 1000.0f);
const float GameWindow::halfWidth = 800.0f;
const float GameWindow::halfHeight = 1000.0f;

struct stat info;

std::vector<float> frameRateLog;
int main() {
    if (stat("resources", &info) != 0) {
        std::cout << "Changed path";
        PATH_START = "../../";
    }
    else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
        PATH_START = "";
    else
        std::cout << "Welp something happened";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    std::cout << "Initializing GLFW window" << std::endl;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    wglSwapIntervalEXT(1.0f);
    Shader* s = Shader::makeShader(PATH_START+std::string("resources/shaders/SpriteShader_U.vert"), PATH_START+std::string("resources/shaders/SpriteShader_U.frag"));
    gameWindow = new GameWindow(window, s);
    float currFrame = glfwGetTime();

    bool debugMode = false;
    bool pressedP = false;
    bool pressedAdvance = false;
    bool canAdvance = false;
    while (!glfwWindowShouldClose(window)) {
        currFrame = glfwGetTime();
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            if (!pressedP) {
                pressedP = true;
                debugMode = !debugMode;
            }
        }
        else if (pressedP) {
            pressedP = false;
        }

        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
            if (!pressedAdvance) {
                pressedAdvance = true;
                canAdvance = true;

            }
        }
        else if (pressedAdvance) {
            pressedAdvance = false;
        }

        if (!canAdvance && debugMode) {
            continue;
        }
        canAdvance = false;
        gameWindow->update();
        //std::cout << glfwGetTime() - currFrame << " U " << Bullet::bullets.size() << std::endl;
        gameWindow->render();
        //std::cout << glfwGetTime() - currFrame << " R " << Bullet::bullets.size() << std::endl;
        if (glfwGetTime() - currFrame > 1000.0f / 60.0f) {
            std::cout << "FR: " << 1.0f / (glfwGetTime() - currFrame) << std::endl;
        }
        
        //_sleep(1000.0f / 60.0f - (glfwGetTime() - currFrame) - 0.06f);
        
        frameRateLog.push_back(glfwGetTime() - currFrame);
        if (frameRateLog.size() == 60) {
            float sum = 0;
            for (float v : frameRateLog) {
                sum += v;
            }
            std::cout << "TFR: " << 60/sum << " B: " << Bullet::bullets.size() << std::endl;
            frameRateLog.clear();
        }
        
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    float ratio = GameWindow::halfHeight / GameWindow::halfWidth;
    glViewport(width/2 - height/2 /ratio, 0, height/ratio, height);
}