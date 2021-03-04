#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <stdbool.h>
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
 enum State {UndefinedState, StandPlass, StoppMellomEtasje, Bevegelse, DørÅpen};
int main(){
    initiateHardware();
    enum State state;
    state = UndefinedState;
    int currentFloor = 0;
    while(1){
        handleStopButton();
        switch(state){
            case UndefinedState : 
                lookForOrders();
               goToDefinedState(&state,&currentFloor);
                break;
            case StandPlass :
                stopElevatorMovement();
                lookForOrders();
                if (stop()){
                    state = DørÅpen;
                }
                else if(orderFound()){
                    state = Bevegelse;
                }
                break;
            case StoppMellomEtasje :
                if (!stop()){
                    lookForOrders();
                }
                if (orderFound()){
                    state = Bevegelse;
                }
                break;
            case Bevegelse :
                if (stop()){
                    checkIfInBetween();
                }
                lookForOrders();
                if (atDestination()){
                    state = DørÅpen;
                }
                
                break;
            case DørÅpen:
                if (!stop()){
                    lookForOrders();
                }
                if (!stop() && !obstruksjon()){
                    openTimedDoor();
                    if (doorIsClose()){
                        state = StandPlass;
                    }
                }
                else{
                openDoor();
                }
                break;

            default :

                break;
        };
    }
    return 0;
}
 