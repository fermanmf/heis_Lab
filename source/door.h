#pragma once
#include <sys/time.h>
/* Code to clear all lights given the obstruction signal 
            if(hardware_read_obstruction_signal()){
                hardware_command_stop_light(1);
                clear_all_order_lights();
            }
            else{
                hardware_command_stop_light(0);
            }*/ 

struct timeval t0;
struct timeval t1;

bool timerStarted;

void openDoor();

float timedifference(struct timeval t0, struct timeval t1);
void openTimedDoor(enum State* state,struct timeval* t0,struct timeval* t1);