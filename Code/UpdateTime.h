#pragma once
#include "Movement.h"

template <class T>
class UpdateTime
{
private:
	float timeWaited = 0;
	float waitTime = 0;
	int numWaits = 0;
	int numWaitTrue = 0;
public:
	
	typedef void (*UpdateFunc)(T*);
	UpdateFunc updatefunc;
	std::vector<float> customFloats;
	//use this if you want, not necessary
	glm::vec2 dir = glm::vec2(0.0f, -1.0f);
	//use this if you want, not necessary
	float speed = 0.0f;

	glm::vec2 getVelocity() { return dir * speed; }
	void setVelocity(glm::vec2 vel) { dir = normalizeSafe(vel); speed = glm::length(vel); }

	void rotateDir(float angle) {
		float newAngle = glm::radians(angle) + getRadians(dir);
		dir = glm::vec2(glm::cos(newAngle), glm::sin(newAngle));
	}

	typedef Movement::Direction Direction;
	typedef Movement::Speed Speed;
	typedef Movement::Velocity Velocity;

	void initializeCustomVars(float x)
	{
		customFloats.push_back(x);
	}

	void initializeCustomVars(int x)
	{
		customFloats.push_back((float)x);
	}

	void initializeCustomVars(Velocity x)
	{
		setVelocity(x.vel);
	}

	void initializeCustomVars(Direction x)
	{
		dir = x.dir;
	}

	void initializeCustomVars(Speed x)
	{
		speed = x.spd;
	}

	void initializeCustomVars(glm::vec2 vec)
	{
		customFloats.push_back(vec.x);
		customFloats.push_back(vec.y);
	}
	template<typename T, typename... Args>
	void initializeCustomVars(T x, Args... args) // recursive variadic function
	{
		initializeCustomVars(x);
		initializeCustomVars(args...);
	}

	float currTime;
	bool shouldRun = true;
	
	UpdateTime(UpdateFunc func) {
		updatefunc = func;
		currTime = -1.0f;
		timeWaited = 0;
		numWaitTrue = 0;
	}

	void frameUpdate(T* derivedpointer) {
		currTime += 1.0f;
		triggerNum = 0;
		numWaits = 0;
		waitTime = 0;
		updatefunc(derivedpointer);
	}

	void setCurrentTime(float time) {
		currTime = time;
	}

	//do not nest waits. This will break things
	bool wait(float time, float numTrue = 1.0f) {
		assert(time >= 0);
		numWaits += 1;
		waitTime += time;
		//std::cout << currTime << " " << timeWaited << " " << numTrue << " " << numWaits << " " << numWaitTrue << "\n";
		if (currTime >= timeWaited + time && currTime >= waitTime && numWaits > numWaitTrue) {
			timeWaited += time;
			numWaitTrue += 1;
		}
		if (currTime >= waitTime && numTrue == -1.0f && numWaits <= numWaitTrue) {
			return shouldRun;
		}
		if (currTime < waitTime + numTrue && currTime >= waitTime && numWaits <= numWaitTrue) {
			return shouldRun;
		}
		else {
			return false;
		}
	}

	std::vector<float> triggerTimes;
	int triggerNum = 0;

	bool waitForTrigger(bool cond, float maxWaitTime) {
		//make sure this works properly when shouldRun is false
		triggerNum += 1;
		float wt = currTime - waitTime;
		if (triggerTimes.size() >= triggerNum) {
			maxWaitTime = triggerTimes[triggerNum - 1];
		}
		else if (shouldRun && cond) {
			maxWaitTime = std::clamp(wt, 0.0f, maxWaitTime);
		}
		bool res = wait(maxWaitTime);
		if (res) {
			triggerTimes.push_back(wt);
		}
		return res;
	}

	bool waitUntil(float time, float numTrue = 1.0f) {
		if (time < waitTime) { return false; }
		return wait(time - waitTime, numTrue);
	}

	bool runUntil(float time) {
		if (time < waitTime) { return false; }
		return wait(0, time - waitTime + 1);
	}

	void updateWaitTime(T* derivedpointer) {
		numWaitTrue = 0;
		shouldRun = false;
		updatefunc(derivedpointer);
		shouldRun = true;
	}

	void reInitializeTime() {
		triggerTimes.clear();
		triggerNum = 0;
		timeWaited = 0.0f;
		waitTime = 0.0f;
		numWaits = 0;
		numWaitTrue = 0;
		customFloats.clear();
		currTime = -1.0f;
		shouldRun = true;
	}

	float getNestedTime() {
		return currTime - timeWaited;
	}

	//try to use macro instead, its easier, or find a shorter name for this function
	inline bool frameInterval(int interval, int offset = 0, int numTrue = 1) {
		return shouldRun && ((int)currTime - offset) % interval >= 0 && ((int)currTime - offset) % interval < numTrue;
	}

	virtual ~UpdateTime() {};
};

