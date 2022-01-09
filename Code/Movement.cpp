#include "Movement.h"
#include <random>

float Movement::randomFloat(float low, float high) {
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

glm::vec2 Movement::randomDir(float minAngle, float maxAngle) {
    float angle = randomFloat(minAngle, maxAngle);
    return glm::vec2(cos(angle), sin(angle));
}

float Movement::linearBurst(float currTime, float initialVelocity, float deceleration, float maxTime) {
    float decelTime = initialVelocity / deceleration;
    //std::cout << decelTime << " " << currTime << " " << initialVelocity - deceleration * (currTime - (maxTime - decelTime)) << std::endl;
    if (currTime > maxTime) { return 0.0f; }
    else if (currTime > maxTime - decelTime) { return initialVelocity - deceleration * (currTime - (maxTime - decelTime)); }
    else if (currTime > 0) { return initialVelocity; }
    else { return 0.0f; }
}

float Movement::oscillate(float currTime, float min, float max, float spd, float startPos) {
    std::pair<float, float> boundspair = std::minmax(min, max);

    float rem = startPos + spd * currTime;
    float diff = boundspair.second - boundspair.first;
    int numWraps = floor(rem / diff);
    rem -= diff * numWraps;
    //std::cout << rem << " " << diff << " " << numWraps << std::endl;
    if (numWraps % 2 == 0) {
        return boundspair.first + rem;
    }
    else {
        return boundspair.second - rem;
    }
};

float Movement::linearAcceleration(float currTime, float acceleration, float maxVelocity, float maxTime, bool reverseFlag) {
    float accelTime = maxVelocity / acceleration;
    float dist = accelTime * accelTime * acceleration / 2;

    if (maxVelocity == -1.0f || currTime <= accelTime) {
        return currTime * currTime * acceleration / 2;
    }
    else if (maxTime == -1.0f || currTime <= accelTime + maxTime) {
        return dist + maxVelocity * (currTime - accelTime);
    }
    else if (currTime <= accelTime * 2 + maxTime) {
        float remTime = currTime - accelTime - maxTime;
        return dist + maxVelocity * maxTime + maxVelocity * remTime + 0.5 * (-acceleration) * remTime * remTime;
    }

    int laps = floor(currTime / (2 * accelTime + maxTime));
    float remTime = currTime - laps * (2 * accelTime + maxTime);
    if (laps % 2 == 1 && reverseFlag) {
        float extraDist = dist + maxVelocity * maxTime + dist;
        return extraDist - linearAcceleration(remTime, acceleration, maxVelocity, maxTime, reverseFlag);
    }

    float extraDist = reverseFlag ? 0 : laps * (2 * dist + maxVelocity * maxTime);
    return extraDist + linearAcceleration(remTime, acceleration, maxVelocity, maxTime, reverseFlag);
}