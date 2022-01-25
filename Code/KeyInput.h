#pragma once
#include <unordered_map>
#include <memory>
#include <string>

class KeyInput {
public:
	typedef std::unordered_map<std::string, std::unique_ptr<KeyInput>> KeyMap;
	static KeyMap keys;
	static int currFrame;
	static void track(std::string keyName, int key, int inputDelay = -1);
	static void checkEvents();
	inline static bool isPressed(std::string keyName) { return isPressed(keyName, keys[keyName]->inputDelay); }
	static bool isPressed(std::string keyName, int _inputDelay, int repeatDelay = 1);

	int key;
	int lastRelease = 0;
	int lastPress = 0;
	int inputDelay;
	bool currentlyPressed = true;
	KeyInput(int _key, int _inputDelay);
	void update();
};