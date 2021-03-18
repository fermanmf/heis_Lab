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

    while(1){

        i_updateCurrentFloor();
        h_updateObstructionVar();
        h_handleStopButton();

        switch(h_getState()){
            case UndefinedState :

                h_goToDefinedState();

                break;
            case AtRest :

                h_stopElevatorMovement();
                i_resetFinishedOrderLights();
                o_lookForOrders();
                i_setOrderLights();
                o_removeFinishedOrders();
                h_goToStopStateIfPushed();
                h_goToMovingStateIf(o_newOrderExists());

                break;
            case StoppBetweenFloors :

                h_stopElevatorMovement();
                o_lookForOrders();
                h_goToMovingStateIf(newOrderExists());
                
                break;
            case Moving :

                h_goToDestination(o_returnNextOrder());
                o_lookForOrders();
                i_setOrderLights();
                h_goToStopStateIfPushed();

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                o_lookForOrders();
                i_setOrderLights();
                d_openTimedDoor();
                h_goToAtRestStateIf(d_timeIsUp());

                break;
            default :
                break;
        };
    }
    return 0;
}
 
