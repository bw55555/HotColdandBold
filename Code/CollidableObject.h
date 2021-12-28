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
#include "BulletMovement.h"

class GameWindow;

enum class HitboxType {Circle, Box};

//yeah this is bad design but idc bite me
struct Hitbox {
    //note that the hitbox should be localized. 
    //So center is (0,0) means centered at the center of the CollidableObject.
    glm::vec2 center = glm::vec2(0,0);
    HitboxType type = HitboxType::Circle;
    float radius = 0; //only for circle
    glm::vec2 half_extents = glm::vec2(0, 0); //only for box
};

class CollidableObject :
    public Sprite
{
private:
    glm::vec2 pos;
public:
    bool collisionEnabled;
    Hitbox hitbox;
    CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
    CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
    bool checkCollision(CollidableObject* other);
    bool checkCollision(std::shared_ptr<CollidableObject> other);
    void move(glm::vec2 movement);
    void move(glm::vec2 movement, glm::vec4 clampBox);

    glm::vec2 getPos();
    void setPos(glm::vec2 aPos);
    float getX();
    float getY();
};

