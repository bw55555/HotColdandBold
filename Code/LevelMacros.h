#pragma once
#include "GameLevel.h"
#include "Movement.h"
#include <tuple>

//do not include this file in another header file...
//please do not use namespace std... you will probably break some of these macros

/*
* --------------
* TIME FUNCTIONS
* --------------
*/

//time (in number of frames)
#define t(obj) obj->currTime


//time (in number of frames) as an integer
#define ti(obj) static_cast<int>(obj->currTime)


//time (in number of frames) inside the wait. Will be 0 first time the wait is executed. 
#define nt(obj) obj->getNestedTime()


//reduce time modulo n. Use this instead of c style casting time to an int
#define rt(obj, n) static_cast<float>(static_cast<int>(t(obj)) % static_cast<int>(n))


//every interval frames
#define every(obj, interval) if (obj->frameInterval(interval))


//every interval frames, with an offset
#define everyo(obj, interval, offset) if (obj->frameInterval(interval, offset))


//every interval frames, declaring reduced time as reducedTimeName
#define rtevery(obj, reducedTimeName, interval) if (float reducedTimeName = rt(obj, interval); obj->frameInterval(interval))


//every interval frames, with an offset, declaring reduced time as reducedTimeName
#define rteveryo(obj, reducedTimeName, interval, offset) if (float reducedTimeName = rt(obj, interval); obj->frameInterval(interval, offset))


//better name plz...
//For Y frames Every X frames
#define fyex(obj, x, y) if (obj->frameInterval(x, 0, y))


//too bad no easy support for overloading macros... if someone wants to figure this out go ahead
//For Y frames Every X frames at Offset o
#define fyexo(obj, x, y, o) if (obj->frameInterval(x, o, y))


//For Y frames Every X frames, declaring reduced time
#define rtfyex(obj, reducedTimeName, x, y) if (float reducedTimeName = rt(obj, x); obj->frameInterval(x, 0, y))


//For Y frames Every X frames at Offset o, declaring reduced time
#define rtfyexo(obj, reducedTimeName, x, y, o) if (float reducedTimeName = rt(obj, x); obj->frameInterval(x, o, y))


//to make timecurves easier to use, expr should return a float between 0 and 1
#define addTC(timeCurveObj, _maxTime, timeCurvePart, exprTimeVar, expr) {float maxTime = _maxTime; float exprTimeVar = maxTime; float maxTCPartEvalTime = expr; exprTimeVar = std::clamp(timeCurveObj.TCcurrTime, 0.0f, static_cast<float>(maxTime)); timeCurveObj.TCcurrTime -= static_cast<float>(maxTime); timeCurveObj.TCreturnTime += static_cast<float>(timeCurvePart) * static_cast<float>(expr) / maxTCPartEvalTime;}


//with constexpr, to make timecurves easier to use
//#define addTC(timeCurveObj, maxTime, timeCurvePart, exprTimeVar, expr) {float exprTimeVar = std::clamp(timeCurveObj.TCcurrTime, 0.0f, static_cast<float>(maxTime)); timeCurveObj.TCcurrTime -= static_cast<float>(maxTime); {const exprTimeVar = maxTime; constexpr maxTCEvaluatedTime = expr; timeCurveObj.TCreturnTime += static_cast<float>(timeCurvePart) * static_cast<float>(expr) / static_cast<float>(maxTime);}}


/*
* --------------
* WAIT FUNCTIONS
* --------------
* Wait functions use something I call a wait timer.
* This is basically the amount of time the program needs to wait until the next set of instructions can execute.
* It is easier to explain with an example, but increasing the wait timer at a line will increase the time needed for all lines after it to execute.
* Most of these functions are if statements, so you should provide your own braces. (only t, ti, and rt are not)
* Any statement outside one of the waiting functions will be executed every frame, so be careful.
* Wait functions should only be top level (aka every wait function should run every frame) or something will break.
* The macros should provide basically every general functionality you can think of, but in case it doesn't, you can manually do it or add a new macro.
*/


//wait for. Increases the wait timer **by** time. 
#define wf(obj, time) if (obj->wait(time))


//wait for, returns true n times. Increases the wait timer **by** time. 
#define wf2(obj, time, n) if (obj->wait(time, n))


//wait for trigger at most maxWaitTime frames
#define wft(obj, cond, maxWaitTime) if (obj->waitForTrigger(cond, maxWaitTime))


