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

    float overHeatTime;
    float superchargeHeatInstant;
    float superchargeHeatPermanent;
    float superchargeHeatMax;

    float noInstantHeatTimer;

    float deathbombTimer;

    int grazeAmount;
    bool destroyed;

    float bombs;

    int deaths;
    int bombsUsed;

    Player(Hitbox collisionbox, unsigned int textureID);
    void initialize();
    void checkMovement();
    void fire();
    void update();
    void takeDamage();
    void destroy();
    void respawn();
    void bomb();
    void addHeat(float amt);

    void collect(DropItem* item);
    bool checkGraze(Bullet* b);

    void useContinue();
};

