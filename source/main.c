#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "indicators.h"
#include "hardware.h"
#include <stdbool.h>
#include "heis.h"
#include "bestilling.h"
#include "door.h"

int main(){
    h_initiateHardware();
    numOrders = 0;
    while(1){
        i_updateCurrentFloor();
        h_handleStopButton();
        
        switch(h_getState()){
            case UndefinedState :

                h_goToDefinedState();

                break;
            case StandPlass :

                h_stopElevatorMovement();
                i_resetOrderLights();
                o_lookForOrders();
                i_setLightOnOrders();
                o_checkIfOrderDone();
                h_goToStopState();
                h_goToBevegelse(numOrders);

                break;
            case StoppMellomEtasje :

                h_stopElevatorMovement();
                o_lookForOrders();
                h_goToBevegelse(numOrders);
                
                break;
            case Bevegelse :

                h_goToDestination(o_returnNextOrder());
                o_lookForOrders();
                i_setLightOnOrders();
                h_goToStopState();

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                o_lookForOrders();
                i_setLightOnOrders();
                d_openTimedDoor();
                h_goToStandPlass(timeIsUp);

                break;
            default :
                break;
        };
    }
    return 0;
}
 
