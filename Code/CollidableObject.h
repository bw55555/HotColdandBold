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

#include "Sprite.h"
struct Hitbox {
    int center;
    int bound;
};

class CollidableObject :
    public Sprite
{
public:
    //static std::vector<CollidableObject*> collList;
    bool collisionEnabled;
    Hitbox hitbox;
    CollidableObject(Hitbox collisionBox, unsigned int textureID, glm::vec3 scaling = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
    bool checkCollision(CollidableObject* other);
};

