#pragma once

#include "CollidableObject.h"
#include "UpdateTime.h"

enum class DropItemType {Red, Blue, Life};

class DropItem :
    public CollidableObject, public UpdateTime<DropItem>
{
public:
    static unsigned int itemTextures[10];
    static std::vector<std::shared_ptr<DropItem>> dropItems;
    static std::shared_ptr<DropItem> makeDropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling = glm::vec3(50.0f));
    static std::shared_ptr<DropItem> makeDropItem(DropItemType type, glm::vec2 pos);
    static void standardFunc(DropItem* item);

    DropItemType itemType;
    bool destroyed = false;
    bool autoCollected = false;

    DropItem(Hitbox collisionbox, glm::vec2 initialPos, DropItemType type, void (*func)(DropItem*), glm::vec3 scaling = glm::vec3(50.0f));
    void update();
    void destroy();
};

