#include <stdbool.h>
#include <sys/time.h>

#include "hardware.h"
#include "heis.h"
#include "bestilling.h"
#include "door.h"


static struct timeval t0;
static struct timeval t1;
static bool timerStarted= false;

bool timeIsUp = false;

static float timedifference(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec);
}

static void openDoor(){
    hardware_command_door_open(1);
};

 
void d_openTimedDoor(){
    if (h_stopPushed() || obstruction){
        timerStarted = false;
        timeIsUp = false;
        openDoor();
    }
    else{
        openDoor();
        timeIsUp = false;
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
            timeIsUp = true;
        }
    }
}