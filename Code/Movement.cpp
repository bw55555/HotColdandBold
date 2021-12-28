#include "Movement.h"

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