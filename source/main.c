#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
//dummy
bool obstruksjon = false;
 
int main(){
    h_initiateHardware();
    timerStarted = false;
    state = UndefinedState;

    bool m_orderDone = true;
    int currentDestination = 0;
    //int (*m_currentDestination)(bool) = &o_returnNextOrder(m_orderDone);
    bool m_currentMomentumDir = 1;
    
    while(1){
        h_updateCurrentFloor(&currentFloor);
        //h_handleStopButton();
        //o_returnNextOrder(&m_orderDone);
        switch(state){
            case UndefinedState : 

                //o_lookForOrders();
                h_goToDefinedState(&state,&currentFloor);

                break;
            case StandPlass :

                h_stopElevatorMovement();
                o_lookForOrders();
                h_setDestination(&currentDestination,&state);
                h_goToStopState(&state);
               /* else if(o_orderFound()){

                    state = Bevegelse;
                }*/

                break;
            case StoppMellomEtasje :

                h_stopElevatorMovement();
                if (!h_stopPushed()){
                    o_lookForOrders();
                }
                //if (o_orderFound()){
                 //   state = Bevegelse;
                //}

                break;
            case Bevegelse :

                h_goToDestination(o_returnNextOrder(&m_orderDone),currentFloor,&m_currentMomentumDir,&state,&m_orderDone);
                o_lookForOrders();
                h_goToStopState(&state);

                break;
            case DoorOpen:

                h_stopElevatorMovement();
                if (!h_stopPushed()){
                    o_lookForOrders();
                }
                if (!h_stopPushed() && !obstruksjon){
                    //openTimedDoor går til neste tilstand når timeren er ferdig.
                    openTimedDoor(&state,&t0,&t1);
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
 