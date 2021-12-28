#pragma once

namespace Movement {
	struct Direction {
		glm::vec2 dir;
		Direction() : dir(glm::vec2(0.0f, -1.0f)) {}
		Direction(float x, float y) { dir = glm::vec2(x, y); }
		Direction(glm::vec2 aDir) { dir = aDir; }
	};

	struct Speed {
		float spd;
		Speed() : spd(10.0f) {}
		Speed(float aSpd) { spd = aSpd; }
	};
}

template <class T>
class UpdateTime
{
public:
	typedef void (*UpdateFunc)(T*);
	UpdateFunc updatefunc;
	std::vector<float> customFloats;
	//use this if you want, not necessary
	glm::vec2 dir = glm::vec2(0.0f, -1.0f);
	//use this if you want, not necessary
	float speed = 10.0f;

	typedef Movement::Direction Direction;
	typedef Movement::Speed Speed;

	void initializeCustomVars(float x)
	{
		customFloats.push_back(x);
	}

	void initializeCustomVars(Direction x)
	{
		dir = x.dir;
	}

	void initializeCustomVars(Speed x)
	{
		speed = x.spd;
	}

	template<typename T, typename... Args>
	void initializeCustomVars(T x, Args... args) // recursive variadic function
	{
		initializeCustomVars(x);
		initializeCustomVars(args...);
	}

	float currTime;
	float waitTime;
	int numWaits = 0;
	int numWaitTrue = 0;
	bool shouldRun = false;
	
	UpdateTime(UpdateFunc func) {
		updatefunc = func;
		currTime = 0;
		waitTime = 0;
	}

	void frameUpdate(T* derivedpointer) {
		currTime += 1.0f;
		numWaits = 0;
		updatefunc(derivedpointer);
	}

	void setCurrentTime(float time) {
		currTime = time;
	}
	bool wait(float time, float numTrue = 1.0f) {
		numWaits += 1;
		if (currTime >= time + waitTime && numWaits > numWaitTrue) {
			waitTime += time;
			numWaitTrue += 1;
		}
		//std::cout << currTime << " " << waitTime << std::endl;
		if (currTime < waitTime + numTrue && currTime >= waitTime && numWaits <= numWaitTrue) {
			return true;
		}
		else {
			return false;
		}
	}
	bool waitUntil(float time, float numTrue = 1.0f) {
		numWaits += 1;
		if (currTime >= time && numWaits > numWaitTrue) {
			waitTime = time;
			numWaitTrue += 1;
		}
		//std::cout << currTime << " " << waitTime << std::endl;
		if (currTime < waitTime + numTrue && currTime >= waitTime && numWaits <= numWaitTrue) {
			return shouldRun;
		}
		else {
			return false;
		}
	}
	void updateWaitTime(T* derivedpointer) {
		shouldRun = false;
		updatefunc(derivedpointer);
		shouldRun = true;
	}
};