// delay minWaitTime, then wait for trigger at most maxWaitTime frames
#define wfmt(obj, cond, minWaitTime, maxWaitTime) delay(obj, minWaitTime); if (obj->waitForTrigger(cond, maxWaitTime - minWaitTime))


//wait until. Increases the wait timer **to** time. 
#define wu(obj, time) if (obj->waitUntil(time))


//wait until, returns true for n frames. Increases the wait timer **to** time. 
#define wu2(obj, time, n) if (obj->waitUntil(time, n))


//returns true forever. Does not increase the wait timer
#define forever(obj) if (obj->wait(0, -1.0f))


//returns true for n frames. Does not increase the wait timer
#define during(obj, n) if (obj->wait(0, n))


//returns true until time. Does not increase the wait timer
#define until(obj, time) if (obj->runUntil(time))


//returns true forever after time frames.
#define after(obj, time) if (obj->wait(time, -1.0f))


//returns true once after time frames. does not increase the wait timer.
#define when(obj, time) if (obj->wait(0, time) && nt(obj) == (time)-1)


//do nothing for time frames. Increases the wait timer by time.
#define delay(obj, time) if (obj->wait(time)) {}


//do nothing until time frames. Increases the wait timer to time.
#define delayTo(obj, time) if (obj->waitUntil(time)) {return;}


//delay until trigger
#define delayTrigger(obj, cond, maxWaitTime) if (obj->waitForTrigger(cond, maxWaitTime)) {}


//delay at least minWaitTime time, then delay until trigger
#define delayMinTrigger(obj, cond, minWaitTime, maxWaitTime) delay(obj, minWaitTime); if (obj->waitForTrigger(cond, maxWaitTime - minWaitTime)) {}


//delay until enemy wave is cleared
#define delayClear(obj, minWaitTime, maxWaitTime) delay(obj, minWaitTime); if (obj->waitForTrigger(Enemy::enemies.size() == 0, maxWaitTime - minWaitTime)) {}


//do this only once immediately (equivalent to wf(obj, 0))
#define once(obj) if (obj->wait(0))


//move over time to the destination. Does not increase wait timer.
#define mot(obj, dest, numFrames) during(obj, numFrames) {obj->moveTo(dest, numFrames - nt(obj));}


//move over time to the destination. Increases wait timer by numFrames. 
#define motw(obj, dest, numFrames) mot(obj, dest, numFrames) delay(obj, numFrames)


/*
* ----------------
* BULLET FUNCTIONS
* ----------------
*/


//standard repeating
#define nrep(vname, num) for (float vname = 0; vname < num; vname += 1)


//bullet ring, vname is the variable name to insert
#define nring(vname, num) for (float vname = 0; vname < 360.0f; vname += 360.0f/(num))


//bullet ring, vname is the variable name to insert, i is the index (also a variable name to insert)
#define nringi(vname, iname, num) for (auto [vname, iname] = std::tuple{0.0f, 0}; vname < 360.0f; vname += 360.0f/(num), iname+=1)


//bullet stack, vname is the variable name to insert
#define nstack(vname, minspd, incr, num) for (float vname = minspd; vname<(num) * (incr) + (minspd); vname += incr)


//bullet stack, vname is the variable name to insert, i is the index (also a variable name to insert)
#define nstacki(vname, iname, minspd, incr, num) for (auto [vname, iname] = std::tuple{(minspd), 0}; vname<(num) * (incr) + (minspd); vname += incr, iname+=1)


//bullet spread, vname is the variable name to insert, assumes range > 0, num > 0
#define nspread(vname, center, range, num) for (float vname = (center)- (num > 1) * (range)/2; vname < (center) + (range)/2 + (range)/(num); vname += (num) <= 1 ? 2 * (range) : (range)/((num)-1))


//bullet spread, vname is the variable name to insert, i is the index (also a variable name to insert) assumes num > 1
#define nspreadi(vname, iname, center, range, num) for (auto [vname, iname] = std::tuple{(center)-(range)/2, 0}; vname < (center) + (range)/2 + (range)/(num); vname += (range)/((num)-1), iname+=1)


#define rad glm::radians


//declares a vector2 from angle, i is the variable name to insert
#define avec(vname, angle) glm::vec2 vname{cos(angle), sin(angle)}


//get vector from angle in degrees, is not a declaration. 
#define avecd(angle) glm::vec2(cos(rad(static_cast<float>(angle))), sin(rad(static_cast<float>(angle))))


//idk maybe I just want to be lazy
#define sfs [](BulletSpawner* s)
#define sf(name) [](BulletSpawner* name)


#define cf(obj, num) obj->customFloats[num]

