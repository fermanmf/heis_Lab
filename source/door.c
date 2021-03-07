#include <stdbool.h>
#include "door.h"
#include "hardware.h"
#include "heis.h"
#include "bestilling.h"
#include <sys/time.h>


bool timerStarted = false;
void openDoor(){
    hardware_command_door_open(1);
};
float timedifference(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1.0+ (t1.tv_usec - t0.tv_usec) / 1.0;
}
void openTimedDoor(enum State* state){
    struct timeval t0;
    struct timeval t1;
    gettimeofday(&t1,NULL);
    float elapsed = timedifference(t0,t1);
    if(!timerStarted){
        gettimeofday(&t0, NULL);
        timerStarted = true;
    }
   else if (elapsed > 5){
        hardware_command_door_open(0);
        timerStarted = false;
        *state = StandPlass;
    }
}