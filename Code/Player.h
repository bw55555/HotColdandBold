#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "CollidableObject.h"
class Player :
    public CollidableObject
{
public:
    float speed;
    float hMove;
    float vMove;

    Player(Hitbox collisionbox, unsigned int textureID);
    void checkMovement(GLFWwindow* window);
};

