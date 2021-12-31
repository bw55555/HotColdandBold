#pragma once
#include "GameLevel.h"
#include "Movement.h"

//do not include this file in another header file...
//please do not use namespace std... you will probably break some of these macros

//better name plz...
//For Y frames Every X frames
#define fyex(obj, x, y) if (obj->frameInterval(x, 0, y))

//every interval frames
#define every(obj, interval) if (obj->frameInterval(interval))

//wait for
#define wf(obj, time) if (obj->wait(time))

//wait for, returns true n times
#define wf2(obj, time, n) if (obj->wait(time, n))

//wait until
#define wu(obj, time) if (obj->waitUntil(time))

//wait until, returns true n times
#define wu2(obj, time, n) if (obj->waitUntil(time, n))

//returns true for n frames
#define during(obj, time) if (obj->wait(0, time))

#define forever(obj) if (obj->wait(0, -1.0f))

//bullet ring, vname is the variable name to insert
#define nring(vname, num) for (float vname = 0; vname < 360.0; vname += 360.0f/num)

//bullet stack, vname is the variable name to insert
#define nstack(vname, minspd, incr, num) for (float vname = minspd; vname<num * incr + minspd; vname += incr)

//unfortunate that you cant declare i as an int but it'll have to do
#define nstacki(vname, i, minspd, incr, num) for (float vname = minspd, i = 0; vname<num * incr + minspd; vname += incr, i+=1)

//bullet spread, vname is the variable name to insert, assumes num > 1
#define nspread(vname, center, range, num) for (float vname = center-range/2; vname < center + range/2 + range/num; vname += range/(num-1))

#define rad glm::radians

//get vector from angle, i is the variable name to insert
#define avec(vname, angle) glm::vec2 vname{cos(angle), sin(angle)}

#define avecd(angle) glm::vec2(cos(rad(angle)), sin(rad(angle)))

//idk maybe I just want to be lazy
#define sfs [](BulletSpawner* s)
#define sf(name) [](BulletSpawner* name)


#define t(obj) obj->currTime

//reduce time
#define rt(obj, n) static_cast<float>(static_cast<int>(t(obj)) % static_cast<int>(n))

#define initwait(obj, time) if (t(obj) < static_cast<float>(time)) {return;}

#define onStart(obj) if (t(obj) == 1.0f)