#pragma once
#include "CollidableObject.h"

typedef struct GLFWwindow GLFWwindow;
class Shader;

class Player :
    public CollidableObject
{
public:
    bool focus = false;
    float speed;
    float currTime;
    float lastFired;
    Player(Hitbox collisionbox, unsigned int textureID);
    void checkMovement(GLFWwindow* window);
    void fire();
    void update(GLFWwindow* window);
};

