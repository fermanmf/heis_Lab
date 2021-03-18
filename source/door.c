#include <stdbool.h>
#include <sys/time.h>

#include "hardware.h"
#include "heis.h"
#include "bestilling.h"
#include "door.h"


static struct timeval t0;
static struct timeval t1;
static bool timerStarted= false;

bool d_timeIsUp = false;

static float timedifference(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec);
}

static void openDoor(){
    hardware_command_door_open(1);
};

 
void d_openTimedDoor(){
    if (h_stopPushed() || g_obstructed){
        timerStarted = false;
        d_timeIsUp = false;
        openDoor();
    }
    else{
        openDoor();
        d_timeIsUp = false;
        float elapsed = 0;
        gettimeofday(&t1,0);
        if (timerStarted){
            elapsed = timedifference(t0,t1);
        }
        if(!timerStarted){
            gettimeofday(&t0, 0);
            timerStarted = true;
        }
        else if (elapsed > 5){
            hardware_command_door_open(0);
            timerStarted = false;
            d_timeIsUp = true;
        }
    }
}