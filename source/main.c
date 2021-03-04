#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <stdbool.h>
#include "heis.h"
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
int o_returnNextOrder(m_orderDone){
    return 2;
}

 enum State {UndefinedState, StandPlass, StoppMellomEtasje, Bevegelse, DoorOpen};
int main(){
    h_initiateHardware();
    enum State state;
    state = UndefinedState;

    bool m_orderDone = false;

    int currentFloor = 0;
    //int (*m_currentDestination)(bool) = &o_returnNextOrder(m_orderDone);
    int m_currentMomentumDir = 0;
    
    while(1){
        h_handleStopButton();
        o_returnNextOrder(&m_orderDone);
        switch(state){
            case UndefinedState : 
                o_lookForOrders();
                h_goToDefinedState(&state,&currentFloor);
                break;
            case StandPlass :
                h_stopElevatorMovement();
                o_lookForOrders();
                if (h_stop(&state)){
                    state = DoorOpen;
                }

                else if(o_orderFound()){

                    state = Bevegelse;
                }
                break;
            case StoppMellomEtasje :
                h_stopElevatorMovement();
                if (!h_stop(&state)){
                    o_lookForOrders();
                }
                if (o_orderFound()){
                    state = Bevegelse;
                }
                break;
            case Bevegelse :
                h_goToDestination(o_returnNextOrder(false),currentFloor,&m_currentMomentumDir,&state,&m_orderDone);
                o_lookForOrders();
                h_stop(&state);
                break;
            case DoorOpen:
                /*h_stopElevatorMovement();
                if (!h_stop(&state)){
                    o_lookForOrders();
                }

                if (!h_stop(&state) && !obstruksjon()){

                    openTimedDoor();
                    if (doorIsClose()){
                        state = StandPlass;
                    }
                }
                else{
                //openDoor();
                }*/
                break;

            default :

                break;
        };
    }
    return 0;
}
 