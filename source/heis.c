
#include "main.c"
#include "heis.h"
#include <stdbool.h>
#include "bestilling.h"
#include "hardware.h"


void kjorTilDestinasjon(int currentDestination){
    settNyDestinasjon(currentDestination);
    settRetning(currentDestination,true);
}
void sjekkOmDestinasjonErNaadd(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f) == currentDestination){
            if (!tomBestillingsliste()){
                kjorTilDestinasjon();
            }
            else{
                enterWaitingMode();
            }
        }
    }
}
void settNyDestinasjon(int currentDestination){
    currentDestination = bestillingsListe[0].etasje;
}
void settRetning(int currentDestination,bool retnintOpp){
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
