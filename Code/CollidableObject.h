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

namespace Movement {
    struct Direction {
        glm::vec2 dir;
        Direction() : dir(glm::vec2(0.0f, -1.0f)) {}
        Direction(float x, float y) { dir = glm::vec2(x, y); }
        Direction(glm::vec2 aDir) { dir = aDir; }
    };

    struct Speed {
        float spd;
        Speed() : spd(10.0f) {}
        Speed(float aSpd) { spd = aSpd; }
    };
}

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

    std::vector<float> customFloats;
    //use this if you want, not necessary
    glm::vec2 dir = glm::vec2(0.0f, -1.0f);
    //use this if you want, not necessary
    float speed = 10.0f;

    typedef Movement::Direction Direction;
    typedef Movement::Speed Speed;

    void initializeCustomVars(float x)
    {
        customFloats.push_back(x);
    }

    void initializeCustomVars(Direction x)
    {
        dir = x.dir;
    }

    void initializeCustomVars(Speed x)
    {
        speed = x.spd;
    }

    template<typename T, typename... Args>
    void initializeCustomVars(T x, Args... args) // recursive variadic function
    {
        initializeCustomVars(x);
        initializeCustomVars(args...);
    }

    glm::vec2 getPos();
    void setPos(glm::vec2 aPos);
    float getX();
    float getY();
};

