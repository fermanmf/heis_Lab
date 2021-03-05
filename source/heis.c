
#include "stdbool.h"
#include "stdio.h"
//#include "bestilling.h"
#include "heis.h"
#include "hardware.h"

/*void h_initiateHardware(){
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}*/
void h_goToDestination(int currentDestination, int currentFloor, bool*currentMomentumDir, enum State* state,bool* m_orderDone){
    //Settretning
    h_settRetning(currentDestination,&currentMomentumDir,currentFloor);
    //sjekk om destasjonen er nådd og rapporter til bestillingsmodul + send til neste tilstand.
    atDestination(currentFloor,currentDestination,&state,&m_orderDone);
}
void atDestination(int currentFloor,int currentDestination, enum State* state,bool* m_orderDone){
    if (currentFloor == currentDestination){
        state = StandPlass;
        m_orderDone = true;
    }
}

void settNyDestinasjon(int bestillingsListe []){
    int currentDestination = bestillingsListe[0];
}
void h_settRetning(int currentDestination,bool* retningOpp,int currentFloor){
    if (currentDestination < naavaerendeEtasje){
        hardware_command_movement(HARDWARE_ORDER_DOWN);
        *retningOpp = false;
    }
    else if (currentDestination > naavaerendeEtasje){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        *retningOpp = true;
    }
    return;
    }

bool tomBestillingsListe(int b[]){
    if (b[0]=0){
        return true;
    };
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

bool h_stop(enum State* state){
    bool stopPushed = false;
    if(hardware_read_stop_signal()){
          stopPushed = true;
    }
    switch(*state){
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
        return stopPushed;
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