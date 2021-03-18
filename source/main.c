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
                i_resetFinishedOrderLight();
                o_lookForOrders();
                i_setOrderLights();
                o_removeFinishedOrders();
                h_goToStopStateIfStopPushed();
                h_goToMovingIfOrderExists(numOrders);

                break;
            case StoppBetweenFloors :

                h_stopElevatorMovement();
                o_lookForOrders();
                h_goToMovingIfOrderExists(numOrders);
                
                break;
            case Moving :

                h_goToDestination(o_returnNextOrder());
                o_lookForOrders();
                i_setOrderLights();
                h_goToStopState();

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                o_lookForOrders();
                i_setorderLights();
                d_openTimedDoor();
                h_goToAtRestIf(timeIsUp);

                break;
            default :
                break;
        };
    }
    return 0;
}
 
