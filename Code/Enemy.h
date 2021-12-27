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
#include <memory>
#include "BulletSpawner.h"

#include "CollidableObject.h"
class Enemy :
    public CollidableObject, public std::enable_shared_from_this<Enemy>
{
public:
    static std::vector<std::shared_ptr<Enemy>> enemies;
    static std::shared_ptr<Enemy> makeEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    static std::shared_ptr<Enemy> findNearestEnemy(glm::vec2 pos);
    typedef void (*UpdateFunc)(Enemy*);
    UpdateFunc updatefunc;

    bool destroyed;

    std::vector<std::unique_ptr<BulletSpawner>> spawners;
    float currTime;
    Enemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    void update();
    void destroy();
    ~Enemy();
    void createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*));
};

