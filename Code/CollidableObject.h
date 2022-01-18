#pragma once

#include "Sprite.h"
#include "BulletMovement.h"

class GameWindow;

enum class DestroyReason { Timeout, Damage };

enum class HitboxType {Circle, Box, None};

enum class WallDirection { Left, Right, Up, Down, AnyHorizontal, AnyVertical, Any };

//yeah this is bad design but idc bite me
struct Hitbox {
    //note that the hitbox should be localized. 
    //So center is (0,0) means centered at the center of the CollidableObject.
    glm::vec2 center = glm::vec2(0,0);
    HitboxType type = HitboxType::Circle;
    float radius = 0; //only for circle
    glm::vec2 half_extents = glm::vec2(0, 0); //only for box
    static Hitbox Circle(float r) {
        Hitbox h;
        h.type = HitboxType::Circle;
        h.radius = r;
        return h;
    }
    static Hitbox Box(glm::vec2 _half_extents) {
        Hitbox h;
        h.type = HitboxType::Box;
        h.half_extents = _half_extents;
        return h;
    }
    static Hitbox None() {
        Hitbox h;
        h.type = HitboxType::None;
        return h;
    }
};

class CollidableObject :
    public Sprite
{
private:
    glm::vec2 pos;
public:
    virtual ~CollidableObject() {};
    bool collisionEnabled;
    Hitbox hitbox;
    CollidableObject(Hitbox collisionBox, glm::vec3 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
    CollidableObject(Hitbox collisionBox, glm::vec2 initialPos, unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), float rotation = 0.0f);
    bool checkCollision(Hitbox otherHitbox, glm::vec2 otherPos);
    bool checkCollision(CollidableObject* other);
    bool checkCollision(std::shared_ptr<CollidableObject> other);
    void move(glm::vec2 movement);
    void move(glm::vec2 movement, glm::vec4 clampBox);
    void moveTo(glm::vec2 dest, float numFramesLeft = 1);
    glm::vec2 rotateAround(glm::vec2 center, float angle);

    glm::vec2 getPos();
    void setPos(glm::vec2 aPos);
    float getX();
    float getY();

    bool touchingWall(WallDirection dir);
    Hitbox getHitbox() { return hitbox; };
};

