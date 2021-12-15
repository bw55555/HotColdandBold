#pragma once
class GameWindow
{
	private:
		unsigned int playerTexture;
		GLFWwindow* window;
		Shader* shader;
	public:
		unsigned int playerVAO;
		GameWindow(GLFWwindow* w, Shader* s);
		void render();
		void update();
		void initialize();
		void loadTexture(const char* filePath, unsigned int* texturePointer);
};

