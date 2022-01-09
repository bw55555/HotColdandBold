#pragma once
#include "CollidableObject.h"

typedef struct GLFWwindow GLFWwindow;
class Shader;

class Player :
    public CollidableObject
{
public:
    static unsigned int hitboxTexture;
    bool focus = false;
    float speed;
    float currTime;
    float lastFired;
    float health;
    float invTimer;
    bool destroyed;
    Player(Hitbox collisionbox, unsigned int textureID);
    void checkMovement(GLFWwindow* window);
    void fire();
    void update(GLFWwindow* window);
    void drawHitbox(Shader* shader);
    void takeDamage();
    void destroy();
};

