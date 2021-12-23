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

#include "CollidableObject.h"

enum class DropItemType {Red, Blue};

class DropItem :
    public CollidableObject
{
public:
    static unsigned int itemTextures[10];
    static std::vector<std::shared_ptr<DropItem>> dropItems;
    static std::shared_ptr<DropItem> makeDropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling = glm::vec3(50.0f));
    static std::shared_ptr<DropItem> DropItem::makeDropItem(DropItemType type);
    static void standardFunc(DropItem* item);

    typedef void (*UpdateFunc)(DropItem*);
    UpdateFunc updatefunc;
    std::vector<float> customFloats;

    DropItemType itemType;
    float currTime;
    bool destroyed = false;
    DropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling = glm::vec3(50.0f));
    void update();
    void destroy();
};
