#pragma once
#include "GameLevel.h"
#include "Movement.h"

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

//reduce time modulo n. Use this instead of c style casting time to an int
#define rt(obj, n) static_cast<float>(static_cast<int>(t(obj)) % static_cast<int>(n))

//every interval frames
#define every(obj, interval) if (obj->frameInterval(interval))

//every interval frames, with an offset
#define every2(obj, interval, offset) if (obj->frameInterval(interval, offset))

//better name plz...
//For Y frames Every X frames
#define fyex(obj, x, y) if (obj->frameInterval(x, 0, y))

//too bad no easy support for overloading macros... if someone wants to figure this out go ahead
//For Y frames Every X frames at Offset o
#define fyexo(obj, x, y, o) if (obj->frameInterval(x, o, y))

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

//do nothing for time frames. Does not increase the wait timer. 
#define sleep(obj, time) if (obj->wait(0, time)) {return;}

//do nothing for time frames. Increases the wait timer by time.
#define delay(obj, time) if (obj->wait(time)) {return;}

//do nothing until time frames. Increases the wait timer to time.
#define delayTo(obj, time) if (obj->waitUntil(time)) {return;}

//do this only once immediately (equivalent to wf(obj, 0))
#define once(obj) if (obj->wait(0))

/*
* ----------------
* BULLET FUNCTIONS
* ----------------
*/


//bullet ring, vname is the variable name to insert
#define nring(vname, num) for (float vname = 0; vname < 360.0; vname += 360.0f/num)

//bullet ring, vname is the variable name to insert, i is the index (also a variable name to insert)
#define nringi(vname, iname, num) for (float vname = 0, iname = 0; vname < 360.0; vname += 360.0f/num, iname+=1.0f)

//bullet stack, vname is the variable name to insert
#define nstack(vname, minspd, incr, num) for (float vname = minspd; vname<num * incr + minspd; vname += incr)

//bullet stack, vname is the variable name to insert, i is the index (also a variable name to insert)
#define nstacki(vname, iname, minspd, incr, num) for (float vname = minspd, iname = 0; vname<num * incr + minspd; vname += incr, iname+=1)

//bullet spread, vname is the variable name to insert, assumes num > 1
#define nspread(vname, center, range, num) for (float vname = center-range/2; vname < center + range/2 + range/num; vname += range/(num-1))

//bullet spread, vname is the variable name to insert, i is the index (also a variable name to insert) assumes num > 1
#define nspreadi(vname, iname, center, range, num) for (float vname = center-range/2, iname = 0; vname < center + range/2 + range/num; vname += range/(num-1), iname+=1)

#define rad glm::radians

//get vector from angle, i is the variable name to insert
#define avec(vname, angle) glm::vec2 vname{cos(angle), sin(angle)}

#define avecd(angle) glm::vec2(cos(rad(angle)), sin(rad(angle)))

//idk maybe I just want to be lazy
#define sfs [](BulletSpawner* s)
#define sf(name) [](BulletSpawner* name)