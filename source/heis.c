
#include "main.c"
#include "heis.h"
#include "hardware.h"


void initiateHardware(){
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}
void kjorTilNesteDestinasjon(int* currentDestination){
    settNyDestinasjon(currentDestination);
    settRetning(currentDestination,true,5);
}
void sjekkOmDestinasjonErNaadd(int bestillingsListe[],int currentDestination){
    
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f) == currentDestination){
            if (!tomBestillingsliste(bestillingsListe)){
                kjorTilNesteDestinasjon(f);
            }
            else{
                enterWaitingMode();
            }
        }
    }
}
void settNyDestinasjon(int bestillingsListe []){
    int currentDestination = bestillingsListe[0];
}
void settRetning(int currentDestination,bool retnintOpp,int currentFloor){
    if (currentDestination < naavaerendeEtasje){
        hardware_command_movement(HARDWARE_ORDER_DOWN);
    }
    else if (currentDestination > naavaerendeEtasje){

        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }
    else{
        //error
        return;
    }
    return;
    }

bool tomBestillingsListe(int b[]){
    if (b[0]=0){
        return true;
    };
}

void GoToDefinedState(enum State* state,int* currentFloor){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            state = StandPlass;
            currentFloor = f;
        }
    }
}

bool stop(){
    if(hardware_read_stop_signal()){
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
}
void stopElevatorMovement(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}
