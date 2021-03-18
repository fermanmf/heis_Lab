
#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"
#include "door.h"
#include <stdlib.h>
#include "indicators.h"


int g_currentFloor = 0;
bool g_elevatorHasHandeledCurrentOrder = false;
bool g_directionOfElevatorIsUp = true;
bool g_obstructed = false;

static enum State state = UndefinedState;
static bool elevatorIsMoving = true;
static bool isAbove = false;


static void atDestination(int currentDestination){
     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if((hardware_read_floor_sensor(f))&&(f==currentDestination)){
        state = DoorOpen;
        g_elevatorHasHandeledCurrentOrder = true;
        }
    }
}

static void settRetning(int currentDestination){
    
    if (currentDestination < g_currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        elevatorIsMoving = true;
        }
        g_directionOfElevatorIsUp = false;
        
        if (hardware_read_floor_sensor(g_currentFloor)){
        isAbove = false;
        }
    }
    else if (currentDestination > g_currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        elevatorIsMoving = true;
        }
        g_directionOfElevatorIsUp = true;
        
        if (hardware_read_floor_sensor(g_currentFloor)){
        
            isAbove =true;
        }
    }
    else if (isAbove){
        
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        elevatorIsMoving = true;
        g_directionOfElevatorIsUp = false;
       
        
        
    }
    else  {

            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        
        elevatorIsMoving = true;
        g_directionOfElevatorIsUp = true;
        
    }
}



void h_initiateHardware(){
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}

void h_goToDestination(int currentDestination){
    atDestination(currentDestination);
    settRetning(currentDestination);
    
}

void h_goToDefinedState(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            state = AtRest;
            g_currentFloor = f;
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

void h_goToStopStateIfPushed(){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
        stopPushed = true;
    }
    switch(state){
        case AtRest : 
            if(stopPushed){
            state = DoorOpen;}
            break;
        case Moving : 
            if (stopPushed && h_checkIfInbetween()){
                state = StoppBetweenFloors;
            }
            else if (stopPushed){
                state = DoorOpen;
            }
            break;
        default: 
            break;
    }
};

void h_stopElevatorMovement(){
    //returnToCurrentFloor = true;
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

void h_goToAtRestStateIf(bool timeIsUp){
    if (timeIsUp){
        state = AtRest;
        hardware_command_door_open(0);
    }
}

void h_goToMovingStateIf(bool queueIsEmpty){
    if (queueIsEmpty){
        state = Moving;
    }
}

enum State h_getState(){
    return state;
}

void h_updateObstructionVar(){
    if(hardware_read_obstruction_signal()){
        g_obstructed = true;
    }
    else { g_obstructed = false;}
}

void h_handleStopButton(){
    if (hardware_read_stop_signal()){
        o_clearOrders();
        i_resetAllOrderLights();
        hardware_command_stop_light(1);
    }
    else if (!hardware_read_stop_signal()){
        hardware_command_stop_light(0);
    }
}

