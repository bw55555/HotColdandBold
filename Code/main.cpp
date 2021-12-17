#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameWindow.h"
#include <vector>
#include "BulletSpawner.h"
#include "Enemy.h"

GameWindow* gameWindow;
void loadTexture(const char* filePath, unsigned int* texturePointer, GLenum format);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int Sprite::VAO;
Player* GameWindow::player;
std::vector<std::shared_ptr<Enemy>> Enemy::enemies;
std::vector<std::shared_ptr<Sprite>> Sprite::spriteList;
unsigned int BulletSpawner::bulletPresetTextures[10];
unsigned int GameWindow::enemyTextures[10];
std::vector<std::shared_ptr<Bullet>> Bullet::bullets;


int main() {
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
    Shader s = Shader("../../resources/shaders/SpriteShader_U.vert", "../../resources/shaders/SpriteShader_U.frag");
    gameWindow = new GameWindow(window, &s);
    float currFrame = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {

        gameWindow->update();
        gameWindow->render();
        _sleep(1000.0f / 60.0f - (glfwGetTime() - currFrame));
        currFrame = glfwGetTime();
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
    glViewport(0, 0, width, height);
}