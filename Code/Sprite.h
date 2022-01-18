#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>

//class Shader; //forward declaration no longer needed

struct Hitbox;

//just for understandability
typedef glm::vec2 Scale;
typedef glm::vec2 Pos;

class Sprite
{
private:
	
public: 
	static unsigned int circleHitboxTexture;
	static unsigned int VAO;
	static unsigned int backgroundTextures[];
	static std::vector<std::shared_ptr<Sprite>> spriteList;
	static std::shared_ptr<Sprite> makeSprite(unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	Sprite(unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	unsigned int texture = 0;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 scale;
	glm::vec3 trans;
	bool renderEnabled;
	float rot;
	virtual void draw();
	virtual void draw(glm::mat4 customProjection) {};
	void rotate(float angle);
	void rotate(glm::vec2 dir);
	void setRotation(glm::vec2 dir);
	bool isOnScreen();
	virtual ~Sprite() {};
	virtual Hitbox getHitbox();
	void drawHitbox();
};

inline bool isZeroVec(glm::vec2 vec) {
	return vec == glm::vec2(0.0f, 0.0f);
}

inline glm::vec2 normalizeSafe(glm::vec2 dir) {
	return isZeroVec(dir) ? dir : glm::normalize(dir);
}

inline float getAngle(glm::vec2 vec) {
	return isZeroVec(vec) ? 0 : glm::degrees(glm::orientedAngle(glm::vec2(1, 0), glm::normalize(vec)));
}

inline float getRadians(glm::vec2 vec) {
	return isZeroVec(vec) ? 0 : glm::orientedAngle(glm::vec2(1, 0), glm::normalize(vec));
}