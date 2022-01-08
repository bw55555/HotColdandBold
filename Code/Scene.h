#pragma once

enum class SceneName { MainMenu, DifficultyMenu, Level1, Level2, Level3 };

class Scene {
public:
	virtual void initialize() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual ~Scene() {};
};