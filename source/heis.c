
#include "main.c"
#include "heis.h"




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

void undefinedManouver(enum State* state){
     hardware_command_movement(HARDWARE_MOVEMENT_UP);
     *state = StandPlass;
}