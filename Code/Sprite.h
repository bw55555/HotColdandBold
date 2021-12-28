#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>

class Shader; //included in cpp file

class Sprite
{
private:
	
public: 
	static unsigned int VAO;
	static std::vector<std::shared_ptr<Sprite>> spriteList;
	static std::shared_ptr<Sprite> makeSprite(unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	Sprite(unsigned int textureID, glm::vec3 scaling = glm::vec3(1000.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	unsigned int texture = 0;
	glm::vec3 scale;
	glm::vec3 trans;
	bool renderEnabled;
	float rot;
	void draw(Shader* shader);
	void rotate(float angle);
	void rotate(glm::vec2 dir);
	void setRotation(glm::vec2 dir);
	bool isOnScreen();
	~Sprite();
};

