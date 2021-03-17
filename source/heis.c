
#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"
#include "door.h"
#include <stdlib.h>
#include "indicators.h"


int currentFloor = 0;
bool m_orderDone = false;
bool m_currentMomentumDir = 1;
bool obstruction = false;

static enum State state = UndefinedState;
static bool elevatorIsMoving = true;
static bool returnToCurrentFloor = true;
static bool isAbove = false;


static void atDestination(int currentDestination){
     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if((hardware_read_floor_sensor(f))&&(f==currentDestination)){
        state = DoorOpen;
        m_orderDone = true;
        }
    }
}

static void settRetning(int currentDestination){
    
    if (currentDestination < currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        elevatorIsMoving = true;
        }
        m_currentMomentumDir = false;
        
        if (hardware_read_floor_sensor(currentFloor)){
        isAbove = false;
        }
    }
    else if (currentDestination > currentFloor){
        if (!elevatorIsMoving){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        elevatorIsMoving = true;
        }
        m_currentMomentumDir = true;
        
        if (hardware_read_floor_sensor(currentFloor)){
        
            isAbove ==true;
        }
    }
    else if (isAbove){
        
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        elevatorIsMoving = true;
        m_currentMomentumDir = false;
       
        
        
    }
    else  {

            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        
        elevatorIsMoving = true;
        m_currentMomentumDir = true;
        
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
            state = StandPlass;
            currentFloor = f;
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

void h_goToStopState(){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
        stopPushed = true;
    }
    switch(state){
        case StandPlass : 
            if(stopPushed){
            state = DoorOpen;}
            break;
        case Bevegelse : 
            if (stopPushed && h_checkIfInbetween()){
                state = StoppMellomEtasje;
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
    returnToCurrentFloor = true;
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

void h_goToStandPlass(bool timeIsUp){
    if (timeIsUp){
        state = StandPlass;
        hardware_command_door_open(0);
    }
}

void h_goToBevegelse(bool queueIsEmpty){
    if (queueIsEmpty){
        state = Bevegelse;
    }
}

enum State h_getState(){
    return state;
}

void h_updateObstructionVar(){
    if(hardware_read_obstruction_signal()){
        obstruction = true;
    }
    else { obstruction = false;}
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

