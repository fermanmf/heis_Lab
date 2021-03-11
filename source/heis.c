
#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"
#include "door.h"
#include <stdlib.h>

int currentFloor = 0;

static bool elevatorIsMoving = true;
void atDestination(int currentFloor,int currentDestination, enum State* state,bool* m_orderDone){
     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){{
        *state = DoorOpen;
        *m_orderDone = true;
        
    }
}
void settRetning(int currentDestination,bool* retningOpp,int currentFloor){
    if (currentDestination < currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        elevatorIsMoving = true;
        }
        *retningOpp = false;
    }
    else if (currentDestination > currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        elevatorIsMoving = true;
        }
        *retningOpp = true;
    }
}
void h_initiateHardware(){
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}
void h_goToDestination(int currentDestination, int currentFloor, bool*currentMomentumDir, enum State* state,bool* m_orderDone){
    settRetning(currentDestination,currentMomentumDir,currentFloor);
    atDestination(currentFloor,currentDestination,state,m_orderDone);
}


void h_goToDefinedState(enum State* state,int* currentFloor){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            *state = StandPlass;
            *currentFloor = f;
        }
    }
}
bool h_stopPushed(){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
          stopPushed = true;
    }
    return stopPushed;
}
void h_goToStopState(enum State* state){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
          stopPushed = true;
    }
    switch(*state){
        case StandPlass : 
            if(stopPushed){
            *state = DoorOpen;}
            break;
        case Bevegelse : 
            if (stopPushed && h_checkIfInbetween()){
                *state = StoppMellomEtasje;
            }
            else if (stopPushed){
                *state = DoorOpen;
            }
            break;
        default: 
            break;
    }
};

void h_stopElevatorMovement(){
    
    if (elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        elevatorIsMoving = false;
        }
}

bool h_checkIfInbetween(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            return false;
        }
    }
    return true;
}

void h_setDestination(enum State* state){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (hardware_read_order(i, j)) {
                *state = Bevegelse;
            }
        }
    }
}

void h_updateCurrentFloor(int*currentFloor){
   for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            hardware_command_floor_indicator_on(f);
            *currentFloor = f;
        }
    }
}