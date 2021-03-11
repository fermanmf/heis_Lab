
#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"
#include "door.h"

void h_initiateHardware(){
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}
void h_goToDestination(int currentDestination, int currentFloor, bool*currentMomentumDir, enum State* state,bool* m_orderDone){
    //Settretning
    h_settRetning(currentDestination,currentMomentumDir,currentFloor);
    //sjekk om destasjonen er nådd og rapporter til bestillingsmodul + send til neste tilstand.
    h_atDestination(currentFloor,currentDestination,state,m_orderDone);
}
static void h_atDestination(int currentFloor,int currentDestination, enum State* state,bool* m_orderDone){
    if (currentFloor == currentDestination){
        *state = DoorOpen;
        *m_orderDone = true;

    }
}
static void h_settRetning(int currentDestination,bool* retningOpp,int currentFloor){
    if (currentDestination < currentFloor){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        *retningOpp = false;
    }
    else if (currentDestination > currentFloor){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        *retningOpp = true;
    }
    return;
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
bool h_bool_stop(){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
          stopPushed = true;
    }
    return stopPushed;
}
void h_stop(enum State* state){
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
        default: 
            break;
    }
};

    


    

void h_stopElevatorMovement(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

bool h_checkIfInbetween(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            return false;
        }
    }
    return true;
}

void setDestination(int* nextDestination,enum State* state){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (hardware_read_order(i, j)) {
                *nextDestination = i;
                *state = Bevegelse;
            }
        }
    }
}
void updateCurrentFloor(int*currentFloor){
   for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            hardware_command_floor_indicator_on(f);
            *currentFloor = f;
        }
    }

}