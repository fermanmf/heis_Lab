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
        h_updateCurrentFloor();
        //h_handleStopButton();
        //o_returnNextOrder(&m_orderDone);
        switch(h_getState()){
            case UndefinedState :

                h_goToDefinedState();

                break;
            case StandPlass :

                h_stopElevatorMovement();
                h_resetOrderLights();
                o_lookForOrders();
                h_setLightOnOrders();
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
                h_setLightOnOrders();
                h_goToStopState();

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                o_lookForOrders();
                h_setLightOnOrders();
                openTimedDoor();
                h_goToStandPlass(timeIsUp);

                break;
            default :
                break;
        };
    }
    return 0;
}
 
