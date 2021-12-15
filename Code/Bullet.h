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
class Bullet :
    public CollidableObject
{
public:
    static std::vector<Bullet*> bullets;

    typedef void (*UpdateFunc)(Bullet*);
    UpdateFunc updatefunc;
    
    float currTime;

    Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*));
    void update();
};

