#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "indicators.h"
#include "hardware.h"
#include <stdbool.h>
#include "heis.h"
#include "bestilling.h"
#include "door.h"

static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}


 
int main(){
    h_initiateHardware();
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
                o_lookForOrders();
                //h_setDestination();
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
                h_goToStopState();

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                o_lookForOrders();
                openTimedDoor();
                h_goToStandPlass(timeIsUp);

                break;
            default :
                break;
        };
    }
    return 0;
}
 