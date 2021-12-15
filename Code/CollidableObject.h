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
private:
    glm::vec3 pos;
public:
    //static std::vector<CollidableObject*> collList;
    bool collisionEnabled;
    Hitbox hitbox;
    CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1.0f, 1.0f, 1.0f), float rotation = 0.0f);
    CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1.0f, 1.0f, 1.0f), float rotation = 0.0f);
    bool checkCollision(CollidableObject* other);
    void move(glm::vec2 movement);
    glm::vec3 getPos();
};

