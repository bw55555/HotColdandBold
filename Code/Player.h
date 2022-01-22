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
    float lastHomingFired;
    float health;
    float invTimer;
    float heat;
    int continues;
    int level;

    int grazeAmount;
    bool destroyed;

    float bombs;
    Player(Hitbox collisionbox, unsigned int textureID);
    void initialize();
    void checkMovement();
    void fire();
    void update();
    void takeDamage();
    void destroy();
    void respawn();
    void bomb();

    void collect(DropItem* item);
    bool checkGraze(Bullet* b);
};

