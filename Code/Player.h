#pragma once
#include "CollidableObject.h"

typedef struct GLFWwindow GLFWwindow;
class Shader;
class DropItem;

class Player :
    public CollidableObject
{
public:
    bool focus = false;
    float speed;
    float currTime;
    float lastFired;
    float health;
    float invTimer;
    bool destroyed;

    float bombs;
    Player(Hitbox collisionbox, unsigned int textureID);
    void initialize();
    void checkMovement(GLFWwindow* window);
    void fire();
    void update(GLFWwindow* window);
    void takeDamage();
    void destroy();

    void collect(DropItem* item);
};

