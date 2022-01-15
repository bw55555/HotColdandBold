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

glm::vec2 Movement::followBezierCurve(float t, glm::vec2 start, glm::vec2 end, glm::vec2 control) {
    if (t >= 1) { return end; }
    if (t <= 0) { return start; }
    return (1 - t) * (1 - t) * start + 2.0f * t * (1 - t) * control + t * t * end;
}

float Movement::quickBurst(float currTime, float maxTime, float burstTime, float initialMult, float accel) {
    assert(maxTime >= burstTime);

    assert(accel != 0); // nonzero acceleration

    float accelTime = (1 - initialMult) / accel;

    assert(burstTime > accelTime); // make sure you slow down faster than burstTime or bad things happen
    
    if (currTime < 0) { return 0; }
    if (currTime > maxTime) { return 1; }

    float MburstTime = 0;
    

    MburstTime = currTime * initialMult + 0.5f * accel * currTime * currTime;

    float rt = 0;
    rt += std::min(currTime, burstTime - accelTime) * initialMult;
    if (currTime > burstTime - accelTime) {
        float t = (std::min(currTime, burstTime) - burstTime + accelTime);
        rt += (initialMult * t + 0.5f * accel * t * t);
    } 
    if (currTime > burstTime) {
        rt += (currTime - burstTime) / (maxTime - burstTime) * (maxTime - rt);
    }
    return rt / maxTime;
}

float Movement::cubic_bezier_time(float currTime, float maxTime, float v1, float v2, float v3, float v4) {
    float t = currTime / maxTime;
    if (t > 1) { return 1; }
    else if (t < 0) { return 0; }
    return (glm::vec2(0.0f, 0.0f) * pow(1-t, 3.0f) + glm::vec2(v1, v2) * 3.0f * pow(1-t, 2.0f) * t + glm::vec2(v3, v4) * 3.0f * (1-t) * pow(t, 2.0f) + glm::vec2(1, 1) * pow(t, 3.0f)).y;
}